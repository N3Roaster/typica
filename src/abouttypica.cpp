/*287:*/
#line 33 "./abouttypica.w"

#include "abouttypica.h"

/*288:*/
#line 42 "./abouttypica.w"

AboutTypica::AboutTypica():QMainWindow(NULL)
{
QFile aboutFile(":/resources/html/about.html");
aboutFile.open(QIODevice::ReadOnly);
QByteArray content= aboutFile.readAll();
TypicaWebView*banner= new TypicaWebView;
banner->setHtml(content,QUrl("qrc:/resources/html/about.html"));
aboutFile.close();
setCentralWidget(banner);
}

#line 6811 "./typica.w"

/*:288*/
#line 36 "./abouttypica.w"


/*:287*/
