/*602:*/
#line 30 "./daterangeselector.w"


#include <QComboBox> 

#ifndef TypicaDateRangeSelectorHeader
#define TypicaDateRangeSelectorHeader

class CustomDateRangePopup;

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

/*:602*/
