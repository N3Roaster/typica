/*586:*/
#line 383 "./webview.w"

#include "webelement.h"

/*584:*/
#line 326 "./webview.w"

TypicaWebElement::TypicaWebElement(QWebElement element):e(element)
{

}

/*:584*//*585:*/
#line 335 "./webview.w"

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

/*:585*/
#line 386 "./webview.w"


/*:586*/
