@* Web Views in Typica.

\noindent Typica makes extensive use of web views. All printing is currently
handled by generating HTML with the required information, loading it into a web
view, and using the print capabilities provided there. Reports are provided by
running SQL queries, generating HTML, and displaying the results in a web view.
Even the program'@q'@>s about window is primarily a web view.

In order to simplify the implementation of certain features, we subclass
|QWebView| and provide some additional functionality.

@s QWebElement int

@(webview.h@>=
#include <QWebView>
#include <QFile>
#include <QMessageBox>
#include <QDesktopServices>
#include <QPrinter>
#include <QPrintDialog>
#include <QWebFrame>
#include <QWebElement>
#include <QSettings>

#ifndef TypicaWebViewHeader
#define TypicaWebViewHeader

class TypicaWebView : public QWebView@/
{
	@[Q_OBJECT@]@;
	public:@/
		TypicaWebView();
		@[Q_INVOKABLE@,@, void@]@, load(const QString &url);@t\2\2@>@/
		@[Q_INVOKABLE@,@, void@]@, print();@t\2\2@>@/
		@[Q_INVOKABLE@,@, void@]@, setHtml(const QString &html, const QUrl &baseUrl = QUrl());@t\2\2@>@/
		@[Q_INVOKABLE@,@, void@]@, setContent(QIODevice *device);@t\2\2@>@/
		@[Q_INVOKABLE@,@, QString@]@, saveXml();@t\2\2@>@/
		@[Q_INVOKABLE@,@, QWebElement@]@, documentElement();@t\2\2@>@/
		@[Q_INVOKABLE@,@, QWebElement@]@, findFirstElement(const QString &selector);@t\2\2@>@/
	@[signals@]:@/
		void scriptLinkClicked(const QString &link);
	@[private slots@]:@/
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
	QSettings settings;
	device->reset();
	QByteArray content = device->readAll();
	QUrl baseDir = QUrl("file://" + settings.value("config").toString() + "/");
	QWebView::setContent(content, "application/xhtml+xml", baseDir);
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

@* Web View DOM Access.

\noindent Two methods in |TypicaWebView| provide access to the DOM for the
currently displayed page. These are simple wrappers. The |QWebElement| is also

@<TypicaWebView implementation@>=
QWebElement TypicaWebView::documentElement()
{
	return page()->mainFrame()->documentElement();
}

QWebElement TypicaWebView::findFirstElement(const QString &selector)
{
	return page()->mainFrame()->findFirstElement(selector);
}

@ In order to call these methods we need to be able to convert a |QWebElement|
to and from a |QScriptValue|.

@<Function prototypes for scripting@>=
QScriptValue QWebElement_toScriptValue(QScriptEngine *engine, const QWebElement &element);
void QWebElement_fromScriptValue(const QScriptValue &value, QWebElement &element);

@ The implementation simply packs these in a variant.

@<Functions for scripting@>=
QScriptValue QWebElement_toScriptValue(QScriptEngine *engine, const QWebElement &element)
{
	QVariant var;
	var.setValue(element);
	QScriptValue object = engine->newVariant(var);
	return object;
}

void QWebElement_fromScriptValue(const QScriptValue &value, QWebElement &element)
{
	element = value.toVariant().@[value<QWebElement>()@];
}

@ These methods must be registered with the engine.

@<Set up the scripting engine@>=
qScriptRegisterMetaType(engine, QWebElement_toScriptValue, QWebElement_fromScriptValue);

@ As |QWebElement| by itself is not well suited for scripting, we must provide
a way to attach useful properties to the returned object. We do this with a
simple wrapper class.

@(webelement.h@>=
#include <QWebElement>
#include <QObject>

#ifndef TypicaWebElementHeader
#define TypicaWebElementHeader

class TypicaWebElement : public QObject@/
{@/
	@[Q_OBJECT@]@;
	public:@/
		TypicaWebElement(QWebElement element);
		@[Q_INVOKABLE@,@, void@]@, appendInside(const QString &markup);@t\2\2@>@/
		@[Q_INVOKABLE@,@, void@]@, appendOutside(const QString &markup);@t\2\2@>@/
		@[Q_INVOKABLE@,@, void@]@, prependInside(const QString &markup);@t\2\2@>@/
		@[Q_INVOKABLE@,@, void@]@, prependOutside(const QString &markup);@t\2\2@>@/
		@[Q_INVOKABLE@,@, void@]@, removeFromDocument();@t\2\2@>@/
		@[Q_INVOKABLE@,@, void@]@, replace(const QString &markup);@t\2\2@>@/
		@[Q_INVOKABLE@,@, void@]@, setInnerXml(const QString &markup);@t\2\2@>@/
		@[Q_INVOKABLE@,@, void@]@, setOuterXml(const QString &markup);@t\2\2@>@/
		@[Q_INVOKABLE@,@, void@]@, setPlainText(const QString &text);@t\2\2@>@/
	private:@/
		QWebElement e;@/
};

#endif

@ A constructor is required for creating this wrapper for the host environment.

@<Function prototypes for scripting@>=
QScriptValue constructWebElement(QScriptContext *context,
                                 QScriptEngine *engine);

@ The script engine is informed of this function.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructWebElement);
engine->globalObject().setProperty("WebElement", constructor);

@ A specialization of the |argument()| template method is required to
pass the |QWebElement| through to the wrapper constructor.

@<Functions for scripting@>=
template<> QWebElement argument(int arg, QScriptContext *context)
{
	return qscriptvalue_cast<QWebElement>(context->argument(arg));
}

@ Our wrapper constructor takes a single argument which is the |QWebElement| to
wrap.

@<Functions for scripting@>=
QScriptValue constructWebElement(QScriptContext *context,
                                 QScriptEngine *engine)
{
	QWebElement element = argument<QWebElement>(0, context);
	QScriptValue object = engine->newQObject(new TypicaWebElement(element));
	return object;
}

@ The |TypicaWebElement| constructor just keeps a copy of the element passed as
an argument.

@<TypicaWebElement implementation@>=
TypicaWebElement::TypicaWebElement(QWebElement element) : e(element)
{
	/* Nothing needs to be done here. */
}

@ Everything else is a simple wrapper around the equivalent |QWebElement|
method.

@<TypicaWebElement implementation@>=
void TypicaWebElement::appendInside(const QString &markup)
{
	e.appendInside(markup);
}

void TypicaWebElement::appendOutside(const QString &markup)
{
	e.appendOutside(markup);
}

void TypicaWebElement::prependInside(const QString &markup)
{
	e.prependInside(markup);
}

void TypicaWebElement::prependOutside(const QString &markup)
{
	e.prependOutside(markup);
}

void TypicaWebElement::removeFromDocument()
{
	e.removeFromDocument();
}

void TypicaWebElement::replace(const QString &markup)
{
	e.replace(markup);
}

void TypicaWebElement::setInnerXml(const QString &markup)
{
	e.setInnerXml(markup);
}

void TypicaWebElement::setOuterXml(const QString &markup)
{
	e.setOuterXml(markup);
}

void TypicaWebElement::setPlainText(const QString &text)
{
	e.setPlainText(text);
}

@ Implementation is in a separate file.

@(webelement.cpp@>=
#include "webelement.h"

@<TypicaWebElement implementation@>@;

@ Another header is required.

@<Header files to include@>=
#include "webelement.h"

