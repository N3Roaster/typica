/*655:*/
#line 30 "./daterangeselector.w"


#include <QComboBox> 
#include <QPushButton> 
#include <QCalendarWidget> 

#ifndef TypicaDateRangeSelectorHeader
#define TypicaDateRangeSelectorHeader

/*657:*/
#line 91 "./daterangeselector.w"

class CustomDateRangePopup:public QWidget
{
Q_OBJECT
public:
CustomDateRangePopup(QWidget*parent= NULL);
public slots:
void applyRange();
signals:
void hidingPopup();
protected:
virtual void hideEvent(QHideEvent*event);
private slots:
void validateRange();
private:
QCalendarWidget*startDateSelector;
QCalendarWidget*endDateSelector;
QPushButton*applyButton;
};

/*:657*/
#line 39 "./daterangeselector.w"


class DateRangeSelector:public QWidget
{
Q_OBJECT
Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex)
public:
DateRangeSelector(QWidget*parent= NULL);
void setCustomRange(QVariant range);
Q_INVOKABLE QVariant currentRange();
int currentIndex();
public slots:
void setCurrentIndex(int index);
void setLifetimeRange(QString startDate,QString endDate);
void removeIndex(int index);
signals:
void rangeUpdated(QVariant);
private slots:
void toggleCustom();
void popupHidden();
void updateRange(int index);
private:
QComboBox*quickSelector;
CustomDateRangePopup*customRangeSelector;
int lastIndex;
};

#endif

/*:655*/
