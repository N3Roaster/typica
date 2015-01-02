/*650:*/
#line 68 "./daterangeselector.w"

#include <QCalendarWidget> 
#include <QPushButton> 
#include <QBoxLayout> 
#include <QLabel> 
#include <QToolButton> 
#include <QApplication> 
#include <QDesktopWidget> 

#include "daterangeselector.h"

/*652:*/
#line 111 "./daterangeselector.w"

CustomDateRangePopup::CustomDateRangePopup(QWidget*parent):
QWidget(parent,Qt::Popup),startDateSelector(new QCalendarWidget),
endDateSelector(new QCalendarWidget),applyButton(new QPushButton(tr("Apply")))
{
setAttribute(Qt::WA_WindowPropagation);

QVBoxLayout*outerLayout= new QVBoxLayout;
QHBoxLayout*calendarsLayout= new QHBoxLayout;
QVBoxLayout*startDateLayout= new QVBoxLayout;
QVBoxLayout*endDateLayout= new QVBoxLayout;
QHBoxLayout*buttonLayout= new QHBoxLayout;
QLabel*startDateLabel= new QLabel(tr("From"));
QLabel*endDateLabel= new QLabel(tr("To"));
startDateSelector->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
endDateSelector->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
DateRangeSelector*selector= qobject_cast<DateRangeSelector*> (parent);
if(parent){
QStringList range= selector->currentRange().toStringList();
startDateSelector->setSelectedDate(QDate::fromString(range.first(),Qt::ISODate));
endDateSelector->setSelectedDate(QDate::fromString(range.last(),Qt::ISODate));
}
connect(startDateSelector,SIGNAL(selectionChanged()),this,SLOT(validateRange()));
connect(endDateSelector,SIGNAL(selectionChanged()),this,SLOT(validateRange()));

startDateLayout->addWidget(startDateLabel);
startDateLayout->addWidget(startDateSelector);
endDateLayout->addWidget(endDateLabel);
endDateLayout->addWidget(endDateSelector);

connect(applyButton,SIGNAL(clicked()),this,SLOT(applyRange()));

buttonLayout->addStretch();
buttonLayout->addWidget(applyButton);

calendarsLayout->addLayout(startDateLayout);
calendarsLayout->addLayout(endDateLayout);
outerLayout->addLayout(calendarsLayout);
outerLayout->addLayout(buttonLayout);
setLayout(outerLayout);
}

/*:652*//*653:*/
#line 159 "./daterangeselector.w"

void CustomDateRangePopup::hideEvent(QHideEvent*)
{
emit hidingPopup();
}

/*:653*//*654:*/
#line 168 "./daterangeselector.w"

void CustomDateRangePopup::applyRange()
{
DateRangeSelector*selector= qobject_cast<DateRangeSelector*> (parentWidget());
if(selector)
{
selector->setCustomRange(QVariant(QStringList()<<
startDateSelector->selectedDate().toString(Qt::ISODate)<<
endDateSelector->selectedDate().toString(Qt::ISODate)));
}
hide();
}

/*:654*//*655:*/
#line 185 "./daterangeselector.w"

void CustomDateRangePopup::validateRange()
{
if(startDateSelector->selectedDate()> endDateSelector->selectedDate())
{
applyButton->setEnabled(false);
}
else
{
applyButton->setEnabled(true);
}
}

/*:655*/
#line 79 "./daterangeselector.w"

/*656:*/
#line 203 "./daterangeselector.w"

DateRangeSelector::DateRangeSelector(QWidget*parent):
QWidget(parent),quickSelector(new QComboBox(this)),
customRangeSelector(NULL),lastIndex(0)
{
connect(quickSelector,SIGNAL(currentIndexChanged(int)),this,SLOT(updateRange(int)));

QDate currentDate= QDate::currentDate();

QHBoxLayout*layout= new QHBoxLayout;
/*657:*/
#line 232 "./daterangeselector.w"

quickSelector->addItem("Yesterday",QVariant(QStringList()<<
currentDate.addDays(-1).toString(Qt::ISODate)));
quickSelector->addItem("Today",QVariant(QStringList()<<
currentDate.toString(Qt::ISODate)));
quickSelector->insertSeparator(quickSelector->count());
quickSelector->addItem("This Week",QVariant(QStringList()<<
(currentDate.dayOfWeek()%7?
currentDate.addDays(-currentDate.dayOfWeek()).toString(Qt::ISODate):
currentDate.toString(Qt::ISODate))<<
currentDate.addDays(6-(currentDate.dayOfWeek()%7)).toString(Qt::ISODate)));
quickSelector->addItem("This Week to Date",currentDate.dayOfWeek()%7?
QVariant(QStringList()<<
currentDate.addDays(-currentDate.dayOfWeek()).toString(Qt::ISODate)<<
currentDate.toString(Qt::ISODate)):
QVariant(QStringList()<<currentDate.toString(Qt::ISODate)));
quickSelector->addItem("Last Week",QVariant(QStringList()<<
currentDate.addDays(-(currentDate.dayOfWeek()%7)-7).toString(Qt::ISODate)<<
currentDate.addDays(-(currentDate.dayOfWeek()%7)-1).toString(Qt::ISODate)));
quickSelector->addItem("Last 7 Days",QVariant(QStringList()<<
currentDate.addDays(-6).toString(Qt::ISODate)<<
currentDate.toString(Qt::ISODate)));
quickSelector->insertSeparator(quickSelector->count());
quickSelector->addItem("This Month",QVariant(QStringList()<<
QDate(currentDate.year(),currentDate.month(),1).toString(Qt::ISODate)<<
QDate(currentDate.year(),currentDate.month(),
currentDate.daysInMonth()).toString(Qt::ISODate)));
quickSelector->addItem("This Month to Date",(currentDate.day()==1?
(QVariant(QStringList()<<currentDate.toString(Qt::ISODate))):
(QVariant(QStringList()<<
QDate(currentDate.year(),currentDate.month(),1).toString(Qt::ISODate)<<
currentDate.toString(Qt::ISODate)))));
quickSelector->addItem("Last Four Weeks",QVariant(QStringList()<<
currentDate.addDays(-27).toString(Qt::ISODate)<<
currentDate.toString(Qt::ISODate)));
quickSelector->addItem("Last 30 Days",QVariant(QStringList()<<
currentDate.addDays(-29).toString(Qt::ISODate)<<
currentDate.toString(Qt::ISODate)));
quickSelector->insertSeparator(quickSelector->count());
quickSelector->addItem("This Quarter",QVariant(QStringList()<<
QDate(currentDate.year(),currentDate.month()-((currentDate.month()-1)%3),1).toString(Qt::ISODate)<<
(currentDate.month()> 9?
QDate(currentDate.year(),12,31).toString(Qt::ISODate):
QDate(currentDate.year(),currentDate.month()-((currentDate.month()-1)%3)+3,1).addDays(-1).toString(Qt::ISODate))));
quickSelector->addItem("This Quarter to Date",
(currentDate.day()==1&&(currentDate.month()-1)%3==0)?
QVariant(QStringList()<<currentDate.toString(Qt::ISODate)):
QVariant(QStringList()<<
QDate(currentDate.year(),currentDate.month()-((currentDate.month()-1)%3),1).toString(Qt::ISODate)<<
currentDate.toString(Qt::ISODate)));
quickSelector->addItem("Last Quarter",currentDate.month()<4?
QVariant(QStringList()<<
QDate(currentDate.year()-1,10,1).toString(Qt::ISODate)<<
QDate(currentDate.year()-1,12,31).toString(Qt::ISODate)):
QVariant(QStringList()<<
QDate(currentDate.year(),currentDate.month()-((currentDate.month()-1)%3)-3,1).toString(Qt::ISODate)<<
QDate(currentDate.year(),currentDate.month()-((currentDate.month()-1)%3),1).addDays(-1).toString(Qt::ISODate)));
quickSelector->addItem("Last 90 Days",QVariant(QStringList()<<
currentDate.addDays(-89).toString(Qt::ISODate)<<
currentDate.toString(Qt::ISODate)));
quickSelector->insertSeparator(quickSelector->count());
quickSelector->addItem("This Year",QVariant(QStringList()<<
QDate(currentDate.year(),1,1).toString(Qt::ISODate)<<
QDate(currentDate.year(),12,31).toString(Qt::ISODate)));
quickSelector->addItem("This Year to Date",(currentDate.dayOfYear()==1)?
QVariant(QStringList()<<currentDate.toString(Qt::ISODate)):
QVariant(QStringList()<<QDate(currentDate.year(),1,1).toString(Qt::ISODate)<<
currentDate.toString(Qt::ISODate)));
quickSelector->addItem("Last Year",QVariant(QStringList()<<
QDate(currentDate.year()-1,1,1).toString(Qt::ISODate)<<
QDate(currentDate.year()-1,12,31).toString(Qt::ISODate)));
quickSelector->addItem("Last 365 Days",QVariant(QStringList()<<
currentDate.addDays(-364).toString(Qt::ISODate)<<
currentDate.toString(Qt::ISODate)));
quickSelector->insertSeparator(quickSelector->count());
quickSelector->addItem("Lifetime");
quickSelector->addItem("Custom");

/*:657*/
#line 213 "./daterangeselector.w"

QToolButton*customButton= new QToolButton;
customButton->setIcon(QIcon::fromTheme("office-calendar",
QIcon(":/resources/icons/tango/scalable/apps/office-calendar.svg")));
layout->addWidget(quickSelector);
layout->addWidget(customButton);
setLayout(layout);

connect(customButton,SIGNAL(clicked()),this,SLOT(toggleCustom()));
}

/*:656*//*658:*/
#line 315 "./daterangeselector.w"

void DateRangeSelector::updateRange(int index)
{
if(index!=lastIndex&&index==quickSelector->count()-1)
{
toggleCustom();
}
else
{
lastIndex= index;
emit rangeUpdated(quickSelector->itemData(quickSelector->currentIndex()));
}
}

/*:658*//*659:*/
#line 332 "./daterangeselector.w"

void DateRangeSelector::popupHidden()
{
customRangeSelector->deleteLater();
customRangeSelector= NULL;
quickSelector->setCurrentIndex(lastIndex);
}

/*:659*//*660:*/
#line 343 "./daterangeselector.w"

void DateRangeSelector::setCustomRange(QVariant range)
{
quickSelector->setItemData(quickSelector->count()-1,range);
emit rangeUpdated(range);
lastIndex= quickSelector->count()-1;
quickSelector->setCurrentIndex(lastIndex);
}

/*:660*//*661:*/
#line 358 "./daterangeselector.w"

void DateRangeSelector::toggleCustom()
{
if(!customRangeSelector){
customRangeSelector= new CustomDateRangePopup(this);
QPoint pos= rect().bottomLeft();
QPoint pos2= rect().topLeft();
pos= mapToGlobal(pos);
pos2= mapToGlobal(pos2);
QSize size= customRangeSelector->sizeHint();
QRect screen= QApplication::desktop()->availableGeometry(pos);
if(pos.x()+size.width()> screen.right()){
pos.setX(screen.right()-size.width());
}
pos.setX(qMax(pos.x(),screen.left()));
if(pos.y()+size.height()> screen.bottom()){
pos.setY(pos2.y()-size.height());
}else if(pos.y()<screen.top()){
pos.setY(screen.top());
}
if(pos.y()<screen.top()){
pos.setY(screen.top());
}
if(pos.y()+size.height()> screen.bottom()){
pos.setY(screen.bottom()-size.height());
}
customRangeSelector->move(pos);
customRangeSelector->show();
connect(customRangeSelector,SIGNAL(hidingPopup()),
this,SLOT(popupHidden()));
}
else
{
customRangeSelector->close();
customRangeSelector->deleteLater();
customRangeSelector= NULL;
}
}

/*:661*//*662:*/
#line 400 "./daterangeselector.w"

QVariant DateRangeSelector::currentRange()
{
return quickSelector->itemData(lastIndex);
}

/*:662*//*663:*/
#line 408 "./daterangeselector.w"

void DateRangeSelector::setCurrentIndex(int index)
{
quickSelector->setCurrentIndex(index);
}

/*:663*//*664:*/
#line 423 "./daterangeselector.w"

void DateRangeSelector::setLifetimeRange(QString startDate,QString endDate)
{
quickSelector->setItemData(quickSelector->count()-2,
QVariant(QStringList()<<startDate<<endDate));
}

/*:664*//*665:*/
#line 433 "./daterangeselector.w"

void DateRangeSelector::removeIndex(int index)
{
quickSelector->removeItem(index);
}

/*:665*/
#line 80 "./daterangeselector.w"


#include "moc_daterangeselector.cpp"

/*:650*/
