/*499:*/
#line 12 "./webview.w"

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

class TypicaWebView:public QWebView
{
Q_OBJECT
public:
TypicaWebView();
Q_INVOKABLE void load(const QString&url);
Q_INVOKABLE void print();
Q_INVOKABLE void setHtml(const QString&html,const QUrl&baseUrl= QUrl());
Q_INVOKABLE void setContent(QIODevice*device);
Q_INVOKABLE QString saveXml();
Q_INVOKABLE QWebElement documentElement();
Q_INVOKABLE QWebElement findFirstElement(const QString&selector);
signals:
void scriptLinkClicked(const QString&link);
private slots:
void linkDelegate(const QUrl&url);
};

#endif

/*:499*/
