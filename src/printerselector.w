@* Saved Printers.

\noindent In most cases it's best to handle printing in a way that is common
across many applications. Put a Print menu option in a File menu, bring up the
platform's standard print dialog, and allow people to take full advantage of
the flexibility this provides.

In more specialized use cases, however, it may make more sense to provide
faster access to a printer that might not be the default printer for that
computer. The first use in Typica where this makes sense is in printing tags
that can follow the coffee and uniquely identify that batch. Using a full sheet
of paper for this might be excessive and time consuming. Instead, it might make
sense to get a small, inexpensive thermal receipt printer to keep at the
roaster. If this were not the default printer, it would quickly become tedious
to bring up the print dialog and change the selected printer after every batch.

In cases like this, it would be better to provide a combo box in the window
where a printer can be selected and remembered as the default printer just for
that particular use, and allowing people to print directly to that printer
without going through extra steps.

@(printerselector.h@>=
#include <QPrinterInfo>
#include <QComboBox>

#ifndef TypicaPrinterSelectorHeader
#define TypicaPrinterSelectorHeader

class PrinterSelector : public QComboBox@/
{
	@[Q_OBJECT@]@;
	public:
		PrinterSelector();
};

#endif

@ The main file also requires this header.

@<Header files to include@>=
#include "printerselector.h"

@ Implementation of this class is in a separate file.

@(printerselector.cpp@>=
#include "printerselector.h"

@<PrinterSelector implementation@>@;

@ The constructor looks at the list of available printers and populates itself
with these.

@<PrinterSelector implementation@>=
PrinterSelector::PrinterSelector() : QComboBox(NULL)
{
	QList<QPrinterInfo> printers = QPrinterInfo::availablePrinters();
	foreach(QPrinterInfo info, printers)
	{
		addItem(info.printerName());
	}
}

@ The host environment is informed of this class in the usual way starting with
a constructor function prototype.

@<Function prototypes for scripting@>=
QScriptValue constructPrinterSelector(QScriptContext *context,
                                      QScriptEngine *engine);

@ The engine is informed of this function.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructPrinterSelector);
engine->globalObject().setProperty("PrinterSelector", constructor);

@ There is nothing special about the constructor. If there were additional
properties needed beyond those supplied by |setQComboBoxProperties()| it would
make sense to add another function to the chain for setting script value
properties.

@<Functions for scripting@>=
QScriptValue constructPrinterSelector(QScriptContext *, QScriptEngine *engine)
{
	QScriptValue object = engine->newQObject(new PrinterSelector);
	setQComboBoxProperties(object, engine);
	return object;
}
