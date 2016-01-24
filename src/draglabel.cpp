/*1002:*/
#line 33 "./scales.w"

#include "draglabel.h"

#include <QDrag> 
#include <QMouseEvent> 

DragLabel::DragLabel(const QString&labelText,QWidget*parent):
QLabel(labelText,parent)
{
QFont labelFont= font();
labelFont.setPointSize(14);
setFont(labelFont);
}

void DragLabel::mousePressEvent(QMouseEvent*event)
{
if(event->button()==Qt::LeftButton)
{
QDrag*drag= new QDrag(this);
QMimeData*mimeData= new QMimeData;
mimeData->setText(text());
drag->setMimeData(mimeData);
drag->exec();
}
}

/*:1002*/
