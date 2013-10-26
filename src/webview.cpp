/*491:*/
#line 49 "./webview.w"

#include "webview.h"

/*492:*/
#line 56 "./webview.w"

TypicaWebView::TypicaWebView():QWebView()
{
page()->setLinkDelegationPolicy(QWebPage::DelegateExternalLinks);
connect(page(),SIGNAL(linkClicked(QUrl)),this,SLOT(linkDelegate(QUrl)));
}

/*:492*//*493:*/
#line 72 "./webview.w"

void TypicaWebView::linkDelegate(const QUrl&url)
{
if(url.scheme()=="typica")
{
QString address(url.toEncoded());
/*494:*/
#line 90 "./webview.w"

if(address=="typica://aboutqt")
{
QMessageBox::aboutQt(this);
return;
}

/*:494*/
#line 78 "./webview.w"

/*495:*/
#line 99 "./webview.w"

if(address.startsWith("typica://script/"))
{
emit scriptLinkClicked(address.remove(0,16));
return;
}

/*:495*/
#line 79 "./webview.w"

}
else
{
QDesktopServices::openUrl(url);
}
}

/*:493*//*496:*/
#line 111 "./webview.w"

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

/*:496*//*502:*/
#line 202 "./webview.w"

QWebElement TypicaWebView::documentElement()
{
return page()->mainFrame()->documentElement();
}

QWebElement TypicaWebView::findFirstElement(const QString&selector)
{
return page()->mainFrame()->findFirstElement(selector);
}

/*:502*/
#line 52 "./webview.w"


/*:491*/
