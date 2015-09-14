@** A Widget for Selecting Date Ranges.

\noindent Many of the reports in Typica operate over a range of dates. In these
cases it should generally be possible to set that range to any arbitrary start
or end, however there are some ranges that are commonly useful where it may be
convenient to provide easy access to that range. While Qt provides a widget
for selecting a single date, it does not provide a widget that allows two dates
to be conveniently selected. One approach which Typica has previously taken is
to simply use two |QDateEdit| widgets. This works, however validation that the
range is valid must then be performed in every report that uses such an
approach. Another down side to this is that changing either side of the date
range is either going to result in a database query to obtain results in the
new range or another button must be introduced to make setting a new range
explicit. One typically wants to adjust both sides of the range at the same
time and only have one trip to the database for the new data and increasing the
number of controls required for each filter quickly creates a mess.

The solution to this is the introduction of a new composite widget for
selecting date ranges. The main widget consists of two parts. First there is a
|QComboBox| which contains many common date ranges. A |QToolButton| is also
provided for convenient one click access to the Custom range. Whether selected
from the |QComboBox| or the |QToolButton|, selecting Custom creates a new pop
up widget containing two |QCalendarWidget|s and a button to explicitly set the
range. This button will not be available unless the selected ending date is not
before the selected starting date.

As the common use for the selected date is database operations, convenient
access to the ISO 8601 string representation of these dates is provided.

@(daterangeselector.h@>=

#include <QComboBox>
#include <QPushButton>
#include <QCalendarWidget>

#ifndef TypicaDateRangeSelectorHeader
#define TypicaDateRangeSelectorHeader

@<CustomDateRangePopup declaration@>@;

class DateRangeSelector : public QWidget
{
	@[Q_OBJECT@]@;
	Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex)@/
	public:@/
		DateRangeSelector(QWidget *parent = NULL);
		void setCustomRange(QVariant range);
		Q_INVOKABLE QVariant currentRange();
		int currentIndex();@/
	@[public slots@]:@/
		void setCurrentIndex(int index);
		void setLifetimeRange(QString startDate, QString endDate);
		void removeIndex(int index);@/
	@[signals@]:@/
		void rangeUpdated(QVariant);
	@[private slots@]:@/
		void toggleCustom();
		void popupHidden();
		void updateRange(int index);@/
	private:@/
		QComboBox *quickSelector;
		CustomDateRangePopup *customRangeSelector;
		int lastIndex;
};

#endif

@ Implementation details are in a different file.

@(daterangeselector.cpp@>=
#include <QCalendarWidget>
#include <QPushButton>
#include <QBoxLayout>
#include <QLabel>
#include <QToolButton>
#include <QApplication>
#include <QDesktopWidget>

#include "daterangeselector.h"

@<CustomDateRangePopup implementation@>
@<DateRangeSelector implementation@>

#ifdef __linux__
#include "moc_daterangeselector.cpp"
#endif

@ The custom range pop up is represented as a separate class which is not to be
instantiated except by |DateRangeSelector|.

@<CustomDateRangePopup declaration@>=
class CustomDateRangePopup : public QWidget
{
	@[Q_OBJECT@]@;
	public:@/
		CustomDateRangePopup(QWidget *parent = NULL);@/
	@[public slots@]:@/
		void applyRange();@/
	@[signals@]:@/
		void hidingPopup();@/
	protected:@/
		virtual void hideEvent(QHideEvent *event);@/
	@[private slots@]:@/
		void validateRange();@/
	private:@/
		QCalendarWidget *startDateSelector;
		QCalendarWidget *endDateSelector;
		QPushButton *applyButton;
};

@ The pop up constructor is responsible for laying out the component widgets,
setting the dates selected in each calendar to match the currently selected
range, and connecting the appropriate signal handlers.

@<CustomDateRangePopup implementation@>=
CustomDateRangePopup::CustomDateRangePopup(QWidget *parent) :
	QWidget(parent, Qt::Popup), startDateSelector(new QCalendarWidget),
	endDateSelector(new QCalendarWidget), applyButton(new QPushButton(tr("Apply")))
{
	setAttribute(Qt::WA_WindowPropagation);

	QVBoxLayout *outerLayout = new QVBoxLayout;
	QHBoxLayout *calendarsLayout = new QHBoxLayout;
	QVBoxLayout *startDateLayout = new QVBoxLayout;
	QVBoxLayout *endDateLayout = new QVBoxLayout;
	QHBoxLayout *buttonLayout = new QHBoxLayout;
	QLabel *startDateLabel = new QLabel(tr("From"));
	QLabel *endDateLabel = new QLabel(tr("To"));
	startDateSelector->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
	endDateSelector->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
	DateRangeSelector *selector = qobject_cast<DateRangeSelector *>(parent);
	if(parent) {
		QStringList range = selector->currentRange().toStringList();
		startDateSelector->setSelectedDate(QDate::fromString(range.first(), Qt::ISODate));
		endDateSelector->setSelectedDate(QDate::fromString(range.last(), Qt::ISODate));
	}
	connect(startDateSelector, SIGNAL(selectionChanged()), this, SLOT(validateRange()));
	connect(endDateSelector, SIGNAL(selectionChanged()), this, SLOT(validateRange()));

	startDateLayout->addWidget(startDateLabel);
	startDateLayout->addWidget(startDateSelector);
	endDateLayout->addWidget(endDateLabel);
	endDateLayout->addWidget(endDateSelector);

	connect(applyButton, SIGNAL(clicked()), this, SLOT(applyRange()));

	buttonLayout->addStretch();
	buttonLayout->addWidget(applyButton);

	calendarsLayout->addLayout(startDateLayout);
	calendarsLayout->addLayout(endDateLayout);
	outerLayout->addLayout(calendarsLayout);
	outerLayout->addLayout(buttonLayout);
	setLayout(outerLayout);
}

@ The pop up can be hidden in two ways. Clicking anywhere outside of the widget
will hide the pop up. Clicking the Apply button will also hide the pop up. In
the former case, we must inform the parent widget that it is fine to destroy
the pop up widget, which we do by emitting a signal. Note that clicking outside
of the widget will cause the |QHideEvent| to be posted automatically.

@<CustomDateRangePopup implementation@>=
void CustomDateRangePopup::hideEvent(QHideEvent *)
{
	emit hidingPopup();
}

@ Clicking the Apply button requires setting the Custom date range to the
currently selected range and then hiding the pop up manually.

@<CustomDateRangePopup implementation@>=
void CustomDateRangePopup::applyRange()
{
	DateRangeSelector *selector = qobject_cast<DateRangeSelector *>(parentWidget());
	if(selector)
	{
		selector->setCustomRange(QVariant(QStringList() <<
			startDateSelector->selectedDate().toString(Qt::ISODate) <<
			endDateSelector->selectedDate().toString(Qt::ISODate)));
	}
	hide();
}

@ The Apply button is enabled or disabled depending on if the currently
selected dates form a valid range in which the end date does not occur before
the start date.

@<CustomDateRangePopup implementation@>=
void CustomDateRangePopup::validateRange()
{
	if(startDateSelector->selectedDate() > endDateSelector->selectedDate())
	{
		applyButton->setEnabled(false);
	}
	else
	{
		applyButton->setEnabled(true);
	}
}

@ The |DateRangeSelector| constructor is responsible for setting up the layout
of the |QComboBox| and the |QToolButton|, adding appropriate items to the
|QComboBox|, and connecting the signals required to handle the pop up
correctly.

@<DateRangeSelector implementation@>=
DateRangeSelector::DateRangeSelector(QWidget *parent) :
	QWidget(parent), quickSelector(new QComboBox(this)),
	customRangeSelector(NULL), lastIndex(0)
{
	connect(quickSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(updateRange(int)));

	QDate currentDate = QDate::currentDate();

	QHBoxLayout *layout = new QHBoxLayout;
	@<Set common date ranges to quick selector@>@;
	QToolButton *customButton = new QToolButton;
	customButton->setIcon(QIcon::fromTheme("office-calendar",
		QIcon(":/resources/icons/tango/scalable/apps/office-calendar.svg")));
	layout->addWidget(quickSelector);
	layout->addWidget(customButton);
	setLayout(layout);

	connect(customButton, SIGNAL(clicked()), this, SLOT(toggleCustom()));
}

@ The |QComboBox| provides a mechanism for associating additional data with an
item. Several possible representations were considered, but what was ultimately
selected was a |QVariant| containing a |QStringList| in which the first entry
in the list is the starting date of the range and the last entry in the list is
the ending date of the range. Note that the list may contain only one item in
cases where the range only covers a single date, however one should not assume
that a range covering a single date will only have a single list entry.

@<Set common date ranges to quick selector@>=
quickSelector->addItem("Yesterday", QVariant(QStringList() <<
	currentDate.addDays(-1).toString(Qt::ISODate)));
quickSelector->addItem("Today", QVariant(QStringList() <<
	currentDate.toString(Qt::ISODate)));
quickSelector->insertSeparator(quickSelector->count());
quickSelector->addItem("This Week", QVariant(QStringList() <<
	(currentDate.dayOfWeek() % 7 ?
		currentDate.addDays(-currentDate.dayOfWeek()).toString(Qt::ISODate) :
		currentDate.toString(Qt::ISODate)) <<
			currentDate.addDays(6 - (currentDate.dayOfWeek() % 7)).toString(Qt::ISODate)));
quickSelector->addItem("This Week to Date", currentDate.dayOfWeek() % 7 ?
	QVariant(QStringList() <<
	currentDate.addDays(-currentDate.dayOfWeek()).toString(Qt::ISODate) <<
	currentDate.toString(Qt::ISODate)) :
	QVariant(QStringList() << currentDate.toString(Qt::ISODate)));
quickSelector->addItem("Last Week", QVariant(QStringList() <<
	currentDate.addDays(-(currentDate.dayOfWeek() % 7) - 7).toString(Qt::ISODate) <<
	currentDate.addDays(-(currentDate.dayOfWeek() % 7) - 1).toString(Qt::ISODate)));
quickSelector->addItem("Last 7 Days", QVariant(QStringList() <<
	currentDate.addDays(-6).toString(Qt::ISODate) <<
	currentDate.toString(Qt::ISODate)));
quickSelector->insertSeparator(quickSelector->count());
quickSelector->addItem("This Month", QVariant(QStringList() <<
	QDate(currentDate.year(), currentDate.month(), 1).toString(Qt::ISODate) <<
	QDate(currentDate.year(), currentDate.month(),
		currentDate.daysInMonth()).toString(Qt::ISODate)));
quickSelector->addItem("This Month to Date", (currentDate.day() == 1 ?
	(QVariant(QStringList() << currentDate.toString(Qt::ISODate))) :
	(QVariant(QStringList() <<
	QDate(currentDate.year(), currentDate.month(), 1).toString(Qt::ISODate) <<
	currentDate.toString(Qt::ISODate)))));
quickSelector->addItem("Last Four Weeks", QVariant(QStringList() <<
	currentDate.addDays(-27).toString(Qt::ISODate) <<
	currentDate.toString(Qt::ISODate)));
quickSelector->addItem("Last 30 Days", QVariant(QStringList() <<
	currentDate.addDays(-29).toString(Qt::ISODate) <<
	currentDate.toString(Qt::ISODate)));
quickSelector->insertSeparator(quickSelector->count());
quickSelector->addItem("This Quarter", QVariant(QStringList() <<
	QDate(currentDate.year(), currentDate.month() - ((currentDate.month() - 1) % 3), 1).toString(Qt::ISODate) <<
	(currentDate.month() > 9 ?
		QDate(currentDate.year(), 12, 31).toString(Qt::ISODate) :
		QDate(currentDate.year(), currentDate.month() - ((currentDate.month() - 1) % 3) + 3, 1).addDays(-1).toString(Qt::ISODate))));
quickSelector->addItem("This Quarter to Date",
	(currentDate.day() == 1 && (currentDate.month() - 1) % 3 == 0) ?
		QVariant(QStringList() << currentDate.toString(Qt::ISODate)) :
		QVariant(QStringList() <<
		QDate(currentDate.year(), currentDate.month() - ((currentDate.month() - 1) % 3), 1).toString(Qt::ISODate) <<
		currentDate.toString(Qt::ISODate)));
quickSelector->addItem("Last Quarter", currentDate.month() < 4 ?
	QVariant(QStringList() <<
		QDate(currentDate.year() - 1, 10, 1).toString(Qt::ISODate) <<
		QDate(currentDate.year() - 1, 12, 31).toString(Qt::ISODate)) :
	QVariant(QStringList() <<
		QDate(currentDate.year(), currentDate.month() - ((currentDate.month() - 1) % 3) - 3, 1).toString(Qt::ISODate) <<
		QDate(currentDate.year(), currentDate.month() - ((currentDate.month() - 1) % 3), 1).addDays(-1).toString(Qt::ISODate)));
quickSelector->addItem("Last 90 Days", QVariant(QStringList() <<
	currentDate.addDays(-89).toString(Qt::ISODate) <<
	currentDate.toString(Qt::ISODate)));
quickSelector->insertSeparator(quickSelector->count());
quickSelector->addItem("This Year", QVariant(QStringList() <<
	QDate(currentDate.year(), 1, 1).toString(Qt::ISODate) <<
	QDate(currentDate.year(), 12, 31).toString(Qt::ISODate)));
quickSelector->addItem("This Year to Date", (currentDate.dayOfYear() == 1) ?
	QVariant(QStringList() << currentDate.toString(Qt::ISODate)) :
	QVariant(QStringList() << QDate(currentDate.year(), 1, 1).toString(Qt::ISODate) <<
	currentDate.toString(Qt::ISODate)));
quickSelector->addItem("Last Year", QVariant(QStringList() <<
	QDate(currentDate.year() - 1, 1, 1).toString(Qt::ISODate) <<
	QDate(currentDate.year() - 1, 12, 31).toString(Qt::ISODate)));
quickSelector->addItem("Last 365 Days", QVariant(QStringList() <<
	currentDate.addDays(-364).toString(Qt::ISODate) <<
	currentDate.toString(Qt::ISODate)));
quickSelector->insertSeparator(quickSelector->count());
quickSelector->addItem("Lifetime");
quickSelector->addItem("Custom");

@ Special handling of the Custom range is required because it is possible to
select this from the |QComboBox| and then not set a range. This should result
in the selection changing back to the most recent valid selection. Creating the
pop up in this way is handled in |updateRange()|.

@<DateRangeSelector implementation@>=
void DateRangeSelector::updateRange(int index)
{
	if(index != lastIndex && index == quickSelector->count() - 1)
	{
		toggleCustom();
	}
	else
	{
		lastIndex = index;
		emit rangeUpdated(quickSelector->itemData(quickSelector->currentIndex()));
	}
}

@ Resetting the range to the most recent valid selection is handled in
|popupHidden()|.

@<DateRangeSelector implementation@>=
void DateRangeSelector::popupHidden()
{
	customRangeSelector->deleteLater();
	customRangeSelector = NULL;
	quickSelector->setCurrentIndex(lastIndex);
}

@ If Custom is set to a new valid range, |lastIndex| will have been set to
point to the appropriate item by a call to |setCustomRange()|.

@<DateRangeSelector implementation@>=
void DateRangeSelector::setCustomRange(QVariant range)
{
	quickSelector->setItemData(quickSelector->count() - 1, range);
	emit rangeUpdated(range);
	lastIndex = quickSelector->count() - 1;
	quickSelector->setCurrentIndex(lastIndex);
}

@ When creating the pop up, it should ideally be placed such that the left of
the pop up is aligned with the left of the widget that is normally shown and
immediately under it, however if this would result in part of the pop up not
fitting on the same screen, it should be moved to make a best effort at full
visibility.

@<DateRangeSelector implementation@>=
void DateRangeSelector::toggleCustom()
{
	if(!customRangeSelector) {
		customRangeSelector = new CustomDateRangePopup(this);
		QPoint pos = rect().bottomLeft();
		QPoint pos2 = rect().topLeft();
		pos = mapToGlobal(pos);
		pos2 = mapToGlobal(pos2);
		QSize size = customRangeSelector->sizeHint();
		QRect screen = QApplication::desktop()->availableGeometry(pos);
		if(pos.x()+size.width() > screen.right()) {
			pos.setX(screen.right()-size.width());
		}
		pos.setX(qMax(pos.x(), screen.left()));
		if(pos.y() + size.height() > screen.bottom()) {
			pos.setY(pos2.y() - size.height());
		} else if (pos.y() < screen.top()){
			pos.setY(screen.top());
		}
		if(pos.y() < screen.top()) {
			pos.setY(screen.top());
		}
		if(pos.y()+size.height() > screen.bottom()) {
			pos.setY(screen.bottom()-size.height());
		}
		customRangeSelector->move(pos);
		customRangeSelector->show();
		connect(customRangeSelector, SIGNAL(hidingPopup()),
				this, SLOT(popupHidden()));
    }
	else
	{
		customRangeSelector->close();
		customRangeSelector->deleteLater();
		customRangeSelector = NULL;
	}
}

@ While a signal is emitted when the selected range changes, it is frequently
convenient to have a way to request the currently selected range at any time.

@<DateRangeSelector implementation@>=
QVariant DateRangeSelector::currentRange()
{
	return quickSelector->itemData(lastIndex);
}

@ Methods are provided to get and set the current index of the combo box.

@<DateRangeSelector implementation@>=
void DateRangeSelector::setCurrentIndex(int index)
{
	quickSelector->setCurrentIndex(index);
}

int DateRangeSelector::currentIndex()
{
	return quickSelector->currentIndex();
}

@ The Lifetime range is handled somewhat differently from other ranges as there
is no general way to know what that range should be without making unsafe
assumptions. As such, reports are expected to remove the option, provide a
sensible range for it, or handle this selection in a special case. The expected
source of the lifetime date range is the result of a database query so a method
is provided that accepts string representations of the dates. Note that this
method must not be called if the Lifetime option is no longer the second to
last option in the combo box.

@<DateRangeSelector implementation@>=
void DateRangeSelector::setLifetimeRange(QString startDate, QString endDate)
{
	quickSelector->setItemData(quickSelector->count() - 2,
		QVariant(QStringList() << startDate << endDate));
}

@ The |removeIndex()| method is intended for removing the Lifetime option in
cases where this is not supported. Use of this method is strongly discouraged.

@<DateRangeSelector implementation@>=
void DateRangeSelector::removeIndex(int index)
{
	quickSelector->removeItem(index);
}

@ To use this new control in Typica, we should provide a way to create it from
the XML description of a window.

@<Additional box layout elements@>=
else if(currentElement.tagName() == "daterange")
{
	addDateRangeToLayout(currentElement, widgetStack, layoutStack);
}

@ The method for adding a date range selector to a layout is currently trivial.
The |"id"| attribute is supported as usual, as is an |"initial"| attribute for
setting the combo box index.

@<Functions for scripting@>=
void addDateRangeToLayout(QDomElement element, QStack<QWidget *> *,@|
                          QStack<QLayout *> *layoutStack)
{
	DateRangeSelector *widget = new DateRangeSelector;
	if(element.hasAttribute("id"))
	{
		widget->setObjectName(element.attribute("id"));
	}
	if(element.hasAttribute("initial"))
	{
		widget->setCurrentIndex(element.attribute("initial").toInt());
	}
	QBoxLayout *layout = qobject_cast<QBoxLayout *>(layoutStack->top());
	layout->addWidget(widget);
}

@ The prototype needs to be specified.

@<Function prototypes for scripting@>=
void addDateRangeToLayout(QDomElement element,
                          QStack<QWidget *> *widgetStack,
                          QStack<QLayout *> *layoutStack);

@ Our header is also required.

@<Header files to include@>=
#include "daterangeselector.h"
