@** A Window for Displaying Information About Typica.

\noindent The About window for an application typically displays a few pieces
of information: The application logo, name, and version number, copyright and
license information, and other assorted information. In Typica this also
includes a list of the people and companies that have provided financial
assistance toward the ongoing development of the software and information that
others can use to help in this way.

This class previously provided some additional functionality which is no
longer required because it is handled by the |TypicaWebView| class introduced
in version 1.6.

@(abouttypica.h@>=
#include <QMainWindow>
#include <QFile>
#include "webview.h"

#ifndef AboutTypicaHeader
#define AboutTypicaHeader

class AboutTypica : public QMainWindow
{
	Q_OBJECT
	public:
		AboutTypica();
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
	TypicaWebView *banner = new TypicaWebView;
 	banner->setHtml(content, QUrl("qrc:/resources/html/about.html"));
	aboutFile.close();
	setCentralWidget(banner);
}

