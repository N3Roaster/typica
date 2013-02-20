/*227:*/
#line 12 "./abouttypica.w"

#include <QMainWindow> 
#include <QWebView> 
#include <QFile> 
#include <QtDebug> 
#include <QMessageBox> 
#include <QDesktopServices> 

#ifndef AboutTypicaHeader
#define AboutTypicaHeader

class AboutTypica:public QMainWindow
{
Q_OBJECT
public:
AboutTypica();
public slots:
void linkClicked(const QUrl&url);
};

#endif

/*:227*/
