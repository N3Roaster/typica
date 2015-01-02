/*971:*/
#line 13 "./scales.w"

#ifndef TypicaDragLabelInclude
#define TypicaDragLabelInclude

#include <QLabel> 

class DragLabel:public QLabel
{
Q_OBJECT
public:
explicit DragLabel(const QString&labelText,QWidget*parent= NULL);
protected:
void mousePressEvent(QMouseEvent*event);
};

#endif

/*:971*/
