/*590:*/
#line 45 "./printerselector.w"

#include "printerselector.h"

/*591:*/
#line 53 "./printerselector.w"

PrinterSelector::PrinterSelector():QComboBox(NULL)
{
QList<QPrinterInfo> printers= QPrinterInfo::availablePrinters();
foreach(QPrinterInfo info,printers)
{
addItem(info.printerName());
}
}

/*:591*/
#line 48 "./printerselector.w"


/*:590*/
