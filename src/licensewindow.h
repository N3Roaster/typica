/*212:*/
#line 13 "./licensewindow.w"

#include <QMainWindow> 
#include <QListWidgetItem> 
#include <QWebView> 

#ifndef TypicaLicenseHeader
#define TypicaLicenseHeader

class LicenseWindow:public QMainWindow
{
Q_OBJECT
public:
LicenseWindow();
private slots:
void setWebView(QListWidgetItem*current,QListWidgetItem*);
private:
QWebView*view;
};

#endif

/*:212*/
