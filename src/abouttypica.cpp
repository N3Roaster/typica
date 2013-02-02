/*224:*/
#line 31 "./abouttypica.w"

#include "abouttypica.h"

/*225:*/
#line 40 "./abouttypica.w"

AboutTypica::AboutTypica():QMainWindow(NULL)
{
QFile aboutFile(":/resources/html/about.html");
aboutFile.open(QIODevice::ReadOnly);
QByteArray content= aboutFile.readAll();
QWebView*banner= new QWebView;
banner->setHtml(content,QUrl("qrc:/resources/html/about.html"));
aboutFile.close();
setCentralWidget(banner);
}

#line 5656 "./typica.w"

/*:225*/
#line 34 "./abouttypica.w"


/*:224*/
