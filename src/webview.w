@* Web Views in Typica.

\noindent Typica makes extensive use of web views. All printing is currently
handled by generating HTML with the required information, loading it into a web
view, and using the print capabilities provided there. Reports are provided by
running SQL queries, generating HTML, and displaying the results in a web view.
Even the program'@q'@>s about window is primarily a web view.

In order to simplify the implementation of certain features, we subclass
|QWebView| and provide some additional functionality.

@(webview.h@>=
#include <QWebView>
#include <QFile>
#include <QMessageBox>
#include <QDesktopServices>
#include <QPrinter>
#include <QPrintDialog>
#include <QWebFrame>
#include <QWebElement>

#ifndef TypicaWebViewHeader
#define TypicaWebViewHeader

class TypicaWebView : public QWebView
{
	Q_OBJECT
	public:
		TypicaWebView();
		Q_INVOKABLE void load(const QString &url);
		Q_INVOKABLE void print();
		Q_INVOKABLE void setHtml(const QString &html, const QUrl &baseUrl = QUrl());
		Q_INVOKABLE void setContent(QIODevice *device);
		Q_INVOKABLE QString saveXml();
	signals:
		void scriptLinkClicked(const QString &link);
	private slots:
		void linkDelegate(const QUrl &url);
};

#endif

@ The implementation is in a separate file.

@(webview.cpp@>=
#include "webview.h"

@<TypicaWebView implementation@>@;

@ In the constructor we set up our link delegation policy.

@<TypicaWebView implementation@>=
TypicaWebView::TypicaWebView() : QWebView()
{
	page()->setLinkDelegationPolicy(QWebPage::DelegateExternalLinks);
	connect(page(), SIGNAL(linkClicked(QUrl)), this, SLOT(linkDelegate(QUrl)));
}

@ When a link is clicked, one of three things may happen. Certain reserved URLs
will trigger an immediate event which is just handled internally without
providing any kind of external notification. URLs that start with
|"typica://script/"| will produce a signal containing the rest of the URL. This
is intended for script code to intercept, interpret, and update the web view
with the requested information. Everything else is passed to |QDesktopServices|
which will defer to system-wide preferences for how to handle different link
and file types.

@<TypicaWebView implementation@>=
void TypicaWebView::linkDelegate(const QUrl &url)
{
	if(url.scheme() == "typica")
	{
		QString address(url.toEncoded());
		@<Detect and handle special links@>@;
		@<Detect and handle script links@>@;
	}
	else
	{
		QDesktopServices::openUrl(url);
	}
}

@ Currently the only special link is |"typica://aboutqt"| which brings up
information about the Qt framework. This is used in the About Typica window.

@<Detect and handle special links@>=
if(address == "typica://aboutqt")
{
	QMessageBox::aboutQt(this);
	return;
}

@ Script links split the link data to simplify interpretation in script code.

@<Detect and handle script links@>=
if(address.startsWith("typica://script/"))
{
	emit scriptLinkClicked(address.remove(0, 16));
	return;
}

@ There is a limited set of functions that should be available to the host
environment which are not declared as slots or otherwise have some missing
functionality in the base class. In some cases the new functions can be
distinguished by signature.

@<TypicaWebView implementation@>=
void TypicaWebView::load(const QString &url)
{
	QWebView::load(QUrl(url));
}

void TypicaWebView::print()
{
	QPrinter *printer = new QPrinter(QPrinter::HighResolution);
	QPrintDialog printDialog(printer, NULL);
	if(printDialog.exec() == QDialog::Accepted)
	{
		QWebView::print(printer);
	}
}

void TypicaWebView::setHtml(const QString &html, const QUrl &baseUrl)
{
	QWebView::setHtml(html, baseUrl);
}

void TypicaWebView::setContent(QIODevice *device)
{
	device->reset();
	QByteArray content = device->readAll();
	QWebView::setContent(content, "application/xhtml+xml");
}

QString TypicaWebView::saveXml()
{
	return page()->currentFrame()->documentElement().toOuterXml();
}

@ Web views are exposed to the host environment in the usual manner.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructWebView);
value = engine->newQMetaObject(&TypicaWebView::staticMetaObject, constructor);
engine->globalObject().setProperty("WebView", value);

@ Now that |QWebView| is subclassed, all of the features that we need should
be available through the meta-object system automatically.

@<Functions for scripting@>=
QScriptValue constructWebView(QScriptContext *, QScriptEngine *engine)
{
	QScriptValue object = engine->newQObject(new TypicaWebView);
	setQWebViewProperties(object, engine);
	return object;
}

void setQWebViewProperties(QScriptValue value, QScriptEngine *engine)
{
	setQWidgetProperties(value, engine);
}

@ It is also possible to create these web views from the XML portion of the
configuration document. A function is provided to add a new view to a box
layout.

@<Functions for scripting@>=
void addWebViewToLayout(QDomElement element, QStack<QWidget *> *,
                        QStack<QLayout *> *layoutStack)
{
	TypicaWebView *view = new TypicaWebView;
	if(element.hasAttribute("id"))
	{
		view->setObjectName(element.attribute("id"));
	}
	QBoxLayout *layout = qobject_cast<QBoxLayout *>(layoutStack->top());
	layout->addWidget(view);
}

@ Prototypes must be provided for these functions.

@<Function prototypes for scripting@>=
QScriptValue constructWebView(QScriptContext *context, QScriptEngine *engine);
void setQWebViewProperties(QScriptValue value, QScriptEngine *engine);
void addWebViewToLayout(QDomElement element, QStack<QWidget *> *widgetStack,
                        QStack<QLayout *> *layoutStack);

@ Finally, we must include our new header in |"typica.cpp"|.

@<Header files to include@>=
#include "webview.h"

