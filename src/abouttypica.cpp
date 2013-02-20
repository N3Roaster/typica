/*228:*/
#line 36 "./abouttypica.w"

#include "abouttypica.h"

/*229:*/
#line 45 "./abouttypica.w"

AboutTypica::AboutTypica():QMainWindow(NULL)
{
QFile aboutFile(":/resources/html/about.html");
aboutFile.open(QIODevice::ReadOnly);
QByteArray content= aboutFile.readAll();
QWebView*banner= new QWebView;
banner->setHtml(content,QUrl("qrc:/resources/html/about.html"));
aboutFile.close();
setCentralWidget(banner);
QWebPage*page= banner->page();
page->setLinkDelegationPolicy(QWebPage::DelegateExternalLinks);
connect(page,SIGNAL(linkClicked(QUrl)),this,SLOT(linkClicked(QUrl)));
}

/*:229*//*230:*/
#line 63 "./abouttypica.w"

void AboutTypica::linkClicked(const QUrl&url)
{
if(url.scheme()=="typica")
{
QString address(url.toEncoded());
if(address=="typica://aboutqt")
{
QMessageBox::aboutQt(this);
}
else
{
qDebug()<<"Unexpected link. Got: "<<address;
}
}
else
{
QDesktopServices::openUrl(url);
}
}
#line 5697 "./typica.w"

/*:230*/
#line 39 "./abouttypica.w"


/*:228*/
