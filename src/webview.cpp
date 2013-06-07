/*500:*/
#line 47 "./webview.w"

#include "webview.h"

/*501:*/
#line 54 "./webview.w"

TypicaWebView::TypicaWebView():QWebView()
{
page()->setLinkDelegationPolicy(QWebPage::DelegateExternalLinks);
connect(page(),SIGNAL(linkClicked(QUrl)),this,SLOT(linkDelegate(QUrl)));
}

/*:501*//*502:*/
#line 70 "./webview.w"

void TypicaWebView::linkDelegate(const QUrl&url)
{
if(url.scheme()=="typica")
{
QString address(url.toEncoded());
/*503:*/
#line 88 "./webview.w"

if(address=="typica://aboutqt")
{
QMessageBox::aboutQt(this);
return;
}

/*:503*/
#line 76 "./webview.w"

/*504:*/
#line 97 "./webview.w"

if(address.startsWith("typica://script/"))
{
emit scriptLinkClicked(address.remove(0,16));
return;
}

/*:504*/
#line 77 "./webview.w"

}
else
{
QDesktopServices::openUrl(url);
}
}

/*:502*//*505:*/
#line 109 "./webview.w"

void TypicaWebView::load(const QString&url)
{
QWebView::load(QUrl(url));
}

void TypicaWebView::print()
{
QPrinter*printer= new QPrinter(QPrinter::HighResolution);
QPrintDialog printDialog(printer,NULL);
if(printDialog.exec()==QDialog::Accepted)
{
QWebView::print(printer);
}
}

void TypicaWebView::setHtml(const QString&html,const QUrl&baseUrl)
{
QWebView::setHtml(html,baseUrl);
}

void TypicaWebView::setContent(QIODevice*device)
{
device->reset();
QByteArray content= device->readAll();
QWebView::setContent(content,"application/xhtml+xml");
}

QString TypicaWebView::saveXml()
{
return page()->currentFrame()->documentElement().toOuterXml();
}

/*:505*//*511:*/
#line 200 "./webview.w"

QWebElement TypicaWebView::documentElement()
{
return page()->mainFrame()->documentElement();
}

QWebElement TypicaWebView::findFirstElement(const QString&selector)
{
return page()->mainFrame()->findFirstElement(selector);
}

/*:511*/
#line 50 "./webview.w"


/*:500*/
