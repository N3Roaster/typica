/*506:*/
#line 245 "./webview.w"

#include <QWebElement> 
#include <QObject> 

#ifndef TypicaWebElementHeader
#define TypicaWebElementHeader

class TypicaWebElement:public QObject
{
Q_OBJECT
public:
TypicaWebElement(QWebElement element);
Q_INVOKABLE void appendInside(const QString&markup);
Q_INVOKABLE void appendOutside(const QString&markup);
Q_INVOKABLE void prependInside(const QString&markup);
Q_INVOKABLE void prependOutside(const QString&markup);
Q_INVOKABLE void removeFromDocument();
Q_INVOKABLE void replace(const QString&markup);
Q_INVOKABLE void setInnerXml(const QString&markup);
Q_INVOKABLE void setOuterXml(const QString&markup);
Q_INVOKABLE void setPlainText(const QString&text);
private:
QWebElement e;
};

#endif

/*:506*/
