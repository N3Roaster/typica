/*563:*/
#line 50 "./webview.w"

#include "webview.h"

/*564:*/
#line 57 "./webview.w"

TypicaWebView::TypicaWebView():QWebView()
{
page()->setLinkDelegationPolicy(QWebPage::DelegateExternalLinks);
connect(page(),SIGNAL(linkClicked(QUrl)),this,SLOT(linkDelegate(QUrl)));
}

/*:564*//*565:*/
#line 73 "./webview.w"

void TypicaWebView::linkDelegate(const QUrl&url)
{
if(url.scheme()=="typica")
{
QString address(url.toEncoded());
/*566:*/
#line 91 "./webview.w"

if(address=="typica://aboutqt")
{
QMessageBox::aboutQt(this);
return;
}

/*:566*/
#line 79 "./webview.w"

/*567:*/
#line 100 "./webview.w"

if(address.startsWith("typica://script/"))
{
emit scriptLinkClicked(address.remove(0,16));
return;
}

/*:567*/
#line 80 "./webview.w"

}
else
{
QDesktopServices::openUrl(url);
}
}

/*:565*//*568:*/
#line 112 "./webview.w"

void TypicaWebView::load(const QString&url)
{
QWebView::load(QUrl(url));
}

void TypicaWebView::setHtml(const QString&html,const QUrl&baseUrl)
{
QWebView::setHtml(html,baseUrl);
}

void TypicaWebView::setContent(QIODevice*device)
{
QSettings settings;
device->reset();
QByteArray content= device->readAll();
QUrl baseDir= QUrl("file://"+settings.value("config").toString()+"/");
QWebView::setContent(content,"application/xhtml+xml",baseDir);
}

QString TypicaWebView::saveXml()
{
return page()->currentFrame()->documentElement().toOuterXml();
}

/*:568*//*569:*/
#line 144 "./webview.w"

void TypicaWebView::print(const QString&printerName)
{
QPrinter*printer= new QPrinter(QPrinter::HighResolution);
if(!printerName.isEmpty())
{
printer->setPrinterName(printerName);
printer->setFullPage(true);
QWebView::print(printer);
return;
}
QPrintDialog printDialog(printer,NULL);
if(printDialog.exec()==QDialog::Accepted)
{
QWebView::print(printer);
}
}

/*:569*//*575:*/
#line 220 "./webview.w"

QWebElement TypicaWebView::documentElement()
{
return page()->mainFrame()->documentElement();
}

QWebElement TypicaWebView::findFirstElement(const QString&selector)
{
return page()->mainFrame()->findFirstElement(selector);
}

/*:575*/
#line 53 "./webview.w"


/*:563*/
