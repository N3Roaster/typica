/*563:*/
#line 368 "./webview.w"

#include "webelement.h"

/*561:*/
#line 311 "./webview.w"

TypicaWebElement::TypicaWebElement(QWebElement element):e(element)
{

}

/*:561*//*562:*/
#line 320 "./webview.w"

void TypicaWebElement::appendInside(const QString&markup)
{
e.appendInside(markup);
}

void TypicaWebElement::appendOutside(const QString&markup)
{
e.appendOutside(markup);
}

void TypicaWebElement::prependInside(const QString&markup)
{
e.prependInside(markup);
}

void TypicaWebElement::prependOutside(const QString&markup)
{
e.prependOutside(markup);
}

void TypicaWebElement::removeFromDocument()
{
e.removeFromDocument();
}

void TypicaWebElement::replace(const QString&markup)
{
e.replace(markup);
}

void TypicaWebElement::setInnerXml(const QString&markup)
{
e.setInnerXml(markup);
}

void TypicaWebElement::setOuterXml(const QString&markup)
{
e.setOuterXml(markup);
}

void TypicaWebElement::setPlainText(const QString&text)
{
e.setPlainText(text);
}

/*:562*/
#line 371 "./webview.w"


/*:563*/
