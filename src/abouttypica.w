@** A Window for Displaying Information About Typica.

\noindent The About window for an application typically displays a few pieces
of information: The application logo, name, and version number, copyright and
license information, and other assorted information. In Typica this also
includes a list of the people and companies that have provided financial
assistance toward the ongoing development of the software and information that
others can use to help in this way. Some of this information would benefit
from existing as a link which can open an external application such as a web
browser or email client.

@(abouttypica.h@>=
#include <QMainWindow>
#include <QWebView>
#include <QFile>
#include <QtDebug>
#include <QMessageBox>
#include <QDesktopServices>

#ifndef AboutTypicaHeader
#define AboutTypicaHeader

class AboutTypica : public QMainWindow
{
	Q_OBJECT
	public:
		AboutTypica();
	public slots:
		void linkClicked(const QUrl &url);
};

#endif

@ The implementation is in a separate file.

@(abouttypica.cpp@>=
#include "abouttypica.h"

@<AboutTypica implementation@>@;

@ The information provided here comes from a set of HTML documents stored as
compiled resources and presented in a set of |QWebView| instances accessible
through a set of tabs.

@<AboutTypica implementation@>=
AboutTypica::AboutTypica() : QMainWindow(NULL)
{
	QFile aboutFile(":/resources/html/about.html");
	aboutFile.open(QIODevice::ReadOnly);
	QByteArray content = aboutFile.readAll();
	QWebView *banner = new QWebView;
 	banner->setHtml(content, QUrl("qrc:/resources/html/about.html"));
	aboutFile.close();
	setCentralWidget(banner);
	QWebPage *page = banner->page();
	page->setLinkDelegationPolicy(QWebPage::DelegateExternalLinks);
	connect(page, SIGNAL(linkClicked(QUrl)), this, SLOT(linkClicked(QUrl)));
}

@ In order to display the About Qt window, we detect a special URL from a link
clicked in the about box.

@<AboutTypica implementation@>=
void AboutTypica::linkClicked(const QUrl &url)
{
	if(url.scheme() == "typica")
	{
		QString address(url.toEncoded());
		if(address == "typica://aboutqt")
		{
			QMessageBox::aboutQt(this);
		}
		else
		{
			qDebug() << "Unexpected link. Got: " << address;
		}
	}
	else
	{
		QDesktopServices::openUrl(url);
	}
}