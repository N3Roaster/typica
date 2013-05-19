@** Collecting Measurements from Scales.

\noindent When a computer connected scale is available, it can be useful to
eliminate manual transcription from the data entry for batches. In general it
is difficult to determine where a measurement should go automatically, but
there are a number of situations where the ability to drag a measurement from a
label and drop it to whatever input widget is appropriate would be a useful
operation to support.

To support this, we need to subclass |QLabel| to allow it to initiate a drag
and drop operation.

@(draglabel.h@>=
#ifndef TypicaDragLabelInclude
#define TypicaDragLabelInclude

#include <QLabel>

class DragLabel : public QLabel
{
	Q_OBJECT
	public:
		explicit DragLabel(const QString &labelText, QWidget *parent = NULL);
	protected:
		void mousePressEvent(QMouseEvent *event);
};

#endif

@ The font size of the label is increased by default to make it easier to
manipulate on a touch screen. Otherwise, there is little to do in this class.

@(draglabel.cpp@>=
#include "draglabel.h"

#include <QDrag>
#include <QMouseEvent>

DragLabel::DragLabel(const QString &labelText, QWidget *parent) :
	QLabel(labelText, parent)
{
	QFont labelFont = font();
	labelFont.setPointSize(14);
	setFont(labelFont);
}

void DragLabel::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		QDrag *drag = new QDrag(this);
		QMimeData *mimeData = new QMimeData;
		mimeData->setText(text());
		drag->setMimeData(mimeData);
		drag->exec();
	}
}

