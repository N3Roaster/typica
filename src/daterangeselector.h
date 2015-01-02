/*649:*/
#line 30 "./daterangeselector.w"


#include <QComboBox> 
#include <QPushButton> 
#include <QCalendarWidget> 

#ifndef TypicaDateRangeSelectorHeader
#define TypicaDateRangeSelectorHeader

/*651:*/
#line 87 "./daterangeselector.w"

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

/*:651*/
#line 39 "./daterangeselector.w"


class DateRangeSelector:public QWidget
{
Q_OBJECT
public:
DateRangeSelector(QWidget*parent= NULL);
void setCustomRange(QVariant range);
Q_INVOKABLE QVariant currentRange();
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

/*:649*/
