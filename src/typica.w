% Instructions for generating source code and documentation
% Step 1. Convert metapost diagrams into PDF documents
% $ mptopdf pipes.mp ; epstopdf pipes.ps
% $ mptopdf roast.mp ; epstopdf roast.ps
% $ mptopdf search.mp ; epstopdf search.ps
% Step 2. Weave and typeset
% $ cweave typica
% $ pdftex typica
% Step 3. Tangle and moc
% $ ctangle typica ; mv typica.c typica.cpp
% $ moc typica.cpp > moc_typica.cpp
%
% If you have trouble compiling, check to make sure the required headers are in
% your header search path and check to make sure the required libraries are
% linked. If using qmake to generate a project file, remember to add the
% following lines to your .pro file:
% QT += xml
% QT += script

% Document style instructions
\input graphicx.tex
\mark{\noexpand\nullsec0{A Note on Notation}}
\def\pn{Typica}
\def\filebase{typica}
\def\version{1.6 \number\year-\number\month-\number\day}
\def\years{2007--2013}
\def\title{\pn{} (Version \version)}
\newskip\dangerskipb
\newskip\dangerskip
\dangerskip=20pt
\dangerskipb=42pt
\def\hang{\hangindent\dangerskip}
\def\hangb{\hangindent\dangerskipb}

\font\manual=manfnt at 12pt
\def\danbend{{\manual\char127}}
\def\datanger{\medbreak\begingroup\clubpenalty=10000
	\def\par{\endgraf\endgroup\medbreak} \noindent\hang\hangafter=-2
	\hbox to0pt{\hskip-3.5pc\danbend\hfill}}
\outer\def\danger{\datanger}%
%
\def\datangerb{\medbreak\begingroup\clubpenalty=10000
	\def\par{\endgraf\endgroup\medbreak} \noindent\hang\hangafter=-2
	\hbox to0pt{\hskip-3.5pc\danbend\hfill}}
\outer\def\dangerb{\datangerb}

\def\endanger{\medskip}

\def\nullsec{\S1}
\def\lheader{\mainfont\the\pageno\kern1pc(\topsecno)\eightrm
	\qquad\grouptitle\hfill\title}
\def\rheader{\eightrm\title\hfill\grouptitle\qquad\mainfont
	(\topsecno)\kern1pc\the\pageno}
\def\botofcontents{\vfill
	\noindent Copyright \copyright\ \years~Neal Evan Wilson
	\bigskip\noindent Permission is hereby granted, free of charge, to any
	person obtaining a copy of this software and associated documentation files
	(the ``Software''), to deal in the Software without restriction, including
	without limitation the rights to use, copy, modify, merge, publish,
	distribute, sublicense, and/or sell copies of the Software, and to permit
	persons to whom the Software is furnished to do so, subject to the following
	conditions:\medskip

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.\medskip

	THE SOFTWARE IS PROVIDED ``AS IS'', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
	IN THE SOFTWARE.

	\bigskip\noindent Parts of \pn{} are from QextSerialPort which is used under the
	MIT license as follows:

	\bigskip\noindent Copyright \copyright\ 2000--2003 Wayne Roth

    \noindent Copyright \copyright\ 2004--2007 Stefan Sander

	\noindent Copyright \copyright\ 2007 Michal Policht

	\noindent Copyright \copyright\ 2008 Brandon Fosdick

	\noindent Copyright \copyright\ 2009--2010 Liam Staskawicz

	\noindent Copyright \copyright\ 2011 Debao Zhang

    \bigskip\noindent Web: http://code.google.com/p/qextserialport/

    \bigskip\noindent Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the
    ``Software''), to deal in the Software without restriction, including
    without limitation the rights to use, copy, modify, merge, publish,
    distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so, subject to
    the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED ``AS IS'', WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
}

\let\K=\leftarrow
\def\CPLUSPLUS/{{%
	\mc C{\hbox{\kern.5pt\raise1pt\hbox{\sevenrm+\kern-1pt+}\kern.5pt}}
	\spacefactor1000}}
\def\PP{\uparrow}
\def\MM{\downarrow}
\newbox\DCBox
\setbox\DCBox=\hbox{$\in$}
\def\DC{\copy\DCBox}
\newbox\MODbox \setbox\MODbox=\hbox{\eightrm MOD}
\def\MOD{\mathbin{\copy\MODbox}}

% Title page
\font\authorfont=cmr12
\null\vfill
\centerline{\titlefont \pn}
\vskip 18pt\centerline{(Version \version)}
\vskip 24pt\centerline{\authorfont Neal Evan Wilson}
\vfill
\titletrue\eject\hbox to 0pt{}
\pageno=0 \titletrue\eject

\secpagedepth=1

% Convenience macros
\def\newline{\vskip\baselineskip}
\def\cweb{\.{CWEB}}
\def\web{\.{WEB}}
\newcount\footnotenumber
\def\nfnote{\global\advance\footnotenumber by 1
	\footnote{$^{\the\footnotenumber}$}}

% Listing macro from The TeXBook. See page 381 for an explaination.
\def\uncatcodespecials{\def\do##1{\catcode`##1=12 }\dospecials}
\newcount\lineno
\def\setupverbatim{\tt \lineno=0
	\def\par{\leavevmode\endgraf} \catcode`\`=\active
	\obeylines \uncatcodespecials \obeyspaces
	\everypar{\advance\lineno by1 \llap{\sevenrm\the\lineno\ \ }}}
{\obeyspaces\global\let =\ }
\def\listing#1{\par\begingroup\setupverbatim\input#1 \endgroup}

% Javascript chunk handling
\def\jsfile#1#2{\Y\B\4\X\secno:\.{#1}\X${}\E{}\6$\par
\listing{#2}}

% Type formatting
@s QTime int
@s QMetaType int
@s DAQ int
@s Channel int
@s QString int
@s QObject int
@s QThread int
@s DAQImplementation int
@s QVector int
@s TaskHandle int
@s qint32 int
@s int32 int
@s QMessageBox int
@s QLCDNumber int
@s QWidget int
@s AnnotationButton int
@s AnnotationSpinBox int
@s QPushButton int
@s QTimer int
@s QAction int
@s QApplication int
@s PackLayout int
@s QLayout int
@s QLayoutItem int
@s QRect int
@s QList int
@s QSize int
@s QGraphicsScene int
@s SceneButton int
@s QGraphicsSceneMouseEvent int
@s QPoint int
@s true const
@s false const
@s QGraphicsView int
@s QGraphicsTextItem int
@s QFrame int
@s QPaintDevice int
@s QColor int
@s QBrush int
@s QHash int
@s QPointF int
@s QGraphicsLineItem int
@s MeasurementModel int
@s QTableView int
@s QVariant int
@s QAbstractItemView int
@s QAbstractItemModel int
@s QStringList int
@s QModelIndex int
@s MeasurementList int
@s QVariantList int
@s QSplitter int
@s QHBoxLayout int
@s QMainWindow int
@s QCoreApplication int
@s QSettings int
@s QMenu int
@s QCloseEvent int
@s LogEditWindow int
@s QFile int
@s QFileInfo int
@s QDir int
@s QXmlStreamWriter int
@s QXmlStreamReader int
@s QIODevice int
@s QLabel int
@s QTimeEdit int
@s QSpinBox int
@s QDoubleSpinBox int
@s ThermocoupleType int
@s TemperatureUnits int
@s Qt int
@s emit throw
@s TemperatureDisplay int
@s ZeroEmitter int
@s MeasurementAdapter int
@s GraphView int
@s ZoomLog int
@s TimerDisplay int
@s QBoxLayout int
@s WidgetDecorator int
@s XMLInput int
@s XMLOutput int
@s CSVOutput int
@s QTextStream int
@s QTranslator int
@s QLocale int
@s Application int
@s QScriptContext int
@s QScriptEngine int
@s QScriptEngineDebugger int
@s QScriptValue int
@s FakeDAQ int
@s QMenuBar int
@s QKeySequence int
@s QFileDialog int
@s Measurement int
@s Date int
@s QLibrary int
@s daqfp int
@s QResizeEvent int
@s QVBoxLayout int
@s QByteArray int
@s QSqlDatabase int
@s QComboBox int
@s QXmlStreamAttribute int
@s QSqlQuery int
@s QLineEdit int
@s QDoubleValidator int
@s QIntValidator int
@s QTextEdit int
@s QStandardItemModel int
@s QValidator int
@s QMap int
@s QDomElement int
@s QDomNodeList int
@s QDomNode int
@s QStack int
@s QDomDocument int
@s QDomNamedNodeMap int
@s QFormLayout int
@s QAbstractButton int
@s QAbstractScrollArea int
@s SqlComboBox int
@s QUuid int
@s SqlComboBoxDelegate int
@s QItemDelegate int
@s SqlConnectionSetup int
@s QDialog int
@s QCheckBox int
@s SaltModel int
@s QStyleOptionViewItem int
@s QBuffer int
@s QDateEdit int
@s QCalendarWidget int
@s QDate int
@s QFocusEvent int
@s QGridLayout int
@s QScrollArea int
@s QSqlQueryModel int
@s QSqlRecord int
@s QSqlResult int
@s SqlQueryConnection int
@s QFont int
@s SqlQueryView int
@s QTextDocument int
@s QTextCursor int
@s QTextFrame int
@s ReportTable int
@s QTextTable int
@s QTextTableFormat int
@s QTextFrameFormat int
@s QTextTableCell int
@s QPrinter int
@s QPrintDialog int
@s QSqlError int
@s FormArray int
@s QRegExp int
@s QRegExpValidator int
@s QDomDocumentFragment int
@s QStackedLayout int
@s QMouseEvent int
@s QGraphicsPolygonItem int
@s QPolygonF int
@s QGraphicsPathItem int
@s QPainterPath int
@s QXmlQuery int
@s QGraphicsItem int
@s QWebView int
@s QUrl int
@s QShowEvent int
@s QDateTimeEdit int
@s ThresholdDetector int
@s EdgeDirection int
@s DeviceTreeModelNode int
@s QMetaObject int
@s QTreeView int
@s QToolButton int
@s QextPortInfo int
@s QextSerialEnumerator int
@s QMetaEnum int
@s quint16 int
@s QextSerialPort int
@s QGroupBox int
@s QVariantMap int
@s QIcon int
@s QFileInfoList int
@s QMetaMethod int

@f error normal
@f line normal
@f signals public
@f slots int
@f qRegisterMetaType make_pair
@f READ TeX
@f WRITE TeX
@f tr TeX
@f this TeX
@f foreach while
@f qobject_cast make_pair
@f t1 TeX
@f t2 TeX
@f AppInstance TeX
@f getself make_pair
@f TYPE TeX
@f argument make_pair
@f toScriptValue make_pair
@f arg1 TeX
@f arg2 TeX
@f arg3 TeX
@f arg4 TeX
@f findChild make_pair
@f qscriptvalue_cast make_pair

\def\READ{\kern4pt{\tt READ}\kern4pt}
\def\WRITE{\kern4pt{\tt WRITE}\kern4pt}
\def\tr{\delta}
\def\this{\forall}
\def\t#1{t_{#1}}
\def\AppInstance{\.{AppInstance}}
\def\TYPE{\cal T\kern1pt}
\def\arg#1{arg_{#1}}

% Document
@** A Note on Notation.

\noindent As noted by Falkoff and Iverson\nfnote{A.~D.~Falkoff and
K.~E.~Iverson, ``The Design of APL'' (1973)}~there is little need to limit the
typography used to represent a computer program in print. The printed code of
\pn{} uses a number of notations that I have found useful in making clear the
intent of the code. For example, a common mistake in \CPLUSPLUS/ \kern-0.5em
code is the confusion of assignment ({\tt =}) with a test for equality
({\tt ==}). The \web{} convention of using |=| for assignment and |==| to test
for equality makes such errors obvious at a glance. A list of special symbols
and the equivalent \CPLUSPLUS/text is provided in Table \secno. Most of these
symbols should be familiar\nfnote{The {\tt NULL} symbol is a break with the
conventions of most Qt applications. According the the \CPLUSPLUS/standard, |0|
is both an integer constant and a null pointer constant. Most programs using Qt
use |0| in place of any name for the null pointer, however conceptually these
are two very different things. The notation chosen here was used by Knuth for
similar purposes and seems to have worked well there.}.

\medskip

\settabs 9 \columns
\+&&&{\tt =}&|=|&Assignment\cr
\+&&&{\tt --}&|--|&Decrement\cr
\+&&&{\tt ==}&|==|&Equality Test\cr
\+&&&{\tt >=}&|>=|&Greater or Equal Test\cr
\+&&&{\tt ++}&|++|&Increment\cr
\+&&&{\tt !=}&|!=|&Inequality Test\cr
\+&&&{\tt <=}&|<=|&Less or Equal Test\cr
\+&&&{\tt \char'046\char'046}&$\land$&Logical AND\cr
\+&&&{\tt \char'174\char'174}&$\lor$&Logical OR\cr
\+&&&{\tt ::}&|::|&Member of\cr
\+&&&{\tt !}&|!|&Negation\cr
\+&&&{\tt NULL}&|NULL|&Null Pointer\cr
\+&&&{\tt this}&|this|&Object\cr
\+&&&{\tt \%}&|%|&Remainder\cr
\+&&&{\tt tr()}&|tr()|&Translate\cr

\smallskip

\centerline{Table \secno: Special Characters In \pn}

\medskip

Reserved words are set in bold face. As some of these reserved words are also
the names of types, type names that are not specified in \CPLUSPLUS/are also
set in bold face. Type placeholders in template definitions, however, are set in
caligraphic capitals to emphasize that it will be replaced with a real type at
compile time. Variables and class members are set in italics, character strings
are set in a typewriter style with visible spaces. Macro names are also set in
typewriter style. Numeric constants and plain text comments are set in an
upright roman style. Comments containing \CEE/ or mathematics are styled as
such. Code that will be interpreted by the ECMA-262 host environment has no
pretty printing.

\danger With apologies to prof.~Knuth\nfnote{This symbol was introduced in
{\underbar{Computers~\char'046~Typesetting}}@q'@> (Knuth, 1984) to point out material
that is for ``wizards only.'' It seems to be as appropriate a symbol as any to
point out the darker corners of this program.}, code that is known to be
potentially buggy is flagged with a dangerous bend sign. Some of this code is
buggy due to issues with the code \pn{} depends on, others are things that
should be fixed in \pn{}. Of course, there may also be bugs that have not yet
been noticed or have not been attached to a particular block of code.\endanger

A basic familiarity with literate programming techniques (particularly the
conventions of \cweb{}), Qt, and \CPLUSPLUS/is recommended before altering the
program, but an effort has been made to keep the program understandable for
those who are only interested in studying it.

@** Changes from Version 1{\char`.}4.

\noindent An improper conversion bug when viewing data in Celsius has been
corrected.

Modbus RTU device configurations in which no configuration information was
requested from the device at setup time previously did not collect any
measurements. This has been fixed.

The script binding for |QTime| now features the {\tt valueOf()} method. This is
called implicitly when comparing two time values and allows the results of such
comparisons to be as one might expect.

The script binding for SqlComboBox now supports |findText()|.

@** Changes from Version 1{\char`.}3.

\noindent The {\tt CalendarPopupEdit}, {\tt CoffeeOrderForm}, and
{\tt CoffeeItemPurchaseEditor} classes have been removed.

Data exported in CSV now depends on the current view granularity.

Derived data series by linear spline interpolation now supported.

Both NI DAQmx Base and NI DAQmx are now supported in the same build along
with all other new hardware support.

Changes have been made to improve support for collecting measurements from
multiple devices.

The |GraphView| now supports roast profile translation. A new class has been
added to support this feature.

The new {\tt -c} command line argument allows the load configuration prompt
to be bypassed.

Support for reports loaded into a menu dynamically and for presenting reports
in a menu hierarchy.

The ZoomLog should no longer be editable.

Basic use of |QWebView| has been added. This has been used to enable printing
roast profiles and allows for a larger range of reports than is possible with
the reporting framework used previously. The old reporting framework is still
available for compatability with old configurations, however that code is now
considered to be depreciated.

The |ZoomLog| is now capable of dispaying temperature measurements in various
units.

Ambiguity in library bindings has been eliminated to improve reliability of
Windows builds.

Minor changes to improve coding style consistency.

|QIODevice| has been extended for simpler use with classes that expect string
data.

New convenience properties have been added to the |QDateEdit| script binding.

Database error reporting has been improved.

The {\tt <stretch>} element can now be used in horizontal and vertical layouts.
This can be used to change the distribution of excess space in a layout in ways
that look better than the default handling.

The |MeasurementTimeOffset| filter now works correctly when midnight occurs
during a batch.

The |openEntryRow| signal has been added to |SqlQueryView|. This can be used in
situations where it is not convenient to have a unique identifier in the first
column of the view. An invokable |data()| method was also added to this class.

Preliminary support for Modbus RTU devices has been added.

A new device and logging window configuration system has been introduced which
allows people to edit their device configuration graphically instead of needing
to create new configuration XML documents for the most common types of
configuration change.

Table views expecting numeric data now support entering arithmetical
expressions for evaluation.

@** Changes from Version 1{\char`.}2.

\noindent A vast number of changes have been made to the source code since
version 1.2.

@* New Reporting Framework.

\noindent A new reporting framework has been added to \pn{}, greatly simplifying
the creation of reports. See the Reporting section for full details.

@* New Classes.

\noindent The |AnnotationSpinBox| class has been introduced. This allows manual
entry of numerical annotations. The use of this class is not recommended as it
would almost certainly be better to have this information logged automatically.
The class is provided for situations in which this is prohibitively expensive.

The |FormArray| class has been introduced. This class makes it easy to create
user interface elements consisting of an arbitrary number of duplicated forms.
This depreciates the {\tt CoffeeOrderForm} and {\tt CoffeeItemPurchaseEditor}
classes.

A proxy class named |SqlQueryConnection| has been added. This wraps |QSqlQuery|
and manages its own |QSqlDatabase| connection. The |invalidate()| property has
been added to query objects in the host environment in order to correct database
connection leaks.

Horizontal and vertical scale widgets have been added to improve the user
experience when filling out cupping forms.

@* Modified Classes.

\noindent The |XMLOutput|, |XMLInput|, |CSVOutput|, and |ZoomLog| classes have
been modified along with the XML format used by \pn{} to support saving and
restoring multiple data series in a single file.

Inserting measurements into a model has been optimized for the most common use.
A large reduction in CPU utilization from \pn{} should be observed.

@* New Configuration Options.

\noindent Several additional methods have been added to the host environment for
working with tables created by {\tt <sqltablearray>} elements. The |data()| and
|setData()| methods can be used for examining and manipulating data in table
cells. The |quotedColumnArray()| method can be used to obtain arrays suitable
for insertion in {\tt text[]} fields of a database. The |bindableColumnArray()|
and |bindableQuotedColumnArray()| methods produce values appropriate for binding
to query placeholders.

The |sqlToArray()| method has been modified to strip quote characters from the
start and end of each array element if that element is quoted.

It is now possible to change the application default fonts from the host
environment.

There are new layout options available. Grid layouts and stacked layouts are now
available. It is also possible to assign an ID to any layout for manipulation
from script code.

It is now possible to specify that a combo box should be editable without adding
script code.

It is now possible to apply validators to line edits through configuration
element attributes. Numeric, integer, and regular expression validators are
supported.

Support for Qt stylesheets has been added. Please use this sparingly.

|QXmlStreamWriter| and |QXmlStreamReader| can now be used from within the host
environment.

@* New Versions of Qt.

\noindent \pn{} has been linked against Qt 4.6.2 and is tested as working on Mac
OS X 10.6.

@* Bug fixes.

\noindent A change in the |Application| class eliminates a problem with
segmentation faults in the Linux build.

@** Changes from Version 1{\char`.}1.

\noindent The code has been tested when linked against NI-DAQmxBase 3.2 for use
with a NI USB-9162 Hi-Speed USB Carrier. No code changes were required and no
text appears on the console.

NI-DAQmxBase is linked at run time rather than compile time. Also, nidaqmxbase.h
is no longer required.

It is now possible to inspect a |Measurement| object to determine the unit used
for the measurement or create a new |Measurement| converted to a different unit.

Recent versions of Qt have corrected bugs in the graphics view architecture.
This has allowed some of the kludges of previous versions to be removed. The use
of Qt 4.4.3 is now recommended.

The configuration system has been changed significantly. The preferred method of
describing the user interface is with an XML description with application data
flow still defined through script fragments. Most configurations from version
1.1 should continue to work when wrapped in {\tt <application><program>} XML
elements, however the new configuration system makes it easier to produce far
more complex and featureful configurations. Work on this portion of the code is
not complete and requires additional documentation which is beyond the scope of
the source code documentation.

Several new classes have been added to the host environment.

The |Application| class now manages a connection to a PostgreSQL database which
other classes and the host environment can use to interact with a database.

The {\tt RoastControlWindow} class used in version 1.0 and depreciated in
version 1.1 has been removed.

@* Bug fixes.

\noindent The |GraphView| class now scales the graph to fit the viewport when
the widget is resized. This was not the case prior to version 1.1.3.

@** Changes from Version 1{\char`.}0.

\noindent The most substantial change from \pn{} version 1.0 is the introduction
of an ECMA-262 host environment intended for setting up the user interface and
program data flow. The old {\tt RoastControlWindow} class was depreciated.

This host environment provides access to most of the classes in \pn{} and a
selection of classes from Qt. These classes can be used in scripts to the extent
needed to prevent feature regressions. The example scripts provided should work,
however attempts to go beyond what is provided by these examples may require
modification to the source code.

@* Bug fixes.

\noindent The |TimerDisplay| class had a bug that would cause three error
messages to appear on the console for every |TimerDisplay| object instantiated.
This bug was fixed in version 1.0.6.

When the user interface and data flow was hard coded, other parts of the program
could make assumptions that are not necessarily true in different configurations
without being detected. Moving from a configuration with one channel on the DAQ
to a configuration with two revealed faulty assumptions in two classes.

The |DAQImplementation| class used a constant 1 instead of the number of
channels to specify the size of the measurement buffer. The result of this was
that no measurements would be generated when more than one channel was set up.
This bug was fixed in version 1.0.7.

The |XMLOutput| class failed to handle rows with no value in the temperature
column for rows with values in any column after the temperature column. Such
rows were never produced in version 1.0 but can be produced now. Such rows were
frequently produced during development. This bug was fixed in version 1.0.8.

@** Introduction.

\noindent A common tool in the craft of coffee roasting is the data logger.
Perhaps the most commonly used of these fall into the category of manual data
loggers which require the roaster to use paper and a writing utensil,
periodically recording measurements and noting control changes and observations
of interest as needed.

While there are many benefits to recording roast data\nfnote{Torrey Lee, Stephan
Diedrich, Carl Staub, and Jack Newall, ``How to Obtain Excellence with Drum
Roasters'' (2002) {\it Specialty Coffee Association of America 14$^{th}$ Annual
Conference and Exhibition}}, there are a number of limitations to the manual
approach; maintaining the records in a useful order is time consuming and error
prone, it is difficult to work with aggregates of such records, and the
attention required to log the data by hand can distract from the roasting. Using
a computer with automatic data logging software designed with coffee roasting in
mind can reduce or eliminate these deficiencies. \pn{} is one such program.

The file {\tt \filebase.w} contains both \CPLUSPLUS/source code and the
documentation for that code. This file is intended to be processed by
\cweb\nfnote{Donald E. Knuth and Silvio Levy, ``The \cweb{} System of Structured
Documentation'' (1994)}~to produce source code for your compiler and plain
\TeX{}\nfnote{\TeX{} (pronounced $\tau\epsilon\chi$) is a trademark of the
American Mathematical Society.} documentation that can be used to generate a PDF
document for gorgeous printable documentation. These generated files may have
been distributed with your copy of {\tt \filebase.w} for convenience.

Changes to the program can be made in three ways. \cweb{} provides a patching
mechanism which can be used to experiment with the code without risk of
clobbering it. Instructions for the construction of such a change file can be
found in the \cweb{} documentation. Adding the name of the change file to the
invocation of {\tt ctangle} and {\tt cweave} will incorporate that change
seamlessly in both source and documentation files. A section is provided at the
end of this program for use with this mechanism in the case that new sections
must be added. Another way to create persistent modifications is to alter
{\tt \filebase.w} however this may make it more difficult to use changes with
future versions of the software. Changes should not be made to
{\tt \filebase.cpp} if these changes are expected to persist. Finally, it is
possible to make many changes to how the program looks and behaves by creating a
new configuration document for the program to load. Modifications made in this
way do not even require recompiling the software. Examples that can serve as a
starting point for such customizations are provided with \pn{}.

\pn{} is a work in progress. There are several portions of the documentation
that contain suggestions for future improvement. These notes provide clues for
my future development plans. Naturally, if you have needs which are not quite
addressed by this program, you should feel free to modify the code to suit your
needs. Hopefully this will be easy to do.

In the spirit of Benjamin Franklin\nfnote{``\dots as we enjoy great advantages
from the inventions of others, we should be glad of an opportunity to serve
others by any invention of ours; and this we should do freely and
generously.''
--- Benjamin Franklin, \underbar{The Private Life of the Late
Benjamin Franklin, LL.D.~Originally
Written By Himself, And Now}\par\noindent
\underbar{Translated From The French} (1793)}, \pn{} is shared
with minimal restriction (see the license after the table of contents for legal
requirements). Libraries used by \pn{} may have other restrictions. Before
undertaking to distribute a binary created from this code, you may want to
either determine your rights with regard to these libraries or modify the
program to remove them.

As CWEB generates files with the wrong extension, we leave the default
generated file empty.

@c
/* Nothing to see here. */

@ The following is an overview of the structure of \pn:

@(typica.cpp@>=
#define PROGRAM_NAME "Typica"

@<Header files to include@>@/
@<Class declarations@>@/
@<Function prototypes for scripting@>@/
@<Class implementations@>@/
@<Functions for scripting@>@/
@<The main program@>
#include "moc_typica.cpp"

@ \pn{} is made of a number of distinct classes.

@<Class implementations@>=
@<NodeInserter implementation@>@/
@<Measurement implementation@>@/
@<DAQ Implementation@>@/
@<DataqSdkDevice implementation@>@/
@<FakeDAQ Implementation@>@/
@<Channel Implementation@>@/
@<TemperatureDisplay Implementation@>@/
@<MeasurementTimeOffset Implementation@>@/
@<ZeroEmitter Implementation@>@/
@<MeasurementAdapter Implementation@>@/
@<GraphView Implementation@>@/
@<ZoomLog Implementation@>@/
@<MeasurementModel Implementation@>@/
@<AnnotationButton Implementation@>@/
@<AnnotationSpinBox Implementation@>@/
@<TimerDisplay Implementation@>@/
@<PackLayout Implementation@>@/
@<SceneButton Implementation@>@/
@<WidgetDecorator Implementation@>@/
@<LogEditWindow Implementation@>@/
@<XMLOutput Implementation@>@/
@<XMLInput Implementation@>@/
@<CSVOutput Implementation@>@/
@<SaltModel Implementation@>@/
@<SqlComboBox Implementation@>@/
@<SqlComboBoxDelegate Implementation@>@/
@<Application Implementation@>@/
@<SqlConnectionSetup implementation@>@/
@<SqlQueryView implementation@>@/
@<SqlQueryConnection implementation@>@/
@<ReportTable implementation@>@/
@<FormArray implementation@>@/
@<ScaleControl implementation@>@/
@<IntensityControl implementation@>@/
@<ThresholdDetector Implementation@>@/
@<PortSelector implementation@>@/
@<BaudSelector implementation@>@/
@<ParitySelector implementation@>@/
@<FlowSelector implementation@>@/
@<StopSelector implementation@>@/
@<ModbusConfigurator implementation@>@/
@<ShortHexSpinBox implementation@>@/
@<ModbusRTUDevice implementation@>@/
@<DeviceTreeModelNode implementation@>@/
@<DeviceTreeModel implementation@>@/
@<BasicDeviceConfigurationWidget implementation@>@/
@<DeviceConfigurationWindow implementation@>@/
@<Ni9211TcConfWidget implementation@>@/
@<NiDaqMxBase9211ConfWidget implementation@>@/
@<NiDaqMxBaseDriverConfWidget implementation@>@/
@<ReportAction implementation@>@/
@<NumericDelegate implementation@>@/
@<NiDaqMxDriverConfWidget implementation@>@/
@<NiDaqMx9211ConfWidget implementation@>@/
@<NiDaqMxTc01ConfWidget implementation@>@/
@<ModbusRtuPortConfWidget implementation@>@/
@<ModbusRtuDeviceConfWidget implementation@>@/
@<ModbusRtuDeviceTPvConfWidget implementation@>@/
@<ModbusRtuDeviceTSvConfWidget implementation@>@/
@<RoasterConfWidget implementation@>@/
@<AnnotationButtonConfWidget implementation@>@/
@<NoteSpinConfWidget implementation@>@/
@<LinearCalibrator Implementation@>@/
@<LinearSplineInterpolator Implementation@>@/
@<LinearSplineInterpolationConfWidget implementation@>@/
@<TranslationConfWidget implementation@>@/
@<FreeAnnotationConfWidget implementation@>@/
@<RateOfChange implementation@>@/
@<SettingsWindow implementation@>@/
@<GraphSettingsWidget implementation@>@/
@<DataqSdkDeviceConfWidget implementation@>@/

@ A few headers are required for various parts of \pn{}. These allow the use of
various Qt modules.

@<Header files to include@>=
#include <QtCore>
#include <QtGui>
#include <QtScript>
#include <QtScriptTools>
#include <QtXml>
#include <QtSql>
#include <QtDebug>
#include <QtXmlPatterns>
#include <QtWebKit>

@ New code is being written in separate files in a long term effort to improve
organization of the code. The result of this is that some additional headers
are required here.

@<Header files to include@>=
#include "helpmenu.h"

@** The Scripting Engine.

\noindent The main enhancement of \pn{} version 1.1 is the introduction of a
scriptable environment. This change allows people to easily customize \pn{}
without having to alter the program code. Instead, the user interface and
program data flow is set up with a small script that runs in an ECMA-262 host
environment\nfnote{Standard ECMA-262, 3$^{\rm{rd}}$ Edition\par\hbox{\indent%
\pdfURL{%
http://www.ecma-international.org/publications/files/ECMA-ST/Ecma-262.pdf}%
{http://www.ecma-international.org/publications/files/ECMA-ST/Ecma-262.pdf}}}
which requires
significantly less expertise to modify than \pn{} itself. Such a scripting
environment will be familiar to anybody with experience using JavaScript on web
pages or ActionScript in Flash. \pn{}'@q'@>s configuration system was later updated
to support running several script fragments found in an XML configuration
document.

Most of the application classes are available from the scripting environment.
The functions that make this possible are presented along with the classes. A
selection of classes provided by Qt are also available. These are presented
here.

This chunk provides two |QScriptValue| objects which are used in other sections
appended to this chunk.

@<Set up the scripting engine@>=
QScriptEngine *engine = new QScriptEngine;
QScriptValue constructor;
QScriptValue value;

@ A common task when working with objects created from a script is finding the
object a method is called on from the current script context. The code for this
is simple, but lengthy. This is shortened with the use of a template function
that obtains the object in question and casts it to the appropriate type. If an
incorrect type is specified, a null pointer or similarly invalid value will be
returned.

@<Functions for scripting@>=
template<class TYPE> TYPE@, getself(QScriptContext *context)
{
	TYPE@, self = qobject_cast<TYPE>(context->thisObject().toQObject());
	return self;
}

template<> QTime getself(QScriptContext *context)
{
	QTime self = context->thisObject().toVariant().toTime();
	return self;
}

template<> SqlQueryConnection* getself(QScriptContext *context)
{
	SqlQueryConnection *self =@|
		(SqlQueryConnection *)qscriptvalue_cast<void *>(context->thisObject());
	return self;
}

template<> QXmlQuery* getself(QScriptContext *context)
{
	QXmlQuery *self =
		(QXmlQuery *)qscriptvalue_cast<void *>(context->thisObject());
	return self;
}

template<> QXmlStreamWriter* getself(QScriptContext *context)
{
	QXmlStreamWriter *self = @|
		(QXmlStreamWriter *)qscriptvalue_cast<void *>(context->thisObject());
	return self;
}

template<> QXmlStreamReader* getself(QScriptContext *context)
{
	QXmlStreamReader *self = @|
		(QXmlStreamReader *)qscriptvalue_cast<void *>(context->thisObject());
	return self;
}

@ Another common task is obtaining the arguments of a method call from the
script context and casting these arguments to the proper type. This is once
again done with templates.

@<Functions for scripting@>=
template<class TYPE> TYPE@, argument(int arg, QScriptContext *context)
{
	TYPE@, argument = qobject_cast<TYPE>(context->argument(arg).toQObject());
	return argument;
}

template<> QString argument(int arg, QScriptContext *context)
{
	return context->argument(arg).toString();
}

template<> QVariant argument(int arg, QScriptContext *context)
{
	return context->argument(arg).toVariant();
}

template<> int argument(int arg, QScriptContext *context)
{
	return context->argument(arg).toInt32();
}

template<> SqlQueryConnection* argument(int arg, QScriptContext *context)
{
	return (SqlQueryConnection *)
	        qscriptvalue_cast<void *>(context->argument(arg));
}

template<> QModelIndex argument(int arg, QScriptContext *context)
{
	return qscriptvalue_cast<QModelIndex>(context->argument(arg));
}

template<> double argument(int arg, QScriptContext *context)
{
	return (double)(context->argument(arg).toNumber());
}

template<> Units::Unit argument(int arg, QScriptContext *context)
{
	return (Units::Unit)(context->argument(arg).toInt32());
}

@ The scripting engine is informed of a number of classes defined elsewhere in
the program. Code related to scripting these classes is grouped with the code
implementing the classes. Additionally, there are several classes from Qt which
are also made scriptable. These are detailed in the following sections.

@* Exposing an Object Hierarchy to the Host Environment.

\noindent While QtScript does a generally acceptable job of exposing
information about objects that are available through the meta-object system,
some methods require special handling in order to make them fully available to
the host environment. Several functions are provided which provide a
|QScriptValue| with these additional properties. The functions providing these
properties also call other functions providing the properties of any base
classes. In this way, any additional functionality provided to the host
environment for a base class is also provided for any class that inherits that
base class.

For example, a |QBoxLayout| created in a script will have properties from
|QLayout| which in turn brings in properties from |QObject| and |QLayoutItem|.
A |QMainWindow| would bring in properties from |QWidget| which would bring in
properties from |QObject|.

Neither all methods nor all Qt classes are available from the host environment.
When adding functionality to the host environment, there is a priority on
classes and methods that are useful for \pn{}'@q'@>s intended purpose.

@* Base Classes.

\noindent There are a few classes that are base classes of classes exposed to
the scripting engine. There is no need for the host environment to allow the
creation of these base classes and there may not be methods that must be added
as properties in derived classes, however stub functions are provided so that
in the event that a method from one of these base classes is needed later, it
can be added once for all derived classes.

The first of these is |QObject|.

@<Function prototypes for scripting@>=
void setQObjectProperties(QScriptValue value, QScriptEngine *engine);

@ As there are no properties that need to be set for this class and as this
class does not inherit any other class, nothing needs to be done in this method.
It will, however, be called by subclasses in case this changes in the future.

@<Functions for scripting@>=
void setQObjectProperties(QScriptValue, QScriptEngine *)
{
	/* Nothing needs to be done here. */
}

@ The same can be done for |QPaintDevice| and |QLayoutItem|.

@<Function prototypes for scripting@>=
void setQPaintDeviceProperties(QScriptValue value, QScriptEngine *engine);
void setQLayoutItemProperties(QScriptValue value, QScriptEngine *engine);

@ The implementations are similarly empty.

@<Functions for scripting@>=
void setQPaintDeviceProperties(QScriptValue, QScriptEngine *)
{
	/* Nothing needs to be done here. */
}

void setQLayoutItemProperties(QScriptValue, QScriptEngine *)
{
	/* Nothing needs to be done here. */
}

@* Scripting QWidget.

\noindent The first interesting class in this hierarchy is |QWidget|. This is
mainly used as a base class for other widgets and in such a role it is not
particularly interesting. It is, however, possible to apply a layout to a
|QWidget| and use that to manage the size and position of one or more child
widgets. A few functions are used to accomplish this.

@<Function prototypes for scripting@>=
void setQWidgetProperties(QScriptValue value, QScriptEngine *engine);
QScriptValue constructQWidget(QScriptContext *context, QScriptEngine *engine);
QScriptValue QWidget_setLayout(QScriptContext *context, QScriptEngine *engine);
QScriptValue QWidget_activateWindow(QScriptContext *context,
                                    QScriptEngine *engine);

@ The script constructor must be passed to the scripting engine.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructQWidget);
value = engine->newQMetaObject(&QWidget::staticMetaObject, constructor);
engine->globalObject().setProperty("QWidget", value);

@ The constructor creates a script value, but uses another function to add
properties that wrap methods we want to make available to subclasses. Note that
properties of the base classes are added before properties of this class. This
procedure ensures that properties added from base classes can be be replaced in
subclasses.

@<Functions for scripting@>=
QScriptValue constructQWidget(QScriptContext *, QScriptEngine *engine)
{
	QScriptValue object = engine->newQObject(new QWidget);
	setQWidgetProperties(object, engine);
	return object;
}

void setQWidgetProperties(QScriptValue value, QScriptEngine *engine)
{
	setQObjectProperties(value, engine);
	setQPaintDeviceProperties(value, engine);
	value.setProperty("setLayout", engine->newFunction(QWidget_setLayout));
	value.setProperty("activateWindow",
	                  engine->newFunction(QWidget_activateWindow));
}

@ This just leaves the property implementations. |QWidget::setLayout()| takes
one argument, a |QLayout| and returns |void|. This wrapper duplicates this
interface. |QWidget::activateWindow()| takes no arguments and returns nothing
meaningful.

@<Functions for scripting@>=
QScriptValue QWidget_setLayout(QScriptContext *context, QScriptEngine *)
{
	if(context->argumentCount() == 1)
	{
		QWidget *self = getself<QWidget *>(context);
		QLayout *layout = argument<QLayout *>(0, context);
		if(layout)
		{
			self->setLayout(layout);
		}
		else
		{
			context->throwError("Incorrect argument type passed to "@|
			                    "QWidget::setLayout(). This method requires "@|
								"a QLayout.");
		}
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QWidget::setLayout(). This method takes one "@|
							"QLayout as an argument.");
	}
	return QScriptValue();
}

QScriptValue QWidget_activateWindow(QScriptContext *context,
                                    QScriptEngine *)
{
	QWidget *self = getself<QWidget *>(context);
	self->activateWindow();
	return QScriptValue();
}

@* Scripting QMainWindow.

\noindent Rather than directly exposing |QMainWindow| to the scripting engine,
we expose a class derived from |QMainWindow| with a minor change allowing the
script to be notified when the window is about to be closed.

This allows us to save settings for objects populating the window. Close
handlers can be established by connecting to the |aboutToClose()| signal which
is emitted in the |closeEvent()| handler. The close event is always accepted
after the script has had a chance to respond, so this cannot be used to present
an, ``Are you sure?'' message without additional modification.

Slots are also provided for saving the size and position of the window to
settings and restoring the window geometry from these settings.

As of version 1.4 window geometry management is provided for all windows. The
|restoreSizeAndPosition()| and |saveSizeAndPosition()| methods should be
considered depreciated.

Version 1.6 adds a new property for handling the |windowModified| property
such that an appropriate prompt is provided to confirm or cancel close events.

@<Class declarations@>=
class ScriptQMainWindow : public QMainWindow@/
{@t\1@>@/
	Q_OBJECT@;@/
	Q_PROPERTY(QString closePrompt READ closePrompt WRITE setClosePrompt)@;@/
	public:@/
		ScriptQMainWindow();
		QString closePrompt();@/
	@t\4@>public slots@t\kern-3pt@>:@/
		void show();
		void saveSizeAndPosition(const QString &key);
		void restoreSizeAndPosition(const QString &key);
		void displayStatus(const QString &message = QString());
		void setClosePrompt(QString prompt);@/
	protected:@/
		void closeEvent(QCloseEvent *event);
		void showEvent(QShowEvent *event);@/
	signals:@/
		void aboutToClose(void);@t\2@>@/
	private:@/
		QString cprompt;
}@t\kern-3pt@>;

@ The implementation of these functions is simple.

@<Functions for scripting@>=
ScriptQMainWindow::ScriptQMainWindow()@+: QMainWindow(NULL),
	cprompt(tr("Closing this window may result in loss of data. Continue?"))@/
{
	/* Nothing needs to be done here. */
}

void ScriptQMainWindow::saveSizeAndPosition(const QString &key)
{
	QSettings settings;
	settings.beginGroup(key);
	settings.setValue("pos", pos());
	settings.setValue("size", size());
	settings.endGroup();
}

void ScriptQMainWindow::restoreSizeAndPosition(const QString &key)
{
	QSettings settings;
	settings.beginGroup(key);
	if(settings.contains("size"))
	{
		resize(settings.value("size").toSize());
	}
	if(settings.contains("pos"))
	{
		move(settings.value("pos").toPoint());
	}
	settings.endGroup();
}

void ScriptQMainWindow::displayStatus(const QString &message)
{
	statusBar()->showMessage(message);
}

void ScriptQMainWindow::showEvent(QShowEvent *event)
{
	if(!event->spontaneous())
	{
		@<Restore window geometry@>@;
		event->accept();
	}
	else
	{
		event->ignore();
	}
}

void ScriptQMainWindow::show()
{
	QMainWindow::show();
}

@ When a close event occurs, we check the |windowModified| property to
determine if closing the window could result in loss of data. If this is
true, we allow the event to be cancelled. Otherwise, a signal is emitted which
allows scripts to perform any cleanup that may be required before closing the
window and the window geometry data is saved before allowing the window to
close.

@<Functions for scripting@>=
void ScriptQMainWindow::closeEvent(QCloseEvent *event)
{
	if(isWindowModified()) {
		@<Allow close event to be cancelled@>@;
	}
	emit aboutToClose();
	@<Save window geometry@>@;
	event->accept();
}

@ The prompt text for our confirmation window is provided through the
|closePrompt| property.

@<Allow close event to be cancelled@>=
QMessageBox::StandardButton result;
result = QMessageBox::warning(this, "Typica", closePrompt(),
                              QMessageBox::Ok | QMessageBox::Cancel);
if(result == QMessageBox::Cancel)
{
	event->ignore();
	return;
}

@ Implementation of the |closePrompt| property is trivial.

@<Functions for scripting@>=
QString ScriptQMainWindow::closePrompt()
{
	return cprompt;
}

void ScriptQMainWindow::setClosePrompt(QString prompt)
{
	cprompt = prompt;
}

@ Window geometry management from version 1.4 on makes use of the window ID to
produce an appropriate QSettings key. This decision relies on the ID being set
before any show or close events are received and it relies on every distinct
type of window having a unique ID. If this is not the case then other things
are likely very broken. Note that with this approach multiple instances of the
same type of window will use the same key. This may not be ideal in all cases,
but further refinements can be produced if necessary.

@<Save window geometry@>=
QSettings settings;
settings.setValue(QString("geometries/%1").arg(objectName()), saveGeometry());

@ Restoring saved geometry is performed similarly to saving it.

@<Restore window geometry@>=
QSettings settings;
restoreGeometry(settings.value(QString("geometries/%1").arg(objectName())).
					toByteArray());

@ Three functions are required to obtain the required functionality from a
script. A fourth adds properties for the object hierarchy.

@<Function prototypes for scripting@>=
QScriptValue constructQMainWindow(QScriptContext *context,
                                  QScriptEngine *engine);
QScriptValue QMainWindow_setCentralWidget(QScriptContext *context,@|
                                          QScriptEngine *engine);
QScriptValue QMainWindow_menuBar(QScriptContext *context,
                                 QScriptEngine *engine);
void setQMainWindowProperties(QScriptValue value, QScriptEngine *engine);

@ Of these, the engine only needs to be informed of the constructor initially.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructQMainWindow);
value = engine->newQMetaObject(&ScriptQMainWindow::staticMetaObject,
                               constructor);
engine->globalObject().setProperty("QMainWindow", value);

@ The constructor calls a function to add the additional properties to the
newly created value.

@<Functions for scripting@>=
QScriptValue constructQMainWindow(QScriptContext *, QScriptEngine *engine)
{
	QScriptValue object = engine->newQObject(new ScriptQMainWindow);
	setQMainWindowProperties(object, engine);
	return object;
}

void setQMainWindowProperties(QScriptValue value, QScriptEngine *engine)
{
	setQWidgetProperties(value, engine);
	value.setProperty("setCentralWidget",
	                  engine->newFunction(QMainWindow_setCentralWidget));
	value.setProperty("menuBar", engine->newFunction(QMainWindow_menuBar));
}

@ The |"setCentralWidget"| property is used for setting a widget in the main
area of the window. In \pn{} this will usually be a |QSplitter| object, but it
could also be a bare |QWidget| with a layout managing multiple widgets or a
custom widget defined in a local change. This is a simple wrapper around
|QMainWindow::setCentralWidget()|.

@<Functions for scripting@>=
QScriptValue QMainWindow_setCentralWidget(QScriptContext *context,
											QScriptEngine *)
{
	if(context->argumentCount() == 1)
	{
		QMainWindow *self = getself<QMainWindow *>(context);
		QWidget *widget = argument<QWidget *>(0, context);
		if(widget)
		{
			self->setCentralWidget(widget);
		}
		else
		{
			context->throwError("Incorrect argument type passed to "@|
			                    "QMainWindow::setCentralWidget(). This "@|
								"method requires a QWidget.");
		}
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QMainWindow::setCentralWidget(). This method "@|
							"takes one QWidget as an argument.");
	}
	return QScriptValue();
}

@ The |"menuBar"| property requires that we expose |QMenuBar| to the scripting
environment in a limited fashion. We don'@q'@>t need to allow scripts to create a
new menu bar as it can be obtained from the window, however to add the menus to
the menu bar, we need to add a property to the |QMenuBar| object before passing
it back.

@<Functions for scripting@>=
QScriptValue QMainWindow_menuBar(QScriptContext *context, QScriptEngine *engine)
{
	QScriptValue object;
	if(context->argumentCount() == 0)
	{
		QMainWindow *self = getself<@[QMainWindow *@]>(context);
		QMenuBar *bar = self->menuBar();
		object = engine->newQObject(bar);
		setQMenuBarProperties(object, engine);
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QMainWindow::menuBar(). This method takes no "@|
							"arguments.");
	}
	return object;
}

@ The previous function is the only place a new |QMenuBar| is created through
the host environment. Two functions are used in handling this object creation.

@<Function prototypes for scripting@>=
void setQMenuBarProperties(QScriptValue value, QScriptEngine *engine);
QScriptValue QMenuBar_addMenu(QScriptContext *context, QScriptEngine *engine);

@ The first of these adds the appropriate properties to the newly created
object.

@<Functions for scripting@>=
void setQMenuBarProperties(QScriptValue value, QScriptEngine *engine)
{
	setQWidgetProperties(value, engine);
	value.setProperty("addMenu", engine->newFunction(QMenuBar_addMenu));
}

@ This function can be used to add new menus to a menu bar. In order to do
anything with the newly created menus, two properties are added to the |QMenu|
objects which allow actions to be added as menu items and allow separators to be
placed between groups of menu items.

At the time of this writing, there are three |QMenuBar::addMenu()| methods. This
function wraps |QMenu* QMenuBar::addMenu(const QString &title)|.

@<Functions for scripting@>=
QScriptValue QMenuBar_addMenu(QScriptContext *context, QScriptEngine *engine)
{
	QScriptValue object;
	if(context->argumentCount() == 1)
	{
		QMenuBar *self = getself<@[QMenuBar *@]>(context);
		QString title = argument<QString>(0, context);
		object = engine->newQObject(self->addMenu(title));
		setQMenuProperties(object, engine);
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QMenuBar::addMenu(). This method takes one "@|
							"string as an argument.");
	}
	return object;
}

@ These three functions allow adding items to the menu and adding separators
between groups of items.

@<Function prototypes for scripting@>=
void setQMenuProperties(QScriptValue value, QScriptEngine *engine);
QScriptValue QMenu_addAction(QScriptContext *context, QScriptEngine *engine);
QScriptValue QMenu_addSeparator(QScriptContext *context, QScriptEngine *engine);

@ The first of these add properties to newly created |QMenu| objects.

@<Functions for scripting@>=
void setQMenuProperties(QScriptValue value, QScriptEngine *engine)
{
	setQWidgetProperties(value, engine);
	value.setProperty("addAction", engine->newFunction(QMenu_addAction));
	value.setProperty("addSeparator", engine->newFunction(QMenu_addSeparator));
}

@ These functions are simple wrappers around |QMenu| methods.

@<Functions for scripting@>=
QScriptValue QMenu_addAction(QScriptContext *context, QScriptEngine *)
{
	if(context->argumentCount() == 1)
	{
		QMenu *self = getself<@[QMenu *@]>(context);
		QAction *action = argument<QAction *>(0, context);
		if(action)
		{
			self->addAction(action);
		}
		else
		{
			context->throwError("Incorrect argument type passed to "@|
			                    "QMenu::addAction(). This method requires a "@|
								"QAction.");
		}
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QMenu::addAction(). This method takes one "@|
							"QAction as an argument.");
	}
	return QScriptValue();
}

QScriptValue QMenu_addSeparator(QScriptContext *context, QScriptEngine *)
{
	if(context->argumentCount() == 0)
	{
		QMenu *self = getself<@[QMenu *@]>(context);
		self->addSeparator();
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QMenu::addSeparator(). This method takes no "@|
							"arguments.");
	}
	return QScriptValue();
}

@* Scripting QFrame.

\noindent |QFrame| is another class for which little needs to be done. It exists
as a subclass of |QWidget| and a superclass for |QSplitter|, |QLCDNumber|, and
|QAbstractScrollArea| among other classes.

@<Function prototypes for scripting@>=
void setQFrameProperties(QScriptValue value, QScriptEngine *engine);
QScriptValue constructQFrame(QScriptContext *context, QScriptEngine *engine);

@ The constructor must be passed to the scripting engine.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructQFrame);
value = engine->newQMetaObject(&QFrame::staticMetaObject, constructor);
engine->globalObject().setProperty("QFrame", value);

@ The implementation of these functions should seem familiar.

@<Functions for scripting@>=
QScriptValue constructQFrame(QScriptContext *, QScriptEngine *engine)
{
	QScriptValue object = engine->newQObject(new QFrame);
	setQFrameProperties(object, engine);
	return object;
}

void setQFrameProperties(QScriptValue value, QScriptEngine *engine)
{
	setQWidgetProperties(value, engine);
}

@* Scripting QLabel.

\noindent When constructing an interface wholly or partially through dynamic
means rather than entirely through the XML configuration document it can
sometimes be desirable to construct |QLabel| instances. This is usually used
to provide a very small amount of text.

@<Function prototypes for scripting@>=
void setQLabelProperties(QScriptValue value, QScriptEngine *engine);
QScriptValue constructQLabel(QScriptContext *context, QScriptEngine *engine);

@ The constructor must be passed to the scripting engine.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructQLabel);
value = engine->newQMetaObject(&QLabel::staticMetaObject, constructor);
engine->globalObject().setProperty("QLabel", value);

@ In the constructor we allow an optional argument to specify the text of the
label.

@<Functions for scripting@>=
QScriptValue constructQLabel(QScriptContext *context, QScriptEngine *engine)
{
	QString text;
	if(context->argumentCount() == 1)
	{
		text = argument<QString>(0, context);
	}
	QScriptValue object = engine->newQObject(new QLabel(text));
	setQLabelProperties(object, engine);
	return object;
}

void setQLabelProperties(QScriptValue value, QScriptEngine *engine)
{
	setQFrameProperties(value, engine);
}

@* Scripting QLineEdit.

\noindent Similarly, we may want to allow line edits in interfaces defined
through the host environment. For example, this is used for the free text
annotation control for roasters this has been configured on.

@<Function prototypes for scripting@>=
void setQLineEditProperties(QScriptValue value, QScriptEngine *engine);
QScriptValue constructQLineEdit(QScriptContext *context, QScriptEngine *engine);

@ The constructor must be passed to the host environment.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructQLineEdit);
value = engine->newQMetaObject(&QLineEdit::staticMetaObject, constructor);
engine->globalObject().setProperty("QLineEdit", value);

@ The constructor is trivial.

@<Functions for scripting@>=
QScriptValue constructQLineEdit(QScriptContext *, QScriptEngine *engine)
{
	QScriptValue object = engine->newQObject(new QLineEdit());
	setQLineEditProperties(object, engine);
	return object;
}

@ At present all of the QLineEdit functionality exposed through this interface
is provided automatically through the meta-object system.

@<Functions for scripting@>=
void setQLineEditProperties(QScriptValue value, QScriptEngine *engine)
{
	setQWidgetProperties(value, engine);
}

@* Scripting QSplitter.

\noindent The |QSplitter| class is one of the main classes used for user
interface object layout in \pn{}. To provide this class to the scripting engine,
we provide five functions: a constructor, a method for adding widgets to the
splitter, a method for saving the size of each widget in the splitter, a
method for restoring these saved sizes, and a function for adding these methods
as properties of newly created |QSplitter| objects.

@<Function prototypes for scripting@>=
QScriptValue constructQSplitter(QScriptContext *context, QScriptEngine *engine);
QScriptValue QSplitter_addWidget(QScriptContext *context,
									QScriptEngine *engine);
QScriptValue QSplitter_saveState(QScriptContext *context,
									QScriptEngine *engine);
QScriptValue QSplitter_restoreState(QScriptContext *context,
									QScriptEngine *engine);
void setQSplitterProperties(QScriptValue value, QScriptEngine *engine);

@ Of these, the scripting engine must be informed of the constructor.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructQSplitter);
value = engine->newQMetaObject(&QSplitter::staticMetaObject, constructor);
engine->globalObject().setProperty("QSplitter", value);

@ The constructor creates the object and adds the required properties to it.

@<Functions for scripting@>=
QScriptValue constructQSplitter(QScriptContext *, QScriptEngine *engine)
{
	QScriptValue object = engine->newQObject(new QSplitter);
	setQSplitterProperties(object, engine);
	return object;
}

void setQSplitterProperties(QScriptValue value, QScriptEngine *engine)
{
	setQFrameProperties(value, engine);
	value.setProperty("addWidget", engine->newFunction(QSplitter_addWidget));
	value.setProperty("saveState", engine->newFunction(QSplitter_saveState));
	value.setProperty("restoreState",
	                  engine->newFunction(QSplitter_restoreState));
}

@ The |"addWidget"| property is a simple wrapper around
|QSplitter::addWidget()|.

@<Functions for scripting@>=
QScriptValue QSplitter_addWidget(QScriptContext *context, QScriptEngine *)
{
	if(context->argumentCount() == 1)
	{
		QSplitter *self = getself<QSplitter *>(context);
		QWidget *widget = argument<QWidget *>(0, context);
		if(widget)
		{
			self->addWidget(widget);
		}
		else
		{
			context->throwError("Incorrect argument type passed to "@|
			                    "QSplitter::addWidget(). This method "@|
								"requires a QWidget.");
		}
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QSplitter::addWidget(). This method takes one "@|
							"QWidget as an argument.");
	}
	return QScriptValue();
}

@ When saving and restoring the state of a splitter, we always want to do this
through a |QSettings| object. For this, we take an extra argument specifying the
settings key to read from or write to. Unlike the equivalent functions called
from native code, neither of these functions called from a script will return
the data being saved.

@<Functions for scripting@>=
QScriptValue QSplitter_saveState(QScriptContext *context, QScriptEngine *)
{
	if(context->argumentCount() == 1)
	{
		QSplitter *self = getself<QSplitter *>(context);
		QString key = argument<QString>(0, context);
		QSettings settings;
		settings.setValue(key, self->saveState());
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QSplitter::saveState(). This method takes one "@|
							"string as an argument.");
	}
	return QScriptValue();
}

QScriptValue QSplitter_restoreState(QScriptContext *context, QScriptEngine *)
{
	if(context->argumentCount() == 1)
	{
		QSplitter *self = getself<QSplitter *>(context);
		QString key = argument<QString>(0, context);
		QSettings settings;
		self->restoreState(settings.value(key).toByteArray());
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QSplitter::restoreState(). This method takes "@|
							"one string as an argument.");
	}
	return QScriptValue();
}

@* Scripting Layout classes.

\noindent Layout classes simplify managing the size and position of widgets in a
user interface. Qt provides several such classes, including |QBoxLayout| which
can be used to construct a variety of different interfaces. As widgets
containing a layout should not really need to care which layout is being used,
the |QLayout| class acts as an abstract base for all layout classes. A bare
|QLayout| will never be constructed, however subclasses can make use of the
|addWidget()| property.

@<Function prototypes for scripting@>=
void setQLayoutProperties(QScriptValue value, QScriptEngine *engine);
QScriptValue QLayout_addWidget(QScriptContext *context, QScriptEngine *engine);

@ The implementation is trivial.

@<Functions for scripting@>=
void setQLayoutProperties(QScriptValue value, QScriptEngine *engine)
{
	setQLayoutItemProperties(value, engine);
	value.setProperty("addWidget", engine->newFunction(QLayout_addWidget));
}

QScriptValue QLayout_addWidget(QScriptContext *context, QScriptEngine *)
{
	if(context->argumentCount() == 1)
	{
		QLayout *self = getself<QLayout *>(context);
		QWidget *widget = argument<QWidget *>(0, context);
		if(widget)
		{
			self->addWidget(widget);
		}
		else
		{
			context->throwError("Incorrect argument type passed to "@|
		                        "QLayout::addWidget(). This method requires "@|
				    			"a QWidget.");
		}
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QLayout::addWidget(). This method takes one "@|
							"QWidget as an argument.");
	}
	return QScriptValue();
}

@ |QBoxLayout| is a more interesting layout class. This allows widgets to be
arranged in a single row or column and can be used, for example, to arrange a
row of buttons as in figure \secno.

\medskip

\resizebox*{6.3in}{!}{\includegraphics{boxlayoutexample}}

\smallskip

\centerline{Figure \secno: Buttons in a |QBoxLayout|.}

\medskip

This class makes use of the |addWidget()| method from |QLayout|.

@<Function prototypes for scripting@>=
QScriptValue constructQBoxLayout(QScriptContext *context,
                                 QScriptEngine *engine);
void setQBoxLayoutProperties(QScriptValue value, QScriptEngine *engine);
QScriptValue QBoxLayout_addLayout(QScriptContext *context, QScriptEngine *engine);
QScriptValue QBoxLayout_addWidget(QScriptContext *context, QScriptEngine *engine);

@ The script constructor must be passed to the scripting engine.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructQBoxLayout);
value = engine->newQMetaObject(&QBoxLayout::staticMetaObject, constructor);
engine->globalObject().setProperty("QBoxLayout", value);

@ The implementation of these functions should seem familiar by now. Note that
while a horizontal layout is provided by default, this can be changed from the
script once the layout is created.

@<Functions for scripting@>=
QScriptValue constructQBoxLayout(QScriptContext *, QScriptEngine *engine)
{
	QScriptValue object =
		engine->newQObject(new QBoxLayout(QBoxLayout::LeftToRight));
	setQBoxLayoutProperties(object, engine);
	return object;
}

void setQBoxLayoutProperties(QScriptValue value, QScriptEngine *engine)
{
	setQLayoutProperties(value, engine);
	value.setProperty("addLayout", engine->newFunction(QBoxLayout_addLayout));
	value.setProperty("addWidget", engine->newFunction(QBoxLayout_addWidget));
}

QScriptValue QBoxLayout_addLayout(QScriptContext *context, QScriptEngine *)
{
	if(context->argumentCount() > 0 && context->argumentCount() < 3)
	{
		QBoxLayout *self = getself<QBoxLayout *>(context);
		QLayout *layout = argument<QLayout *>(0, context);
		int stretch = 0;
		if(context->argumentCount() == 2)
		{
			stretch = argument<int>(1, context);
		}
		if(layout)
		{
			self->addLayout(layout, stretch);
		}
		else
		{
			context->throwError("Incorrect argument type passed to "@|
			                    "QLayout::addLayout(). This method requires "@|
								"a QLayout.");
		}
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QLayout::addLayout(). This method takes one "@|
							"QLayout as an argument and optionally one integer.");
	}
	return QScriptValue();
}

@ We override the base class wrapper for |addWidget| to add two optional
arguments: one specifies the stretch factor of the widget and the other
specifies the alignment of the widget within the layout.

@<Functions for scripting@>=
QScriptValue QBoxLayout_addWidget(QScriptContext *context, QScriptEngine *)
{
	if(context->argumentCount() > 0 && context->argumentCount() < 4)
	{
		QBoxLayout *self = getself<QBoxLayout *>(context);
		QWidget *widget = argument<QWidget *>(0, context);
		int stretch = 0;
		Qt::Alignment alignment = 0;
		if(context->argumentCount() > 1)
		{
			stretch = argument<int>(1, context);
		}
		if(context->argumentCount() > 2)
		{
			alignment = (Qt::Alignment)(argument<int>(2, context));
		}
		if(widget)
		{
			self->addWidget(widget, stretch, alignment);
		}
		else
		{
			context->throwError("Incorrect argument type passed to "@|
			                    "QBoxLayout::addWidget(). This method requires "@|
								"a QWidget.");
		}
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QBoxLayout::addWidget(). This method takes one "@|
							"QWidget and optionally up to two integers as "@|
							"arguments.");
	}
	return QScriptValue();
}

@* Scripting QAction.

\noindent The |QAction| class is used in \pn{} to create menu items and respond
to the selection of these items. Three functions are required for our scripting
needs with regard to this class.

@<Function prototypes for scripting@>=
QScriptValue constructQAction(QScriptContext *context, QScriptEngine *engine);
QScriptValue QAction_setShortcut(QScriptContext *context,
                                 QScriptEngine *engine);
void setQActionProperties(QScriptValue value, QScriptEngine *engine);

@ The scripting engine must be informed of the constructor.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructQAction);
value = engine->newQMetaObject(&QAction::staticMetaObject, constructor);
engine->globalObject().setProperty("QAction", value);

@ The constructor is simple, however some might sensibly question why the
|"setShortcut"| property is needed at all. Why not have scripts simply set the
|shortcut| property of the |QAction| directly? The answer to this is that the
property expects data of the |QKeySequence| type. While this can be created from
a |QString|, passing a string to the property through the scripting engine did
not work at the time this was written.

@<Functions for scripting@>=
QScriptValue constructQAction(QScriptContext *, QScriptEngine *engine)
{
	QScriptValue object = engine->newQObject(new QAction(NULL));
	setQActionProperties(object, engine);
	return object;
}

void setQActionProperties(QScriptValue value, QScriptEngine *engine)
{
	setQObjectProperties(value, engine);
	value.setProperty("setShortcut", engine->newFunction(QAction_setShortcut));
}

QScriptValue QAction_setShortcut(QScriptContext *context, QScriptEngine *)
{
	if(context->argumentCount() == 1)
	{
		QAction *self = getself<@[QAction *@]>(context);
		self->setShortcut(argument<QString>(0, context));
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QAction::setShortcut(). This method takes one "@|
							"string as an argument.");
	}
	return QScriptValue();
}

@* Scripting QFileDialog.

\noindent |QFileDialog| provides two static member functions which is all that
we need. The objects returned from these methods are built on the |QDialog|
abstract base class.

@<Function prototypes for scripting@>=
QScriptValue QFileDialog_getOpenFileName(QScriptContext *context,
                                         QScriptEngine *engine);
QScriptValue QFileDialog_getSaveFileName(QScriptContext *context,
                                         QScriptEngine *engine);
void setQFileDialogProperties(QScriptValue value, QScriptEngine *engine);
void setQDialogProperties(QScriptValue value, QScriptEngine *engine);

@ The scripting engine must be informed of the wrapper functions for the static
methods.

@<Set up the scripting engine@>=
value = engine->newQMetaObject(&QFileDialog::staticMetaObject);
value.setProperty("getOpenFileName",
                  engine->newFunction(QFileDialog_getOpenFileName));
value.setProperty("getSaveFileName",
                  engine->newFunction(QFileDialog_getSaveFileName));
engine->globalObject().setProperty("QFileDialog", value);

@ This function is just a simple wrapper around the |QFileDialog| method, but
the object returned has any properties added to the base class available.

@<Functions for scripting@>=
QScriptValue QFileDialog_getOpenFileName(QScriptContext *context,
                                         QScriptEngine *engine)
{
	QScriptValue retval;
	if(context->argumentCount() == 3)
	{
		QWidget *widget = argument<QWidget *>(0, context);
		if(widget)
		{
			QString caption = argument<QString>(1, context);
			QString dir = argument<QString>(2, context);
			retval = QScriptValue(engine,
			                      QFileDialog::getOpenFileName(widget, caption,
								                               dir, "", 0, 0));
			setQFileDialogProperties(retval, engine);
		}
		else
		{
			context->throwError("Incorrect argument type passed to "@|
			                    "QFileDialog::getOpenFileName(). The first "@|
								"argument to this method must be a QWidget.");
		}
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QFileDialog::getOpenFileName(). This method "@|
							"takes one QWidget followed by two strings for a "@|
							"total of three arguments.");
	}
	return retval;
}

@ Similarly, this just wraps |QFileDialog::getSaveFileName()|.

@<Functions for scripting@>=
QScriptValue QFileDialog_getSaveFileName(QScriptContext *context,
                                         QScriptEngine *engine)
{
	QScriptValue retval;
	if(context->argumentCount() == 3)
	{
		QWidget *widget = argument<QWidget *>(0, context);
		if(widget)
		{
			QString caption = argument<QString>(1, context);
			QString dir = argument<QString>(2, context);
			retval = QScriptValue(engine,
							      QFileDialog::getSaveFileName(widget, caption,
								                               dir, "", 0, 0));

			setQFileDialogProperties(retval, engine);
		}
		else
		{
			context->throwError("Incorrect argument type passed to "@|
			                    "QFileDialog::getSaveFileName(). The first "@|
								"argument to this method must be a QWidget.");
		}
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QFileDialog::getSaveFileName(). This method "@|
							"takes one QWidget followed by two strings for a "@|
							"total of three arguments.");
	}
	return retval;
}

@ Adding object hierarchy properties to the objects created above is simple.

@<Functions for scripting@>=
void setQFileDialogProperties(QScriptValue value, QScriptEngine *engine)
{
	setQDialogProperties(value, engine);
}

void setQDialogProperties(QScriptValue value, QScriptEngine *engine)
{
	setQWidgetProperties(value, engine);
}

@* Scripting QFile.

\noindent When using a |QFile| in a script, we only need the constructor and two
functions for hooking it in with the rest of the object hierarchy.

@<Function prototypes for scripting@>=
QScriptValue constructQFile(QScriptContext *context, QScriptEngine *engine);
void setQFileProperties(QScriptValue value, QScriptEngine *engine);
QScriptValue QFile_remove(QScriptContext *context, QScriptEngine *engine);
void setQIODeviceProperties(QScriptValue value, QScriptEngine *engine);
QScriptValue QIODevice_open(QScriptContext *context, QScriptEngine *engine);
QScriptValue QIODevice_close(QScriptContext *context, QScriptEngine *engine);
QScriptValue QIODevice_readToString(QScriptContext *context,
                                    QScriptEngine *engine);

@ This function is passed to the scripting engine.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructQFile);
value = engine->newQMetaObject(&QFile::staticMetaObject, constructor);
engine->globalObject().setProperty("QFile", value);

@ The implementation is trivial.

@<Functions for scripting@>=
QScriptValue constructQFile(QScriptContext *context, QScriptEngine *engine)
{
	QScriptValue object =
		engine->newQObject(new QFile(argument<QString>(0, context)));@/
	setQFileProperties(object, engine);
	return object;
}

@ |QFile| gets a wrapper around |remove()| to support deleting temporary files.

@<Functions for scripting@>=
void setQFileProperties(QScriptValue value, QScriptEngine *engine)
{
	setQIODeviceProperties(value, engine);
	value.setProperty("remove", engine->newFunction(QFile_remove));
}

QScriptValue QFile_remove(QScriptContext *context, QScriptEngine *engine)
{
	QFile *self = getself<QFile *>(context);
	bool retval = self->remove();
	return QScriptValue(engine, retval);
}

@ Although we aren'@q'@>t going to create any instances of |QIODevice| directly,
subclasses such as |QFile| and |QBuffer| get two additional properties for
opening and closing the device.

In order to solve some class interoperability issues, a convenience method is
also added which is equivalent to creating a |QString| from the |QByteArray|
returned from the |readAll()| method.

@<Functions for scripting@>=
void setQIODeviceProperties(QScriptValue value, QScriptEngine *engine)
{
	setQObjectProperties(value, engine);
	value.setProperty("open", engine->newFunction(QIODevice_open));
	value.setProperty("close", engine->newFunction(QIODevice_close));
	value.setProperty("readToString",
	                  engine->newFunction(QIODevice_readToString));
}

@ These are simple wrappers. In the case of the |open()| property, one argument
may be passed specifying the mode used for opening. The supported values for
this are 1 (Read Only), 2 (Write Only), and 3 (Read Write). If this argument is
not passed, it is assumed that the user wants read and write access.

@<Functions for scripting@>=
QScriptValue QIODevice_open(QScriptContext *context, QScriptEngine *)
{
	QIODevice *self = getself<QIODevice *>(context);
	if(context->argumentCount() == 1)
	{
		switch(argument<int>(0, context))
		{
			case 1:
				self->open(QIODevice::ReadOnly);
				break;
			case 2:
				self->open(QIODevice::WriteOnly);
				break;
			case 3:
				self->open(QIODevice::ReadWrite);
				break;
			default:
				break;
		}
	}
	else
	{
		self->open(QIODevice::ReadWrite);
	}
	return QScriptValue();
}

QScriptValue QIODevice_close(QScriptContext *context, QScriptEngine *)
{
	QIODevice *self = getself<QIODevice *>(context);
	self->close();
	return QScriptValue();
}

@ The |readToString()| method is a simple extension of |QIODevice::readAll()| to
interface with classes that expect document data in the form of a string. Most
notably, this includes |QWebView|.

@<Functions for scripting@>=
QScriptValue QIODevice_readToString(QScriptContext *context, QScriptEngine *)
{
	QIODevice *self = getself<QIODevice *>(context);
	self->reset();
	return QScriptValue(QString(self->readAll()));
}

@* Scripting QBuffer.

\noindent Sometimes it is desirable to load a roast profile from a file. At
other times, it is more useful to load that profile from a byte array stored in
a database. The |XMLInput| class takes data from a |QIODevice| object, which
means that we can choose from a |QFile| when we want the former or a |QBuffer|
when we want the latter.

@<Function prototypes for scripting@>=
QScriptValue constructQBuffer(QScriptContext *context, QScriptEngine *engine);
void setQBufferProperties(QScriptValue value, QScriptEngine *engine);
QScriptValue QBuffer_setData(QScriptContext *context, QScriptEngine *engine);

@ The host environment needs to be aware of the constructor.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructQBuffer);
value = engine->newQMetaObject(&QBuffer::staticMetaObject, constructor);
engine->globalObject().setProperty("QBuffer", value);

@ The implementation is trivial.

@<Functions for scripting@>=
QScriptValue constructQBuffer(QScriptContext *context, QScriptEngine *engine)
{
	QByteArray *array = new QByteArray(argument<QString>(0, context).toAscii());
	QScriptValue object = engine->newQObject(new QBuffer(array));
	setQBufferProperties(object, engine);
	return object;
}

void setQBufferProperties(QScriptValue value, QScriptEngine *engine)
{
	setQIODeviceProperties(value, engine);
	value.setProperty("setData", engine->newFunction(QBuffer_setData));
}

QScriptValue QBuffer_setData(QScriptContext *context, QScriptEngine *)
{
	QBuffer *self = getself<QBuffer *>(context);
	self->setData(argument<QString>(0, context).toAscii());
	return QScriptValue();
}

@* Scripting QXmlQuery.

\noindent Sometimes we have some XML data in a file or a buffer and we would
like to extract certain information from that data in the host environment.
Rather than write complicated string manipulation routines in an attempt to deal
with this sensibly, we can use the XQuery language to extract the information we
want. One common use case for this is extracting all measurements from a roast
profile that are associated with an annotation.

@<Function prototypes for scripting@>=
QScriptValue constructXQuery(QScriptContext *context, QScriptEngine *engine);
QScriptValue XQuery_bind(QScriptContext *context, QScriptEngine *engine);
QScriptValue XQuery_exec(QScriptContext *context, QScriptEngine *engine);
QScriptValue XQuery_setQuery(QScriptContext *context, QScriptEngine *engine);
void setXQueryProperties(QScriptValue value, QScriptEngine *engine);

@ The constructor must be registered with the host environment. This is done a
bit differently from most classes as |QXmlQuery| is not a |QObject|.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructXQuery);
engine->globalObject().setProperty("XQuery", constructor);

@ The constructor just needs to make sure the functions we want to make
available are applied.

@<Functions for scripting@>=
QScriptValue constructXQuery(QScriptContext *, QScriptEngine *engine)
{
	QScriptValue object = engine->toScriptValue<void *>(new QXmlQuery);
	setXQueryProperties(object, engine);
	return object;
}

void setXQueryProperties(QScriptValue value, QScriptEngine *engine)
{
	value.setProperty("bind", engine->newFunction(XQuery_bind));
	value.setProperty("exec", engine->newFunction(XQuery_exec));
	value.setProperty("setQuery", engine->newFunction(XQuery_setQuery));
}

@ The |bind()| property can be used to specify a |QIODevice| to be referenced by
a variable within a query.

@<Functions for scripting@>=
QScriptValue XQuery_bind(QScriptContext *context, QScriptEngine *)
{
	QXmlQuery *self = getself<QXmlQuery *>(context);
	QIODevice *buffer = argument<QIODevice *>(1, context);
	self->bindVariable(argument<QString>(0, context), buffer);
	return QScriptValue();
}

@ A method is also required for setting the query we wish to conduct.

@<Functions for scripting@>=
QScriptValue XQuery_setQuery(QScriptContext *context, QScriptEngine *)
{
	QXmlQuery *self = getself<QXmlQuery *>(context);
	self->setQuery(argument<QString>(0, context));
	return QScriptValue();
}

@ This method runs the previously specified query.

@<Functions for scripting@>=
QScriptValue XQuery_exec(QScriptContext *context, QScriptEngine *)
{
	QXmlQuery *self = getself<QXmlQuery *>(context);
	QString result;
	self->evaluateTo(&result);
	return QScriptValue(result);
}

@* Scripting QXmlStreamWriter.

\noindent There are some cases where it may be desirable to produce XML from the
host environment. While there are several ways to accomplish this, the
|QXmlStreamWriter| class greatly simplifies generating complex XML documents.
This class is not related to |QObject|, so several functions are needed to
expose the functionality of this class to the host environment.

@<Function prototypes for scripting@>=
QScriptValue constructXmlWriter(QScriptContext *context, QScriptEngine *engine);
QScriptValue XmlWriter_setDevice(QScriptContext *context,
                                 QScriptEngine *engine);
QScriptValue XmlWriter_writeAttribute(QScriptContext *context,
                                      QScriptEngine *engine);
QScriptValue XmlWriter_writeCDATA(QScriptContext *context,
                                  QScriptEngine *engine);
QScriptValue XmlWriter_writeCharacters(QScriptContext *context,
                                       QScriptEngine *engine);
QScriptValue XmlWriter_writeDTD(QScriptContext *context, QScriptEngine *engine);
QScriptValue XmlWriter_writeEmptyElement(QScriptContext *context,
                                         QScriptEngine *engine);
QScriptValue XmlWriter_writeEndDocument(QScriptContext *context,
                                        QScriptEngine *engine);
QScriptValue XmlWriter_writeEndElement(QScriptContext *context,
                                       QScriptEngine *engine);
QScriptValue XmlWriter_writeEntityReference(QScriptContext *context,
                                            QScriptEngine *engine);
QScriptValue XmlWriter_writeProcessingInstruction(QScriptContext *context,
                                                  QScriptEngine *engine);
QScriptValue XmlWriter_writeStartDocument(QScriptContext *context,
                                          QScriptEngine *engine);
QScriptValue XmlWriter_writeStartElement(QScriptContext *context,
                                         QScriptEngine *engine);
QScriptValue XmlWriter_writeTextElement(QScriptContext *context,
                                        QScriptEngine *engine);
void setXmlWriterProperties(QScriptValue value, QScriptEngine *engine);

@ The constructor must be registered with the host environment.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructXmlWriter);
engine->globalObject().setProperty("XmlWriter", constructor);

@ The constructor takes an optional argument allowing the output device to be
specified.

@<Functions for scripting@>=
QScriptValue constructXmlWriter(QScriptContext *context, QScriptEngine *engine)
{
	QXmlStreamWriter *retval;
	if(context->argumentCount() == 1)
	{
		retval = new QXmlStreamWriter(argument<QIODevice *>(0, context));
	}
	else
	{
		retval = new QXmlStreamWriter;
	}
	QScriptValue object = engine->toScriptValue<void *>(retval);
	setXmlWriterProperties(object, engine);
	return object;
}

void setXmlWriterProperties(QScriptValue value, QScriptEngine *engine)
{
	value.setProperty("setDevice", engine->newFunction(XmlWriter_setDevice));
	value.setProperty("writeAttribute",
	                  engine->newFunction(XmlWriter_writeAttribute));
	value.setProperty("writeCDATA", engine->newFunction(XmlWriter_writeCDATA));
	value.setProperty("writeCharacters",
	                  engine->newFunction(XmlWriter_writeCharacters));
	value.setProperty("writeDTD", engine->newFunction(XmlWriter_writeDTD));
	value.setProperty("writeEmptyElement",
	                  engine->newFunction(XmlWriter_writeEmptyElement));
	value.setProperty("writeEndDocument",
	                  engine->newFunction(XmlWriter_writeEndDocument));
	value.setProperty("writeEndElement",
	                  engine->newFunction(XmlWriter_writeEndElement));
	value.setProperty("writeEntityReference",
	                  engine->newFunction(XmlWriter_writeEntityReference));
	value.setProperty("writeProcessingInstruction",
	                  engine->newFunction(XmlWriter_writeProcessingInstruction));
	value.setProperty("writeStartDocument",
	                  engine->newFunction(XmlWriter_writeStartDocument));
	value.setProperty("writeStartElement",
					  engine->newFunction(XmlWriter_writeStartElement));
	value.setProperty("writeTextElement",
					  engine->newFunction(XmlWriter_writeTextElement));
}

@ If the output device needs to be changed or if one is not passed to the
constructor, the |setDevice()| method can be used.

@<Functions for scripting@>=
QScriptValue XmlWriter_setDevice(QScriptContext *context, QScriptEngine *)
{
	QXmlStreamWriter *self = getself<QXmlStreamWriter *>(context);
	QIODevice *device = argument<QIODevice *>(0, context);
	self->setDevice(device);
	return QScriptValue();
}

@ The remaining functions are simple wrappers used for writing various types of
data. After creating a writer and setting the output device, the start of the
document should be written. One argument is required containing the XML version
number. Another function handles writing the end of the document.

@<Functions for scripting@>=
QScriptValue XmlWriter_writeStartDocument(QScriptContext *context,
                                          QScriptEngine *)
{
	QXmlStreamWriter *self = getself<QXmlStreamWriter *>(context);
	self->writeStartDocument(argument<QString>(0, context));
	return QScriptValue();
}

QScriptValue XmlWriter_writeEndDocument(QScriptContext *context,
                                        QScriptEngine *)
{
	QXmlStreamWriter *self = getself<QXmlStreamWriter *>(context);
	self->writeEndDocument();
	return QScriptValue();
}

@ After the start of the document, a DTD is commonly needed.

@<Functions for scripting@>=
QScriptValue XmlWriter_writeDTD(QScriptContext *context, QScriptEngine *)
{
	QXmlStreamWriter *self = getself<QXmlStreamWriter *>(context);
	self->writeDTD(argument<QString>(0, context));
	return QScriptValue();
}

@ After this, elements need to be written. For this, we write the start
element, any attributes needed, character data, and the end element.

@<Functions for scripting@>=
QScriptValue XmlWriter_writeStartElement(QScriptContext *context,
                                         QScriptEngine *)
{
	QXmlStreamWriter *self = getself<QXmlStreamWriter *>(context);
	self->writeStartElement(argument<QString>(0, context));
	return QScriptValue();
}

QScriptValue XmlWriter_writeAttribute(QScriptContext *context, QScriptEngine *)
{
	QXmlStreamWriter *self = getself<QXmlStreamWriter *>(context);
	self->writeAttribute(argument<QString>(0, context),
	                     argument<QString>(1, context));
	return QScriptValue();
}

QScriptValue XmlWriter_writeCharacters(QScriptContext *context, QScriptEngine *)
{
	QXmlStreamWriter *self = getself<QXmlStreamWriter *>(context);
	self->writeCharacters(argument<QString>(0, context));
	return QScriptValue();
}

QScriptValue XmlWriter_writeEndElement(QScriptContext *context, QScriptEngine *)
{
	QXmlStreamWriter *self = getself<QXmlStreamWriter *>(context);
	self->writeEndElement();
	return QScriptValue();
}

@ For convenience, two other methods are provided for writing elements. Elements
which do not require anything between the start and end elements can be created
with |writeEmptyElement()|. Elements which do not require attributes, but do
contain text can be created with |writeTextElement()|.

@<Functions for scripting@>=
QScriptValue XmlWriter_writeEmptyElement(QScriptContext *context,
                                         QScriptEngine *)
{
	QXmlStreamWriter *self = getself<QXmlStreamWriter *>(context);
	self->writeEmptyElement(argument<QString>(0, context));
	return QScriptValue();
}

QScriptValue XmlWriter_writeTextElement(QScriptContext *context,
                                        QScriptEngine *)
{
	QXmlStreamWriter *self = getself<QXmlStreamWriter *>(context);
	self->writeTextElement(argument<QString>(0, context),
	                       argument<QString>(1, context));
	return QScriptValue();
}

@ Less commonly needed are functions for writing CDATA sections, entity
references, and processing instructions.

@<Functions for scripting@>=
QScriptValue XmlWriter_writeCDATA(QScriptContext *context, QScriptEngine *)
{
	QXmlStreamWriter *self = getself<QXmlStreamWriter *>(context);
	self->writeCDATA(argument<QString>(0, context));
	return QScriptValue();
}

QScriptValue XmlWriter_writeEntityReference(QScriptContext *context,
                                            QScriptEngine *)
{
	QXmlStreamWriter *self = getself<QXmlStreamWriter *>(context);
	self->writeEntityReference(argument<QString>(0, context));
	return QScriptValue();
}

QScriptValue XmlWriter_writeProcessingInstruction(QScriptContext *context,
                                                  QScriptEngine *)
{
	QXmlStreamWriter *self = getself<QXmlStreamWriter *>(context);
	self->writeProcessingInstruction(argument<QString>(0, context),
	                                 argument<QString>(1, context));
	return QScriptValue();
}

@* Scripting QXmlStreamReader.

\noindent When a serializer is written using |QXmlStreamWriter|, a corresponding
deserializer should also be written. While there are several possible ways to do
this, using |QXmlStreamReader| is often the best choice. \pn{} provides a subset
of the functionality from this class which should be adequate for most purposes.

@<Function prototypes for scripting@>=
QScriptValue constructXmlReader(QScriptContext *context, QScriptEngine *engine);
QScriptValue XmlReader_atEnd(QScriptContext *context, QScriptEngine *engine);
QScriptValue XmlReader_attribute(QScriptContext *context,
                                 QScriptEngine *engine);
QScriptValue XmlReader_hasAttribute(QScriptContext *context,
                                    QScriptEngine *engine);
QScriptValue XmlReader_isDTD(QScriptContext *context, QScriptEngine *engine);
QScriptValue XmlReader_isStartElement(QScriptContext *context,
                                      QScriptEngine *engine);
QScriptValue XmlReader_name(QScriptContext *context, QScriptEngine *engine);
QScriptValue XmlReader_readElementText(QScriptContext *context,
                                       QScriptEngine *engine);
QScriptValue XmlReader_readNext(QScriptContext *context, QScriptEngine *engine);
QScriptValue XmlReader_text(QScriptContext *context, QScriptEngine *engine);
void setXmlReaderProperties(QScriptValue value, QScriptEngine *engine);

@ The constructor must be registered with the host environment.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructXmlReader);
engine->globalObject().setProperty("XmlReader", constructor);

@ The constructor requires an argument specifying the output device. This can be
any |QIODevice|. The |open()| method must be called on the device before passing
it as an argument to this function.

@<Functions for scripting@>=
QScriptValue constructXmlReader(QScriptContext *context, QScriptEngine *engine)
{
	QXmlStreamReader *retval =
		new QXmlStreamReader(argument<QIODevice *>(0, context));
	QScriptValue object = engine->toScriptValue<void *>(retval);
	setXmlReaderProperties(object, engine);
	return object;
}

void setXmlReaderProperties(QScriptValue value, QScriptEngine *engine)
{
	value.setProperty("atEnd", engine->newFunction(XmlReader_atEnd));
	value.setProperty("attribute", engine->newFunction(XmlReader_attribute));
	value.setProperty("hasAttribute",
	                  engine->newFunction(XmlReader_hasAttribute));
	value.setProperty("isDTD", engine->newFunction(XmlReader_isDTD));
	value.setProperty("isStartElement",
	                  engine->newFunction(XmlReader_isStartElement));
	value.setProperty("name", engine->newFunction(XmlReader_name));
	value.setProperty("readElementText",
	                  engine->newFunction(XmlReader_readElementText));
	value.setProperty("readNext",
	                  engine->newFunction(XmlReader_readNext));
	value.setProperty("text", engine->newFunction(XmlReader_text));
}

@ Most of the functions are simple member function wrappers. Two of these
properties are not. These are the |attribute()| and |hasAttribute()| properties.

@<Functions for scripting@>=
QScriptValue XmlReader_attribute(QScriptContext *context, QScriptEngine *)
{
	QXmlStreamReader *self = getself<QXmlStreamReader *>(context);
	QString retval =
		self->attributes().value(argument<QString>(0, context)).toString();
	return QScriptValue(retval);
}

QScriptValue XmlReader_hasAttribute(QScriptContext *context, QScriptEngine *)
{
	QXmlStreamReader *self = getself<QXmlStreamReader *>(context);
	bool retval =
		self->attributes().hasAttribute(argument<QString>(0, context));
	return QScriptValue(retval);
}

@ Other properties can be used for determining how to proceed with the
processing.

@<Functions for scripting@>=
QScriptValue XmlReader_atEnd(QScriptContext *context, QScriptEngine *)
{
	QXmlStreamReader *self = getself<QXmlStreamReader *>(context);
	return QScriptValue(self->atEnd());
}

QScriptValue XmlReader_isDTD(QScriptContext *context, QScriptEngine *)
{
	QXmlStreamReader *self = getself<QXmlStreamReader *>(context);
	return QScriptValue(self->isDTD());
}

QScriptValue XmlReader_isStartElement(QScriptContext *context, QScriptEngine *)
{
	QXmlStreamReader *self = getself<QXmlStreamReader *>(context);
	return QScriptValue(self->isStartElement());
}

@ We move from one element to the next with the |readNext()| property.

@<Functions for scripting@>=
QScriptValue XmlReader_readNext(QScriptContext *context, QScriptEngine *)
{
	QXmlStreamReader *self = getself<QXmlStreamReader *>(context);
	self->readNext();
	return QScriptValue();
}

@ The remaining properties return the element name and text.

@<Functions for scripting@>=
QScriptValue XmlReader_name(QScriptContext *context, QScriptEngine *)
{
	QXmlStreamReader *self = getself<QXmlStreamReader *>(context);
	return QScriptValue(self->name().toString());
}

QScriptValue XmlReader_readElementText(QScriptContext *context, QScriptEngine *)
{
	QXmlStreamReader *self = getself<QXmlStreamReader *>(context);
	return QScriptValue(self->readElementText());
}

QScriptValue XmlReader_text(QScriptContext *context, QScriptEngine *)
{
	QXmlStreamReader *self = getself<QXmlStreamReader *>(context);
	return QScriptValue(self->text().toString());
}

@* Scripting QSettings.

\noindent Rather than have a script create a |QSettings| object when it needs to
save or load settings, the object is provided along with properties for getting
and setting values. Two functions are needed for this along with a third which
ensures any properties added to |QObject| are also available to |QSettings| from
the host environment.

@<Function prototypes for scripting@>=
QScriptValue QSettings_value(QScriptContext *context, QScriptEngine *engine);
QScriptValue QSettings_setValue(QScriptContext *context, QScriptEngine *engine);
void setQSettingsProperties(QScriptValue value, QScriptEngine *engine);

@ The object with properties for these functions is passed to the scripting
engine.

@<Set up the scripting engine@>=
value = engine->newQObject(&settings);
setQSettingsProperties(value, engine);
engine->globalObject().setProperty("QSettings", value);

@ Adding properties to the |QSettings| object should seem familiar.

@<Functions for scripting@>=
void setQSettingsProperties(QScriptValue value, QScriptEngine *engine)
{
	setQObjectProperties(value, engine);
	value.setProperty("value", engine->newFunction(QSettings_value));
	value.setProperty("setValue", engine->newFunction(QSettings_setValue));
}

@ When getting a value from saved settings, there is the possibility that there
will not be a value saved for the requested key. An optional second argument can
be used to supply a default value.

@<Functions for scripting@>=
QScriptValue QSettings_value(QScriptContext *context, QScriptEngine *engine)
{
	QScriptValue object;
	if(context->argumentCount() == 1 || context->argumentCount() == 2)
	{
		QSettings settings;
		QString key = argument<QString>(0, context);
		QVariant value;
		QVariant retval;
		if(context->argumentCount() > 1)
		{
			value = argument<QVariant>(1, context);
			retval = settings.value(key, value);
		}
		else
		{
			retval = settings.value(key);
		}
		object = engine->newVariant(retval);
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QSettings::value(). This method takes one "@|
							"string and one optional variant type.");
	}
	return object;
}

QScriptValue QSettings_setValue(QScriptContext *context, QScriptEngine *)
{
	if(context->argumentCount() == 2)
	{
		QSettings settings;
		QString key = argument<QString>(0, context);
		QVariant value = argument<QVariant>(1, context);
		settings.setValue(key, value);
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QSettings::setValue(). This method takes one "@|
							"string and one variant type for a total of two "@|
							"arguments.");
	}
	return QScriptValue();
}

@* Scripting QLCDNumber.

\noindent |QLCDNumber| is used as a base class for \pn{}'@q'@>s |TemperatureDisplay|
and |TimerDisplay| classes, but it can also be used on its own for the display
of mainly numeric information.

@<Function prototypes for scripting@>=
QScriptValue constructQLCDNumber(QScriptContext *context,
                                 QScriptEngine *engine);
void setQLCDNumberProperties(QScriptValue value, QScriptEngine *engine);

@ The constructor must be passed to the scripting engine.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructQLCDNumber);
value = engine->newQMetaObject(&QLCDNumber::staticMetaObject, constructor);
engine->globalObject().setProperty("QLCDNumber", value);

@ There is nothing special about the implementation.

@<Functions for scripting@>=
QScriptValue constructQLCDNumber(QScriptContext *, QScriptEngine *engine)
{
	QScriptValue object = engine->newQObject(new QLCDNumber());
	setQLCDNumberProperties(object, engine);
	return object;
}

void setQLCDNumberProperties(QScriptValue value, QScriptEngine *engine)
{
	setQFrameProperties(value, engine);
}

@* Scripting QTime.

\noindent |QTime| is a little different from the classes examined so far. This
class can be used for synchonizing time among various objects by creating a
common base reference time. This should not be needed as ECMA-262 already
specifies a |Date| class, however this has historically been troublesome to use.

One thing that makes this class different is that it is not related to
|QObject|. This makes usefully exposing it to the scripting engine a little more
difficult.

@<Function prototypes for scripting@>=
QScriptValue constructQTime(QScriptContext *context, QScriptEngine *engine);
QScriptValue QTime_addMSecs(QScriptContext *context, QScriptEngine *engine);
QScriptValue QTime_addSecs(QScriptContext *context, QScriptEngine *engine);
QScriptValue QTime_elapsed(QScriptContext *context, QScriptEngine *engine);
QScriptValue QTime_hour(QScriptContext *context, QScriptEngine *engine);
QScriptValue QTime_isNull(QScriptContext *context, QScriptEngine *engine);
QScriptValue QTime_isValid(QScriptContext *context, QScriptEngine *engine);
QScriptValue QTime_minute(QScriptContext *context, QScriptEngine *engine);
QScriptValue QTime_msec(QScriptContext *context, QScriptEngine *engine);
QScriptValue QTime_msecsTo(QScriptContext *context, QScriptEngine *engine);
QScriptValue QTime_restart(QScriptContext *context, QScriptEngine *engine);
QScriptValue QTime_second(QScriptContext *context, QScriptEngine *engine);
QScriptValue QTime_secsTo(QScriptContext *context, QScriptEngine *engine);
QScriptValue QTime_setHMS(QScriptContext *context, QScriptEngine *engine);
QScriptValue QTime_start(QScriptContext *context, QScriptEngine *engine);
QScriptValue QTime_toString(QScriptContext *context, QScriptEngine *engine);
QScriptValue QTime_currentTime(QScriptContext *context, QScriptEngine *engine);
QScriptValue QTime_fromString(QScriptContext *context, QScriptEngine *engine);
QScriptValue QTime_valueOf(QScriptContext *context, QScriptEngine *engine);
void setQTimeProperties(QScriptValue value, QScriptEngine *engine);

@ We must tell the script engine about the constructor. This is not done in
quite the same way as is done for |QObject| derived types.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructQTime);
engine->globalObject().setProperty("QTime", constructor);

@ The constructor has a couple interesting twists. The first is the ability to
accept a variable number of integer arguments. The other is that |QTime| is not
derived from |QObject|. The lack of |break| statements in the |switch| is
intended.

@<Functions for scripting@>=
QScriptValue constructQTime(QScriptContext *context,
                            QScriptEngine *engine)
{
	QScriptValue object;
	if(context->argumentCount() == 0 ||
	   (context->argumentCount() >= 2 && context->argumentCount() <= 4))@/
	{
		int arg1 = 0;
		int arg2 = 0;
		int arg3 = 0;
		int arg4 = 0;
		switch(context->argumentCount())
		{@t\1@>@/
			case 4:@/
				arg4 = argument<int>(3, context);
			case 3:@/
				arg3 = argument<int>(2, context);
			case 2:@/
				arg2 = argument<int>(1, context);
				arg1 = argument<int>(0, context);
			default:@/
				break;@t\2@>@/
		}
		if(context->argumentCount())
		{
			object = engine->toScriptValue<QTime>(QTime(arg1, arg2, arg3,
			                                            arg4));
		}
		else
		{
			object = engine->toScriptValue<QTime>(QTime());
		}
		setQTimeProperties(object, engine);
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QTime::QTime(). This method takes zero, two, "@|
							"three, or four integer arguments.");
	}
	return object;
}

@ In order to use the various |QTime| methods, we must add wrapper functions as
properties of newly created script objects. The last two of these should really
be callable without starting from an existing |QTime|.

@<Functions for scripting@>=
void setQTimeProperties(QScriptValue value, QScriptEngine *engine)
{
	value.setProperty("addMSecs", engine->newFunction(QTime_addMSecs));
	value.setProperty("addSecs", engine->newFunction(QTime_addSecs));
	value.setProperty("elapsed", engine->newFunction(QTime_elapsed));
	value.setProperty("hour", engine->newFunction(QTime_hour));
	value.setProperty("isNull", engine->newFunction(QTime_isNull));
	value.setProperty("isValid", engine->newFunction(QTime_isValid));
	value.setProperty("minute", engine->newFunction(QTime_minute));
	value.setProperty("msec", engine->newFunction(QTime_msec));
	value.setProperty("msecsTo", engine->newFunction(QTime_msecsTo));
	value.setProperty("restart", engine->newFunction(QTime_restart));
	value.setProperty("second", engine->newFunction(QTime_second));
	value.setProperty("secsTo", engine->newFunction(QTime_secsTo));
	value.setProperty("setHMS", engine->newFunction(QTime_setHMS));
	value.setProperty("start", engine->newFunction(QTime_start));
	value.setProperty("toString", engine->newFunction(QTime_toString));
	value.setProperty("currentTime", engine->newFunction(QTime_currentTime));
	value.setProperty("fromString", engine->newFunction(QTime_fromString));
	value.setProperty("valueOf", engine->newFunction(QTime_valueOf));
}

@ The |valueOf()| method exposes a numeric representation of the time
suitable for use in comparing two time values. With this it is possible to
take two |QTime| values in script code {\tt t1} and {\tt t2} and get the
expected results from {\tt t1 == t2}, {\tt t1 < t2}, {\tt t1 > t2} and
similar comparative operations.

@<Functions for scripting@>=
QScriptValue QTime_valueOf(QScriptContext *context, QScriptEngine *)
{
	QTime self = getself<QTime>(context);
	int retval = (self.hour() * 60 * 60 * 1000) + (self.minute() * 60 * 1000) +
	             (self.second() * 1000) + self.msec();
	return QScriptValue(retval);
}

@ These functions are effectively wrapper functions around existing |QTime|
functionality with some error checking for the scripting engine.

The |addMSecs()| and |addSecs()| methods return a new |QTime| object.

@<Functions for scripting@>=
QScriptValue QTime_addMSecs(QScriptContext *context, QScriptEngine *engine)
{
	QTime time;
	QScriptValue retval;
	if(context->argumentCount() == 1)
	{
		QTime self = getself<QTime>(context);
		time = self.addMSecs(argument<int>(0, context));
		retval = engine->toScriptValue<QTime>(time);
		setQTimeProperties(retval, engine);
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QTime::addMSecs(). This method takes one "@|
							"integer as an argument.");
	}
	return retval;
}

QScriptValue QTime_addSecs(QScriptContext *context, QScriptEngine *engine)
{
	QTime time;
	QScriptValue retval;
	if(context->argumentCount() == 1)
	{
		QTime self = getself<QTime>(context);
		time = self.addSecs(argument<int>(0, context));
		retval = engine->toScriptValue<QTime>(time);
		setQTimeProperties(retval, engine);
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QTime::addSecs(). This method takes one "@|
							"integer as an argument.");
	}
	return retval;
}

@ The |elapsed()| method returns an integer value.

@<Functions for scripting@>=
QScriptValue QTime_elapsed(QScriptContext *context, QScriptEngine *engine)
{
	QScriptValue retval;
	if(context->argumentCount() == 0)
	{
		QTime self = getself<QTime>(context);
		retval = QScriptValue(engine, self.elapsed());
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QTime::elapsed(). This method takes no "@|
							"arguments.");
	}
	return retval;
}

@ The |hour()|, |minute()|, |second()| and |msec()| methods return an integer
with various parts of the time. The |hour()| method is typical of these methods.

@<Functions for scripting@>=
QScriptValue QTime_hour(QScriptContext *context, QScriptEngine *engine)
{
	QScriptValue retval;
	if(context->argumentCount() == 0)
	{
		QTime self = getself<QTime>(context);
		retval = QScriptValue(engine, self.hour());
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QTime::hour(). This method takes no "@|
							"arguments.");
	}
	return retval;
}

@ The |minute()|, |second()|, and |msec()| methods are implemented similarly.

@<Functions for scripting@>=
QScriptValue QTime_minute(QScriptContext *context, QScriptEngine *engine)
{
	QScriptValue retval;
	if(context->argumentCount() == 0)
	{
		QTime self = getself<QTime>(context);
		retval = QScriptValue(engine, self.minute());
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
							"QTime::minute(). This method takes no "@|
							"arguments.");
	}
	return retval;
}

QScriptValue QTime_second(QScriptContext *context, QScriptEngine *engine)
{
	QScriptValue retval;
	if(context->argumentCount() == 0)
	{
		QTime self = getself<QTime>(context);
		retval = QScriptValue(engine, self.second());
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QTime::second(). This method takes no "@|
							"arguments.");
	}
	return retval;
}

QScriptValue QTime_msec(QScriptContext *context, QScriptEngine *engine)
{
	QScriptValue retval;
	if(context->argumentCount() == 0)
	{
		QTime self = getself<QTime>(context);
		retval = QScriptValue(engine, self.msec());
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QTime::msec(). This method takes no "@|
							"arguments.");
	}
	return retval;
}

@ The |isNull()| and |isValid()| methods return a boolean value. A |QTime| is
considered null if it was created with a constructor with no arguments. It is
considered invalid if it is null or if part of the time is out of range.

@<Functions for scripting@>=
QScriptValue QTime_isNull(QScriptContext *context, QScriptEngine *engine)
{
	QScriptValue retval;
	if(context->argumentCount() == 0)
	{
		QTime self = getself<QTime>(context);
		retval = QScriptValue(engine, self.isNull());
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QTime::isNull(). This method takes no "@|
							"arguments.");
	}
	return retval;
}

QScriptValue QTime_isValid(QScriptContext *context, QScriptEngine *engine)
{
	QScriptValue retval;
	if(context->argumentCount() == 0)
	{
		QTime self = getself<QTime>(context);
		retval = QScriptValue(engine, self.isValid());
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QTime::isValid(). This method takes no "@|
							"arguments.");
	}
	return retval;
}

@ The |secsTo()| and |msecsTo()| methods return an integer value indicating the
number of seconds or milliseconds until a |QTime| argument.

@<Functions for scripting@>=
QScriptValue QTime_msecsTo(QScriptContext *context, QScriptEngine *engine)
{
	QScriptValue retval;
	if(context->argumentCount() == 1)
	{
		QTime self = getself<QTime>(context);
		QTime arg = argument<QVariant>(0, context).toTime();
		retval = QScriptValue(engine, self.msecsTo(arg));
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QTime::msecsTo(). This method takes one QTime.");
	}
	return retval;
}

QScriptValue QTime_secsTo(QScriptContext *context, QScriptEngine *engine)
{
	QScriptValue retval;
	if(context->argumentCount() == 1)
	{
		QTime self = getself<QTime>(context);
		QTime arg = argument<QVariant>(0, context).toTime();
		retval = QScriptValue(engine, self.secsTo(arg));
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QTime::secsTo(). This method takes one QTime.");
	}
	return retval;
}

@ The |start()| and |restart()| methods each set the value of the |QTime()| to
the current time. The |restart()| method additionally returns the same value as
the |elapsed()| method.

@<Functions for scripting@>=
QScriptValue QTime_restart(QScriptContext *context, QScriptEngine *engine)
{
	QScriptValue retval;
	if(context->argumentCount() == 0)
	{
		QTime self = getself<QTime>(context);
		retval = QScriptValue(engine, self.restart());
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QTime::restart(). This method takes no "@|
							"arguments.");
	}
	return retval;
}

QScriptValue QTime_start(QScriptContext *context, QScriptEngine *)
{
	if(context->argumentCount() == 0)
	{
		QTime self = getself<QTime>(context);
		self.start();
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QTime::start(). This method takes no arguments.");
	}
	return QScriptValue();
}

@ The slightly inappropriately named |setHMS()| method changes the current value
of the time and returns a boolean to indicate if the new time value is valid.

@<Functions for scripting@>=
QScriptValue QTime_setHMS(QScriptContext *context, QScriptEngine *engine)
{
	QScriptValue retval;
	if(context->argumentCount() == 3 || context->argumentCount() == 4)
	{
		QTime self = getself<QTime>(context);
		int arg1 = 0;
		int arg2 = 0;
		int arg3 = 0;
		int arg4 = 0;
		switch(context->argumentCount())@/
		{@t\1@>@/
			case 4:@/
				arg4 = argument<int>(3, context);
			case 3:@/
				arg3 = argument<int>(2, context);
				arg2 = argument<int>(1, context);
				arg1 = argument<int>(0, context);
			default:@/
				break;@t\2@>@/
		}
		retval = QScriptValue(engine, self.setHMS(arg1, arg2, arg3, arg4));
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QTime::setHMS(). This method takes three or "@|
							"four integer arguments.");
	}
	return retval;
}

@ The |toString()| method returns a string representation of the time. See the
Qt documentation for instructions on creating a valid format string.

@<Functions for scripting@>=
QScriptValue QTime_toString(QScriptContext *context, QScriptEngine *engine)
{
	QScriptValue retval;
	if(context->argumentCount() == 1)
	{
		QTime self = getself<QTime>(context);
		retval = QScriptValue(engine, self.toString(argument<QString>(0, context)));
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QTime::toString(). This method takes one QString "@|
							"as an argument.");
	}
	return retval;
}

@ The |currentTime()| and |fromString()| methods return a new |QTime| object.
These methods make no reference to the any other existing |QTime|.

@<Functions for scripting@>=
QScriptValue QTime_currentTime(QScriptContext *, QScriptEngine *engine)
{
	QScriptValue object;
	object = engine->toScriptValue<QTime>(QTime::currentTime());
	setQTimeProperties(object, engine);
	return object;
}

QScriptValue QTime_fromString(QScriptContext *context, QScriptEngine *engine)
{
	QScriptValue object;
	if(context->argumentCount() == 2)
	{
		QString time = argument<QString>(0, context);
		QString format = argument<QString>(1, context);
		object = engine->toScriptValue<QTime>(QTime::fromString(time, format));
		setQTimeProperties(object, engine);
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
		                    "QTime::fromString(). This method takes two "@|
							"string arguments.");
	}
	return object;
}

@* Scripting Item View Classes.

\noindent |QAbstractScrollArea| is a |QFrame| that serves as the base class for
classes such as |QGraphicsView| and |QAbstractItemView|. Objects from this class
are not created directly.

@<Function prototypes for scripting@>=
void setQAbstractScrollAreaProperties(QScriptValue value,
                                      QScriptEngine *engine);

@ The implementation of this is simple.

@<Functions for scripting@>=
void setQAbstractScrollAreaProperties(QScriptValue value, QScriptEngine *engine)
{
	setQFrameProperties(value, engine);
}

@ This class is used by the |QAbstractItemView| class. This is another class
that we do not need a script constructor for.

@<Function prototypes for scripting@>=
void setQAbstractItemViewProperties(QScriptValue value, QScriptEngine *engine);

@ This function has another simple implementation.

@<Functions for scripting@>=
void setQAbstractItemViewProperties(QScriptValue value, QScriptEngine *engine)
{
	setQAbstractScrollAreaProperties(value, engine);
}

@ The |QGraphicsView| and |QTableView| classes form the base of \pn{} classes.

@<Function prototypes for scripting@>=
void setQGraphicsViewProperties(QScriptValue value, QScriptEngine *engine);
void setQTableViewProperties(QScriptValue value, QScriptEngine *engine);

@ Again, the implementations are boring.

@<Functions for scripting@>=
void setQGraphicsViewProperties(QScriptValue value, QScriptEngine *engine)
{
	setQAbstractScrollAreaProperties(value, engine);
}

void setQTableViewProperties(QScriptValue value, QScriptEngine *engine)
{
	setQAbstractItemViewProperties(value, engine);
}

@* Scripting Button Classes.

\noindent \pn{} provides an |AnnotationButton| class which is a special kind of
|QPushButton| which in turn comes from |QAbstractButton|. While
|AnnotationButton| can be used in exactly the same way as a |QPushButton|, if
an annotation is not needed, there is little reason not to use the base class.

@<Function prototypes for scripting@>=
void setQAbstractButtonProperties(QScriptValue value, QScriptEngine *engine);
void setQPushButtonProperties(QScriptValue value, QScriptEngine *engine);
QScriptValue constructQPushButton(QScriptContext *context,
                                  QScriptEngine *engine);

@ The constructor for |QPushButton| should be passed to the scripting engine.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructQPushButton);
value = engine->newQMetaObject(&QPushButton::staticMetaObject, constructor);
engine->globalObject().setProperty("QPushButton", value);

@ The implementation should seem familiar.

@<Functions for scripting@>=
QScriptValue constructQPushButton(QScriptContext *, QScriptEngine *engine)
{
	QScriptValue object = engine->newQObject(new QPushButton());
	setQPushButtonProperties(object, engine);
	return object;
}

void setQPushButtonProperties(QScriptValue value, QScriptEngine *engine)
{
	setQAbstractButtonProperties(value, engine);
}

void setQAbstractButtonProperties(QScriptValue value, QScriptEngine *engine)
{
	setQWidgetProperties(value, engine);
}

@* Scripting QSqlQuery.

\noindent With this class exposed to the host environment, it becomes possible
for script code to execute SQL queries and evaluate the result.

Rather than use |QSqlQuery| directly, however, we use a proxy \nfnote{Erich
Gamma, Richard Helm, Raph Johnson, and John
Vlissides,\par\indent\underbar{Design Patterns: elements of reusable
object-oriented software} (1995) pp. 207--217} class. This class obtains its own
database connection and handles properly closing and removing these connections
when the query object is destroyed.

@<Class declarations@>=
class SqlQueryConnection : public QSqlQuery@/
{
	public:@/
		SqlQueryConnection(const QString &query = QString());
		~SqlQueryConnection();
		QSqlQuery* operator->();
	private:@/
		QString connection;
		QSqlQuery *q;
};

@ The constructor can be somewhat simplified from the four forms of |QSqlQuery|.
We are not interested in creating an object from a |QSqlResult| or from another
|QSqlQuery|. The database connection is managed by the class itself so the
constructor only needs an optional string containing a query. This is used to
initialize a real |QSqlQuery| object.

@<SqlQueryConnection implementation@>=
SqlQueryConnection::SqlQueryConnection(const QString &query)
{
	QSqlDatabase database = AppInstance->database();
	database.open();
	q = new QSqlQuery(query, database);
	connection = database.connectionName();
}

@ The destructor handles removing the |QSqlQuery| and the database connection
associated with it. The extra brackets introduce a new scope for the
|QSqlDatabase| so that it is out of scope when the connection is removed.

@<SqlQueryConnection implementation@>=
SqlQueryConnection::~SqlQueryConnection()
{
	delete q;
	{
		QSqlDatabase database = QSqlDatabase::database(connection);
		database.close();
	}
	QSqlDatabase::removeDatabase(connection);
}

@ For all other functionality, we simply forward the request to our |QSqlQuery|
object.

@<SqlQueryConnection implementation@>=
QSqlQuery* SqlQueryConnection::operator->()
{
	return q;
}

@ In order to use this new class in the host environment, a number of functions
are needed.

@<Function prototypes for scripting@>=
void setQSqlQueryProperties(QScriptValue value, QScriptEngine *engine);
QScriptValue constructQSqlQuery(QScriptContext *context, QScriptEngine *engine);
QScriptValue QSqlQuery_bind(QScriptContext *context, QScriptEngine *engine);
QScriptValue QSqlQuery_bindDeviceData(QScriptContext *context,
                                      QScriptEngine *engine);
QScriptValue QSqlQuery_bindFileData(QScriptContext *context,
                                    QScriptEngine *engine);
QScriptValue QSqlQuery_exec(QScriptContext *context,
                            QScriptEngine *engine);
QScriptValue QSqlQuery_executedQuery(QScriptContext *context,
                                     QScriptEngine *engine);
QScriptValue QSqlQuery_invalidate(QScriptContext *context, QScriptEngine *engine);
QScriptValue QSqlQuery_next(QScriptContext *context, QScriptEngine *engine);
QScriptValue QSqlQuery_prepare(QScriptContext *context, QScriptEngine *engine);
QScriptValue QSqlQuery_value(QScriptContext *context, QScriptEngine *engine);

@ For conceptual convenience we simply pretend that we are working with a real
|QSqlQuery| object.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructQSqlQuery);
engine->globalObject().setProperty("QSqlQuery", constructor);

@ With connection creation no longer needed in the constructor, all that is
needed is object creation and applying the appropriate properties to the script
value.

@<Functions for scripting@>=
QScriptValue constructQSqlQuery(QScriptContext *, QScriptEngine *engine)
{
	QScriptValue object =
	     engine->toScriptValue<void *>(new SqlQueryConnection());
	setQSqlQueryProperties(object, engine);
	return object;
}

@ As this class does not derive from |QObject|, we must wrap all of the methods
we might want to use.

@<Functions for scripting@>=
void setQSqlQueryProperties(QScriptValue value, QScriptEngine *engine)
{
	value.setProperty("bind", engine->newFunction(QSqlQuery_bind));
	value.setProperty("bindFileData",
	                  engine->newFunction(QSqlQuery_bindFileData));
	value.setProperty("bindDeviceData",
	                  engine->newFunction(QSqlQuery_bindDeviceData));
	value.setProperty("exec", engine->newFunction(QSqlQuery_exec));
	value.setProperty("executedQuery", engine->newFunction(QSqlQuery_executedQuery));
	value.setProperty("invalidate", engine->newFunction(QSqlQuery_invalidate));
	value.setProperty("next", engine->newFunction(QSqlQuery_next));
	value.setProperty("prepare", engine->newFunction(QSqlQuery_prepare));
	value.setProperty("value", engine->newFunction(QSqlQuery_value));
}

@ Most of these properties are wrappers around existing |QSqlQuery| functions.

@<Functions for scripting@>=
QScriptValue QSqlQuery_exec(QScriptContext *context, QScriptEngine *engine)
{
	SqlQueryConnection *query = getself<SqlQueryConnection *>(context);
	QScriptValue retval;
	if(context->argumentCount() == 1)
	{
		retval = QScriptValue(engine,
		                      query->exec(argument<QString>(0, context)));
	}
	else
	{
		retval = QScriptValue(engine, query->exec());
	}
	if(query->lastError().isValid())
	{
		qDebug() << query->lastQuery();
		qDebug() << query->lastError().text();
	}
	return retval;
}

QScriptValue QSqlQuery_executedQuery(QScriptContext *context, QScriptEngine *)
{
	SqlQueryConnection *query = getself<SqlQueryConnection *>(context);
	return QScriptValue(query->lastQuery());
}

QScriptValue QSqlQuery_next(QScriptContext *context, QScriptEngine *engine)
{
	SqlQueryConnection *query = getself<SqlQueryConnection *>(context);
	return QScriptValue(engine, query->next());
}

QScriptValue QSqlQuery_value(QScriptContext *context, QScriptEngine *engine)
{
	SqlQueryConnection *query = getself<SqlQueryConnection *>(context);
	return QScriptValue(engine,
	                    query->value(argument<int>(0, context)).toString());
}

@ For prepared queries, we support binding variables available to the script,
data available in a named file, or data from any open |QIODevice|.

@<Functions for scripting@>=
QScriptValue QSqlQuery_prepare(QScriptContext *context, QScriptEngine *engine)
{
	SqlQueryConnection *query = getself<SqlQueryConnection *>(context);
	return QScriptValue(engine, query->prepare(argument<QString>(0, context)));
}

QScriptValue QSqlQuery_bind(QScriptContext *context, QScriptEngine *)
{
	SqlQueryConnection *query = getself<SqlQueryConnection *>(context);
	query->bindValue(argument<QString>(0, context),
	                 argument<QVariant>(1, context));
	return QScriptValue();
}

QScriptValue QSqlQuery_bindFileData(QScriptContext *context,
                                    QScriptEngine *)
{
	SqlQueryConnection *query = getself<SqlQueryConnection *>(context);
	QString placeholder = argument<QString>(0, context);
	QString filename = argument<QString>(1, context);
	QFile file(filename);
	QByteArray data;
	if(file.open(QIODevice::ReadOnly))
	{
		data = file.readAll();
		file.close();
	}
	query->bindValue(placeholder, data);
	return QScriptValue();
}

QScriptValue QSqlQuery_bindDeviceData(QScriptContext *context,
                                      QScriptEngine *)
{
	SqlQueryConnection *query = getself<SqlQueryConnection *>(context);
	QString placeholder = argument<QString>(0, context);
	QIODevice *device = argument<QIODevice *>(1, context);
	device->reset();
	QByteArray data;
	data = device->readAll();
	query->bindValue(placeholder, data);
	return QScriptValue();
}

@ To avoid leaking database connections, we add the |invalidate()| property
which destroys our object. The object on which this method is called must not be
used after calling this method. In script code this will typically be used as in
the following example:

{\tt query = query.invalidate();}

@<Functions for scripting@>=
QScriptValue QSqlQuery_invalidate(QScriptContext *context, QScriptEngine *)
{
	SqlQueryConnection *query = getself<SqlQueryConnection *>(context);
	delete query;
	return QScriptValue::UndefinedValue;
}

@* Other scripting functions.

\noindent There are a few functions that are exposed to the scripting engine
that are not associated with any class. Two functions are used for extracting
information from file names. Another is used to construct array values from SQL
array values. There is also a function for setting the default font for the
application or some part of the application.

@<Function prototypes for scripting@>=
QScriptValue baseName(QScriptContext *context, QScriptEngine *engine);
QScriptValue dir(QScriptContext *context, QScriptEngine *engine);
QScriptValue sqlToArray(QScriptContext *context, QScriptEngine *engine);
QScriptValue setFont(QScriptContext *context, QScriptEngine *engine);
QScriptValue annotationFromRecord(QScriptContext *context,
                                  QScriptEngine *engine);
QScriptValue setTabOrder(QScriptContext *context, QScriptEngine *engine);

@ These functions are passed to the scripting engine.

@<Set up the scripting engine@>=
engine->globalObject().setProperty("baseName", engine->newFunction(baseName));
engine->globalObject().setProperty("dir", engine->newFunction(dir));
engine->globalObject().setProperty("sqlToArray",
                                   engine->newFunction(sqlToArray));
engine->globalObject().setProperty("setFont", engine->newFunction(setFont));
engine->globalObject().setProperty("annotationFromRecord",
                                   engine->newFunction(annotationFromRecord));
engine->globalObject().setProperty("setTabOrder", engine->newFunction(setTabOrder));

@ These functions are not part of an object. They expect a string specifying
the path to a file and return a string with either the name of the file without
the path and extension or the path of the directory containing the file.

@<Functions for scripting@>=
QScriptValue baseName(QScriptContext *context, QScriptEngine *engine)
{
	QFileInfo info(argument<QString>(0, context));
	QScriptValue retval(engine, info.baseName());
	return retval;
}

QScriptValue dir(QScriptContext *context, QScriptEngine *engine)
{
	QFileInfo info(argument<QString>(0, context));
	QDir dir = info.dir();
	QScriptValue retval(engine, dir.path());
	return retval;
}

@ This function takes a string representing a SQL array and returns an array
value.

@<Functions for scripting@>=
QScriptValue sqlToArray(QScriptContext *context, QScriptEngine *engine)
{
	QString source = argument<QString>(0, context);
	source.remove(0, 1);
	source.chop(1);
	QStringList elements = source.split(",");
	QString element;
	QScriptValue dest = engine->newArray(elements.size());
	int i = 0;
	foreach(element, elements)
	{
		if(element.startsWith("\"") && element.endsWith("\""))
		{
			element.chop(1);
			element = element.remove(0, 1);
		}
		dest.setProperty(i, QScriptValue(engine, element));
		i++;
	}
	return dest;
}

@ This function can be used to set the default font for the application or on
a per-class hierarchy basis.

@<Functions for scripting@>=
QScriptValue setFont(QScriptContext *context, QScriptEngine *)
{
	QString font = argument<QString>(0, context);
	QString classname;
	if(context->argumentCount() > 1)
	{
		classname = argument<QString>(1, context);
		QApplication::setFont(QFont(font), classname.toLatin1().constData());
	}
	else
	{
		QApplication::setFont(QFont(font));
	}
	return QScriptValue();
}

@ This function was briefly used prior to adding support for |QXmlQuery| in the
host environment. The function is now depreciated and should not be used.

@<Functions for scripting@>=
QScriptValue annotationFromRecord(QScriptContext *context, QScriptEngine *)
{
	SqlQueryConnection query;
	QString q = "SELECT file FROM files WHERE id = :file";
	query.prepare(q);
	query.bindValue(":file", argument<int>(0, context));
	query.exec();
	query.next();
	QByteArray array = query.value(0).toByteArray();
	QBuffer buffer(&array);
	buffer.open(QIODevice::ReadOnly);
	QXmlQuery xquery;
	xquery.bindVariable("profile", &buffer);
	QString xq;
	xq = "for $b in doc($profile) //tuple where exists($b/annotation) return $b";
	xquery.setQuery(xq);
	QString result;
	xquery.evaluateTo(&result);
	return QScriptValue(result);
}

@ This function can be used to change the tab order for controls in Typica.
Changes to the example configuration in \pn{} 1.4 made the default handling
of tab controls in the logging window unacceptable.

@<Functions for scripting@>=
QScriptValue setTabOrder(QScriptContext *context, QScriptEngine *)
{
	QWidget::setTabOrder(argument<QWidget*>(0, context),
	                     argument<QWidget*>(1, context));
	return QScriptValue();
}

@** Application Configuration.

\noindent While \pn{} is intended as a data logging application, the diversity
of equipment and supporting technology precludes the option of providing a
single interface for common tasks. It is important that the application can be
configured to work with different roasting equipment, databases, and the like.
To accomplish this, \pn{} utilizes an XML description of the desired application
configuration and provides an ECMA-262 host environment which allows application
dataflow to be configured.

The scripting environment provides access to elements of the XML file and also
allows access to most of the application classes. A selection of classes
provided by Qt is also available. See the section on The Scripting Engine for
more details.

\danger While the code is the ultimate documentation of what is possible with
this interface, additional documentation should be provided to document the
meaning of supported elements and the objects available through the scripting
engine.\endanger

The application configuration is loaded when the program is started.

Starting with version 1.4, we check for a command line option with the path to
the configuration file and load that instead of prompting for the information
if possible.

@<Load the application configuration@>=
QStringList arguments = QCoreApplication::arguments();
int position = arguments.indexOf("-c");
QString filename = QString();
if(position != -1)
{
	if(arguments.size() >= position + 1)
	{
		filename = arguments.at(position + 1);
	}
}
if(filename.isEmpty())
{
	filename = QFileDialog::getOpenFileName(NULL, "Open Configuration File",
					settings.value("config", "").toString());
}
QDir directory;
if(!filename.isEmpty())
{
	QFile file(filename);
	QFileInfo info(filename);
	directory = info.dir();
	settings.setValue("config", directory.path());
	if(file.open(QIODevice::ReadOnly))
	{
		app.configuration()->setContent(&file, true);
	}
}
@<Substitute included fragments@>@;

@ The {\tt <application>} element can contain an arbitrary number of
{\tt <include>} elements. These elements should not appear in the DOM. Instead,
the element should be replaced by the content of the specified document.

@<Substitute included fragments@>=
QDomElement root = app.configuration()->documentElement();
QDomNodeList children = root.childNodes();
QString replacementDoc;
QDomDocument includedDoc;
QDomDocumentFragment fragment;
for(int i = 0; i < children.size(); i++)
{
	QDomNode currentNode = children.at(i);
	QDomElement currentElement;
	if(currentNode.nodeName() == "include")
	{
		currentElement = currentNode.toElement();
		if(currentElement.hasAttribute("src"))
		{
			replacementDoc = directory.path();
			replacementDoc.append('/');
			replacementDoc.append(currentElement.attribute("src"));
			QFile doc(replacementDoc);
			if(doc.open(QIODevice::ReadOnly))
			{
				includedDoc.setContent(&doc, true);
				fragment = includedDoc.createDocumentFragment();
				fragment.appendChild(includedDoc.documentElement());
				root.replaceChild(fragment, currentNode);
				doc.close();
			}
		}
	}
}

@ Simply loading the configuration document does not display a user interface or
set up any objects that allow the program to do anything. To do this, a script
obtained from the configuration document is run. The root element of the
document should be {\tt <application>}. This element should have a number of
child elements including {\tt <window>} elements which describe the various
windows that can be opened in the application and {\tt <program>} elements
containing script code. These {\tt <program>} elements can occur in a number of
different contexts including within {\tt <window>} elements which would indicate
that such scripts should be evaluated when the window being described is
created. After the configuration document is loaded, all {\tt <program>}
elements that are direct children of the {\tt <application>} element are
concatenated and the script is run.

Before the script is run and user interface elements are drawn, we also check
for {\tt <style>} elements which can be used to set up a stylesheet for the
application.

@<Find and evaluate starting script@>=
QString styleText;
QString programText;
QDomElement currentElement;
for(int i = 0; i < children.size(); i++)
{
	QDomNode currentNode = children.at(i);
	if(currentNode.nodeName() == "style")
	{
		currentElement = currentNode.toElement();
		styleText.append(currentElement.text());
	}
	else if(currentNode.nodeName() == "program")
	{
		currentElement = currentNode.toElement();
		programText.append(currentElement.text());
	}
}
app.setStyleSheet(styleText);
QScriptValue result = engine->evaluate(programText);
@<Report scripting errors@>

@ When a script is evaluated, there is a chance that there will be some error in
the execution of that script. If this occurs, we want to report that.

@<Report scripting errors@>=
if(engine->hasUncaughtException())
{
	int line = engine->uncaughtExceptionLineNumber();
	qDebug() << "Uncaught excpetion at line " << line << " : " <<
		result.toString();
	QString trace;
	foreach(trace, engine->uncaughtExceptionBacktrace())
	{
		qDebug() << trace;
	}
}

@* Creating a window.

\noindent When a configuration document is loaded, none of the {\tt <window>}
elements are interpreted or used to create a graphical user interface. Instead,
any {\tt <program>} elements that are immediate children of the
{\tt <application>} element are interpreted. In order to convert a
{\tt <window>} element into a window displayed on screen, the script in the
{\tt <program>} elements must call a function to display a specified window.

\danger This design works, but it'@q'@>s not particularly good design. It was written
under severe time constraints and should be redesigned or at least cleaned up
and reorganized.\endanger

@<Function prototypes for scripting@>=
QScriptValue createWindow(QScriptContext *context, QScriptEngine *engine);
void addLayoutToWidget(QDomElement element, QStack<QWidget*> *widgetStack,
                       QStack<QLayout*> *layoutStack);
void addLayoutToLayout(QDomElement element, QStack<QWidget *> *widgetStack,
                       QStack<QLayout *> *layoutStack);
void addSplitterToLayout(QDomElement element, QStack<QWidget *> *widgetStack,
                         QStack<QLayout *> *layoutStack);
void addSplitterToSplitter(QDomElement element, QStack<QWidget *> *widgetStack,
                           QStack<QLayout *> *layoutStack);
void populateGridLayout(QDomElement element, QStack<QWidget *> *widgetStack,
                        QStack<QLayout *> *layoutStack);
void populateBoxLayout(QDomElement element, QStack<QWidget *> *widgetStack,
                       QStack<QLayout *> *layoutStack);
void populateSplitter(QDomElement element, QStack<QWidget *> *widgetStack,@|
					  QStack<QLayout *> *layoutStack);
void populateWidget(QDomElement element, QStack<QWidget *> *widgetStack,@|
                    QStack<QLayout *> *layoutStack);
void populateStackedLayout(QDomElement element, QStack<QWidget *> *widgetStack,
                           QStack<QLayout *> *layoutStack);
void addTemperatureDisplayToSplitter(QDomElement element,@|
                                     QStack<QWidget *> *widgetStack,
									 QStack<QLayout *> *layoutStack);
void addTemperatureDisplayToLayout(QDomElement element,@|
                                   QStack<QWidget *> *widgetStack,
								   QStack<QLayout *> *layoutStack);
void addTimerDisplayToSplitter(QDomElement element,@|
                               QStack<QWidget *> *widgetStack,
							   QStack<QLayout *> *layoutStack);
void addTimerDisplayToLayout(QDomElement element,@|
                             QStack<QWidget *> *widgetStack,
							 QStack<QLayout *> *layoutStack);
void addDecorationToSplitter(QDomElement element,@|
                             QStack<QWidget *> *widgetStack,
							 QStack<QLayout *> *layoutStack);
void addDecorationToLayout(QDomElement element, QStack<QWidget *> *widgetStack,
                           QStack<QLayout *> *layoutStack);
void addWidgetToSplitter(QDomElement element, QStack<QWidget *> *widgetStack,
                         QStack<QLayout *> *layoutStack);
void addButtonToLayout(QDomElement element, QStack<QWidget *> *widgetStack,
                       QStack<QLayout *> *layoutStack);
void addZoomLogToSplitter(QDomElement element, QStack<QWidget *> *widgetStack,
                          QStack<QLayout *> *layoutStack);
void addGraphToSplitter(QDomElement element, QStack<QWidget *> *widgetStack,
                        QStack<QLayout *> *layoutStack);
void addSqlDropToLayout(QDomElement element, QStack<QWidget *> *widgetStack,
                        QStack<QLayout *> *layoutStack);
void addSaltToLayout(QDomElement element, QStack<QWidget *> *widgetStack,@|
                     QStack<QLayout *> *layoutStack);
void addLineToLayout(QDomElement element, QStack<QWidget *> *widgetStack,@|
                     QStack<QLayout *> *layoutStack);
void addTextToLayout(QDomElement element, QStack<QWidget *> *widgetStack,@|
                     QStack<QLayout *> *layoutStack);
void addSqlQueryViewToLayout(QDomElement element,
                             QStack<QWidget *> *widgetStack,
							 QStack<QLayout *> *layoutStack);
void addCalendarToLayout(QDomElement element, QStack<QWidget *> *widgetStack,
                         QStack<QLayout *> *layoutStack);
void addSpinBoxToLayout(QDomElement element, QStack<QWidget *> *widgetStack,
                        QStack<QLayout *> *layoutStack);

@ The function for creating the window must be made available to the scripting
engine.

@<Set up the scripting engine@>=
engine->globalObject().setProperty("createWindow",
                                   engine->newFunction(createWindow));

@ This function must examine the configuration document in search of the
appropriate window element, parse the contents of that element, and create a
multitude of objects, all of which must be passed to the scripting engine.

@<Functions for scripting@>=
QScriptValue createWindow(QScriptContext *context, QScriptEngine *engine)@/
{
	QString targetID = argument<QString>(0, context);
	QDomNode element;
	QScriptValue object;
	@<Find the window element@>@;
	if(!element.isNull())
	{
		@<Display the window@>@;
	}
	return object;
}

@ First we must locate the {\tt <window>} element. The most sensible way to do
this would require that each {\tt <window>} element has an ID attribute and
search the DOM tree for that ID. Unfortunately, as of this writing,
|QDomDocument::elementByID()| always returns a null element, so that won'@q'@>t work.
Instead, we search the tree for all {\tt <window>} elements and then examine
the resulting list to find the element with the appropriate ID.

@<Find the window element@>=
QDomNodeList windows =
	AppInstance->configuration()->documentElement().elementsByTagName("window");
QDomNode nullNode;
int i = 0;
element = nullNode;
while(i < windows.count())
{
	element = windows.at(i);
	QDomNamedNodeMap attributes = element.attributes();
	if(attributes.contains("id"))
	{
		if(attributes.namedItem("id").toAttr().value() == targetID)
		{
			break;
		}
	}
	element = nullNode;
	i++;
}

@ In order to display a window, we start by creating a new |ScriptQMainWindow|
and set the central widget of that window to a new |QWidget|. After this, we see
if the window element has any children and proceed to populate the window.

When creating child elements, care must be taken that all objects are descended
from the window. If an object is descended from the window and has an object
name, it will be possible for script code to recover the created object.

As of version 1.4, the window itself is given the value of its {\tt id}
attribute as an object name to facilitate automatic window geometry management.

@<Display the window@>=
ScriptQMainWindow *window = new ScriptQMainWindow;
window->setObjectName(targetID);
object = engine->newQObject(window);
setQMainWindowProperties(object, engine);
QWidget *central = new(QWidget);
central->setParent(window);
central->setObjectName("centralWidget");
window->setCentralWidget(central);
if(element.hasChildNodes())
{
	@<Process window children@>@;
}
@<Insert help menu@>@;
window->show();

@ Three element types make sense as top level children of a {\tt <window>}
element. An element representing a layout element can be used to apply that
layout to the central widget. An element representing a menu can be used to add
a menu to the window. A {\tt <program>} element can be used to specify a script
to be run after the window has been assembled.

\danger As the window comes with a blank central widget, elements representing
a widget to be used as the central widget of the window cannot be used directly
here. If only one widget is needed in the window, there is a need to create a
layout element and place that widget in the layout. Also note that there is not
enough error checking in the following code. Provide invalid input at your
peril.\endanger

Program fragments pulled from the window description are executed with the
newly created window available as {\tt this}. When such a fragment is run, the
entire description of the window will have already been evaluated and any
necessary objects created. Obtaining a child object of the window can be done
by calling |findChildObject()|.

@<Process window children@>=
QStack<QWidget*> widgetStack;
QStack<QLayout*> layoutStack;
QString windowScript;
widgetStack.push(central);
QDomNodeList windowChildren = element.childNodes();
int i = 0;
while(i < windowChildren.count())
{
	QDomNode current;
	QDomElement element;
	current = windowChildren.at(i);
	if(current.isElement())
	{
		element = current.toElement();
		if(element.tagName() == "program")
		{
			windowScript.append(element.text());
		}
		else if(element.tagName() == "layout")
		{
			addLayoutToWidget(element, &widgetStack, &layoutStack);
		}
		else if(element.tagName() == "menu")
		{
			@<Process menus@>@;
		}
	}
	i++;
}
QScriptValue oldThis = context->thisObject();
context->setThisObject(object);
QScriptValue result = engine->evaluate(windowScript);
@<Report scripting errors@>@;
context->setThisObject(oldThis);

@ Elements representing menus may provide a number of child elements
representing the items in that menu. The XML portion of the configuration will
not provide any information on what these menu items do. The contents of the
{\tt <program>} element for the window will need to request the |QAction|
objects and connect a signal from that object to the desired functionality.

One special consideration is the Reports menu. This menu will populate itself
according to its own logic and will have a {\tt type} property of
{\tt "reports"} and a {\tt src} property indicating the directory where reports
can be found.

@<Process menus@>=
QMenuBar *bar = window->menuBar();
bar->setParent(window);
bar->setObjectName("menuBar");
if(element.hasAttribute("name"))
{
	QMenu *menu = bar->addMenu(element.attribute("name"));
	menu->setParent(bar);
	if(element.hasAttribute("type"))
	{
		if(element.attribute("type") == "reports")
		{
			if(element.hasAttribute("src"))
			{
				@<Populate reports menu@>@;
			}
		}
	}
	if(element.hasChildNodes())
	{
		@<Process menu items@>@;
	}
}

@ To add items to a menu, we check for {\tt <item>} elements under the
{\tt <menu>} element and create a |QAction| for each item.

@<Process menu items@>=
QDomNodeList menuItems = element.childNodes();
int j = 0;
while(j < menuItems.count())
{
	QDomNode item = menuItems.at(j);
	if(item.isElement())
	{
		QDomElement itemElement = item.toElement();
		if(itemElement.tagName() == "item")
		{
			QAction *itemAction = new QAction(itemElement.text(), menu);
			if(itemElement.hasAttribute("id"))
			{
				itemAction->setObjectName(itemElement.attribute("id"));
			}
			if(itemElement.hasAttribute("shortcut"))
			{
				itemAction->setShortcut(itemElement.attribute("shortcut"));
			}
			menu->addAction(itemAction);
		}
		else if(itemElement.tagName() == "separator")
		{
			menu->addSeparator();
		}
	}
	j++;
}

@i helpmenu.w

@ A layout can contain a number of different elements including a variety of
widget types and other layouts. This function is responsible for applying any
layout class to the widget currently being populated and processing children of
the {\tt <layout>} element to populate that layout. External stacks are used to
keep track of which widgets and layouts are currently being populated. The
{\tt type} attribute is used to determine what sort of layout should be created.
Currently, {\tt horizontal}, {\tt vertical}, {\tt grid}, and {\tt stack} types
are supported. The first two resolve to |QBoxLayout| layouts, {\tt grid}
resolves to a |QGridLayout|, and {\tt stack} resolves to a |QStackedLayout|.

@<Functions for scripting@>=
void addLayoutToWidget(QDomElement element, QStack<QWidget*> *widgetStack,
                       QStack<QLayout*> *layoutStack)
{
	if(element.hasAttribute("type"))
	{
		@<Create and populate layout@>@;
		QWidget *widget = widgetStack->top();
		if(layout)
		{
			widget->setLayout(layout);
		}
		layoutStack->pop();
	}
}

@ As there are multiple places where a {\tt <layout>} element is parsed with
slightly different semantics, the code for creating and populating the layout is
broken out so that code written to support additional layout types only needs to
be written once.

@<Create and populate layout@>=
QLayout *layout;
QString layoutType = element.attribute("type");
if(layoutType == "horizontal")
{
	layout = new QHBoxLayout;
	layoutStack->push(layout);
	populateBoxLayout(element, widgetStack, layoutStack);
}
else if(layoutType == "vertical")
{
	layout = new QVBoxLayout;
	layoutStack->push(layout);
	populateBoxLayout(element, widgetStack, layoutStack);
}
else if(layoutType == "grid")
{
	layout = new QGridLayout;
	layoutStack->push(layout);
	populateGridLayout(element, widgetStack, layoutStack);
}
else if(layoutType == "stack")
{
	layout = new QStackedLayout;
	layoutStack->push(layout);
	populateStackedLayout(element, widgetStack, layoutStack);
}
if(element.hasAttribute("id"))
{
	layout->setObjectName(element.attribute("id"));
}
if(element.hasAttribute("spacing"))
{
	layout->setSpacing(element.attribute("spacing").toInt());
}
if(element.hasAttribute("margin"))
{
	int m = element.attribute("margin").toInt();
	layout->setContentsMargins(m, m, m, m);
}

@ Stacked layouts are a bit different from the other types. A stacked layout has
an arbitrary number of {\tt <page>} children which are just a |QWidget| which
can have the same child elements as {\tt <widget>} elements elsewhere. Only the
first page will be visible initially, however it is possible to use script code
to set the currently visible page provided that an ID is set for the layout.

@<Functions for scripting@>=
void populateStackedLayout(QDomElement element, QStack<QWidget *> *widgetStack,
                           QStack<QLayout *> *layoutStack)
{
	QDomNodeList children = element.childNodes();
	QStackedLayout *layout = qobject_cast<QStackedLayout *>(layoutStack->top());
	for(int i = 0; i < children.count(); i++)
	{
		QDomNode current;
		QDomElement currentElement;
		current = children.at(i);
		if(current.isElement())
		{
			currentElement = current.toElement();
			if(currentElement.tagName() == "page")
			{
				QWidget *widget = new QWidget;
				layout->addWidget(widget);
				widgetStack->push(widget);
				populateWidget(currentElement, widgetStack, layoutStack);
				widgetStack->pop();
			}
		}
	}
}

@ Using a grid layout is a bit different from using a box layout. Child elements
with various attributes are required to take full advantage of this layout type.
All direct children of a grid layout element should be {\tt <row>} elements
which may have optional {\tt height} and {\tt stretch} attributes which apply to
that row.

@<Functions for scripting@>=
void populateGridLayout(QDomElement element, QStack<QWidget *> *widgetStack,
                        QStack<QLayout *> *layoutStack)
{
	QDomNodeList children = element.childNodes();
	int row = -1;
	QGridLayout *layout = qobject_cast<QGridLayout *>(layoutStack->top());
	for(int i = 0; i < children.count(); i++)
	{
		QDomNode current;
		QDomElement currentElement;
		current = children.at(i);
		if(current.isElement())
		{
			currentElement = current.toElement();
			if(currentElement.tagName() == "row")
			{
				row++;
				if(currentElement.hasAttribute("height"))
				{
					layout->setRowMinimumHeight(row,
									currentElement.attribute("height").toInt());
				}
				if(currentElement.hasAttribute("stretch"))
				{
					layout->setRowStretch(row,
					               currentElement.attribute("stretch").toInt());
				}
				@<Populate grid layout row@>@;
			}
		}
	}
}

@ Each {\tt <row>} may have arbitrarily many {\tt <column>} children. A row with
nothing in it or that is entirely populated by spanning cells from previous rows
might have no children.

The {\tt <column>} element supports several optional attributes. The
{\tt column} attribute can be used to specify which column the element refers
to. Sibling {\tt <column>} elements will refer to columns farther right unless
a lower column number is specified. This does mean that it is possible to
specify the same column more than once, however actually doing so is not
recommended. The {\tt width} attribute specifies the minimum width of the
column. If multiple cells in a column specify this attribute, the last one takes
priority. Similarly, the {\tt stretch} attribute specifies the column stretch.
The {\tt rowspan} and {\tt colspan} attributes can be used for cells that span
more than one row or column. A value of |-1| can be used to have the cell span
to the last row or column in the layout.

Once the attributes of the cell are known, a |QHBoxLayout| is added to the
layout at the appropriate location in the grid and it is this layout which is
further populated by child elements. Anything that can be placed under a
{\tt <layout>} element with {\tt "horizontal"} or {\tt "vertical"} {\tt type}
attribute can be a child of a {\tt <column>} element in this context.

@<Populate grid layout row@>=
int column = -1;
QDomNodeList rowChildren = currentElement.childNodes();
for(int j = 0; j < rowChildren.count(); j++)
{
	QDomNode columnNode;
	QDomElement columnElement;
	columnNode = rowChildren.at(j);
	if(columnNode.isElement())
	{
		columnElement = columnNode.toElement();
		if(columnElement.tagName() == "column")
		{
			column++;
			if(columnElement.hasAttribute("column"))
			{
				column = columnElement.attribute("column").toInt();
			}
			if(columnElement.hasAttribute("width"))
			{
				layout->setColumnMinimumWidth(column,
				                      columnElement.attribute("width").toInt());
			}
			if(columnElement.hasAttribute("stretch"))
			{
				layout->setColumnStretch(column,
				                    columnElement.attribute("stretch").toInt());
			}
			int hspan = 1;
			int vspan = 1;
			if(columnElement.hasAttribute("rowspan"))
			{
				vspan = columnElement.attribute("rowspan").toInt();
			}
			if(columnElement.hasAttribute("colspan"))
			{
				hspan = columnElement.attribute("colspan").toInt();
			}
			QHBoxLayout *cell = new QHBoxLayout;
			layout->addLayout(cell, row, column, vspan, hspan);
			layoutStack->push(cell);
			populateBoxLayout(columnElement, widgetStack, layoutStack);
			layoutStack->pop();
		}
	}
}

@ Box layouts are populated by checking for child elements representing
supported widget types and layouts and adding these to the current layout.

@<Functions for scripting@>=
void populateBoxLayout(QDomElement element, QStack<QWidget *> *widgetStack,
                       QStack<QLayout *> *layoutStack)
{
	QDomNodeList children = element.childNodes();
	for(int i = 0; i < children.count(); i++)
	{
		QDomNode current;
		QDomElement currentElement;
		current = children.at(i);
		if(current.isElement())
		{
			currentElement = current.toElement();
			if(currentElement.tagName() == "button")
			{
				addButtonToLayout(currentElement, widgetStack, layoutStack);
			}
			else if(currentElement.tagName() == "calendar")
			{
				addCalendarToLayout(currentElement, widgetStack, layoutStack);
			}
			else if(currentElement.tagName() == "decoration")
			{
				addDecorationToLayout(currentElement, widgetStack,
				                      layoutStack);
			}
			else if(currentElement.tagName() == "layout")
			{
				addLayoutToLayout(currentElement, widgetStack, layoutStack);
			}
			else if(currentElement.tagName() == "splitter")
			{
				addSplitterToLayout(currentElement, widgetStack, layoutStack);
			}
			else if(currentElement.tagName() == "label")
			{
				QBoxLayout *layout =
					qobject_cast<QBoxLayout *>(layoutStack->top());
				QLabel *label = new QLabel(currentElement.text());
				layout->addWidget(label);
			}
			else if(currentElement.tagName() == "lcdtemperature")
			{
				addTemperatureDisplayToLayout(currentElement, widgetStack,
				                              layoutStack);
			}
			else if(currentElement.tagName() == "lcdtimer")
			{
				addTimerDisplayToLayout(currentElement, widgetStack,
				                        layoutStack);
			}
			else if(currentElement.tagName() == "line")
			{
				addLineToLayout(currentElement, widgetStack, layoutStack);
			}
			else if(currentElement.tagName() == "report")
			{
				addReportToLayout(currentElement, widgetStack, layoutStack);
			}
			else if(currentElement.tagName() == "sqldrop")
			{
				addSqlDropToLayout(currentElement, widgetStack, layoutStack);
			}
			else if(currentElement.tagName() == "sqltablearray")
			{
				addSaltToLayout(currentElement, widgetStack, layoutStack);
			}
			else if(currentElement.tagName() == "sqlview")
			{
				addSqlQueryViewToLayout(currentElement, widgetStack,
											 layoutStack);
			}
			else if(currentElement.tagName() == "textarea")
			{
				addTextToLayout(currentElement, widgetStack, layoutStack);
			}
			else if(currentElement.tagName() == "spinbox")
			{
				addSpinBoxToLayout(currentElement, widgetStack, layoutStack);
			}
			else if(currentElement.tagName() == "formarray")
			{
				addFormArrayToLayout(currentElement, widgetStack, layoutStack);
			}
			else if(currentElement.tagName() =="hscale")
			{
				addScaleControlToLayout(currentElement, widgetStack,
				                        layoutStack);
			}
			else if(currentElement.tagName() == "vscale")
			{
				addIntensityControlToLayout(currentElement, widgetStack,
				                            layoutStack);
			}
			else if(currentElement.tagName() == "webview")
			{
				addWebViewToLayout(currentElement, widgetStack, layoutStack);
			}
			else if(currentElement.tagName() == "stretch")
			{
				QBoxLayout *layout = qobject_cast<QBoxLayout *>(layoutStack->top());
				layout->addStretch();
			}
		}
	}
}

@ Box layouts support adding additional layouts to the layout. The form of the
function is very similar to |addLayoutToWidget()|.

@<Functions for scripting@>=
void addLayoutToLayout(QDomElement element, QStack<QWidget *> *widgetStack,
                       QStack<QLayout *> *layoutStack)
{
	QLayout *targetLayout = layoutStack->pop();
	QBoxLayout *boxLayout = qobject_cast<QBoxLayout *>(targetLayout);
	if(element.hasAttribute("type"))
	{
		@<Create and populate layout@>@;
		boxLayout->addLayout(layout);
		layoutStack->pop();
	}
	layoutStack->push(targetLayout);
}

@ A splitter is similar to a layout in that it manages the size and position of
one or more widgets, however it is not a layout and therefore needs to be
handled separately.

@<Functions for scripting@>=
void addSplitterToLayout(QDomElement element, QStack<QWidget *> *widgetStack,
                         QStack<QLayout *> *layoutStack)
{
	QBoxLayout *layout = qobject_cast<QBoxLayout *>(layoutStack->top());
	QSplitter *splitter = new(QSplitter);
	layout->addWidget(splitter);
	@<Set up splitter@>@;
}

@ As there are multiple places where a splitter element must be examined, the
common code is set aside.

@<Set up splitter@>=
QString orientation = element.attribute("type");
if(orientation == "horizontal")
{
	splitter->setOrientation(Qt::Horizontal);
}
else if(orientation == "vertical")
{
	splitter->setOrientation(Qt::Vertical);
}
QString id = element.attribute("id");
if(!id.isEmpty())
{
	splitter->setObjectName(id);
}
if(element.hasChildNodes())
{
	widgetStack->push(splitter);
	populateSplitter(element, widgetStack, layoutStack);
	widgetStack->pop();
}

@ When populating a splitter, it is important to note that only widgets can be
added. If a layout is needed, this can be handled by adding a |QWidget| and
applying the layout to that widget.

@<Functions for scripting@>=
void populateSplitter(QDomElement element, QStack<QWidget *> *widgetStack,@|
                      QStack<QLayout *> *layoutStack)
{
	QDomNodeList children = element.childNodes();
	for(int i = 0; i < children.count(); i++)
	{
		QDomNode current;
		QDomElement currentElement;
		current = children.at(i);
		if(current.isElement())
		{
			currentElement = current.toElement();
			if(currentElement.tagName() == "decoration")
			{
				addDecorationToSplitter(currentElement, widgetStack,
				                        layoutStack);
			}
			else if(currentElement.tagName() == "graph")
			{
				addGraphToSplitter(currentElement, widgetStack, layoutStack);
			}
			else if(currentElement.tagName() == "splitter")
			{
				addSplitterToSplitter(currentElement, widgetStack, layoutStack);
			}
			else if(currentElement.tagName() == "lcdtemperature")
			{
				addTemperatureDisplayToSplitter(currentElement, widgetStack,
				                                layoutStack);
			}
			else if(currentElement.tagName() == "lcdtimer")
			{
				addTimerDisplayToSplitter(currentElement, widgetStack,
				                          layoutStack);
			}
			else if(currentElement.tagName() == "measurementtable")
			{
				addZoomLogToSplitter(currentElement, widgetStack, layoutStack);
			}
			else if(currentElement.tagName() == "widget")
			{
				addWidgetToSplitter(currentElement, widgetStack, layoutStack);
			}
		}
	}
}

@ Adding a splitter to a splitter is similar to adding it to a layout.

@<Functions for scripting@>=
void addSplitterToSplitter(QDomElement element, QStack<QWidget *> *widgetStack,
                           QStack<QLayout *> *layoutStack)
{
	QSplitter *parent = qobject_cast<QSplitter *>(widgetStack->top());
	QSplitter *splitter = new(QSplitter);
	splitter->setParent(parent);
	parent->addWidget(splitter);
	@<Set up splitter@>@;
}

@ Temperature displays are useful to have in an application such as this. At
present, this code only supports the {\tt id} attribute. It may be useful in the
future to allow other attributes for changing default attributes of the
indicator rather than needing to pull the object from script code and set
changes there.

@<Functions for scripting@>=
void addTemperatureDisplayToSplitter(QDomElement element,@|
		                             QStack<QWidget *> *widgetStack,
									 QStack<QLayout *> *)
{
	TemperatureDisplay *display = new(TemperatureDisplay);
	if(element.hasAttribute("id"))
	{
		display->setObjectName(element.attribute("id"));
	}
	QSplitter *splitter = qobject_cast<QSplitter *>(widgetStack->top());
	splitter->addWidget(display);
}

void addTemperatureDisplayToLayout(QDomElement element,@|
								   QStack<QWidget *> *,
								   QStack<QLayout *> *layoutStack)
{
	TemperatureDisplay *display = new(TemperatureDisplay);
	if(element.hasAttribute("id"))
	{
		display->setObjectName(element.attribute("id"));
	}
	QBoxLayout *layout = qobject_cast<QBoxLayout *>(layoutStack->top());
	layout->addWidget(display);
}

@ Timer displays are similarly useful to have. The default format for a timer
display is {\tt hh:mm:ss}, but this can be changed through the {\tt format}
attribute of an {\tt <lcdtimer>} element.

@<Functions for scripting@>=
void addTimerDisplayToSplitter(QDomElement element,@|
                               QStack<QWidget *> *widgetStack,
							   QStack<QLayout *> *)
{
	TimerDisplay *display = new(TimerDisplay);
	if(element.hasAttribute("id"))
	{
		display->setObjectName(element.attribute("id"));
	}
	if(element.hasAttribute("format"))
	{
		display->setDisplayFormat(element.attribute("format"));
	}
	QSplitter *splitter = qobject_cast<QSplitter *>(widgetStack->top());
	splitter->addWidget(display);
}

void addTimerDisplayToLayout(QDomElement element,@|
                             QStack<QWidget *> *,
							 QStack<QLayout *> *layoutStack)
{
	TimerDisplay *display = new(TimerDisplay);
	if(element.hasAttribute("id"))
	{
		display->setObjectName(element.attribute("id"));
	}
	if(element.hasAttribute("format"))
	{
		display->setDisplayFormat(element.attribute("format"));
	}
	QBoxLayout *layout = qobject_cast<QBoxLayout *>(layoutStack->top());
	layout->addWidget(display);
}

@ When multiple timer or temperature displays are required, it can be useful to
provide a label to indicate just what is being measured.

@<Functions for scripting@>=
void addDecorationToLayout(QDomElement element, QStack<QWidget *> *,@|
                           QStack<QLayout *> *layoutStack)
{
	@<Set up decoration@>@;
	QBoxLayout *layout = qobject_cast<QBoxLayout *>(layoutStack->top());
	layout->addWidget(decoration);
}

void addDecorationToSplitter(QDomElement element,
                             QStack<QWidget *> *widgetStack,
							 QStack<QLayout *> *)
{
	@<Set up decoration@>@;
	QSplitter *splitter = qobject_cast<QSplitter *>(widgetStack->top());
	splitter->addWidget(decoration);
}

@ The decoration needs a label text, an orientation, and the widget to be
labeled.

@<Set up decoration@>=
QString labelText = element.attribute("name");
Qt::Orientations@, orientation = Qt::Horizontal;
if(element.hasAttribute("type"))
{
	if(element.attribute("type") == "horizontal")
	{
		orientation = Qt::Horizontal;
	}
	else if(element.attribute("type") == "vertical")
	{
		orientation = Qt::Vertical;
	}
}
@<Find widget to decorate@>@;
WidgetDecorator *decoration = new WidgetDecorator(theWidget, labelText,
												  orientation);
if(element.hasAttribute("id"))
{
	decoration->setObjectName(element.attribute("id"));
}

@ The widget to decorate should be found as a child of the {\tt <decoration>}
element.

@<Find widget to decorate@>=
QWidget *theWidget = NULL;
QDomNodeList children = element.childNodes();
for(int i = 0; i < children.count(); i++)
{
	QDomNode item = children.at(i);
	if(item.isElement())
	{
		QDomElement itemElement = item.toElement();
		if(itemElement.tagName() == "lcdtemperature")
		{
			TemperatureDisplay *display = new TemperatureDisplay;
			if(itemElement.hasAttribute("id"))
			{
				display->setObjectName(itemElement.attribute("id"));
			}
			theWidget = display;
		}
		else if(itemElement.tagName() == "lcdtimer")
		{
			TimerDisplay *display = new TimerDisplay;
			if(itemElement.hasAttribute("id"))
			{
				display->setObjectName(itemElement.attribute("id"));
			}
			if(itemElement.hasAttribute("format"))
			{
				display->setDisplayFormat(itemElement.attribute("format"));
			}
			theWidget = display;
		}
	}
}

@ As splitters cannot contain layouts directly, there is a need to allow
otherwise empty widgets to be included in a splitter for cases where a splitter
should manage several widgets together as a group. A row of annotation buttons
is an example of such a layout.

@<Functions for scripting@>=
void addWidgetToSplitter(QDomElement element, QStack<QWidget *> *widgetStack,
                         QStack<QLayout *> *layoutStack)
{
	QSplitter *splitter = qobject_cast<QSplitter *>(widgetStack->top());
	QWidget *widget = new QWidget;
	if(element.hasAttribute("id"))
	{
		widget->setObjectName(element.attribute("id"));
	}
	splitter->addWidget(widget);
	if(element.hasChildNodes())
	{
		widgetStack->push(widget);
		populateWidget(element, widgetStack, layoutStack);
		widgetStack->pop();
	}
}

void populateWidget(QDomElement element, QStack<QWidget *> *widgetStack,@|
                    QStack<QLayout *> *layoutStack)
{
	QDomNodeList children = element.childNodes();
	for(int i = 0; i < children.count(); i++)
	{
		QDomNode current;
		QDomElement currentElement;
		current = children.at(i);
		if(current.isElement())
		{
			currentElement = current.toElement();
			if(currentElement.tagName() == "layout")
			{
				addLayoutToWidget(currentElement, widgetStack, layoutStack);
			}
		}
	}
}

@ There are two types of buttons that can be added to a layout. There are normal
push buttons and there are annotation buttons. Other button types may be added
in the future.

@<Functions for scripting@>=
void addButtonToLayout(QDomElement element, QStack<QWidget *> *,@|
                       QStack<QLayout *> *layoutStack)
{
	QAbstractButton *button = NULL;
	QString text = element.attribute("name");
	if(element.hasAttribute("type"))
	{
		QString type = element.attribute("type");
		if(type == "annotation")
		{
			AnnotationButton *abutton = new AnnotationButton(text);
			if(element.hasAttribute("annotation"))
			{
				abutton->setAnnotation(element.attribute("annotation"));
			}
			if(element.hasAttribute("series"))
			{
				abutton->setTemperatureColumn(element.attribute("series").
				                              toInt());
			}
			if(element.hasAttribute("column"))
			{
				abutton->setAnnotationColumn(element.attribute("column").
				                             toInt());
			}
			button = abutton;
		}
		else if(type == "check")
		{
			button = new QCheckBox(text);
		}
		else if(type == "push")
		{
			button = new QPushButton(text);
		}
	}
	if(element.hasAttribute("id"))
	{
		button->setObjectName(element.attribute("id"));
	}
	QBoxLayout *layout = qobject_cast<QBoxLayout *>(layoutStack->top());
	layout->addWidget(button);
}

@ While annotation buttons are useful for many batch notes, a spin box is
sometimes a better input choice. There are several attributes that can be set on
a spin box. These include text to be included in the annotation before and after
the value of the spin box, the temperature and annotation columns, the range of
values available in the spin box, the precision of allowed values, and the
amount by which increment and decrement operations change the value.

@<Functions for scripting@>=
void addSpinBoxToLayout(QDomElement element, QStack<QWidget *> *,@|
                        QStack<QLayout *> *layoutStack)
{
	AnnotationSpinBox *box = new AnnotationSpinBox("", "", NULL);
	if(element.hasAttribute("pretext"))
	{
		box->setPretext(element.attribute("pretext"));
	}
	if(element.hasAttribute("posttext"))
	{
		box->setPosttext(element.attribute("posttext"));
	}
	if(element.hasAttribute("series"))
	{
		box->setTemperatureColumn(element.attribute("series").toInt());
	}
	if(element.hasAttribute("column"))
	{
		box->setAnnotationColumn(element.attribute("column").toInt());
	}
	if(element.hasAttribute("min"))
	{
		box->setMinimum(element.attribute("min").toDouble());
	}
	if(element.hasAttribute("max"))
	{
		box->setMaximum(element.attribute("max").toDouble());
	}
	if(element.hasAttribute("decimals"))
	{
		box->setDecimals(element.attribute("decimals").toInt());
	}
	if(element.hasAttribute("step"))
	{
		box->setSingleStep(element.attribute("step").toDouble());
	}
	if(element.hasAttribute("id"))
	{
		box->setObjectName(element.attribute("id"));
	}
	QBoxLayout *layout = qobject_cast<QBoxLayout *>(layoutStack->top());
	layout->addWidget(box);
}

@ Previously, in order to change a |ZoomLog| from the default set of columns,
script code would need to alter the column set. While this works fine on a Mac,
this did not work very well under Windows. For the current version, I would like
to remove the need to deal with table columns from the host environment. The
first step for this is allowing column descriptions in XML. After this, I'@q'@>d like
to remove the default column set from the widget code and provide some better
functionality for dealing with additional data sets.

When creating the |ZoomLog| here, we check for {\tt <column>} child elements
which specify the names of the columns.

@<Functions for scripting@>=
void addZoomLogToSplitter(QDomElement element, QStack<QWidget *> *widgetStack,
                          QStack<QLayout *> *)
{
	ZoomLog *widget = new ZoomLog;
	if(!widget)
	{
		qDebug() << "Error constructing widget!";
	}
	if(element.hasAttribute("id"))
	{
		widget->setObjectName(element.attribute("id"));
	}
	if(element.hasChildNodes())
	{
		QDomNodeList children = element.childNodes();
		int column = 0;
		for(int i = 0; i < children.count(); i++)
		{
			QDomNode current;
			QDomElement currentElement;
			current = children.at(i);
			if(current.isElement())
			{
				currentElement = current.toElement();
				if(currentElement.tagName() == "column")
				{
					QString text = currentElement.text();
					widget->setHeaderData(column, text);
					column++;
				}
			}
		}
	}
	QSplitter *splitter = qobject_cast<QSplitter *>(widgetStack->top());
	if(splitter)
	{
		splitter->addWidget(widget);
	}
	else
	{
		qDebug() << "Splitter not found at top of widget stack!";
	}
}

@ The last of the widgets needed to duplicate the window provided in previous
versions of \pn{} is the |GraphView|.

@<Functions for scripting@>=
void addGraphToSplitter(QDomElement element, QStack<QWidget *> *widgetStack,
                        QStack<QLayout *> *)
{
	GraphView *view = new GraphView;
	if(element.hasAttribute("id"))
	{
		view->setObjectName(element.attribute("id"));
	}
	QSplitter *splitter = qobject_cast<QSplitter *>(widgetStack->top());
	splitter->addWidget(view);
}

@ When interacting with a database, it can be useful to provide a combo box
populated by the results of a database query. One way to do this is through a
|SqlComboBox| widget.

@<Functions for scripting@>=
void addSqlDropToLayout(QDomElement element, QStack<QWidget *> *,@|
                        QStack<QLayout *> *layoutStack)
{
	SqlComboBox *box = new SqlComboBox();
	if(element.hasAttribute("data"))
	{
		box->setDataColumn(element.attribute("data").toInt());
	}
	if(element.hasAttribute("display"))
	{
		box->setDisplayColumn(element.attribute("display").toInt());
	}
	if(element.hasAttribute("showdata"))
	{
		if(element.attribute("showdata") == "true")
		{
			box->showData(true);
		}
	}
	if(element.hasAttribute("editable"))
	{
		if(element.attribute("editable") == "true")
		{
			box->setEditable(true);
		}
	}
	if(element.hasChildNodes())
	{
		QDomNodeList children = element.childNodes();
		for(int i = 0; i < children.count(); i++)
		{
			QDomNode current;
			QDomElement currentElement;
			current = children.at(i);
			if(current.isElement())
			{
				currentElement = current.toElement();
				if(currentElement.tagName() == "null")
				{
					box->addNullOption();
				}
				else if(currentElement.tagName() == "query")
				{
					box->addSqlOptions(currentElement.text());
				}
			}
		}
	}
	if(element.hasAttribute("id"))
	{
		box->setObjectName(element.attribute("id"));
	}
	QBoxLayout *layout = qobject_cast<QBoxLayout *>(layoutStack->top());
	layout->addWidget(box);
}

@ The next database aware widget that can be useful to have in \pn{} is a
{\bf S}QL {\bf A}rray {\bf L}iteral {\bf T}able. As might be apparent from the
name, this is a table view with an associated model and delegates appropriate
for creating ordered arrays to pass into a database. Each column represents an
array of values. The most common use of this is in cases where it is important
to produce multiple arrays of the same size in which each element of one array
is related to the element in the same position of another array. For example,
when roasting coffee there are times when some may want to add more than one
coffee to the roaster at a time. In order to correctly track the green coffee
inventory and so that the roasting log may have an accurate record of what is
really happening, insertions on the roasting log provide two arrays, one
representing all of the coffees being added to the roaster, the other the amount
of each of these coffees. The database can then use a trigger function to
examine these arrays and produce the necessary entries in the use table which in
turn update the record containing the amount of each green coffee currently in
stock.

While a generic |QTableView| is used here, there is a need to add functionality
specific to using this table with a |SaltModel| when obtaining this widget from
the host environment. In order to accomodate this, we add a dynamic property to
the view to identify the type of table in the absense of a unique class name.

@<Functions for scripting@>=
void addSaltToLayout(QDomElement element, QStack<QWidget *> *,@|
                     QStack<QLayout *> *layoutStack)
{
	QTableView *view = new QTableView;
	view->setProperty("tabletype", QVariant(QString("SaltTable")));
	SaltModel *model = new SaltModel(element.childNodes().count());
	if(element.hasAttribute("id"))
	{
		view->setObjectName(element.attribute("id"));
	}
	if(element.hasChildNodes())
	{
		QDomNodeList children = element.childNodes();
		int currentColumn = 0;
		for(int i = 0; i < children.count(); i++)
		{
			QDomNode current;
			QDomElement currentElement;
			current = children.at(i);
			if(current.isElement())
			{
				currentElement = current.toElement();
				if(currentElement.tagName() == "column")
				{
					if(currentElement.hasAttribute("name"))
					{
						model->setHeaderData(currentColumn, Qt::Horizontal,
						                     currentElement.attribute("name"));
					}
					if(currentElement.hasAttribute("delegate"))
					{
						@<Set column delegate from XML attribute@>@;
					}
					currentColumn++;
				}
			}
		}
	}
	view->setModel(model);
	QBoxLayout *layout = qobject_cast<QBoxLayout *>(layoutStack->top());
	layout->addWidget(view);
}

@ It is often desirable to restrict the allowed values in an entry to either a
set of specific values or to a particular type of value. Delegates can be set
on a column to enforce such restrictions.

@<Set column delegate from XML attribute@>=
if(currentElement.attribute("delegate") == "sql")
{
	@<Assign column delegate from SQL@>@;
}
else if(currentElement.attribute("delegate") == "numeric")
{
	@<Assign numeric column delegate@>@;
}

@ When using a |SaltModel|, there are times where the array values being
inserted are identification numbers representing some record that already exists
in the database. For example, the id number representing a green coffee in the
table of items. In such a case, it is beneficial to provide a delegate capable
of presenting a human readable list of choices.

@<Assign column delegate from SQL@>=
SqlComboBoxDelegate *delegate = new SqlComboBoxDelegate;
SqlComboBox *widget = new SqlComboBox();
if(currentElement.hasAttribute("null"))
{
	if(currentElement.attribute("null") == "true")
	{
		widget->addNullOption();
	}
}
if(currentElement.hasAttribute("showdata"))
{
	if(currentElement.attribute("showdata") == "true")
	{
		widget->showData(true);
	}
}
if(currentElement.hasAttribute("data"))
{
	widget->setDataColumn(currentElement.attribute("data").toInt());
}
if(currentElement.hasAttribute("display"))
{
	widget->setDisplayColumn(currentElement.attribute("display").toInt());
}
widget->addSqlOptions(currentElement.text());
delegate->setWidget(widget);
view->setItemDelegateForColumn(currentColumn, delegate);

@ Another common use is allowing numeric values. At present this only
restricts input to numbers, however it may be useful to provide other options
such as restricting the range of allowed values in the future.

@<Assign numeric column delegate@>=
NumericDelegate *delegate = new NumericDelegate;
view->setItemDelegateForColumn(currentColumn, delegate);

@ The |NumericDelegate| will only set the display value to a number, but it
will perform mathematical calculations that are entered into the editor as
well. This allows a person to type something like $13.26+5.06$ with the result
of the expression ($18.32$) appearing in the table.

@<Class declarations@>=
class NumericDelegate : public QItemDelegate@/
{
	@[Q_OBJECT@]@;
	public:@/
		NumericDelegate(QObject *parent = NULL);
		QWidget *createEditor(QWidget *parent,
		                      const QStyleOptionViewItem &option,@|
							  const QModelIndex &index) const;
		void setEditorData(QWidget *editor, const QModelIndex &index) const;
		void setModelData(QWidget *editor, QAbstractItemModel *model,@|
		                  const QModelIndex &index) const;
		void updateEditorGeometry(QWidget *editor,
		                          const QStyleOptionViewItem &option,@|
								  const QModelIndex &index) const;
};

@ There is nothing special about the constructor.

@<NumericDelegate implementation@>=
NumericDelegate::NumericDelegate(QObject *parent) :
	QItemDelegate(parent)
{
	/* Nothing needs to be done here. */
}

@ Two roles are used by this delegate. The edit role should contain whatever
text has been entered in the editor while the display role contain the numeric
result of any expression that has been entered. Our editor only requires the
first of these.

@<NumericDelegate implementation@>=
void NumericDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
	QString value = index.model()->data(index, Qt::EditRole).toString();
	QLineEdit *line = static_cast<QLineEdit*>(editor);
	line->setText(value);
}

@ When editing is finished, the expression text must be saved back to the
model and the expression should be evaluated to set the display role. We make
use of the existing scripting engine to evaluate the expression, but only
preserve the result in the display role if the result of that expression is
numeric.

@<NumericDelegate implementation@>=
void NumericDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
	QLineEdit *line = static_cast<QLineEdit*>(editor);
	model->setData(index, line->text(), Qt::EditRole);
	QScriptEngine *engine = AppInstance->engine;
	engine->pushContext();
	QString script = QString("Number(%1)").arg(line->text());
	QScriptValue result = engine->evaluate(line->text());
	if(result.isNumber())
	{
		model->setData(index, result.toVariant(), Qt::DisplayRole);
	}
	else
	{
		model->setData(index, QVariant(), Qt::DisplayRole);
	}
	engine->popContext();
}

@ There is nothing special about the line edit used for this.

@<NumericDelegate implementation@>=
QWidget* NumericDelegate::createEditor(QWidget *parent,
                                       const QStyleOptionViewItem &,
									   const QModelIndex &) const
{
	return (new QLineEdit(parent));
}

@ To ensure that the editor is displayed appropriately, we must pass the
geometry data to our editor.

@<NumericDelegate implementation@>=
void NumericDelegate::updateEditorGeometry(QWidget *editor,
                                           const QStyleOptionViewItem &option,
										   const QModelIndex &) const
{
	editor->setGeometry(option.rect);
}

@ Line edits are useful when the user is expected to enter text without a
predetermined set of values.

Several attributes are supported on line edits. In addition to the usual
{\tt id} attribute, there is also a {\tt writable} attribute which, if
{\tt false}, can be used to create read only text areas which can only be edited
from script code. A {\tt validator} attribute allows entered text to be
restricted. This can take one of three values. If the value is {\tt "numeric"},
input is restricted to numeric values. If the value is {\tt "integer"}, input is
restricted to integer values. Finally, if the value is {\tt "expression"}, input
is restricted to text which matches a regular expression specified as the value
of the {\tt expression} attribute.

@<Functions for scripting@>=
void addLineToLayout(QDomElement element, QStack<QWidget *> *,@|
                     QStack<QLayout *> *layoutStack)
{
	QLineEdit *widget = new QLineEdit(element.text());
	if(element.hasAttribute("id"))
	{
		widget->setObjectName(element.attribute("id"));
	}
	if(element.hasAttribute("writable"))
	{
		if(element.attribute("writable") == "false")
		{
			widget->setReadOnly(true);
		}
	}
	if(element.hasAttribute("validator"))
	{
		if(element.attribute("validator") == "numeric")
		{
			widget->setValidator(new QDoubleValidator(NULL));
		}
		else if(element.attribute("validator") == "integer")
		{
			widget->setValidator(new QIntValidator(NULL));
		}
		else if(element.attribute("validator") == "expression" &&
		        element.hasAttribute("expression"))
		{
			widget->setValidator(new QRegExpValidator(
			                         QRegExp(element.attribute("expression")),
									                  NULL));
		}
	}
	QBoxLayout *layout = qobject_cast<QBoxLayout *>(layoutStack->top());
	layout->addWidget(widget);
}

@ It is natural for certain database fields to enter potentially large amounts
of free form text, for example, notes and annotations.

@<Functions for scripting@>=
void addTextToLayout(QDomElement element, QStack<QWidget *> *,@|
                     QStack<QLayout *> *layoutStack)
{
	QTextEdit *widget = new QTextEdit;
	if(element.hasAttribute("id"))
	{
		widget->setObjectName(element.attribute("id"));
	}
	QBoxLayout *layout = qobject_cast<QBoxLayout *>(layoutStack->top());
	layout->addWidget(widget);
}

@ The common use of |SqlQueryView| calls for the possibility of changing the
query during use. As such, there is little reason to accept attributes other
than an id for obtaining the view in a script.

@<Functions for scripting@>=
void addSqlQueryViewToLayout(QDomElement element,
                             QStack<QWidget *> *,@|
							 QStack<QLayout *> *layoutStack)
{
	SqlQueryView *view = new SqlQueryView;
	if(element.hasAttribute("id"))
	{
		view->setObjectName(element.attribute("id"));
	}
	QBoxLayout *layout = qobject_cast<QBoxLayout *>(layoutStack->top());
	layout->addWidget(view);
}

@ When the user is expected to enter a date, it is appropriate to use a date
editor. This one provides a calendar.

@<Functions for scripting@>=
void addCalendarToLayout(QDomElement element, QStack<QWidget *> *,@|
                         QStack<QLayout *> *layoutStack)
{
	QDateEdit *widget = new QDateEdit;
	widget->setCalendarPopup(true);
	if(element.hasAttribute("id"))
	{
		widget->setObjectName(element.attribute("id"));
	}
	widget->setDate(QDate::currentDate());
	QBoxLayout *layout = qobject_cast<QBoxLayout *>(layoutStack->top());
	layout->addWidget(widget);
}

@ Some additional properties are added to this object when it is retrieved by
the host environment.

@<Functions for scripting@>=
void setQDateEditProperties(QScriptValue value, QScriptEngine *engine)
{
	setQDateTimeEditProperties(value, engine);
}

void setQDateTimeEditProperties(QScriptValue value, QScriptEngine *engine)
{
	setQAbstractSpinBoxProperties(value, engine);
	value.setProperty("setDate", engine->newFunction(QDateTimeEdit_setDate));
	value.setProperty("day", engine->newFunction(QDateTimeEdit_day));
	value.setProperty("month", engine->newFunction(QDateTimeEdit_month));
	value.setProperty("year", engine->newFunction(QDateTimeEdit_year));
}

@ Certain operations on a |QDateEdit| are easier with a few convenience
properties that bypass the need to use the built in |date| property. For
example, an editor that should be set to 1 January of the current year can
obtain the year and set the date without directly using a |QDate| object.

@<Functions for scripting@>=
QScriptValue QDateTimeEdit_setDate(QScriptContext *context, QScriptEngine *)
{
	QDateTimeEdit *self = getself<QDateTimeEdit *>(context);
	if(context->argumentCount() == 3)
	{
		self->setDate(QDate(argument<int>(0, context),
		                    argument<int>(1, context),
							argument<int>(2, context)));
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "
		"QDateTimeEdit::setDate(). This method takes three integer arguments "
		"specifying the year, month, and day.");
	}
	return QScriptValue();
}

QScriptValue QDateTimeEdit_day(QScriptContext *context, QScriptEngine *)
{
	QDateTimeEdit *self = getself<QDateTimeEdit *>(context);
	return QScriptValue(self->date().day());
}

QScriptValue QDateTimeEdit_month(QScriptContext *context, QScriptEngine *)
{
	QDateTimeEdit *self = getself<QDateTimeEdit *>(context);
	return QScriptValue(self->date().month());
}

QScriptValue QDateTimeEdit_year(QScriptContext *context, QScriptEngine *)
{
	QDateTimeEdit *self = getself<QDateTimeEdit *>(context);
	return QScriptValue(self->date().year());
}

@ A few function prototypes are needed for this.

@<Function prototypes for scripting@>=
void setQDateEditProperties(QScriptValue value, QScriptEngine *engine);
void setQDateTimeEditProperties(QScriptValue value, QScriptEngine *engine);
QScriptValue QDateTimeEdit_setDate(QScriptContext *context,
                                   QScriptEngine *engine);
QScriptValue QDateTimeEdit_day(QScriptContext *context, QScriptEngine *engine);
QScriptValue QDateTimeEdit_month(QScriptContext *context,
                                 QScriptEngine *engine);
QScriptValue QDateTimeEdit_year(QScriptContext *context, QScriptEngine *engine);

@ In order to get to objects created from the XML description, it is necessary
to provide a function that can be called to retrieve children of a given widget.
When providing such an object to the script, it is necessary to determine the
type of that object and add the appropriate properties.

@<Function prototypes for scripting@>=
QScriptValue findChildObject(QScriptContext *context, QScriptEngine *engine);

@ This function must be made available to the scripting engine.

@<Set up the scripting engine@>=
engine->globalObject().setProperty("findChildObject",
								   engine->newFunction(findChildObject));

@ This function takes a script value representing some object which may have
been created from an XML description and a string containing the name of the
requested child element.

@<Functions for scripting@>=
QScriptValue findChildObject(QScriptContext *context, QScriptEngine *engine)
{
	QObject *parent = argument<QObject *>(0, context);
	QString name = argument<QString>(1, context);
	QObject *object = parent->findChild<QObject *>(name);
	QScriptValue value;
	if(object)
	{
		value = engine->newQObject(object);
		QString className = object->metaObject()->className();
		@<Set object properties based on class name@>@;
	}
	return value;
}

@ Properties are added for a large number of class types.

@<Set object properties based on class name@>=
if(className == "TemperatureDisplay")
{
	setTemperatureDisplayProperties(value, engine);
}
else if(className == "TimerDisplay")
{
	setTimerDisplayProperties(value, engine);
}
else if(className == "QAction")
{
	setQActionProperties(value, engine);
}
else if(className == "QBoxLayout")
{
	setQBoxLayoutProperties(value, engine);
}
else if(className == "QDateEdit")
{
	setQDateEditProperties(value, engine);
}
else if(className == "QFrame")
{
	setQFrameProperties(value, engine);
}
else if(className == "QHBoxLayout")
{
	setQBoxLayoutProperties(value, engine);
}
else if(className == "QLCDNumber")
{
	setQLCDNumberProperties(value, engine);
}
else if(className == "QMenu")
{
	setQMenuProperties(value, engine);
}
else if(className == "QMenuBar")
{
	setQMenuBarProperties(value, engine);
}
else if(className == "QPushButton")
{
	setQPushButtonProperties(value, engine);
}
else if(className == "QSplitter")
{
	setQSplitterProperties(value, engine);
}
else if(className == "QTableView")
{
	if(object->property("tabletype").isValid())
	{
		if(object->property("tabletype").toString() == "SaltTable")
		{
			setSaltTableProperties(value, engine);
		}
	}
}
else if(className == "QVBoxLayout")
{
	setQBoxLayoutProperties(value, engine);
}
else if(className == "QWidget")
{
	setQWidgetProperties(value, engine);
}
else if(className == "ScriptQMainWindow")
{
	setQMainWindowProperties(value, engine);
}
else if(className == "SqlComboBox")
{
	setSqlComboBoxProperties(value, engine);
}
else if(className == "SqlQueryView")
{
	setSqlQueryViewProperties(value, engine);
}
else if(className == "ZoomLog")
{
	setZoomLogProperties(value, engine);
}
else if(className == "QTextEdit")
{
	setQTextEditProperties(value, engine);
}
else if(className == "QWebView")
{
	setQWebViewProperties(value, engine);
}
else if(className == "QLineEdit")
{
	setQLineEditProperties(value, engine);
}

@ In the list of classes, the SaltTable entry is for a class which does not
strictly exist on its own. It is, however, useful to provide some custom
properties when passing such an object to the host environment.

@<Function prototypes for scripting@>=
void setSaltTableProperties(QScriptValue value, QScriptEngine *engine);
QScriptValue SaltTable_bindableColumnArray(QScriptContext *context,
                                           QScriptEngine *engine);
QScriptValue SaltTable_bindableQuotedColumnArray(QScriptContext *context,
                                                 QScriptEngine *engine);
QScriptValue SaltTable_columnSum(QScriptContext *context,
                                 QScriptEngine *engine);
QScriptValue SaltTable_columnArray(QScriptContext *context,
                                   QScriptEngine *engine);
QScriptValue SaltTable_data(QScriptContext *context, QScriptEngine *engine);
QScriptValue SaltTable_model(QScriptContext *context, QScriptEngine *engine);
QScriptValue SaltTable_quotedColumnArray(QScriptContext *context,
                                         QScriptEngine *engine);
QScriptValue SaltTable_setData(QScriptContext *context, QScriptEngine *engine);

@ There are times when it is useful to obtain the sum of values in a column of
a SaltTable object. For example, when a column represents the weight of the
green coffee used in a batch, a sum of that column provides the total weight of
the batch which, when presented to the user, can be used to catch errors in
measuring batches or entering data.

@<Functions for scripting@>=
QScriptValue SaltTable_columnSum(QScriptContext *context, QScriptEngine *engine)
{
	QTableView *self = getself<QTableView *>(context);
	SaltModel *model = qobject_cast<SaltModel *>(self->model());
	QString datum;
	double total = 0.0;
	int column = argument<int>(0, context);
	int role = argument<int>(1, context);
	for(int i = 0; i < model->rowCount(); i++)
	{
		datum = model->data(model->index(i, column), role).toString();
		if(!datum.isEmpty())
		{
			total += datum.toDouble();
		}
	}
	return QScriptValue(engine, total);
}

@ Another common use of the SaltTable is producing the text for an array literal
to pass into a SQL query. The |SaltModel| used by this table makes this simple.
There are four functions for this functionality for different use cases.

@<Functions for scripting@>=
QScriptValue SaltTable_columnArray(QScriptContext *context,
                                   QScriptEngine *engine)
{
	QTableView *self = getself<QTableView *>(context);
	SaltModel *model = qobject_cast<SaltModel *>(self->model());
	int column = argument<int>(0, context);
	int role = argument<int>(1, context);
	QString literal = model->arrayLiteral(column, role);
	return QScriptValue(engine, literal);
}

QScriptValue SaltTable_quotedColumnArray(QScriptContext *context,
                                         QScriptEngine *engine)
{
	QTableView *self = getself<QTableView *>(context);
	SaltModel *model = qobject_cast<SaltModel *>(self->model());
	int column = argument<int>(0, context);
	int role = argument<int>(1, context);
	QString literal = model->quotedArrayLiteral(column, role);
	return QScriptValue(engine, literal);
}

QScriptValue SaltTable_bindableColumnArray(QScriptContext *context,
                                           QScriptEngine *engine)
{
	QTableView *self = getself<QTableView *>(context);
	SaltModel *model = qobject_cast<SaltModel *>(self->model());
	int column = argument<int>(0, context);
	int role = argument<int>(1, context);
	QString literal = model->arrayLiteral(column, role);
	literal.chop(1);
	literal = literal.remove(0, 1);
	return QScriptValue(engine, literal);
}

QScriptValue SaltTable_bindableQuotedColumnArray(QScriptContext *context,
                                                 QScriptEngine *engine)
{
	QTableView *self = getself<QTableView *>(context);
	SaltModel *model = qobject_cast<SaltModel *>(self->model());
	int column = argument<int>(0, context);
	int role = argument<int>(1, context);
	QString literal = model->quotedArrayLiteral(column, role);
	literal.chop(1);
	literal = literal.remove(0, 1);
	return QScriptValue(engine, literal);
}

@ In order to obtain signals related to changes in the model, we need a way to
get to the model from the host environment.

@<Functions for scripting@>=
QScriptValue SaltTable_model(QScriptContext *context, QScriptEngine *engine)
{
	QTableView *self = getself<QTableView *>(context);
	QScriptValue value = engine->newQObject(self->model());
	return value;
}

@ While this table was originally intended strictly for user input, there are a
few use cases in which it is useful to allow scripts to set the values in the
table. This can be done with |setData|. This method takes four arguments: the
row and column of the table being set, the value to set, and the role of the
data being set.

@<Functions for scripting@>=
QScriptValue SaltTable_setData(QScriptContext *context, QScriptEngine *)
{
	QTableView *self = getself<QTableView *>(context);
	int row = argument<int>(0, context);
	int column = argument<int>(1, context);
	QVariant value = argument<QVariant>(2, context);
	int role = argument<int>(3, context);
	SaltModel *model = qobject_cast<SaltModel *>(self->model());
	QModelIndex cell = model->index(row, column);
	model->setData(cell, value, role);
	self->update(cell);
	return QScriptValue();
}

@ It is sometimes useful to obtain the data from a single cell of the table.
This can be done with the |data()| property.

@<Functions for scripting@>=
QScriptValue SaltTable_data(QScriptContext *context, QScriptEngine *engine)
{
	QTableView *self = getself<QTableView *>(context);
	int row = argument<int>(0, context);
	int column = argument<int>(1, context);
	int role = argument<int>(2, context);
	SaltModel *model = qobject_cast<SaltModel *>(self->model());
	QModelIndex cell = model->index(row, column);
	QVariant value = model->data(cell, role);
	QScriptValue retval = engine->newVariant(value);
	retval.setProperty("value", QScriptValue(value.toString()));
	return retval;
}

@ These functions need to be added as properties of the table when it is passed
to the host environment.

@<Functions for scripting@>=
void setSaltTableProperties(QScriptValue value, QScriptEngine *engine)
{
	setQWidgetProperties(value, engine);
	value.setProperty("columnArray",
	                  engine->newFunction(SaltTable_columnArray));
	value.setProperty("quotedColumnArray",
	                  engine->newFunction(SaltTable_quotedColumnArray));
	value.setProperty("bindableColumnArray",
	                  engine->newFunction(SaltTable_bindableColumnArray));
	value.setProperty("bindableQuotedColumnArray",
	                  engine->newFunction(SaltTable_bindableQuotedColumnArray));
	value.setProperty("columnSum", engine->newFunction(SaltTable_columnSum));
	value.setProperty("data", engine->newFunction(SaltTable_data));
	value.setProperty("model", engine->newFunction(SaltTable_model));
	value.setProperty("setData", engine->newFunction(SaltTable_setData));
}

@ The |SqlComboBox| is another class that is not constructed from scripts but is
useful to access from them. A property is added to obtain the current user data
from the widget.

@<Function prototypes for scripting@>=
void setSqlComboBoxProperties(QScriptValue value, QScriptEngine *engine);
void setQComboBoxProperties(QScriptValue value, QScriptEngine *engine);
QScriptValue QComboBox_currentData(QScriptContext *context,
                                   QScriptEngine *engine);
QScriptValue QComboBox_addItem(QScriptContext *context, QScriptEngine *engine);
QScriptValue QComboBox_setModel(QScriptContext *context, QScriptEngine *engine);
QScriptValue QComboBox_findText(QScriptContext *context, QScriptEngine *engine);

@ These functions should seem familiar by now.

@<Functions for scripting@>=
void setSqlComboBoxProperties(QScriptValue value, QScriptEngine *engine)
{
	setQComboBoxProperties(value, engine);
}

void setQComboBoxProperties(QScriptValue value, QScriptEngine *engine)
{
	setQWidgetProperties(value, engine);
	value.setProperty("currentData",
	                  engine->newFunction(QComboBox_currentData));
	value.setProperty("addItem", engine->newFunction(QComboBox_addItem));
	value.setProperty("setModel", engine->newFunction(QComboBox_setModel));
	value.setProperty("findText", engine->newFunction(QComboBox_findText));
}

QScriptValue QComboBox_currentData(QScriptContext *context,
                                   QScriptEngine *engine)
{
	QComboBox *self = getself<QComboBox *>(context);
	return QScriptValue(engine,
	                    self->itemData(self->currentIndex()).toString());
}

QScriptValue QComboBox_addItem(QScriptContext *context, QScriptEngine *)
{
	QComboBox *self = getself<QComboBox *>(context);
	self->addItem(argument<QString>(0, context));
	return QScriptValue();
}

QScriptValue QComboBox_setModel(QScriptContext *context, QScriptEngine *)
{
	QComboBox *self = getself<QComboBox *>(context);
	self->setModel(argument<QAbstractItemModel *>(0, context));
	return QScriptValue();
}

QScriptValue QComboBox_findText(QScriptContext *context, QScriptEngine *engine)
{
	QComboBox *self = getself<QComboBox *>(context);
	return QScriptValue(engine, self->findText(argument<QString>(0, context)));
}

@i abouttypica.w

@** A representation of temperature measurements.

\noindent Most of the information in a roast log will be temperature
measurements. These measurements are made of two components: the measured
temperature and the time at which that measurement was taken.

Measurement times are represented as instances of |QTime|.

@i units.w

@ We will require the |units.h| header.

@<Header files to include@>=
#include "units.h"

@i measurement.w

@** The Main Measurement Pipeline.

\noindent Measurements are sent through \pn{} in a way similar to liquid moving
through a series of connected pipes. \pn{} is not something that you just dump
measurements on. It'@q'@>s not a big truck\nfnote{Senator Ted Stevens (R-Alaska) on
network neutrality, June 28, 2006\par
\hbox{\indent\pdfURL{http://media.publicknowledge.org/stevens-on-nn.mp3}%
{http://media.publicknowledge.org/stevens-on-nn.mp3}}}. In most cases the
connections between classes (represented by arrows in Figure \secno) are made
with Qt'@q'@>s signals and slots mechanism\nfnote{Qt 4.4.3: Signals and Slots\par
\hbox{\indent\pdfURL{http://doc.trolltech.com/4.4/signalsandslots.html}%
{http://doc.trolltech.com/4.4/signalsandslots.html}}}, but
these
connections can
also be made through direct function calls as is the case with the connection
between |ZoomLog| and |MeasurementModel|.

\medskip

\includegraphics{pipes}

\smallskip

\centerline{Figure \secno: Example Flow of Measurement objects in \pn}

\medskip

Please note that Figure \secno~is representative of a typical configuration. Now
that the flow of measurements through \pn{} is determined by a script specified
by the user, whatever pipeline is needed can be specified at run time.

@* The DAQ class.

\noindent The |DAQ| class represents a piece of hardware that allows the
computer to read measurements from one or more thermocouples. Presently this
class is only handles continuous sampling on devices from National Instruments.
It should be simple to modify this class to handle similar devices from other
vendors.

Each device is represented by a single instance of this class. Multiple channels
can be used on a device if the device supports it.

Two enumerations are declared in this class to be used as arguments to
|newChannel()|. The first is used to set the measurement unit for the channel.
As the measurements themselves do not carry this information, it is important to
keep track of this information. The values come from {\tt nidaqmxbase.h} and can
be used to select among Fahrenheit, Celsius, Kelvin, and Rankine. The
second enumeration, |ThermocoupleType|, should be used to specify the type of
thermocouple connected to the device. If this does not match reality, the
measurements will not be correct. The meanings of the values should be obvious
from the names.

\danger When this class was originally written the method of thread handling
used was considered appropriate. New functionality in |QThread| has made this
no longer the case. This class is currently planned for depreciation once a
replacement class hierarchy more suited to multiple hardware types is available
however if this is not ready soon it may be beneficial to rewrite this class to
conform to current best practices.\endanger

@<Class declarations@>=
class Channel;
class DAQImplementation;@/

class DAQ : public QObject@;@/
{@t\1@>@/
	Q_OBJECT@/
	Q_ENUMS(ThermocoupleType)@;@/
	DAQImplementation *imp;@/
	@t\4@>private slots@t\kern-3pt@>:@/
		void threadFinished();
	public:@;
		DAQ(QString device, const QString &driver = QString("nidaqmxbase"));
		~DAQ();@/
		Channel* newChannel(int units, int thermocouple);@/
		@[Q_INVOKABLE@,@, void@]@, setClockRate(double Hz);@t\2\2@>@/
		@[Q_INVOKABLE@,@, void@]@, start();@t\2\2@>@/
		@[Q_INVOKABLE@]@, void stop();
		enum ThermocoupleType@/
		{
			@!TypeJ = 10072,
			@!TypeK = 10073,
			@!TypeN = 10077,
			@!TypeR = 10082,
			@!TypeS = 10085,
			@!TypeT = 10086,
			@!TypeB = 10047,
			@!TypeE = 10055
		};@t\2@>@/
}@t\kern-3pt@>;

@ The |DAQ| class has as a private member an instance of a class called
|DAQImplementation|. The two classes together create and run a new thread of
execution. This thread spends most of its time blocking while waiting for a new
measurement to become available. When a new measurement is available, that
measurement is passed to the appropriate channel which in turn passes it to any
interested object.

@<Class declarations@>=
class DAQImplementation : public QThread@;@/
{@;
	Q_OBJECT@;@/
	public:@;
		DAQImplementation(const QString &driverinfo);
		~DAQImplementation();
		void run();
		void measure();
		@<Library function pointers@>@;
		@<DAQImplementation member data@>@;
}@+@t\kern-3pt@>;

@ In order to solve some minor problems, NI-DAQmxBase is no longer linked at
compile time. Rather, this is now linked at runtime through a |QLibrary| object.
In order to use functions from this library, these functions must be stored in
function pointers. Fortunately, all of these functions can be expressed with the
same pointer type. Unfortunately, this way of doing things offers very little
debugging information in the event that something is not quite right.

@<Library function pointers@>=
typedef int (*daqfp)(...);
daqfp read;
daqfp errorInfo;
daqfp startTask;
daqfp createTask;
daqfp createChannel;
daqfp setClock;
daqfp stopTask;
daqfp clearTask;
daqfp resetDevice;
daqfp waitForMeasurement;

@ |DAQImplementation| also maintains information about the device and the
channels the measurements are sent to.

@<DAQImplementation member data@>=
bool useBase;
QString device;
QVector<Channel*> channelMap;
unsigned int handle;@/
int error;
int channels;
bool ready;
QLibrary driver;
QVector<Units::Unit> unitMap;

@ Most of the interesting work associated with the |DAQ| class is handled in
the |measure()| method of |DAQImplementation|. This function will block until a
measurement is available. Once |buffer| is filled by |DAQmxBaseReadAnalogF64()|
that function returns and new |Measurement| objects are created based on the
information in the buffer. These measurements are sent to |Channel| objects
tracked by |channelMap|.

Up until version 1.0.7 there was a bug in this code that would prevent the code
from working when more than one channel is requested. This has been corrected.

With version 1.0.9, time measurement is moved out of the loop, reducing the
number of calls in cases of more than 1 measurement and ensuring that all
simultaneously obtained measurements have the same time stamp.

@<DAQ Implementation@>=
void DAQImplementation::measure()@t\2@>@/
@t\4@>{@/
	int samplesRead = 0;
	double buffer[channels];
	error = read((unsigned int)(handle), (signed long)(1), (double)(10.0),
                 (unsigned long)(0), buffer, (unsigned long)(channels),
			     &samplesRead, (signed long)(0));
	if(error)@/
	@t\1@>{@/
		ready = false;@t\2@>@/
	}
	else@/
	{
		if(samplesRead)@/
		{
			QTime time = QTime::currentTime();@/
			for(int i = 0; i < samplesRead; i++)@/
			{
				for(int j = 0; j < channels; j++)@/
				{
					Measurement measure(buffer[@,j+(i*channels)], time,
									    unitMap[j]);
					channelMap[@,j]->input(measure);
				}
			}
		}
	}
@t\4@>}

@ It was noted that |DAQmxBaseReadAnalogF64()| blocks until it is able to fill
the |buffer| passed to it. To prevent this behavior from having adverse effects
on the rest of the program, measure is called from a loop running in its own
thread of execution. When the thread is started, it begins its execution from
the |run()| method of |DAQImplementation| which overrides the |run()| method of
|QThread|. Here the priority of the thread is set in an attempt to cut down on
the variation in time between recorded measurements.

The while loop is controlled by |ready| which is set to |false| when there is an
error in collecting a measurement or when the user wants to exit the program. It
could also be set to |false| when the |DAQ| is reconfigured.

@<DAQ Implementation@>=
void DAQImplementation::run()
{
	setPriority(QThread::TimeCriticalPriority);
	while(ready)
	{
		measure();
	}
}

@ When this loop exits, |DAQImplementation| emits a finished signal to indicate
that the thread is no longer running. This could be due to perfectly normal
conditions, but there could also be a problem that the user must be informed of.
That signal is connected to a function that checks for error conditions and
reports them if needed.

@<DAQ Implementation@>=
void DAQ::threadFinished()
{
	if(imp->error)
	{
		@<Display DAQ Error@>@;
	}
}

@ Errors are displayed with a |QMessageBox|. NIDAQmxBase provides the message
strings for these errors, but this should probably change as these error strings
are generally completely unrelated to what the problem really is. For example,
``Error: -1'' usually means that the device is not plugged in.
``Error: -200170'' usually means that \pn{} or another program using the device
did not exit cleanly. A table of replacement warning messages should be added to
this program.

\bigskip

\settabs 5 \columns
\+Error Code & NIDAQmxBase Text & & Likely Cause\cr
\+\hrulefill & \hrulefill & \hrulefill & \hrulefill & \hrulefill & \hrulefill\cr
\+ -1 & Not implemented for this device & & The device is not plugged in.\cr
\+ & type. & \cr
\+ -200170 & Physical channel specified & & The program did not exit cleanly\cr
\+ & does not exist on this device. & & or another program is using the\cr
\+ & Refer to the documentation for & & device.\cr
\+ & channels available on this device.\cr
\+ -1073807194 & {\it{(No text)}} & & The device has been unplugged.\cr

\medskip

\centerline{Table \secno: Error codes, text, and what they really mean.}

\bigskip

There are two calls to |DAQmxBaseGetExtendedErrorInfo()| to obtain the error
messages. The first is used just to obtain the length of the error string. That
length is then used to allocate space for the error message. The second call
fills that string. This isn'@q'@>t allowed by ISO \CPLUSPLUS/\nfnote{%
\CPLUSPLUS/Dynamic Arrays (Crowl and Austern, May 16, 2008)\par
\hbox{\indent\pdfURL{%
http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2648.html}{%
http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2648.html}}} but it
works with gcc. If this is a problem, the first call can be
removed and the buffer can be set large enough to fit the largest error message
that will be produced. Heap allocation could be used, but then we need to
remember to free the memory allocated to the string. Alternately, we can get rid
of \CEE/ style strings and write our own error messages. This would be the
preferred correction.

@<Display DAQ Error@>=
imp->ready = false;
QMessageBox warning;
warning.setStandardButtons(QMessageBox::Cancel);
warning.setIcon(QMessageBox::Warning);
warning.setText(QString(tr("Error: %1")).arg(imp->error));
unsigned long bytes = imp->errorInfo(NULL, 0);
char string[bytes];
imp->errorInfo(string, bytes);
warning.setInformativeText(QString(string));
warning.setWindowTitle(QString(PROGRAM_NAME));
warning.exec();

@ Starting the thread is almost as simple as ending it. The hardware is
instructed to begin taking measurements. If there is an error, this is handled.
Otherwise, the finished signal from |DAQImplementation| is connected to
|threadFinished()| and the new thread is started. The call to |imp->start()|
starts a new thread and passes control of that thread to |imp->run()|. The main
thread of execution returns without waiting for the new thread to do anything.

The call to |DAQmxBaseStartTask()| requires some time before the first
measurement is available. This is one of the reasons we start gathering
measurements before we really need them and continue to collect them until it is
time to exit the program.

@<DAQ Implementation@>=
void DAQ::start()
{
	if(imp->ready)
	{
		imp->error = imp->startTask(imp->handle);
		if(imp->error)
		{
			@<Display DAQ Error@>@;
		}
		else
		{
			connect(imp, SIGNAL(finished()), this, SLOT(threadFinished()));
			imp->start();
		}
	}
}

void DAQ::stop()
{
	if(imp->useBase)
	{
		imp->ready = false;
		imp->wait(ULONG_MAX);
		imp->stopTask(imp->handle);
	}
	else
	{
		imp->ready = false;
		imp->error = imp->stopTask(imp->handle);
		if(imp->error)
		{
			@<Display DAQ Error@>@;
		}
		imp->error = imp->clearTask(imp->handle);
		if(imp->error)
		{
			@<Display DAQ Error@>@;
		}
	}
}

@ Setting up the DAQ begins by constructing a new |DAQ| object. The constructor
takes as its argument a string indicating the name of the device and will
typically be something like |"Dev1"|. This creates a new task which is required
for the setup that follows once a new |DAQ| is created.

@<DAQ Implementation@>=
DAQ::DAQ(QString device, const QString &driver) : imp(new DAQImplementation(driver))@/
@t\4\4@>{@/
	imp->device = device;
	imp->error = imp->createTask(device.toAscii().data(), &(imp->handle));
	if(imp->error)@/
	{
		@<Display DAQ Error@>@;
	}
	else@/
	@t\1@>{@/
		imp->ready = true;@t\2@>@/
	}@/
@t\4\4@>}

@ Once the |DAQ| is created, one or more channels can be added to that |DAQ|.
All |Channel| objects are created by the |DAQ| class and are managed by the
|DAQ| class. When a new channel is created, a pointer is passed back allowing
other classes to connect to the channel. Measurements cannot be read from the
|DAQ| directly. They must at some point pass through a channel.

@<DAQ Implementation@>=
Channel* DAQ::newChannel(int units, int thermocouple)
{
	Channel *retval = new Channel();
	imp->channelMap[imp->channels] = retval;
	imp->unitMap[imp->channels] = (Units::Unit)units;
	imp->channels++;
	if(imp->ready)
	{
		if(imp->useBase)
		{
			imp->error = imp->createChannel(imp->handle,
		                                QString("%1/ai%2").arg(imp->device).
										                   arg(imp->channels - 1).
										                   toAscii().data(),
										"", (double)(-1.0), (double)(100.0),
										(signed long)(units),
										(signed long)(thermocouple),
										(signed long)(10200), (double)(0),
										"");
		}
		else
		{
			imp->error = imp->createChannel(imp->handle,
			                            QString("%1/ai%2").arg(imp->device).
										                   arg(imp->channels - 1).
														   toAscii().data(),
										"", (double)(50.0), (double)(500.0),
										(signed long)(units),
										(signed long)(thermocouple),
										(signed long)(10200), (double)(0),
										"");
		}
		if(imp->error)
		{
			@<Display DAQ Error@>@;
		}
	}
	return retval;
}

@ Once the channels are created, it is necessary to set the clock rate of the
DAQ. The clock rate chosen must be supported by the hardware. The clock rates
supported by the hardware may be altered by the number of channels in use.

The amount of time between measurements may vary slightly. A test configuration
at Wilson's Coffee \char'046~Tea used a 4Hz clock rate and provides measurements
every 251$\pm$1ms with 80\% of measurements spaced 251ms apart.

@<DAQ Implementation@>=
void DAQ::setClockRate(double Hz)
{
	if(imp->ready)
	{
		imp->error = imp->setClock(imp->handle, "OnboardClock", Hz,
		                           (signed long)(10280), (signed long)(10123),
								   (unsigned long long)(1));
		if(imp->error)
		{
			@<Display DAQ Error@>@;
		}
	}
}

@ Before the program exits, the |DAQ| should be deleted. The destructor
instructs the measurement thread to stop, waits for it to finish, and resets the
device. If this is not done, an error would be issued the next time a program
attempted to use the device.

@<DAQ Implementation@>=
DAQ::~DAQ()@/
@t\4\4@>{@/
	if(imp->useBase)
	{
		imp->resetDevice(imp->device.toAscii().data());
		imp->clearTask(imp->handle);
	}
	else
	{
		if(imp->ready)
		{
			imp->ready = false;
			imp->wait(ULONG_MAX);
			imp->stopTask(imp->handle);
			imp->resetDevice(imp->device.toAscii().data());
			imp->clearTask(imp->handle);
		}
	}
	delete imp;
@t\4\4@>}

@ This just leaves the constructor and destructor for |DAQImplementation|. The
way the program is currently written, the number of channels available on the
|DAQ| is limited to 4. If a known larger number is required, the value here can
simply be set larger, however the best long term solution would be to modify
|newChannel()| to resize |channelMap| as more channels are added.

The constructor handles loading NI-DAQmxBase and preparing function pointers for
the symbols used in \pn{}.

@<DAQ Implementation@>=
DAQImplementation::DAQImplementation(const QString &driverinfo)
: QThread(NULL), channelMap(4), handle(0), error(0), channels(0), ready(false),
	unitMap(4)@/
{
	if(driverinfo == "nidaqmxbase")
	{
		useBase = true;
	}
	else
	{
		useBase = false;
	}
	if(useBase)
	{
		driver.setFileName("nidaqmxbase.framework/nidaqmxbase");
		if(!driver.load())
		{
			driver.setFileName("nidaqmxbase");
			if(!driver.load())
			{
				QMessageBox::critical(NULL, tr("Typica: Driver not found"),
					tr("Failed to find nidaqmxbase. Please install it."));
				QApplication::quit();
			}
		}
	}
	else
	{
		driver.setFileName("nicaiu");
		if(!driver.load())
		{
			QMessageBox::critical(NULL, tr("Typica: Driver not found"),
					tr("Failed to find nidaqmx. Please install it."));
			QApplication::quit();
		}
	}
	if(useBase)
	{
		if((createTask = (daqfp) driver.resolve("DAQmxBaseCreateTask")) == 0 || @|
		(startTask = (daqfp) driver.resolve("DAQmxBaseStartTask")) == 0 || @|
		(stopTask = (daqfp) driver.resolve("DAQmxBaseStopTask")) == 0 || @|
		(clearTask = (daqfp) driver.resolve("DAQmxBaseClearTask")) == 0 || @|
		(createChannel = (daqfp) driver.resolve("DAQmxBaseCreateAIThrmcplChan"))
			== 0 || @|
		(setClock = (daqfp) driver.resolve("DAQmxBaseCfgSampClkTiming")) ==
			0 || @|
		(read = (daqfp) driver.resolve("DAQmxBaseReadAnalogF64")) == 0 || @|
		(errorInfo = (daqfp) driver.resolve("DAQmxBaseGetExtendedErrorInfo")) ==
			0 || @|
		(resetDevice = (daqfp) driver.resolve("DAQmxBaseResetDevice")) == 0)@/
		{
			waitForMeasurement = NULL;
			QMessageBox::critical(NULL, tr("Typica: Link error"),
			tr("Failed to link a required symbol in NI-DAQmxBase."));
			QApplication::quit();
		}
	}
	else
	{
		if((createTask = (daqfp)driver.resolve("DAQmxCreateTask")) == 0 || @|
		(startTask = (daqfp)driver.resolve("DAQmxStartTask")) == 0 || @|
		(stopTask = (daqfp)driver.resolve("DAQmxStopTask")) == 0 || @|
		(clearTask = (daqfp)driver.resolve("DAQmxClearTask")) == 0 || @|
		(createChannel = (daqfp)driver.resolve("DAQmxCreateAIThrmcplChan"))
			== 0 || @|
		(setClock = (daqfp)driver.resolve("DAQmxCfgSampClkTiming")) == 0 || @|
		(read = (daqfp)driver.resolve("DAQmxReadAnalogF64")) == 0 || @|
		(errorInfo = (daqfp)driver.resolve("DAQmxGetExtendedErrorInfo")) ==
			0 || @|
		(resetDevice = (daqfp)driver.resolve("DAQmxResetDevice")) == 0 ||
		(waitForMeasurement = (daqfp)driver.resolve("DAQmxWaitUntilTaskDone")) == 0)
		{
			QMessageBox::critical(NULL, tr("Typica: Link error"),
			tr("Failed to link a required symbol in NI-DAQmx."));
			QApplication::quit();
		}
	}
}

DAQImplementation::~DAQImplementation()
{
	driver.unload();
}

@ When exposing the |DAQ| class to the scripting engine, we need to provide a
constructor that can be called from a script and we need a way to call
|DAQ::newChannel()|. Other methods that are useful when called from a script are
made available automatically with the |Q_INVOKABLE| macro, however this does not
work for methods such as |newChannel()| which return a pointer to a |Channel|
object.

@<Function prototypes for scripting@>=
QScriptValue constructDAQ(QScriptContext *context, QScriptEngine *engine);
QScriptValue DAQ_newChannel(QScriptContext *context, QScriptEngine *engine);
void setDAQProperties(QScriptValue value, QScriptEngine *engine);

@ First we make these functions known to the scripting engine. We also add
the values from |Units::Unit| as this was widely used in configurations
before this enumeration was removed from the |DAQ| class. As these properties
must be available without an instance, the properties must be added here.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructDAQ);
value = engine->newQMetaObject(&DAQ::staticMetaObject, constructor);
value.setProperty("Fahrenheit", Units::Fahrenheit);
value.setProperty("Celsius", Units::Celsius);
value.setProperty("Kelvin", Units::Kelvin);
value.setProperty("Rankine", Units::Rankine);
engine->globalObject().setProperty("DAQ", value);

@ When creating a new |DAQ|, we make sure that it is owned by the script engine.
This is necessary to ensure that the destructor is called before \pn{} exits.
Just as the constructor requires an argument that specifies the device name, the
constructor available from a script also requires this argument.

@<Functions for scripting@>=
QScriptValue constructDAQ(QScriptContext *context, QScriptEngine *engine)
{
	QScriptValue object;
	if(context->argumentCount() == 1)
	{
		object = engine->newQObject(new DAQ(argument<QString>(0, context)),
									QScriptEngine::ScriptOwnership);
		setDAQProperties(object, engine);
	}
	else if(context->argumentCount() == 2)
	{
		object = engine->newQObject(new DAQ(argument<QString>(0, context),
		                                    argument<QString>(1, context)),
									QScriptEngine::ScriptOwnership);
		setDAQProperties(object, engine);
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to DAQ"@|
							"constructor. The DAQ constructor takes one"@|
							"string as an argument specifying a device name."@|
							"Example: Dev1");
	}
	return object;
}

@ As |DAQ| inherits |QObject|, we add the |newChannel()| property after adding
any |QObject| properties.

@<Functions for scripting@>=
void setDAQProperties(QScriptValue value, QScriptEngine *engine)
{
	setQObjectProperties(value, engine);
	value.setProperty("newChannel", engine->newFunction(DAQ_newChannel));
}

@ The |newChannel()| method method also requires that two arguments are provided
by the script.

@<Functions for scripting@>=
QScriptValue DAQ_newChannel(QScriptContext *context, QScriptEngine *engine)
{
	DAQ *self = getself<@[DAQ *@]>(context);
	QScriptValue object;
	if(self)
	{
		object =
			engine->newQObject(self->newChannel(argument<int>(0, context),@|
												argument<int>(1, context)));
		setChannelProperties(object, engine);
	}
	return object;
}

@ Sometimes it can be useful to test other parts of the program (for example,
when developing new scripts) when the DAQ hardware is not available. In these
cases, it is possible to temporarily use the |FakeDAQ| class. This class mimics
the |DAQ| class, but just makes up the measurements sent to the rest of the
program.

@<Class declarations@>=
class FakeDAQImplementation : public QThread@/
{@/
	Q_OBJECT@;
	public:@/
		FakeDAQImplementation();
		~FakeDAQImplementation();
		void run();
		void measure();
		QVector<Channel *> channelMap;
		int channels;
		bool ready;
		double clockRate;
};@/

class FakeDAQ : public QObject@/
{@/
	Q_OBJECT@;
	FakeDAQImplementation *imp;
	public:@/
		FakeDAQ(QString device);
		~FakeDAQ();
		Channel *newChannel(int units, int thermocouple);@/
		@[Q_INVOKABLE@,@, void@]@, setClockRate(double Hz);@t\2\2@>@/
		@[Q_INVOKABLE@,@, void@]@, start();@t\2\2@>@/
};

@ Just as in the |DAQ| class, most of the interesting stuff happens in
|measure()|. For each invokation of the method, we sleep for some amount of time
based on the clock rate then create a |Measurement| object at random for each
|Channel| that has been created.

@<FakeDAQ Implementation@>=
void FakeDAQImplementation::measure()
{
	msleep((int)(1000/clockRate));
	QTime time = QTime::currentTime();
	for(int i = 0; i < channels; i++)
	{
		Measurement measure(qrand() % 500, time);
		channelMap[i]->input(measure);
	}
}

@ To call |measure|, we need to flesh out the rest of |FakeDAQImplementation|.

@<FakeDAQ Implementation@>=
void FakeDAQImplementation::run()
{
	setPriority(QThread::TimeCriticalPriority);
	while(ready)
	{
		measure();
	}
}

FakeDAQImplementation::FakeDAQImplementation() : QThread(NULL), channelMap(4),
	channels(0), ready(false), clockRate(1)@/
{
	/* Nothing has to be done here. */
}

FakeDAQImplementation::~FakeDAQImplementation()
{
	/* Nothing has to be done here. */
}

@ Next we need an implementation for the |FakeDAQ| class. This is simplified by
the fact that we are just using a random number generator to generate
measurements rather than special hardware for obtaining measurements.

@<FakeDAQ Implementation@>=
void FakeDAQ::start()
{
	if(imp->ready)
	{
		imp->start();
	}
}@#

FakeDAQ::FakeDAQ(QString) : imp(new FakeDAQImplementation())@t\2\2@>@/
{@t\1@>@/
	imp->ready = true;@t\2@>@/
}@#

Channel* FakeDAQ::newChannel(int, int)
{
	Channel *retval;
	if(imp->ready)
	{
		retval = new Channel();
		imp->channelMap[imp->channels] = retval;
		imp->channels++;
	}
	else
	{
		return NULL;
	}
	return retval;
}

void FakeDAQ::setClockRate(double Hz)
{
	if(imp->ready)
	{
		imp->clockRate = Hz;
	}
}@#

FakeDAQ::~FakeDAQ()@t\2\2@>@/
{@t\1@>@/
	imp->ready = false;
	imp->wait(ULONG_MAX);
	delete imp;@t\2@>@/
}

@ As the entire purpose of the |FakeDAQ| class is for testing purposes from
within the scripting engine, we need to make it available to the scripting
engine. This is done in a manner very similar to how the |DAQ| class is handled.

@<Function prototypes for scripting@>=
QScriptValue constructFakeDAQ(QScriptContext *context, QScriptEngine *engine);
QScriptValue FakeDAQ_newChannel(QScriptContext *context, QScriptEngine *engine);
void setFakeDAQProperties(QScriptValue value, QScriptEngine *engine);

@ The scripting engine is informed of the constructor.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructFakeDAQ);
value = engine->newQMetaObject(&FakeDAQ::staticMetaObject, constructor);
engine->globalObject().setProperty("FakeDAQ", value);

@ The constructor sets a property to allow calling |newChannel()| on a |FakeDAQ|
created from a script.

@<Functions for scripting@>=
QScriptValue constructFakeDAQ(QScriptContext *context,
									QScriptEngine *engine)
{
	QScriptValue object;
	if(context->argumentCount() == 1)
	{
		object =
			engine->newQObject(new FakeDAQ(argument<QString>(0, context)),
									QScriptEngine::ScriptOwnership);
		setFakeDAQProperties(object, engine);
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to DAQ"@|
							"constructor. The DAQ constructor takes one"@|
							"string as an argument specifying a device name."@|
							"Example: Dev1");
	}
	return object;
}

void setFakeDAQProperties(QScriptValue value, QScriptEngine *engine)
{
	setQObjectProperties(value, engine);
	value.setProperty("newChannel", engine->newFunction(FakeDAQ_newChannel));
}

QScriptValue FakeDAQ_newChannel(QScriptContext *context, QScriptEngine *engine)
{
	FakeDAQ *self = getself<@[FakeDAQ *@]>(context);
	QScriptValue object;
	if(self)
	{
		object =
			engine->newQObject(self->newChannel(argument<int>(0, context),@|
			                                    argument<int>(1, context)));
		setChannelProperties(object, engine);
	}
	return object;
}

@* The Channel class.

\noindent |Channel| is a simple class. It is a subclass of |QObject| so it can
use Qt'@q'@>s signals and slots mechanism. Any object that is interested in
measurements from a channel can connect to the |newData| signal the channel
emits. Any number of objects can make this connection and each will receive a
copy of the measurement.

|Channel| objects should only be created by the |DAQ| class.

@<Class declarations@>=
class Channel : public QObject@;@/
{@t\1@>@/
	Q_OBJECT@/
	public:@;
		Channel();
		~Channel();@/
	@t\4@>public slots@t\kern-3pt@>:@;
		void input(Measurement measurement);@/
	signals:@;
		void newData(Measurement);@t\2@>@/
};

@ The implementation of this class is trivial.

@<Channel Implementation@>=
Channel::Channel() : QObject(NULL)@/
{
	/* Nothing has to be done here. */
}

Channel::~Channel()
{
	/* Nothing has to be done here. */
}

void Channel::input(Measurement measurement)
{
	emit newData(measurement);
}

@ A function is provided for use when a channel is created by a DAQ from a
script.

@<Function prototypes for scripting@>=
void setChannelProperties(QScriptValue value, QScriptEngine *engine);

@ The implementation is trivial.

@<Functions for scripting@>=
void setChannelProperties(QScriptValue value, QScriptEngine *engine)
{
	setQObjectProperties(value, engine);
}

@* Calibration and Unit Conversion.

\noindent One of the planned features for  \pn{} is support for hardware that
collects non-temperature measurements. This is frequently handled with analog
voltage signals which are proportional to some range in a meaningful unit. Some
hardware also requires calibration in software. In many cases both of these can
be handled at the same time with a single mapping in the form:

$$f(x) = L_1 + (x - L_2){U_1 - L_1\over{U_2 - L_2}}$$

\noindent where $L_1$ is the logical lower bound, $L_2$ is the measured lower
bound, $U_1$ is the logical upper bound, $U_2$ is the measured upper bound, and
$x$ is the value we wish to map from the range $\lbrack L_2, U_2 \rbrack$ to
the range $\lbrack L_1, U_1 \rbrack$.

Some use cases require a closed range but others require that this constraint
is loosened to allow extrapolation. Both are provided by this class.

Starting in \pn{} 1.6 this class has both the |measurement| and the
|newData| signals. This allows a |LinearCalibrator| to be treated like a
|Channel| when used with a |DataqSdkDevice|.

@<Class declarations@>=
class LinearCalibrator : public QObject@/
{@/
	@[Q_OBJECT@]@;
	@[Q_PROPERTY(double measuredLower READ measuredLower
	           WRITE setMeasuredLower)@]@;
	@[Q_PROPERTY(double measuredUpper READ measuredUpper
	           WRITE setMeasuredUpper)@]@;
	@[Q_PROPERTY(double mappedLower READ mappedLower WRITE setMappedLower)@]@;
	@[Q_PROPERTY(double mappedUpper READ mappedUpper WRITE setMappedUpper)@]@;
	@[Q_PROPERTY(bool closedRange READ isClosedRange WRITE setClosedRange)@]@;
	@[Q_PROPERTY(double sensitivity READ sensitivity WRITE setSensitivity)@]@;
	public:@/
		LinearCalibrator(QObject *parent = NULL);
		double measuredLower();
		double measuredUpper();
		double mappedLower();
		double mappedUpper();
		bool isClosedRange();
		double sensitivity();
	@t\4@>@[public slots@t\kern-3pt@>:@]@;
		void setMeasuredLower(double lower);
		void setMeasuredUpper(double upper);
		void setMappedLower(double lower);
		void setMappedUpper(double upper);
		void setClosedRange(bool closed);
		void setSensitivity(double sensitivity);
		Measurement newMeasurement(Measurement measure);
	@t\4@>@[signals:@]@;
		void measurement(Measurement measure);
		void newData(Measurement measure);
	private:@/
		double Lo1;
		double Lo2;
		double Up1;
		double Up2;
		double sensitivitySetting;
		bool clamp;
};

@ When the measured range and the mapped range are identical and the range is
open, we have an identity mapping. This is the default state in a newly
constructed |LinearCalibrator| which should quickly be changed.

@<LinearCalibrator Implementation@>=
LinearCalibrator::LinearCalibrator(QObject *parent) :
	QObject(parent), Lo1(0), Lo2(0), Up1(1), Up2(1), sensitivitySetting(0.0), clamp(false)@/
{
	connect(this, SIGNAL(measurement(Measurement)), this, SIGNAL(newData(Measurement)));
}

@ The functional portion of the class is in the |newMeasurement()| slot. This
will receive measurements as they come in and emit a |measurement()| signal for
each with the calibration and unit adjustment performed.

This method also handles any rounding needed if there has been a call to
|setSensitivity()|.

@<LinearCalibrator Implementation@>=
Measurement LinearCalibrator::newMeasurement(Measurement measure)
{
	double outval = Lo1 + (measure.temperature() - Lo2) * (Up1 - Lo1)/(Up2 - Lo2);
	if(clamp)
	{
		if(outval < Lo1)
		{
			outval = Lo1;
		}
		else if(outval > Up1)
		{
			outval = Up1;
		}
	}
	if(sensitivitySetting >= 0.05)
	{
		int temp = qRound(outval/sensitivitySetting);
		outval = temp * sensitivitySetting;
	}
	Measurement adjusted(outval, measure.time(), measure.scale());
	emit measurement(adjusted);
	return adjusted;
}

@ The rest of the class consists of trivial accessor methods.

@<LinearCalibrator Implementation@>=
double LinearCalibrator::measuredLower()
{
	return Lo2;
}

double LinearCalibrator::measuredUpper()
{
	return Up2;
}

double LinearCalibrator::mappedLower()
{
	return Lo1;
}

double LinearCalibrator::mappedUpper()
{
	return Up1;
}

bool LinearCalibrator::isClosedRange()
{
	return clamp;
}

void LinearCalibrator::setMeasuredLower(double lower)
{
	Lo2 = lower;
}

void LinearCalibrator::setMeasuredUpper(double upper)
{
	Up2 = upper;
}

void LinearCalibrator::setMappedLower(double lower)
{
	Lo1 = lower;
}

void LinearCalibrator::setMappedUpper(double upper)
{
	Up1 = upper;
}

void LinearCalibrator::setClosedRange(bool closed)
{
	clamp = closed;
}

void LinearCalibrator::setSensitivity(double sensitivity)
{
	sensitivitySetting = sensitivity;
}

double LinearCalibrator::sensitivity()
{
	return sensitivitySetting;
}

@ Finally, we make this class available to the scripting engine. Two functions
are required for this.

@<Function prototypes for scripting@>=
QScriptValue constructLinearCalibrator(QScriptContext *context,
                                       QScriptEngine *engine);
void setLinearCalibratorProperties(QScriptValue value, QScriptEngine *engine);

@ The scripting engine is informed of the constructor.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructLinearCalibrator);
value = engine->newQMetaObject(&LinearCalibrator::staticMetaObject,
                               constructor);
engine->globalObject().setProperty("LinearCalibrator", value);

@ The implementation of these functions is typical for this application.

@<Functions for scripting@>=
QScriptValue constructLinearCalibrator(QScriptContext *, QScriptEngine *engine)
{
	QScriptValue object = engine->newQObject(new LinearCalibrator(NULL));
	setLinearCalibratorProperties(object, engine);
	return object;
}

void setLinearCalibratorProperties(QScriptValue value, QScriptEngine *engine)
{
	setQObjectProperties(value, engine);
}

@* Linear Spline Interpolation.

\noindent While linear interpolation is adequate for many purposes, it fails
when a nonlinear mapping is required. The primary use case is to calibrate
multiple coffee roasters so that roast profiles can be shared among coffee
roasters with sufficiently similar heat transfer characteristics even if
differences in the measurement hardware result in different measured values.
By recording measured values at several points known to be equivalent due to
easily observable physical changes in the coffee it is possible to use linear
spline interpolation to produce a data series that approximates on one machine
the measurements that would have been produced at another. Acceptable results
may be available with surprisingly few data points.

It was originally suspected that cubic spline interpolation would produce a
more accurate mapping, but testing with linear spline interpolation produced
results good enough that more complex mappings were not needed. Cubic spline
interpolation may still be implemented in the future, but it is a low
priority.

@<Class declarations@>=
class LinearSplineInterpolator : public QObject
{
	@[Q_OBJECT@]@/
	public:@/
		LinearSplineInterpolator(QObject *parent = NULL);
		@[Q_INVOKABLE@]@, void add_pair(double source, double destination);
	@[public slots@]:@/
		Measurement newMeasurement(Measurement measure);
	@[signals@]:@/
		void newData(Measurement measure);
	private:@/
		void make_interpolators();
		QMap<double, double> *pairs;
		QList<LinearCalibrator *> *interpolators;
};

@ We take advantage of the fact that iterating over a QMap always returns
entries in key order. When new measurement pairs are specified, the
interpolators are regenerated. There is significant room for performance
improvement.

@<LinearSplineInterpolator Implementation@>=
void LinearSplineInterpolator::add_pair(double source, double destination)
{
	pairs->insert(source, destination);
	make_interpolators();
}

void LinearSplineInterpolator::make_interpolators()
{
	if(pairs->size() > 1)
	{
		while(interpolators->size() > 0)
		{
			LinearCalibrator *removed = interpolators->takeFirst();
			removed->deleteLater();
		}
		QMap<double, double>::const_iterator i = pairs->constBegin();
		QMap<double, double>::const_iterator j = i + 1;
		while(j != pairs->constEnd())
		{
			LinearCalibrator *segment = new LinearCalibrator();
			segment->setMeasuredLower(i.key());
			segment->setMappedLower(i.value());
			segment->setMeasuredUpper(j.key());
			segment->setMappedUpper(j.value());
			segment->setClosedRange(false);
			interpolators->append(segment);
			connect(segment, SIGNAL(measurement(Measurement)), this, SIGNAL(newData(Measurement)));
			i++;
			j++;
		}
	}
}

LinearSplineInterpolator::LinearSplineInterpolator(QObject *parent) :
	QObject(parent), pairs(new QMap<double, double>),
	interpolators(new QList<LinearCalibrator *>)
{
	/* Nothing needs to be done here. */
}

Measurement LinearSplineInterpolator::newMeasurement(Measurement measure)
{
	QMap<double, double>::const_iterator i = pairs->constBegin();
	int index = -1;
	while(i != pairs->constEnd())
	{
		if(measure.temperature() <= i.key())
		{
			break;
		}
		i++;
		index++;
	}
	if(index < 0)
	{
		index = 0;
	}
	if(index >= interpolators->size())
	{
		index = interpolators->size() - 1;
	}
	if(interpolators->at(index) != NULL)
	{
		return interpolators->at(index)->newMeasurement(measure);
	}
	return Measurement();
}

@ This is exposed to the scripting environment as usual.

@<Function prototypes for scripting@>=
QScriptValue constructLinearSplineInterpolator(QScriptContext *context, QScriptEngine *engine);
void setLinearSplineInterpolatorProperties(QScriptValue value, QScriptEngine *engine);

@ As usual.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructLinearSplineInterpolator);
value = engine->newQMetaObject(&LinearSplineInterpolator::staticMetaObject, constructor);
engine->globalObject().setProperty("LinearSplineInterpolator", value);

@ And again as usual.

@<Functions for scripting@>=
QScriptValue constructLinearSplineInterpolator(QScriptContext *, QScriptEngine *engine)
{
	QScriptValue object = engine->newQObject(new LinearSplineInterpolator(NULL));
	setLinearSplineInterpolatorProperties(object, engine);
	return object;
}

void setLinearSplineInterpolatorProperties(QScriptValue value, QScriptEngine *engine)
{
	setQObjectProperties(value, engine);
}


@* The TemperatureDisplay class.

Now that measurements have been generated by the |DAQ| and passed to a
|Channel|, any object that is interested in these measurements can connect to
the channel and use the measurements it sends out. So far, the time on each
measurement is the time at which it was collected. Unfortunately, this is often
not what we want. It is more useful to have the time relative to some other
point in time such as the start of the batch.

Until the measurement time is adjusted, the measurements are really only useful
to classes that do not care about the measurement time. The |TemperatureDisplay|
class is such a class. It receives measurements and displays the most recently
measured temperature.

This is a specialization of |QLCDNumber|.

@<Class declarations@>=
class TemperatureDisplay : public QLCDNumber@/
{@t\1@>@/
	Q_OBJECT@;
	int unit;
	bool r;
	public:@/
		TemperatureDisplay(QWidget *parent = NULL);
		~TemperatureDisplay();@/
	@t\4@>public slots@t\kern-3pt@>:@/
		void setValue(Measurement temperature);
		void invalidate();
		void setDisplayUnits(Units::Unit scale);
		void setRelativeMode(bool relative);@t\2@>@/
};

@ Starting in version 1.6 this widget is also used for displaying a relative
temperature value in the form of the rate of change indicator. To calculate
this correctly in Celsius or Kelvin we must have a way to bypass the
conversions for absolute measures.

@<TemperatureDisplay Implementation@>=
void TemperatureDisplay::setRelativeMode(bool relative)
{
	r = relative;
}

@ Displaying a temperature is a simple matter of taking the temperature
component from the measurement and converting it to a string. Presently, this
code assumes that the measurements are in degrees Fahrenheit. If the code
becomes smarter about measurement units it might be a good idea to change this.

|QLCDNumber| is capable of displaying more than just numbers, so the call to
display takes a string which in this case consists of the temperature to the
$1\over100$th of a degree and might be followed by '@q'@> which will be
converted to $^\circ$ and the letter F, C, or r to indicate the unit. This
class should be mofified to allow a user specified precision.

@<TemperatureDisplay Implementation@>=
void TemperatureDisplay::setValue(Measurement temperature)
{
	QString number;
	switch(unit)
	{
		case Units::Fahrenheit:
			display(QString("%1'F").
				arg(number.setNum(temperature.toFahrenheit().temperature(), 'f',
				                  2)));
			break;
		case Units::Celsius:
			if(!r) {
				display(QString("%1'C").
					arg(number.setNum(temperature.toCelsius().temperature(), 'f',
									2)));
			} else {
				number.setNum(temperature.temperature() * (5.0/9.0), 'f', 2);
				display(QString("%1'C").arg(number));
			}
			break;
		case Units::Kelvin:
			if(!r) {
				display(QString("%1").
					arg(number.setNum(temperature.toKelvin().temperature(), 'f',
									2)));
			} else {
				number.setNum(temperature.temperature() * (5.0/9.0), 'f', 2);
				display(QString("%1").arg(number));
			}
			break;
		case Units::Rankine:
			display(QString("%1'r").
				arg(number.setNum(temperature.toRankine().temperature(), 'f',
				                  2)));
			break;
		case Units::Unitless:
			display(QString("%1").arg(number.setNum(temperature.temperature(), 'f', 0)));
			break;
		default:
			switch(temperature.scale())
			{
				case Units::Fahrenheit:
					display(QString("%1'F").
						arg(number.setNum(temperature.temperature(), 'f', 2)));
					break;
				case Units::Celsius:
					display(QString("%1'C").
						arg(number.setNum(temperature.temperature(), 'f', 2)));
					break;
				case Units::Kelvin:
					display(QString("%1").
						arg(number.setNum(temperature.temperature(), 'f', 2)));
					break;
				case Units::Rankine:
					display(QString("%1'r").
						arg(number.setNum(temperature.temperature(), 'f', 2)));
					break;
				case Units::Unitless:
					display(QString("%1").arg(number.setNum(temperature.temperature(), 'f', 0)));
					break;
			}
			break;
	}
}

@ Before measurements are displayed, we set a more sensible default display
style and an initial string. These defaults can all be overridden with calls to
the usual |QLCDNumber| methods.

\medskip
\resizebox*{6.3in}{!}{\includegraphics{QLCDNumber.png}}
\smallskip
\centerline{Figure \secno: Outline (Qt default) and Filled |QLCDNumber| Example}
\medskip

@<TemperatureDisplay Implementation@>=
TemperatureDisplay::TemperatureDisplay(QWidget *parent) :
	QLCDNumber(8, parent), unit(Units::Fahrenheit), r(false)@/
{
	setSegmentStyle(Filled);
	display("---.--'F");
}

@ While it is not currently used, it would be good to allow an error state to
be easily discernible from a very stable temperature. Currently, if an error
occurs that results in the measurement thread exiting, no new measurements will
be generated and the temperature display will continue to read the most recent
measured value. If an error signal were emitted, it could be connected to the
following code to change the display to reflect the fact that the current
temperature is unknown.

@<TemperatureDisplay Implementation@>=
void TemperatureDisplay::invalidate()
{
	display("---.--'F");
}

@ \pn{} supports the display of multiple types of unit. Typically, we use the
Auto scale which will cause |TemperatureDisplay| objects to display measurements
in whichever scale the measurement is associated with. Alternately, we can fix
the scale to a different supported scale and convert measurements to that scale
prior to display.

@<TemperatureDisplay Implementation@>=
void TemperatureDisplay::setDisplayUnits(Units::Unit scale)
{
	unit = scale;
}

@ All that is left to deal with is the empty destructor.

@<TemperatureDisplay Implementation@>=
TemperatureDisplay::~TemperatureDisplay()
{
	/* Nothing has to be done here. */
}

@ To use a |TemperatureDisplay| from a script, we need a function to pass a new
object to the scripting engine.

@<Function prototypes for scripting@>=
QScriptValue constructTemperatureDisplay(QScriptContext *context,
                                         QScriptEngine *engine);
void setTemperatureDisplayProperties(QScriptValue value, QScriptEngine *engine);
QScriptValue TemperatureDisplay_setDisplayUnits(QScriptContext *context,
                                                QScriptEngine *engine);

@ The scripting engine must be informed of this function.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructTemperatureDisplay);
value = engine->newQMetaObject(&TemperatureDisplay::staticMetaObject,
                               constructor);
engine->globalObject().setProperty("TemperatureDisplay", value);

@ The constructor is trivial.

@<Functions for scripting@>=
QScriptValue constructTemperatureDisplay(QScriptContext *,
											QScriptEngine *engine)
{
	QScriptValue object = engine->newQObject(new TemperatureDisplay);
	setTemperatureDisplayProperties(object, engine);
	return object;
}

void setTemperatureDisplayProperties(QScriptValue value, QScriptEngine *engine)
{
	setQLCDNumberProperties(value, engine);
	value.setProperty("setDisplayUnits",
	                  engine->newFunction(TemperatureDisplay_setDisplayUnits));
}

@ There seems to be a bad interaction when enumerated value types as used as
the argument to slot methods called through QtScript. Script code that attempts
to make use of the enumeration appears to get the value without any type
information. When attempting to use that value as an argument the meta-object
system cannot find an appropriate match and the script just hangs silently.
The solution is to wrap such methods in the script bindings and explicitly cast
the argument value to the enumerated type. This looks stupid but it works.

@<Functions for scripting@>=
QScriptValue TemperatureDisplay_setDisplayUnits(QScriptContext *context, QScriptEngine *)
{
	TemperatureDisplay *self = getself<@[TemperatureDisplay *@]>(context);
	self->setDisplayUnits((Units::Unit)argument<int>(0, context));
	return QScriptValue();
}

@* The MeasurementTimeOffset class.

When a |DAQ| object creates a |Measurement| object, the time component is a
system time. In most cases, the system time is not interesting and a more useful
time would be relative to the start of a process. This class should be used as a
filter, taking measurements with a system time stamp and producing measurements
with a relative time.

@<Class declarations@>=
class MeasurementTimeOffset : public QObject@/
{@t\1@>@/
	Q_OBJECT@;
	QTime epoch;
	QTime previous;
	bool hasPrevious;@/
	public:@;
		MeasurementTimeOffset(QTime zero);
		QTime zeroTime();@/
	@t\4@>public slots@t\kern-3pt@>:@;
		void newMeasurement(Measurement measure);
		void setZeroTime(QTime zero);
	signals:@;
		void measurement(Measurement measure);@t\2@>@/
}@t\kern-3pt@>;

@ The interesting part of this class is the function which takes a measurement
with a system time and produces a new measurement with a time relative to some
start time.

When using this class, it is possible that a measurement will arrive with a time
slightly before a newly chosen epoch. In such a case we do not want to simply
subtract the epoch from the measurement time as other classes will interpret
this incorrectly as a measurement time slightly less than 1 hour. This means
that we need to check if the measurement time is before the epoch. If it is, we
consider it to have been generated at the epoch rather than before. Aren't race
conditions fun?

Additionally, since we're only getting time of day information, some special
handling must be done for time series that cross the boundary between days. We
should never get measurements out of order, so keeping a record of the previous
measurement and verifying that the new measurement comes after it is sufficient.

@<MeasurementTimeOffset Implementation@>=
void MeasurementTimeOffset::newMeasurement(Measurement measure)@t\2\2@>@/
{@t\1@>@/
	if(measure.time() < epoch)@/
	{
		if(hasPrevious)@/
		{
			QTime jitBase(epoch.hour() - 1, epoch.minute(), epoch.second(),
						  epoch.msec());
			QTime jitComp(epoch.hour(), measure.time().minute(),
						  measure.time().second(), measure.time().msec());
			int relTime = jitBase.msecsTo(jitComp);
			@<Produce and emit relative time@>@;
		}
		else@/
		{
			Measurement rel = measure;
			rel.setTime(QTime(0, 0, 0, 0));
			emit measurement(rel);
		}
	}
	else@/
	{
		int relTime = epoch.msecsTo(measure.time());
		@<Produce and emit relative time@>@;
	}
	hasPrevious = true;
	previous = measure.time();@t\2@>@/
}

@ The measurement emitted has a time with the number of minutes, seconds, and
milliseconds since the start of the batch.  We never generate a time greater
than 1 hour.

@<Produce and emit relative time@>=
QTime newTime(0, 0, 0, 0);
newTime = newTime.addMSecs(relTime);
if(newTime.hour() > 0)
{
	newTime.setHMS(0, newTime.minute(), newTime.second(), newTime.msec());
}
Measurement rel = measure;
rel.setTime(newTime);
emit measurement(rel);

@ The rest of the code handles updating and reporting the reference time.

@<MeasurementTimeOffset Implementation@>=
MeasurementTimeOffset::MeasurementTimeOffset(QTime zero) : epoch(zero),
	previous(0, 0, 0, 0), hasPrevious(false)
{
	/* Nothing has to be done here. */
}

QTime MeasurementTimeOffset::zeroTime()
{
	return epoch;
}

void MeasurementTimeOffset::setZeroTime(QTime zero)
{
	epoch = zero;
	hasPrevious = false;
}

@ Two functions are required to make this class available to the scripting
engine.

@<Function prototypes for scripting@>=
QScriptValue constructMeasurementTimeOffset(QScriptContext *context,@|
                                            QScriptEngine *engine);
void setMeasurementTimeOffsetProperties(QScriptValue value,
                                        QScriptEngine *engine);

@ The scripting engine must be informed of the constructor.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructMeasurementTimeOffset);
value = engine->newQMetaObject(&MeasurementTimeOffset::staticMetaObject,
                               constructor);
engine->globalObject().setProperty("MeasurementTimeOffset", value);

@ Previously, another property was added to the newly created object. That
method is believed to be obsolete and has been removed. Careful testing will
need to be done to verify that this decision was sane. I was very hungry when
that change was made.

@<Functions for scripting@>=
QScriptValue constructMeasurementTimeOffset(QScriptContext *,
                                            QScriptEngine *engine)
{
	QScriptValue object =@|
		engine->newQObject(new MeasurementTimeOffset(QTime::currentTime()));
	setMeasurementTimeOffsetProperties(object, engine);
	return object;
}

void setMeasurementTimeOffsetProperties(QScriptValue value,
                                        QScriptEngine *engine)
{
	setQObjectProperties(value, engine);
}

@* Measured value threshold detection.

\noindent There are times when one might want to detect when a measured value
from a data series has passed a given value, with the limitation that we are
only interested in the ascending or descending edge. This can be used, for
example, to translate roast profile data in a graph along the time axis such
that the bean temperature series are aligned at a given
temperature.\nfnote{More details on the reasoning behind why one might want
to do this are provided at:\par\indent\pdfURL{http://youtu.be/hS0SfzypyFQ}
{http://youtu.be/hS0SfzypyFQ}} For this we can use a |ThresholdDetector|.

If we would like to catch changes on both the ascending and descending edge, we
can use two objects, however it may be a good idea to use more than two to
allow for sane behavior in the face of hysteresis.

@<Class declarations@>=
class ThresholdDetector : public QObject@/
{
	@[Q_OBJECT@]@;
	@[Q_ENUMS(EdgeDirection)@]@;
	public:@/
		enum EdgeDirection {
			Ascending, Descending
		};
		ThresholdDetector(double value);
	@[public slots@]:@/
		void newMeasurement(Measurement measure);
		void setThreshold(double value);
		void setEdgeDirection(EdgeDirection direction);
	signals:@/
		void timeForValue(double);
	private:@/
		double previousValue;
		double threshold;
		EdgeDirection currentDirection;
};

@ This class emits the time in seconds when a given measurement crosses the
threshold value in the appropriate direction.

@<ThresholdDetector Implementation@>=
void ThresholdDetector::newMeasurement(Measurement measure)
{
	if((currentDirection == Ascending && previousValue < threshold &&
	   previousValue >= 0) || (currentDirection == Descending &&
	   previousValue > threshold && previousValue >= 0))
	{
		if((currentDirection == Ascending && measure.temperature() >= threshold) ||
		   (currentDirection == Descending && measure.temperature() <= threshold))
		{
			double offset = measure.time().hour() * 60 * 60;
			offset += measure.time().minute() * 60;
			offset += measure.time().second();
			offset += measure.time().msec()/1000;
			emit timeForValue(offset);
		}
	}
	previousValue = measure.temperature();
}

ThresholdDetector::ThresholdDetector(double value) : QObject(NULL),
	previousValue(-1), threshold(value), currentDirection(Ascending)
{
	/* Nothing needs to be done here. */
}

void ThresholdDetector::setThreshold(double value)
{
	threshold = value;
}

void ThresholdDetector::setEdgeDirection(EdgeDirection direction)
{
	currentDirection = direction;
}

@ This is exposed to the host environment.

@<Function prototypes for scripting@>=
QScriptValue constructThresholdDetector(QScriptContext *context, QScriptEngine *engine);
void setThresholdDetectorProperties(QScriptValue value, QScriptEngine *engine);

@ Inform the engine of the constructor.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructThresholdDetector);
value = engine->newQMetaObject(&ThresholdDetector::staticMetaObject, constructor);
engine->globalObject().setProperty("ThresholdDetector", value);

@ Implementation. At present I'@q'@>m not bothering to implement constructor
arguments here and am aligning on a fixed point. Another slot method was added
to restore adjustability.

@<Functions for scripting@>=
QScriptValue constructThresholdDetector(QScriptContext *, QScriptEngine *engine)
{
	QScriptValue object = engine->newQObject(new ThresholdDetector(300));
	return object;
}

void setThresholdDetectorProperties(QScriptValue value, QScriptEngine *engine)
{
	setQObjectProperties(value, engine);
}

@* The ZeroEmitter class.

\noindent Now that it is possible to record the time a measurement was taken
relative to an arbitrary start time, there is a minor problem left for logging.
It is extremely unlikely that a measurement will be passed through at the epoch.
For this, what we want to do is save the previous measurement and make it
available at time 0 whenever the start time is reset. This is the role of the
|ZeroEmitter| class.

Another problem is that most classes that are interested in a relative time are
also interested in logging multiple sets of temperature data. To facilitate this
an integer is emitted. Different temperature measurement sources should be set
to emit different numbers. A table view would place measurements in the
indicated column. A graph view would use different colors to plot different sets
of data.

@<Class declarations@>=
class ZeroEmitter : public QObject@/
{@t\1@>@/
	Q_OBJECT@;
	Q_PROPERTY(int column READ column WRITE setColumn)
	Measurement cache;
	int col;
	public:@/
		ZeroEmitter(int tempcolumn = 1);
		int column();
		double lastTemperature();@/
	@t\4@>public slots@t\kern-3pt@>:@;
		void newMeasurement(Measurement measure);
		void setColumn(int column);
		void emitZero();
	signals:@;
		void measurement(Measurement measure, int tempcolumn);@t\2@>@/
}@t\kern-3pt@>;

@ The implementation of the class is trivial.

@<ZeroEmitter Implementation@>=
ZeroEmitter::ZeroEmitter(int tempcolumn) : QObject(NULL), col(tempcolumn)@;
{
	/* Nothing has to be done here. */
}

int ZeroEmitter::column()
{
	return col;
}

double ZeroEmitter::lastTemperature()
{
	return cache.temperature();
}

void ZeroEmitter::newMeasurement(Measurement measure)
{
	cache = measure;
}

void ZeroEmitter::setColumn(int column)
{
	col = column;
}

void ZeroEmitter::emitZero()
{
	cache.setTime(QTime(0, 0, 0, 0));
	emit measurement(cache, col);
}

@ Making this class available to scripts requires only two functions.

@<Function prototypes for scripting@>=
QScriptValue constructZeroEmitter(QScriptContext *context,
                                  QScriptEngine *engine);
void setZeroEmitterProperties(QScriptValue value, QScriptEngine *engine);

@ To use it, we must inform the engine of the constructor.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructZeroEmitter);
value = engine->newQMetaObject(&ZeroEmitter::staticMetaObject, constructor);
engine->globalObject().setProperty("ZeroEmitter", value);

@ The implementation of the constructor is trivial.

@<Functions for scripting@>=
QScriptValue constructZeroEmitter(QScriptContext *context,
                                  QScriptEngine *engine)
{
	QScriptValue object =
		engine->newQObject(new ZeroEmitter(argument<int>(0, context)));
	setZeroEmitterProperties(object, engine);
	return object;
}

void setZeroEmitterProperties(QScriptValue value, QScriptEngine *engine)
{
	setQObjectProperties(value, engine);
}

@* The MeasurementAdapter class.

\noindent The last of the measurement filter classes is the |MeasurementAdapter|
class. This takes measurements, typically from a |MeasurementTimeOffset|, and
sends the measurement out with a number to indicate which data series the
measurement belongs to.

The measurement pipeline could probably be made simpler by introducing a series
identifier into the measurement class.

@<Class declarations@>=
class MeasurementAdapter : public QObject@/
{@t\1@>@/
	Q_OBJECT@;
	int col;
	public:@/
		MeasurementAdapter(int tempcolumn);
		int column();@/
	@t\4@>public slots@t\kern-3pt@>:@/
		void newMeasurement(Measurement measure);
		void setColumn(int column);
	signals:@/
		void measurement(Measurement measure, int tempcolumn);@t\2@>@/
}@t\kern-3pt@>;

@ The implementation of this filter class is trivial.

@<MeasurementAdapter Implementation@>=
MeasurementAdapter::MeasurementAdapter(int tempcolumn) : col(tempcolumn)@;
{
	/* Nothing has to be done here. */
}

int MeasurementAdapter::column()
{
	return col;
}

void MeasurementAdapter::newMeasurement(Measurement measure)
{
	emit measurement(measure, col);
}

void MeasurementAdapter::setColumn(int column)
{
	col = column;
}

@ This filter class is also available from the host environment.

@<Function prototypes for scripting@>=
QScriptValue constructMeasurementAdapter(QScriptContext *context,
                                         QScriptEngine *engine);
void setMeasurementAdapterProperties(QScriptValue value, QScriptEngine *engine);

@ As usual, the engine must be informed of the constructor.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructMeasurementAdapter);
value = engine->newQMetaObject(&MeasurementAdapter::staticMetaObject,
                               constructor);
engine->globalObject().setProperty("MeasurementAdapter", value);

@ The implementation is trivial.

@<Functions for scripting@>=
QScriptValue constructMeasurementAdapter(QScriptContext *context,
                                         QScriptEngine *engine)
{
	QScriptValue object =
		engine->newQObject(new MeasurementAdapter(argument<int>(0, context)));
	setMeasurementAdapterProperties(object, engine);
	return object;
}

void setMeasurementAdapterProperties(QScriptValue value, QScriptEngine *engine)
{
	setQObjectProperties(value, engine);
}

@* A graph of temperature over time.

\noindent A useful tool when roasting is a visual depiction of the current batch
as it happens, possibly laid over a previously recorded target profile. The
|GraphView| class can take multiple sets of temperature data and produce such a
visualization.

\medskip

\centerline{\includegraphics{roast}}

\smallskip

\centerline{Figure \secno: A Typical Roast}

\medskip

This class assumes that temperature data will be passed in the correct order.

@<Class declarations@>=
class GraphView : public QGraphicsView@/
{@t\1@>@/
	Q_OBJECT@;
	QGraphicsScene *theScene;@/
	QMap<int, QList<QGraphicsLineItem * > * > *graphLines;@/
	QMap<int, QPointF> *prevPoints;
	QMap<int, double> *translations;
	QList<QGraphicsItem *> *gridLinesF;
	QList<QGraphicsItem *> *gridLinesC;
	QList<QGraphicsItem *> *relativeGridLines;
	bool relativeEnabled;
	bool timeIndicatorEnabled;
	QGraphicsLineItem *timeLine;
	LinearSplineInterpolator *relativeAdjuster;@/
	public:@/
		GraphView(QWidget *parent = NULL);
		void removeSeries(int column);@/
	protected:@/
		void resizeEvent(QResizeEvent *event);@/
	@t\4@>public slots@t\kern-3pt@>:@/
		void newMeasurement(Measurement measure, int tempcolumn);
		void setSeriesTranslation(int column, double offset);
		void setTimeIndicatorEnabled(bool enabled);
		void clear();
		void showF();
		void showC();@t\2@>@/
}@t\kern-3pt@>;

@ I decided that it would probably be best to keep the graph area the same even
with different roast lengths over different temperature ranges so that similar
portions between these graphs would continue to look similar rather than
constantly attempting to select the best way to display the data currently in
the view.

I have chosen to represent roasting times of up to 20 minutes and temperatures
between 0 and 500$^\circ$ Fahrenheit. This should certainly be configurable at
run time, but until that is implemented, roasters who routinely roast batches
for longer periods of time will want to change the constructor. This class
should probably be modified to allow the user to specify several characteristics
of the display.

This class must also deal with the fact that coordinates in a |QGraphicsScene|
are not quite the same as coordinates in a cartesian plane. The easiest way to
deal with this is to negate the y coordinate and translate the viewport to the
area we draw in.

A small margin area left around the edges of the graph. This should probably be
configurable for those with particularly small displays.

@<GraphView Implementation@>=
GraphView::GraphView(QWidget *parent) : QGraphicsView(parent),
	theScene(new QGraphicsScene),@/
	graphLines(new QMap<int, QList<QGraphicsLineItem *> *>),@/
	prevPoints(new QMap<int, QPointF>),
	translations(new QMap<int, double>),
	gridLinesF(new QList<QGraphicsItem *>),
	gridLinesC(new QList<QGraphicsItem *>),
	relativeGridLines(new QList<QGraphicsItem *>),
	relativeEnabled(false),
	timeIndicatorEnabled(false),
	timeLine(new QGraphicsLineItem),
	relativeAdjuster(new LinearSplineInterpolator)@/
{
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setScene(theScene);
	setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
	QPen timePen;
	timePen.setColor(QColor(160, 160, 164, 127)); //gray, half opacity
	timeLine->setPen(timePen);
	timeLine->setLine(0, 0, 0, -500);
	timeLine->hide();
	theScene->addItem(timeLine);
	@<Draw temperature axis and grid lines@>;
	@<Draw secondary axes@>@;
	@<Draw time axis and ticks@>;
	fitInView(theScene->sceneRect().adjusted(-50,-50,50,50));
}

@ Grid lines are drawn every 100 degrees. These lines are labeled with
|setHtml()| for convenient access to the $^\circ$ symbol. If \pn{} is modified
to allow different units, this code should also be modified.

As of version 1.3.3 it is possible to switch the graph between degrees
Fahrenheit and degrees Celcius. Celcius grid lines are drawn but initially
hidden. Both the grid lines and the labels are added to a list depending on the
unit so that when changing from one view to another all that needs to happen is
hide one list of items and show another.

@<Draw temperature axis and grid lines@>=
QGraphicsLineItem *tempaxis = new QGraphicsLineItem;
tempaxis->setLine(-10, -500, -10, 0);
theScene->addItem(tempaxis);
QGraphicsLineItem *gridLine;
QGraphicsTextItem *label;
for(int y = -100; y > -600; y -= 100)@/
{@/
	gridLine = new QGraphicsLineItem;
	gridLine->setLine(0, y, 1200, y);
	theScene->addItem(gridLine);
	label = new QGraphicsTextItem;
	label->setHtml(QString("%1&deg;F").arg(-y));
	label->setPos(-55, y - (label->boundingRect().height() / 2));
	theScene->addItem(label);
	gridLinesF->append(gridLine);
	gridLinesF->append(label);
}
for(int degC = 50; degC <= 250; degC += 50)
{
	gridLine = new QGraphicsLineItem;
	int y = -(degC * (9.0/5.0) + 32);
	gridLine->setLine(0, y, 1200, y);
	gridLine->hide();
	theScene->addItem(gridLine);
	gridLinesC->append(gridLine);
	label = new QGraphicsTextItem;
	label->setHtml(QString("%1&deg;C").arg(degC));
	label->setPos(-55, y - (label->boundingRect().height() / 2));
	label->hide();
	theScene->addItem(label);
	gridLinesC->append(label);
}

@ If we are going to plot relative temperature measurements, we must obtain
information on how we wish to do that from settings. We take advantage of the
fact that iterating over the keys in a |QMap| produces results in sorted order.

While drawing the grid lines we also set up the |relativeAdjuster| that will be
used to transform incoming measurements to our coordinate system.

@<Draw secondary axes@>=
QSettings settings;
if(settings.contains("settings/graph/relative/enable"))
{
	if(settings.value("settings/graph/relative/enable").toBool())
	{
		relativeEnabled = true;
		QColor relativeColor = QColor(settings.value("settings/graph/relative/color").toString());
		QString unit = QString(settings.value("settings/graph/relative/unit").toInt() == 0 ? "F" : "C");
		QMap<double, QString> relativeAxisPairs;
		QStringList relativeAxisLabels = settings.value("settings/graph/relative/grid").toString().split(QRegExp("[\\s,]+"), QString::SkipEmptyParts);
		foreach(QString item, relativeAxisLabels)
		{
			relativeAxisPairs.insert(item.toDouble(), item);
		}
		if(relativeAxisPairs.size() > 1)
		{
			double skip = 500.0 / (relativeAxisPairs.size() - 1);
			double y = 0;
			foreach(double key, relativeAxisPairs.keys())
			{
				gridLine = new QGraphicsLineItem;
				gridLine->setLine(0, y, 1205, y);
				gridLine->setPen(QPen(relativeColor));
				theScene->addItem(gridLine);
				relativeGridLines->append(gridLine);
				label = new QGraphicsTextItem;
				label->setHtml(QString("%1&deg;%2").arg(relativeAxisPairs.value(key)).arg(unit));
				label->setPos(1210, y - (label->boundingRect().height() / 2));
				theScene->addItem(label);
				relativeGridLines->append(label);
				if(unit == "F")
				{
					relativeAdjuster->add_pair(key, -y);
				}
				else
				{
					relativeAdjuster->add_pair(key * (9.0/5.0), -y);
				}
				y -= skip;
			}
		}
	}
}

@ Two slots are used to switch between the different sets of grid lines.

@<GraphView Implementation@>=
void GraphView::showF()
{
	for(int i = 0; i < gridLinesF->size(); i++)
	{
		gridLinesF->at(i)->show();
	}
	for(int i = 0; i < gridLinesC->size(); i++)
	{
		gridLinesC->at(i)->hide();
	}
}

void GraphView::showC()
{
	for(int i = 0; i < gridLinesF->size(); i++)
	{
		gridLinesF->at(i)->hide();
	}
	for(int i = 0; i < gridLinesC->size(); i++)
	{
		gridLinesC->at(i)->show();
	}
}

@ The time axis has a tick every two minutes. The use of the |?| tertiary
operator shifts the labels with two digits a little more than labels with only
one digit. If it worked, a more resilient approach would be to take the width of
the label and center it under the tick.

@<Draw time axis and ticks@>=
QGraphicsLineItem *timeaxis = new QGraphicsLineItem;
timeaxis->setLine(0, 10, 1200, 10);
theScene->addItem(timeaxis);
for(int x = 0; x < 1201; x += 120)@/
{@/
	QGraphicsLineItem *tick = new QGraphicsLineItem;
	tick->setLine(x, 0, x, 20);
	theScene->addItem(tick);
	QGraphicsTextItem *label = new QGraphicsTextItem;
	label->setPlainText(QString("%1").arg(x/60));
	label->setPos(x - (label->boundingRect().width() / 2), 20);
	theScene->addItem(label);
}

@ Typically, the user will be able to resize the graph. When the widget is
resized, we should fit the graph to the new size of the widget. This is safe to
do as we have already turned off the scroll bars.

@<GraphView Implementation@>=
void GraphView::resizeEvent(QResizeEvent *)
{
	fitInView(theScene->sceneRect().adjusted(-50,-50,50,50));
}

@ When adding a new measurement, there are three cases that should be
considered. In the case of the first measurement, no drawing occurs. A |QList|
of line items is initialized when the second measurement is taken. Subsequent
measurements are able to simply append new line segments to the list.

Relative measurements are first converted to the coordinate system of the
appropriate secondary axis.

@<GraphView Implementation@>=
#define FULLTIMETOINT(t) (t.msec() + (t.second() * 1000) +  (t.minute() * 60 * 1000))

void GraphView::newMeasurement(Measurement measure, int tempcolumn)@/
{@/
	double offset = 0;
	if(measure.contains("relative"))
	{
		if(measure.value("relative").toBool())
		{
			if(relativeEnabled)
			{
				measure.setTemperature(relativeAdjuster->newMeasurement(measure).temperature());
			}
			else
			{
				return;
			}
		}
	}
	if(translations->contains(tempcolumn))
	{
		offset = translations->value(tempcolumn);
	}
	if(prevPoints->contains(tempcolumn))@/
	@t\1@>{@/
		@<At least one measurement exists@>@;
		if(graphLines->contains(tempcolumn))@/
		{@t\1@>
			/* More than one measurement existed. */
			graphLines->value(tempcolumn)->append(segment);@t\2@>@/
		}@/
		else@/
		{@/
			/* This is the second measurement. */
			QList<QGraphicsLineItem *> *newLine =
				new QList<QGraphicsLineItem *>;@/
			newLine->append(segment);
			graphLines->insert(tempcolumn, newLine);
		}@t\2@>@/
	}@/
	else@/
	{@/
		@<Handle the first measurement@>@;
	}
}

@ There are some parts of the code that are correct, but seem somewhat goofy.
This is especially true surrounding the graphics view architecture as this was
not working correctly when I wrote the code that uses it. The code as it is
written works for me, but when these workarounds are no longer needed it would
be better to remove them. Handling values on the time axis is one example of
this.

Some might question the use of an integer data type, particularly when storing
the result of a division operation. While this could be a concern if high
resolution wall sized displays become common, is is expected that in most cases
with sufficiently high sample rates, many data points will map to the same pixel
even with the minor data loss below.

In the case of the first measurement,

@<Handle the first measurement@>=
int x = FULLTIMETOINT(measure.time())/1000;
prevPoints->insert(tempcolumn, QPointF(x, measure.temperature()));
if(timeIndicatorEnabled)
{
	timeLine->setLine(x, 0, x, -500);
}

@ When at least one measurement already exists, we need to handle drawing the
line between the new measurement and the previous measurement.

\danger At present, the color chosen for these lines is based on the temperature
column passed to the graph. It would be better if colors could be passed to the
view for a specified series rather than have this hard coded. \endanger

@<At least one measurement exists@>=
QGraphicsLineItem *segment = new QGraphicsLineItem;
QPointF nextPoint(FULLTIMETOINT(measure.time())/1000, measure.temperature());
segment->setLine(prevPoints->value(tempcolumn).x() + offset,
					-(prevPoints->value(tempcolumn).y()),
					nextPoint.x() + offset, -(nextPoint.y()));
static QColor p[12] = {Qt::yellow, Qt::blue, Qt::cyan, Qt::red, Qt::magenta,
						Qt::green, Qt::darkGreen, Qt::darkMagenta,
						Qt::darkRed, Qt::darkCyan, Qt::darkBlue,
						Qt::darkYellow};
segment->setPen(p[tempcolumn % 12]);
theScene->addItem(segment);
prevPoints->insert(tempcolumn, nextPoint);
if(timeIndicatorEnabled)
{
	timeLine->setLine(nextPoint.x() + offset, 0, nextPoint.x() + offset, -500);
}

@ In addition to adding data to the view, we also sometimes want to clear the
view of data.

@<GraphView Implementation@>=
void GraphView::clear()
{
	int i;
	foreach(i, prevPoints->keys())
	{
		removeSeries(i);
	}
	translations->clear();
}

@ Removing a set of data from the view involves removing the lines from the
scene and removing the column from a couple data structures.

@<GraphView Implementation@>=
void GraphView::removeSeries(int column)
{
	if(graphLines->contains(column))
	{
		QList<QGraphicsLineItem *> *series = graphLines->value(column);
		QGraphicsLineItem *segment;
		foreach(segment, *series)
		{
			theScene->removeItem(segment);
		}
		qDeleteAll(*series);
	}
	graphLines->remove(column);
	prevPoints->remove(column);
}

@ Second prototype for data series translation.

@<GraphView Implementation@>=
void GraphView::setSeriesTranslation(int column, double offset)
{
	if(graphLines->contains(column))
	{
		QList<QGraphicsLineItem *> *series = graphLines->value(column);
		QGraphicsLineItem *segment;
		foreach(segment, *series)
		{
			segment->setPos(segment->pos().x()+offset, segment->pos().y());
		}
	}
	if(translations->contains(column))
	{
		translations->insert(column, offset + translations->value(column));
	}
	else
	{
		translations->insert(column, offset);
	}
}

@ Starting in \pn{} 1.6 it is possible to add a vertical line indicating the
time position of the most recent measurement. This should be hidden for loading
target roast profiles and shown depending on preference. A new method controls
this.

@<GraphView Implementation@>=
void GraphView::setTimeIndicatorEnabled(bool enabled)
{
	timeIndicatorEnabled = enabled;
	if(enabled)
	{
		timeLine->show();
	}
	else
	{
		timeLine->hide();
	}
}

@ These functions are required to create a |GraphView| object from a script.

@<Function prototypes for scripting@>=
void setGraphViewProperties(QScriptValue value, QScriptEngine *engine);
QScriptValue constructGraphView(QScriptContext *context, QScriptEngine *engine);

@ The scripting engine must be informed of the constructor.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructGraphView);
value = engine->newQMetaObject(&GraphView::staticMetaObject, constructor);
engine->globalObject().setProperty("GraphView", value);

@ The function implementation is trivial.

@<Functions for scripting@>=
QScriptValue constructGraphView(QScriptContext *, QScriptEngine *engine)
{
	QScriptValue object = engine->newQObject(new GraphView);
	setGraphViewProperties(object, engine);
	return object;
}

void setGraphViewProperties(QScriptValue value, QScriptEngine *engine)
{
	setQGraphicsViewProperties(value, engine);
}

@* A table of roasting data.

\noindent A typical roast log is a table listing temperature measurements taken
at regular intervals. The introduction of a computer brings several advantages.
A human does not need to record the measurements. Every measurement taken can be
logged, but the measurements do not all need to be displayed. The |ZoomLog|
class presents a table with time, temperature, and annotation for one or more
sets of roasting data and allows the user to select from a few different levels
of detail.

Experience has shown that one measurement every 30 or 15 seconds is most useful,
but it is also possible to view one measurement every 1, 5, 10, or 60 seconds
and there is an option to view every measurement collected. This last is what is
saved to a file.

The zooming log is implemented by keeping a measurement model with every level
of detail of interest and making sure that new measurements get to the models
they belong in. Switching the level of detail of the view then becomes a matter
of changing which model the view is using. This is very inefficient in terms of
space, but it is very fast and simple to code.

Starting in version 1.4, column sizes are persisted automatically using the
same method as described in the section on |SqlQueryView|.

@<Class declarations@>=
class MeasurementModel;@/
class ZoomLog : public QTableView@/
{@/
	@[Q_OBJECT@]@;
	@<ZoomLog private member data@>@;
	void switchLOD(MeasurementModel *m);@/
	@[private slots@]:@/
		void centerOn(int row);
		void persistColumnResize(int column, int oldsize, int newsize);
		void restoreColumnWidths();
	public:@/
		ZoomLog();
		QVariant data(int row, int column) const;
		int rowCount();
		bool saveXML(QIODevice *device);
		bool saveCSV(QIODevice *device);
		QString lastTime(int series);
		@[Q_INVOKABLE@,@, Units::Unit displayUnits()@];@t\2\2@>@/
	@[public slots@]:@/
		void setVisible(bool visibility);
		void setHeaderData(int section, QString text);
		void LOD_ms();
		void LOD_1s();
		void LOD_5s();
		void LOD_10s();
		void LOD_15s();
		void LOD_30s();
		void LOD_1m();
		void newMeasurement(Measurement measure, int tempcolumn);
		void newAnnotation(QString annotation, int tempcolumn,
							int annotationcolumn);
		void clear();
		void addOutputTemperatureColumn(int column);
		void addOutputControlColumn(int column);
		void addOutputAnnotationColumn(int column);
		void clearOutputColumns();
		void setDisplayUnits(Units::Unit scale);
		void addToCurrentColumnSet(int column);
		void clearCurrentColumnSet();@/
	protected:@/
		virtual void showEvent(QShowEvent *event);
};

@ This class uses a different model for each level of detail and provides logic
for placing measurements and annotations in the appropriate models. A list of
each model is provided for conveniently performing operations that apply to
every model.

@<ZoomLog private member data@>=
MeasurementModel *model_ms;
MeasurementModel *model_1s;
MeasurementModel *model_5s;
MeasurementModel *model_10s;
MeasurementModel *model_15s;
MeasurementModel *model_30s;
MeasurementModel *model_1m;
QList<MeasurementModel *> modelSet;
QHash<int, Measurement> lastMeasurement;
MeasurementModel *currentModel;
QList<int> saveTempCols;
QList<int> saveControlCols;
QList<int> saveNoteCols;
QList<int> currentColumnSet;

@ Most of the functionality this class provides is in getting measurements to
the right models. Every measurement goes to the full detail model. We also keep
track of the most recent measurement to detect the first measurement in a new
second and pass all of these on to the 1 second level of detail model. Some of
these are also passed to other models. Additionally, the models that store
coarser data strip the millisecond portion of the time.

A decision was made to present data promptly. With a high sample rate, some
might prefer an average of a few measurements near the reported time, but such
a feature does not exist in \pn{} currently.

The first measurement is always added to each model.

@<ZoomLog Implementation@>=
void ZoomLog::newMeasurement(Measurement measure, int tempcolumn)
{
	if(measure.time() != QTime(0, 0, 0, 0))
	{
		@<Synthesize measurements for slow hardware@>@;
	}
	model_ms->newMeasurement(measure, tempcolumn);
	if(lastMeasurement.contains(tempcolumn))
	{
		if(measure.time().second() !=
			lastMeasurement.value(tempcolumn).time().second())
		{
			Measurement adjusted = measure;
			QTime adjtime(0, measure.time().minute(), measure.time().second(), 0);
			adjusted.setTime(adjtime);
			model_1s->newMeasurement(adjusted, tempcolumn);
			if(adjusted.time().second() % 5 == 0)
			{
				model_5s->newMeasurement(adjusted, tempcolumn);
				if(adjusted.time().second() % 10 == 0)
				{
					model_10s->newMeasurement(adjusted, tempcolumn);
				}
				if(adjusted.time().second() % 15 == 0)
				{
					model_15s->newMeasurement(adjusted, tempcolumn);
					if(adjusted.time().second() % 30 == 0)
					{
						model_30s->newMeasurement(adjusted, tempcolumn);
						if(adjusted.time().second() == 0)
						{
							model_1m->newMeasurement(adjusted, tempcolumn);
						}
					}
				}
			}
		}
		@<Synthesize measurements for columns in set@>@;
	}
	else
	{
		@<Add the first measurement to every model@>@;
	}
	lastMeasurement.insert(tempcolumn, measure);
}

@ The first measurement in a series should be the epoch measurement. This
should exist in every level of detail.

@<Add the first measurement to every model@>=
MeasurementModel *m;
foreach(m, modelSet)
{
	m->newMeasurement(measure, tempcolumn);
}

@ Some measurement hardware in use cannot guarantee delivery of at least one
measurement per second. This causes problems for the current |ZoomLog|
implementation as, for example, if there is no measurement at a time where
the seconds are divisible by 5, there will be no entry in that view. This can
result in situations where the |ZoomLog| at its default view of one measurement
every 30 seconds might not display any data at all aside from the first
measurement, the last measurement, and any measurement that happens to have an
annotation associated with it. The solution in this case is to synthesize
measurements so that the |ZoomLog| thinks it gets at least one measurement
every second.

The current approach simply replicates the last measurement every second until
the time for the most recent measurement is reached, however it would likely be
better to interpolate values between the two most recent real measurements as
this would match the graphic representation rather than altering it when later
reviewing the batch.

@<Synthesize measurements for slow hardware@>=
if(lastMeasurement.contains(tempcolumn))
{
	if(lastMeasurement[tempcolumn].time() < measure.time())
	{
		QList<QTime> timelist;
		for(QTime i = lastMeasurement.value(tempcolumn).time().addSecs(1); i < measure.time(); i = i.addSecs(1))
		{
			timelist.append(i);
		}
		for(int i = 0; i < timelist.size(); i++)
		{
			Measurement synthesized = measure;
			synthesized.setTime(timelist[i]);
			newMeasurement(synthesized, tempcolumn);
		}
	}
}

@ New to \pn{} 1.4 is the concept of a current column set. This was added to
improve support for devices where measurements on different data series may not
arrive at exactly the same time and for multi-device configurations where
measurements from different devices are unlikely to arrive at the same time.
This can cause issues with log annotations and serialization. The solution is
to group all columns that are logically part of the same data acquisition
process and as measurements come in, the most recent measurement from other
columns can be duplicated at the new time. Two methods are responsible for
managing this measurement set. One adds a column to the set and the other
removes all columns from the set.

@<ZoomLog Implementation@>=
void ZoomLog::addToCurrentColumnSet(int column)
{
	currentColumnSet.append(column);
}

void ZoomLog::clearCurrentColumnSet()
{
	currentColumnSet.clear();
}

@ Replicating the measurements occurs as measurements are delivered. Note
that this code will not be called for the first measurement in each column.

@<Synthesize measurements for columns in set@>=
if(currentColumnSet.contains(tempcolumn))
{
	int replicationcolumn;
	foreach(replicationcolumn, currentColumnSet)
	{
		if(replicationcolumn != tempcolumn)
		{
			if(lastMeasurement.contains(replicationcolumn))
			{
				if(measure.time() > lastMeasurement.value(replicationcolumn).time())
				{
					Measurement synthetic = lastMeasurement.value(replicationcolumn);
					synthetic.setTime(measure.time());
					model_ms->newMeasurement(synthetic, replicationcolumn);
					if(synthetic.time().second() != lastMeasurement.value(replicationcolumn).time().second())
					{
						Measurement adjusted = synthetic;
						adjusted.setTime(QTime(0, synthetic.time().minute(), synthetic.time().second(), 0));
						model_1s->newMeasurement(adjusted, replicationcolumn);
						if(adjusted.time().second() % 5 == 0)
						{
							model_5s->newMeasurement(adjusted, replicationcolumn);
							if(adjusted.time().second() % 10 == 0)
							{
								model_10s->newMeasurement(adjusted, replicationcolumn);
							}
							if(adjusted.time().second() % 15 == 0)
							{
								model_15s->newMeasurement(adjusted, replicationcolumn);
								if(adjusted.time().second() % 30 == 0)
								{
									model_30s->newMeasurement(adjusted, replicationcolumn);
									if(adjusted.time().second() == 0)
									{
										model_1m->newMeasurement(adjusted, replicationcolumn);
									}
								}
							}
						}
					}
					lastMeasurement[replicationcolumn] = synthetic;
				}
			}
		}
	}
}

@ Just as the first measurement should exist at every level of detail, so should
any annotations. The measurement models will, when presented with an annotation,
apply it to the most recently entered measurement in the specified data series.
This presents a problem for the coarser views as the data point the annotation
belongs to most likely does not exist in that view. Furthermore, the model as it
is currently written will overwrite annotations that already exist on a
measurement if it is still the most recently entered. When collecting samples
during profile development, it is common to produce several annotations in a
short amount of time. The most useful thing to do in such a case is to add the
most recent measurement to each model and then apply the annotation. This, of
course, should only be done if there is a most recent measurement. An annotation
regarding the starting condition of the roaster should apply to the yet to be
recorded time zero measurement.

Note that only the value from the temperature column specified is displayed in
the row with the annotation. It would be better to check the full detail model
to determine if there are other measurements at the annotation time and present
these as well. Another possibility in the case of data not existing in other
temperature columns would be to interpolate a value from the existing data in
these columns, however this is potentially challenging as I would want to keep
true measurements distinct from estimations.

@<ZoomLog Implementation@>=
void ZoomLog::newAnnotation(QString annotation, int tempcolumn,
							int annotationcolumn)
{
	model_ms->newAnnotation(annotation, tempcolumn, annotationcolumn);
	MeasurementModel *m;
	if(lastMeasurement.contains(tempcolumn))
	{
		foreach(m, modelSet)
		{
			m->newMeasurement(lastMeasurement.value(tempcolumn), tempcolumn);
		}
	}
	foreach(m, modelSet)
	{
		m->newAnnotation(annotation, tempcolumn, annotationcolumn);
	}
}

@ As measurements are added to the model, the model will emit rowChanged
signals. These signals are connected to a function here that will attempt to
scroll the view to keep the most recently entered data in the center of the
view.

@<ZoomLog Implementation@>=
void ZoomLog::centerOn(int row)
{
	scrollTo(currentModel->index(row, 0), QAbstractItemView::PositionAtCenter);
}

@ Once we are done with the data in the table, we want to clear it to prepare
for new data. This also clears the lists holding the output columns to use when
saving data.

@<ZoomLog Implementation@>=
void ZoomLog::clear()
{
	MeasurementModel *m;
	foreach(m, modelSet)
	{
		m->clear();
	}
	lastMeasurement.clear();
	saveTempCols.clear();
	saveControlCols.clear();
	saveNoteCols.clear();
}

@ These are depreciated methods originally written to assist in serializing
model data prior to the introduction of the |XMLOutput| class. These methods are
likely to be removed in a future version of the program.

@<ZoomLog Implementation@>=
QVariant ZoomLog::data(int row, int column) const
{
	return model_ms->data(model_ms->index(row, column, QModelIndex()),
							Qt::DisplayRole);
}

int ZoomLog::rowCount()
{
	return model_ms->rowCount();
}

@ This method initializes an |XMLOutput| instance, passes the columns that we
would like to save to that object, and uses it to write an XML file with the
desired data to the specified device.

Since the output format does not currently specify a unit, there is an
assumption that the XML output will always have measurements in Fahrenheit. If
the model is not currently displaying measurements in Fahrenheit, it is asked to
do so before writing the XML data. User preference is restored after the XML
data has been written. Since this change is only performed on |model_ms|, most
users will never notice this.

@<ZoomLog Implementation@>=
bool ZoomLog::saveXML(QIODevice *device)
{
	Units::Unit prevUnits = model_ms->displayUnits();
	if(prevUnits != Units::Fahrenheit)
	{
		model_ms->setDisplayUnits(Units::Fahrenheit);
	}
	XMLOutput writer(model_ms, device, 0);
	int c;
	foreach(c, saveTempCols)
	{
		writer.addTemperatureColumn(model_ms->headerData(c, Qt::Horizontal).
		                                      toString(), c);
	}
	foreach(c, saveControlCols)
	{
		writer.addControlColumn(model_ms->headerData(c, Qt::Horizontal).
		                                  toString(), c);
	}
	foreach(c, saveNoteCols)
	{
		writer.addAnnotationColumn(model_ms->headerData(c, Qt::Horizontal).
		                                     toString(), c);
	}
	bool retval = writer.output();
	if(prevUnits != Units::Fahrenheit)
	{
		model_ms->setDisplayUnits(prevUnits);
	}
	return retval;
}

@ This method is similar to |saveXML()|. The main difference is that CSV data is
exported instead of XML.

@<ZoomLog Implementation@>=
bool ZoomLog::saveCSV(QIODevice *device)
{
	CSVOutput writer(currentModel, device, 0);
	int c;
	foreach(c, saveTempCols)
	{
		writer.addTemperatureColumn(model_ms->headerData(c, Qt::Horizontal).
		                                                 toString(), c);
	}
	foreach(c, saveControlCols)
	{
		writer.addControlColumn(model_ms->headerData(c, Qt::Horizontal).
		                                             toString(), c);
	}
	foreach(c, saveNoteCols)
	{
		writer.addAnnotationColumn(model_ms->headerData(c, Qt::Horizontal).
		                                     toString(), c);
	}
	return writer.output();
}

@ Several little functions, all alike\nfnote{If you get the reference, you may
enjoy reading another \cweb{} program:\par\indent\pdfURL{%
http://www-cs-staff.stanford.edu/$\sim$uno/programs/advent.w.gz}
{http://www-cs-staff.stanford.edu/~uno/programs/advent.w.gz}}, are used to
switch the view from one level of detail to another.

@<ZoomLog Implementation@>=
void ZoomLog::switchLOD(MeasurementModel *m)
{
	disconnect(currentModel, SIGNAL(rowChanged(int)), this, 0);
	setModel(m);
	currentModel = m;
	connect(currentModel, SIGNAL(rowChanged(int)), this, SLOT(centerOn(int)));
}

void ZoomLog::LOD_ms()
{
	switchLOD(model_ms);
}

void ZoomLog::LOD_1s()
{
	switchLOD(model_1s);
}

void ZoomLog::LOD_5s()
{
	switchLOD(model_5s);
}

void ZoomLog::LOD_10s()
{
	switchLOD(model_10s);
}

void ZoomLog::LOD_15s()
{
	switchLOD(model_15s);
}

void ZoomLog::LOD_30s()
{
	switchLOD(model_30s);
}

void ZoomLog::LOD_1m()
{
	switchLOD(model_1m);
}

@ It can be useful to display temperature measurements in various units. To do
so, we simply tell all of the models which unit to provide data in. It is also
possible to obtain the currently selected unit.

@<ZoomLog Implementation@>=
void ZoomLog::setDisplayUnits(Units::Unit scale)
{
	model_ms->setDisplayUnits(scale);
	model_1s->setDisplayUnits(scale);
	model_5s->setDisplayUnits(scale);
	model_10s->setDisplayUnits(scale);
	model_15s->setDisplayUnits(scale);
	model_30s->setDisplayUnits(scale);
	model_1m->setDisplayUnits(scale);
}

Units::Unit ZoomLog::displayUnits()
{
	return model_ms->displayUnits();
}

@ For convenience, a method is provided for returning a string containing the
time of the last inserted measurement in a given data series.

@<ZoomLog Implementation@>=
QString ZoomLog::lastTime(int series)
{
	Measurement measure = lastMeasurement.value(series);
	QTime time = measure.time();
	return time.toString("h:mm:ss.zzz");
}

@ This just leaves the initial table setup.

@<ZoomLog Implementation@>=
ZoomLog::ZoomLog() : QTableView(NULL), model_ms(new MeasurementModel(this)),
	model_1s(new MeasurementModel(this)),@/ model_5s(new MeasurementModel(this)),
	model_10s(new MeasurementModel(this)),@/ model_15s(new MeasurementModel(this)),
	model_30s(new MeasurementModel(this)),@/ model_1m(new MeasurementModel(this))@/
{@/
	setEditTriggers(QAbstractItemView::NoEditTriggers);
	setSelectionMode(QAbstractItemView::NoSelection);
	modelSet << model_ms << model_1s << model_5s << model_10s << model_15s <<
		model_30s << model_1m;
	currentModel = model_30s;
	setModel(currentModel);
	connect(currentModel, SIGNAL(rowChanged(int)), this, SLOT(centerOn(int)));
	connect(horizontalHeader(), SIGNAL(sectionResized(int, int, int)),
	        this, SLOT(persistColumnResize(int, int, int)));
	connect(horizontalHeader(), SIGNAL(sectionCountChanged(int, int)),
	        this, SLOT(restoreColumnWidths()));
}

@ A new method was added to this class for version 1.0.7. This allows header
data to be set on the log and have it propagate to the model set. The longer
term plan involves removing the hard coding of some of the header data.

@<ZoomLog Implementation@>=
void ZoomLog::setHeaderData(int section, QString text)
{
	MeasurementModel *m;
	foreach(m, modelSet)
	{
		m->setHeaderData(section, Qt::Horizontal, QVariant(text));
	}
}

@ As of version 1.2.3, these methods replace similar methods added for version
1.0.8. The main difference is that it is now possible to save multiple data
series to the same output document.

Starting in version 1.6 it is possible to save control columns. These should
contain unitless data which should remain unaffected by the current displayed
unit.

@<ZoomLog Implementation@>=
void ZoomLog::addOutputTemperatureColumn(int column)
{
	saveTempCols.append(column);
}

void ZoomLog::addOutputControlColumn(int column)
{
	saveControlCols.append(column);
}

void ZoomLog::addOutputAnnotationColumn(int column)
{
	saveNoteCols.append(column);
}

void ZoomLog::clearOutputColumns()
{
	saveTempCols.clear();
	saveControlCols.clear();
	saveNoteCols.clear();
}

@ Starting in version 1.4 two methods have been introduced which are used to
save and restore column widths.

@<ZoomLog Implementation@>=
void ZoomLog::persistColumnResize(int column, int, int newsize)
{
	@<Save updated column size@>@;
}

void ZoomLog::restoreColumnWidths()
{
	@<Restore table column widths@>@;
}

void ZoomLog::setVisible(bool visibility)
{
	QTableView::setVisible(visibility);
}

void ZoomLog::showEvent(QShowEvent *)
{
	@<Restore table column widths@>@;
}

@ The |ZoomLog| class is one of the more complicated classes to expose to the
scripting engine. In addition to a script constructor, we also need functions
for saving and restoring the state of the display and functions for saving data
from the log in the supported formats.

@<Function prototypes for scripting@>=
void setZoomLogProperties(QScriptValue value, QScriptEngine *engine);
QScriptValue constructZoomLog(QScriptContext *context, QScriptEngine *engine);
QScriptValue ZoomLog_saveXML(QScriptContext *context, QScriptEngine *engine);
QScriptValue ZoomLog_saveCSV(QScriptContext *context, QScriptEngine *engine);
QScriptValue ZoomLog_saveState(QScriptContext *context, QScriptEngine *engine);
QScriptValue ZoomLog_restoreState(QScriptContext *context,
                                  QScriptEngine *engine);
QScriptValue ZoomLog_lastTime(QScriptContext *context, QScriptEngine *engine);
QScriptValue ZoomLog_saveTemporary(QScriptContext *context,
                                   QScriptEngine *engnie);
QScriptValue ZoomLog_setDisplayUnits(QScriptContext *context,
                                     QScriptEngine *engine);

@ Of these, the global object only needs to know about the constructor.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructZoomLog);
value = engine->newQMetaObject(&ZoomLog::staticMetaObject, constructor);
engine->globalObject().setProperty("ZoomLog", value);

@ The script constructor sets properties on the newly created object to allow
the other functions to be called.

@<Functions for scripting@>=
QScriptValue constructZoomLog(QScriptContext *, QScriptEngine *engine)@/
{@/
	QScriptValue object = engine->newQObject(new ZoomLog);
	setZoomLogProperties(object, engine);
	return object;@/
}

void setZoomLogProperties(QScriptValue value, QScriptEngine *engine)
{
	setQTableViewProperties(value, engine);
	value.setProperty("saveXML", engine->newFunction(ZoomLog_saveXML));
	value.setProperty("saveCSV", engine->newFunction(ZoomLog_saveCSV));
	value.setProperty("saveState", engine->newFunction(ZoomLog_saveState));
	value.setProperty("restoreState",
					  engine->newFunction(ZoomLog_restoreState));
	value.setProperty("lastTime", engine->newFunction(ZoomLog_lastTime));
	value.setProperty("saveTemporary",
	                  engine->newFunction(ZoomLog_saveTemporary));
	value.setProperty("setDisplayUnits", engine->newFunction(ZoomLog_setDisplayUnits));
}

@ The functions for saving data are simple wrappers around the corresponding
calls in |ZoomLog|, except for a function added for saving data to a temporary
file. The last provides the name of the file saved for use in copying that data
to a database entry.

@<Functions for scripting@>=
QScriptValue ZoomLog_saveXML(QScriptContext *context, QScriptEngine *engine)
{
	ZoomLog *self = getself<ZoomLog *>(context);
	bool retval = self->saveXML(argument<QIODevice *>(0, context));
	return QScriptValue(engine, retval);
}

QScriptValue ZoomLog_saveCSV(QScriptContext *context, QScriptEngine *engine)
{
	ZoomLog *self = getself<ZoomLog *>(context);
	bool retval = self->saveCSV(argument<QIODevice *>(0, context));
	return QScriptValue(engine, retval);
}

QScriptValue ZoomLog_saveTemporary(QScriptContext *context,
                                   QScriptEngine *engine)
{
	ZoomLog *self = getself<ZoomLog *>(context);
	QString filename = QDir::tempPath();
	filename.append("/");
	filename.append(QUuid::createUuid().toString());
	filename.append(".xml");
	QFile *file = new QFile(filename);
	self->saveXML(file);
	file->close();
	delete file;
	return QScriptValue(engine, filename);
}

@ The remaining functions are convenience functions for use with the scripting
engine. One will save the column widths to a |QSettings| object. Another will
restore the column widths from settings. Finally, there is a function for
obtaining a string representation of the most recent measurement from a data
series.

\danger There are a couple of problems with these functions. First, the body of
these functions would probably be better off as methods in the |ZoomLog| class
proper, either as slots or |Q_INVOKABLE| so the special scripting functions
could be eliminated. Second, rather than polluting the settings with separate
entries for each column, it would probably be better to store all of these
values in an array.\endanger

|ZoomLog_saveState()| was changed in version 1.2.3 to not save a new value for
the column width if that width is |0|. This was done mainly to ease debugging.
Similarly, |ZoomLog_restoreState()| picks a new default value when |0| is
encountered.

@<Functions for scripting@>=
QScriptValue ZoomLog_saveState(QScriptContext *context, QScriptEngine *)
{
	ZoomLog *self = getself<@[ZoomLog *@]>(context);
	QString key = argument<QString>(0, context);
	int columns = argument<int>(1, context);
	QSettings settings;
	for(int i = 0; i < columns; i++)
	{
		if(self->columnWidth(i))
		{
			settings.beginGroup(key);
			settings.setValue(QString("%1").arg(i), self->columnWidth(i));
			settings.endGroup();
		}
	}
	return QScriptValue();
}

QScriptValue ZoomLog_restoreState(QScriptContext *context, QScriptEngine *)
{
	ZoomLog *self = getself<@[ZoomLog *@]>(context);
	QString key = argument<QString>(0, context);
	int columns = argument<int>(1, context);
	QSettings settings;
	for(int i = 0; i < columns; i++)
	{
		settings.beginGroup(key);
		self->setColumnWidth(i,
			settings.value(QString("%1").arg(i), 80).toInt());
		if(settings.value(QString("%1").arg(i), 80).toInt() == 0)
		{
			self->setColumnWidth(i, 80);
		}
		settings.endGroup();
	}
	return QScriptValue();
}

QScriptValue ZoomLog_lastTime(QScriptContext *context, QScriptEngine *engine)
{
	ZoomLog *self = getself<@[ZoomLog *@]>(context);
	return QScriptValue(engine, self->lastTime(argument<int>(0, context)));
}

@ There seems to be a bad interaction when enumerated value types as used as
the argument to slot methods called through QtScript. Script code that attempts
to make use of the enumeration appears to get the value without any type
information. When attempting to use that value as an argument the meta-object
system cannot find an appropriate match and the script just hangs silently.
The solution is to wrap such methods in the script bindings and explicitly cast
the argument value to the enumerated type. This looks stupid but it works.

@<Functions for scripting@>=
QScriptValue ZoomLog_setDisplayUnits(QScriptContext *context, QScriptEngine *)
{
	ZoomLog *self = getself<@[ZoomLog *@]>(context);
	self->setDisplayUnits((Units::Unit)argument<int>(0, context));
	return QScriptValue();
}

@* A model for roasting data.

\noindent Qt provides a tool called the model view architecture. This provides a
uniform interface allowing different types of model classes to work with
different types of view classes without either needing to know implementation
details of the other. \pn{} provides the |MeasurementModel| as a specialization
of |QAbstractItemModel| for use in this architecture.

@<Class declarations@>=
class MeasurementList;@/
class MeasurementModel : public QAbstractItemModel@/
{@t\1@>@/
	Q_OBJECT@;
	Units::Unit unit;
	QList<MeasurementList *> *entries;
	QStringList *hData;
	int colcount;
	QHash<int, int> *lastTemperature;
	QList<MeasurementList *>::iterator@, lastInsertion;
	QHash<int, bool> *controlColumns;
	public:@/
		MeasurementModel(QObject *parent = NULL);
		~MeasurementModel();
		int rowCount(const QModelIndex &parent = QModelIndex()) const;
		int columnCount(const QModelIndex &parent = QModelIndex()) const;
		bool setHeaderData(int section, Qt::Orientation orientation,
							const QVariant &value,@|int role = Qt::DisplayRole);
		QVariant data(const QModelIndex &index, int role) const;
		bool setData(const QModelIndex &index, const QVariant &value,
						int role = Qt::EditRole);
		Qt::ItemFlags flags(const QModelIndex &index) const;
		QVariant headerData(int section, Qt::Orientation orientation,
							int role = Qt::DisplayRole) const;
		QModelIndex index(int row, int column,
							const QModelIndex &parent = QModelIndex()) const;
		QModelIndex parent(const QModelIndex &index) const;
		Units::Unit displayUnits();@/
	@t\4@>public slots@t\kern-3pt@>:@/
		void newMeasurement(Measurement measure, int tempcolumn);
		void newAnnotation(QString annotation, int tempcolumn,
							int annotationColumn);
		void clear();
		void setDisplayUnits(Units::Unit scale);
	signals:@/
		void rowChanged(int);@t\2@>@/
}@t\kern-3pt@>;

@ The measurement model stores its data in a list of measurement lists. This
allows the model to store as many sets of data as needed. In order to keep
measurements in the model sorted by time, the measurement list adds two
comparison functions.

@<Class declarations@>=
class MeasurementList : public QVariantList@/
{@t\1@>@/
	@t\4@>public:@/
		bool operator<(const MeasurementList &other) const;
		bool operator==(const MeasurementList &other) const;@t\2@>@/
}@t\kern-3pt@>;

@ The overload of |<| checks if the time in one list (always stored in the first
column) is less than the time stored in the second. The overload of |==| is used
in an optimization that allows us to skip the search procedure on model
insertion.

@<MeasurementModel Implementation@>=
bool MeasurementList::operator<(const MeasurementList &other) const
{
	return this->first().toTime() < other.first().toTime();
}

bool MeasurementList::operator==(const MeasurementList &other) const
{
	return this->first().toTime() == other.first().toTime();
}

@ The |MeasurementModel| class extends the |QAbstractItemModel| class to work
better with measurements and annotations that are passed around in \pn{}. Many
of the class methods are required because of that choice. For example, the
parent function which is never used directly:

@<MeasurementModel Implementation@>=
QModelIndex MeasurementModel::parent(const QModelIndex&) const
{
	return QModelIndex();
}

@ Perhaps the most complicated part of this class is the code for dealing with a
new measurement. This is complicated by the requirement to insert measurements
while keeping the model sorted by time.

@<MeasurementModel Implementation@>=
void MeasurementModel::newMeasurement(Measurement measure, int tempcolumn)
{
	if(measure.scale() == Units::Unitless)
	{
		controlColumns->insert(tempcolumn, true);
	}
	else
	{
		controlColumns->insert(tempcolumn, false);
	}
	MeasurementList *temp;
	temp = new MeasurementList;
	temp->append(QVariant(measure.time()));
	@<Find the insertion point@>@;
	MeasurementList *newEntry;
	int insertion;
	if(i != entries->end())
	{
		insertion = entries->indexOf(*i);
		if((*i)->first().toTime() == measure.time())
		{
			@<Insert a new measurement at an existing time@>@;
		}
		else
		{
			@<Insert a new measurement somewhere else@>@;
		}
	}
	else
	{
		@<Append a measurement@>@;
	}
	if(tempcolumn >= colcount)
	{
		colcount = tempcolumn + 1;
	}
	emit rowChanged(insertion);
	delete temp;
}

@ To find the insertion point for new measurements we use a binary search of the
existing data. The code below is a direct adaptation of Program B\nfnote{%
\underbar{The Art of Computer Programming} Volume 3 Sorting and Searching 2nd
ed. (Knuth, 1997) Section 6.2.1: Searching an Ordered Table} modified to use
list iterators and control structures more familiar to \CPLUSPLUS/programmers
rather than {\mc MIX} machine codes. When the loop exits |i| is the insertion
point.

\medskip

\centerline{\includegraphics{search}}

\smallskip

\centerline{Figure \secno: Binary Search}

\medskip

@<Find the insertion point@>=
@<Scan from most recent insertion@>@;
if(quickscan == false)
{
	i = entries->begin();
	QList<MeasurementList *>::iterator@, u = entries->end();
	QList<MeasurementList *>::iterator@, midpoint;
	int n = u - i;
	int rA;
	while(n > 0)@/
	{
		rA = n>>1; /* |rA = |~$\bigl\lfloor{n\over2}\bigr\rfloor$ */
		midpoint = i + rA;
		if(**midpoint < *temp)@/
		{
			i = midpoint + 1;
			n -= rA + 1;
		}
		else@/
		{
			n = rA;
		}
	}
}

@ The binary search, while correct, is not a particularly optimal choice for
this application. While the average running time for this is on the order of
$\ln N$ when each insertion point is equally likely, the reality of this
application is that insertions will likely be at the beginning of the list, at
the point of the most recent insertion, or a short distance from the most recent
insertion. By first considering the possibility that the measurement should be
inserted at or near the most recent measurement, shorter, more constant running
times as $N$ increases can be obtained.

To do this, when the number of measurements in the list is above a small number
which must be greater than 1, we check first if the insertion point is at the
last insertion (the |<| comparison fails and we do an |==| comparison before
giving up), then we check a small number of rows for either the end of the list,
in which case the insertion point is at the end, or for a point at which the |<|
comparison fails. If neither condition holds for a small number of comparisons
we resort to the binary search.

Performance measurements with this modification compared with previous versions
shows that this provides a huge performance boost.

@<Scan from most recent insertion@>=
@[QList<MeasurementList *>::iterator@, i@] = lastInsertion;@/
bool quickscan = false;@/
if(entries->size() > 5)@/
{@t\1@>@/
	if(**i < *temp)@/
	{@t\1@>@/
		i += 1;@/
		for(int j = 10; j > 0; j--)@/
		{@t\1@>@/
			if(i != entries->end())@/
			{@t\1@>@/
				if(**i < *temp)@/
				{
					i += 1;
				}@/
				else@/
				{@t\1@>@/
					quickscan = true;
					break;@t\2@>@/
				}@t\2@>@/
			}@/
			else@/
			{@t\1@>@/
				quickscan = true;
				break;@t\2@>@/
			}@t\2@>@/
		}@t\2@>@/
	}@/
	else@/
	{@t\1@>@/
		if(**i == *temp)@/
		{@t\1@>@/
			quickscan = true;@t\2@>@/
		}@t\2@>@/
	}@t\2@>@/
}

@ If the chosen insertion point is at an existing time, we don'@q'@>t need to
worry about inserting rows. There may be a need to increase the size of the
measurement list to accept an entry in a new data series.

@<Insert a new measurement at an existing time@>=
if((*i)->size() < tempcolumn + 1)
{
	for(int j = (*i)->size() - 1; j < tempcolumn + 1; j++)
	{
		(*i)->append(QVariant());
	}
}
(*i)->replace(tempcolumn, measure);
lastInsertion = i;
emit dataChanged(createIndex(insertion, tempcolumn),
					createIndex(insertion, tempcolumn));
lastTemperature->insert(tempcolumn, insertion);

@ If the measurement is not past the end of the existing data and the insertion
point has a different time, we need to use |beginInsertRows()| and
|endInsertRows()| to notify any attached view that a new row will be added.

@<Insert a new measurement somewhere else@>=
beginInsertRows(QModelIndex(), insertion, insertion);
newEntry = new MeasurementList;
newEntry->append(QVariant(measure.time()));
for(int j = 0; j < tempcolumn + 1; j++)
{
	newEntry->append(QVariant());
}
newEntry->replace(tempcolumn, measure);
lastInsertion = entries->insert(i, newEntry);
endInsertRows();
lastTemperature->insert(tempcolumn, insertion);

@ If the insertion point is past the end of the existing data, a new row should
be appended to the data. This only needs to be a separate case to prevent the
comparison with a nonexistent entry. This is very similar to the case of
inserting at a new time anywhere else.

@<Append a measurement@>=
insertion = entries->size();@/
@<Insert a new measurement somewhere else@>

@ The other bit of code that'@q'@>s a little bit more complicated than other
parts of the class handles adding annotations to the data. Two signals are
emitted in this method. The |dataChanged| signal is expected by view classes
that can use this model. The |rowChanged| signal is used by |ZoomLog| to scroll
the view to the row the annotation has been added to. This is mainly useful
when loading a target profile and entering the first annotation prior to
starting the batch.

@<MeasurementModel Implementation@>=
void MeasurementModel::newAnnotation(QString annotation, int tempcolumn,@|
										int annotationColumn)
{
	int r;
	if(lastTemperature->contains(tempcolumn))
	{
		r = lastTemperature->value(tempcolumn);
	}
	else
	{
		r = 0;
	}
	if(r == 0 && entries->size() == 0)
	{
		@<Create the first row@>@;
	}
	MeasurementList *row = entries->at(r);
	if(row->size() <= annotationColumn)
	{
		for(int i = row->size() - 1; i < annotationColumn + 1; i++)
		{
			row->append(QVariant());
		}
	}
	row->replace(annotationColumn, annotation);
	emit dataChanged(createIndex(r, annotationColumn),
						createIndex(r, annotationColumn));
	emit rowChanged(r);
	if(annotationColumn > colcount - 1)
	{
		colcount = annotationColumn + 1;
	}
}

@ There is no need to further complicate the function by adding the annotation
when the first row is created.

@<Create the first row@>=
beginInsertRows(QModelIndex(), 0, 0);
MeasurementList *newEntry = new MeasurementList;
newEntry->append(QVariant(QTime(0, 0, 0, 0)));
entries->append(newEntry);
endInsertRows();

@ Clearing the model data is a simple matter of deleting every row, remembering
to let any attached views know that we are doing this, and resetting the number
of columns.

@<MeasurementModel Implementation@>=
void MeasurementModel::clear()
{
	beginRemoveRows(QModelIndex(), 0, entries->size());
	while(entries->size() != 0)
	{
		MeasurementList *row = entries->takeFirst();
		delete row;
	}
	endRemoveRows();
	colcount = hData->size();
	lastTemperature->clear();
	reset();
}

@ While these methods for adding measurements and annotations are fine when
recording a stream of measurements, either from the |DAQ| or when loading saved
data, there are also cases where we'@q'@>d like to edit the data in the model
directly from the table view. For this, we need to reimplement |setData()|.

Note that editing from the |ZoomLog| has never been supported. While stream
inserted data currently preserves all properties of inserted measurements,
using |setData| it is possible to insert a numeric value as if it were a
measurement. Such an entry will not have any additional information associated
and cannot be expected to exhibit behavior implemented through the use of that
extra information.

Very little input checking is done here. Editable views may want to place
delegates\nfnote{Qt 4.4: Delegate Classes\par\indent\hbox{%
\pdfURL{http://doc.trolltech.com/4.4/model-view-delegate.html}{%
http://doc.trolltech.com/4.4/model-view-delegate.html}}} on the columns to make
editing the data easier and less error prone.

@<MeasurementModel Implementation@>=
bool MeasurementModel::setData(const QModelIndex &index,
								const QVariant &value, int role)@t\2\2@>@/
{@t\1@>@/
	if(role != Qt::EditRole && role != Qt::DisplayRole)@/
	{@t\1@>@/
		return false;@t\2@>@/
	}@/
	@<Check that the index is valid@>@;
	if(!valid)@/
	{@t\1@>@/
		return false;@t\2@>@/
	}@/
	MeasurementList *row = entries->at(index.row());
	if(index.column() >= row->size())
	{
		@<Expand the row to prepare for new data@>@;
	}
	if(index.column() == 0)
	{
		@<Edit data in the time column@>@;
	}
	else
	{
		@<Edit data in other columns@>@;
	}
	return true;@t\2@>@/
}

@ There is no sense in attempting to edit the data if there isn'@q'@>t any data
available to edit. This check is also used when retrieving data from the model.

@<Check that the index is valid@>=
bool valid = false;
if(index.isValid())@/
{@t\1@>@/
	if(index.row() < entries->size())@/
	{@t\1@>@/
		if(index.column() < colcount)@/
		{@t\1@>@/
			valid = true;@t\2@>@/
		}@t\2@>@/
	}@t\2@>@/
}

@ When editing data, there might not be anything where we want to add the data.
For example, adding an annotation to an otherwise unannotated measurement. This
is fine, but we need to expand the row instead of inserting data out of bounds.

@<Expand the row to prepare for new data@>=
for(int i = row->size() - 1; i < index.column(); i++)
{
	row->append(QVariant());
}

@ Changing time data must be considered separately from other data. As the model
keeps itself sorted based on the time field, allowing the user to get the model
data out of order would result in poorly defined behavior later. Our approach is
to remove the row from the model temporarily then reuse the code from
|newMeasurement()| to find the new insertion point. No attempt is made to merge
the contents from two rows with identical times, but an attempt is made to not
be too rigid in what we expect the user to enter. If an invalid time is entered,
we give up and leave the data as we found it.

@<Edit data in the time column@>=
QTime time;@/
if(!(time = QTime::fromString(value.toString(), "m:s.z")).isValid())@/
{@t\1@>@/
	if(!(time = QTime::fromString(value.toString(), "m:s")).isValid())@/
	{@t\1@>@/
		return false;@t\2@>@/
	}@t\2@>@/
}@/
row = entries->takeAt(index.row());
row->replace(index.column(), QVariant(time));
MeasurementList *temp = row;
@<Find the insertion point@>@;
entries->insert(i, row);
int newRow = entries->indexOf(*i);
if(newRow < index.row())@/
{
	emit dataChanged(createIndex(newRow, index.column()), index);
}
else@/
{
	emit dataChanged(index, createIndex(newRow, index.column()));
}

@ Data in other columns is a little easier to handle.

@<Edit data in other columns@>=
row->replace(index.column(), value);
emit dataChanged(index, index);

@ As it has already been established that the first column is always considered
the time of the measurement, this assumption can be built into the model
constructor.

@<MeasurementModel Implementation@>=
MeasurementModel::MeasurementModel(QObject *parent) : QAbstractItemModel(parent),
	unit(Units::Fahrenheit), hData(new QStringList),
	lastTemperature(new QHash<int, int>),
	controlColumns(new QHash<int, bool>)@/
{
	colcount = 1;
	entries = new QList<MeasurementList *>;
	lastInsertion = entries->begin();
	hData->append(tr("Time"));
}

@ In the destructor we need to remember to clean up after ourselves.

@<MeasurementModel Implementation@>=
MeasurementModel::~MeasurementModel()
{
	clear();
	delete entries;
	delete hData;
}

@ A pair of functions are used to determine the number of rows and columns the
model provides. No entries in the model have children, so the parent should
always be the invisible root object. If it isn'@q'@>t, we should return 0.

@<MeasurementModel Implementation@>=
int MeasurementModel::rowCount(const QModelIndex &parent) const
{
	if(parent == QModelIndex())
	{
		return entries->size();
	}
	return 0;
}

int MeasurementModel::columnCount(const QModelIndex &parent) const
{
	if(parent == QModelIndex())
	{
		return colcount;
	}
	return 0;
}

@ The model maintains a set of header data. At present, it only supports header
data at the top of the model due to the author'@q'@>s preference to not have row
numbers littering the left of the table (the time column is sufficient to
identify the row for the user).

The model view architecture supports the concept of different data roles in the
header data. At present, this model ignores the role when setting header data.

@<MeasurementModel Implementation@>=
bool MeasurementModel::setHeaderData(int section, Qt::Orientation orientation,@|
										const QVariant &value, int)@t\2@>@/
@t\4@>{@/
	if(orientation == Qt::Horizontal)@/
	{@t\1@>@/
		if(hData->size() < section + 1)@/
		{@/
			for(int i = hData->size(); i < section + 1; i++)@/
			{@/
				if(colcount < i)@/
				{@/
					beginInsertColumns(QModelIndex(), i, i);
				}
				hData->append(QString());
				if(colcount < i)@/
				{@/
					endInsertColumns();
				}
			}
		}
		hData->replace(section, value.toString());
		emit headerDataChanged(orientation, section, section);
		if(colcount < section + 1)@/
		{@/
			colcount = section + 1;
		}@/
		return true;@t\2@>@/
	}@/
	return false;@/
@t\4@>}

@ While the current implementation always receives measurements in degrees
Fahrenheit, international users often want to see data presented in Celsius. To
do this, a slot is provided to allow selecting among different units. When this
method is called, the model indicates that all attached views must update all
displayed data and requests for temperature data will have any needed conversion
performed before sending that information to the view. Another method is
available to request a number identifyin the currently displayed units.

@<MeasurementModel Implementation@>=
void MeasurementModel::setDisplayUnits(Units::Unit scale)
{
	beginResetModel();
	unit = scale;
	endResetModel();
}

Units::Unit MeasurementModel::displayUnits()
{
	return unit;
}

@ A model is generally quite useless if the data the model contains cannot be
retrieved. To do this, we check that the index requested is a valid index that
is within the bounds of the model data and that a role we understand has been
requested. If none of these conditions are met, a default constructed |QVariant|
is returned.

At present, |Qt::DisplayRole| and |Qt::EditRole| are supported. These return the
same thing. Views will request the display role for presenting the information
to the user, but they will request the edit role if the user attempts to modify
the data through a view.

As of version 1.6, |Qt::UserRole| allows retrieval of raw measurement data.

@<MeasurementModel Implementation@>=
QVariant MeasurementModel::data(const QModelIndex &index, int role) const@/
{@/
	@<Check that the index is valid@>@;
	if(!valid)
	{
		return QVariant();
	}
	MeasurementList *row = entries->at(index.row());
	if(role == Qt::UserRole)
	{
		return QVariant(row->at(index.column()));
	}
	if(role == Qt::DisplayRole || role == Qt::EditRole)
	{
		if(index.column() > row->size())
		{
			return QVariant();
		}
		else
		{
			if(index.column() == 0)
			{
				return QVariant(row->at(0).toTime().toString("mm:ss.zzz"));
			}
			else if(lastTemperature->contains(index.column()))
			{
				QVariantMap v = row->at(index.column()).toMap();
				if(!v.contains("measurement"))
				{
					return QVariant();
				}
				if((Units::Unit)(v.value("unit").toInt()) == Units::Unitless)
				{
					return v.value("measurement");
				}
				else
				{
					if(v.contains("relative"))
					{
						if(v.value("relative") == true)
						{
							return QVariant(QString("%1").arg(Units::convertRelativeTemperature(v.value("measurement").toDouble(), (Units::Unit)(v.value("unit").toInt()), unit)));
						}
					}
					return QVariant(QString("%1").arg(Units::convertTemperature(v.value("measurement").toDouble(), (Units::Unit)(v.value("unit").toInt()), unit)));
				}
			}
			return QVariant(row->at(index.column()).toString());
		}
	}
	return QVariant();@/
}

@ Views also must be able to retrieve the header data.

@<MeasurementModel Implementation@>=
QVariant MeasurementModel::headerData(int section, Qt::Orientation orientation,
										int role ) const
{
	if(orientation == Qt::Horizontal)
	{
		if(role == Qt::DisplayRole)
		{
			if(section < hData->size())
			{
				return QVariant(hData->at(section));
			}
		}
	}
	return QVariant();
}

@ Views will sometimes request information about the interactions available for
an index. In the case of this model, each index is treated in the same way.

It may be a good idea to extend the model class to allow models that can be
edited through the view such as the table view presented in the |LogEditWindow|
and models that probably shouldn'@q'@>t be edited in the view, such as the models
managed by |ZoomLog|. This could be done by subclassing and only reimplementing
this method. Otherwise, a new method to specify that the user should not edit
the model could be provided and a flag would be checked here.

@<MeasurementModel Implementation@>=
Qt::ItemFlags MeasurementModel::flags(const QModelIndex &index) const@/
{@/
	@<Check that the index is valid@>@;
	if(valid)
	{
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
	}
	return 0;
}

@ Much of the way models are interacted with in Qt'@q'@>s model view architecture is
through model indices. The model is responsible for creating these indices from
row column pairs.

@<MeasurementModel Implementation@>=
QModelIndex MeasurementModel::index(int row, int column,
									const QModelIndex &parent) const@t\2\2@>@/
{@t\1@>@/
	if(parent == QModelIndex())@/
	{@t\1@>@/
		if(row < entries->size() && entries->isEmpty() == false)@/
		{@/
			if(column < entries->at(row)->size())@/
			{@/
				return createIndex(row, column);@/
			}@/
		}@t\2@>@/
	}@/
	return QModelIndex();@/
@t\4@>}

@** Annotating roast data.

\noindent In addition to recording time temperature pairs, \pn{} allows the user
to annotate the roasting log to indicate control changes, the end of the batch,
or samples collected from the roast. It is important that these annotations can
be applied to the roasting log quickly. This is the purpose of the
|AnnotationButton| class.

@<Class declarations@>=
class AnnotationButton : public QPushButton@/
{@t\1@>@/
	Q_OBJECT@;
	QString note;
	int tc;
	int ac;
	int count;
	public:@/
		AnnotationButton(const QString &text, QWidget *parent = NULL);@/
	@t\4@>public slots@t\kern-3pt@>:@/
		void setAnnotation(const QString &annotation);
		void setTemperatureColumn(int tempcolumn);
		void setAnnotationColumn(int annotationcolumn);
		void annotate();
		void resetCount();
	signals:@/
		void annotation(QString annotation, int tempcolumn,
						int notecolumn);@t\2@>@/
}@t\kern-3pt@>;

@ Setting up a new annotation button begins with the constructor. This takes a
string specifying the text that will appear on the button and optionally a
parent widget. This is also a sensible place to set up the desired behavior the
button should exhibit when clicked.

@<AnnotationButton Implementation@>=
AnnotationButton::AnnotationButton(const QString &text, QWidget *parent) :
	QPushButton(text, parent), note(""), tc(0), ac(0), count(0)@/
{
	connect(this, SIGNAL(clicked()), this, SLOT(annotate()));
}

@ The slot that is called when the button is clicked needs to be able to handle
two types of annotations. Simple annotations send the same annotation every time
the button is clicked. Counting annotations are annotation strings that have a
|"%1"| somewhere in the string. That substring will be replaced with an integer
that is incremented before the annotation is sent. This integer is initialized
to 0. It will be incremented to 1 the first time the button is clicked and that
will be the replacement value.

@<AnnotationButton Implementation@>=
void AnnotationButton::annotate()
{
	if(note.contains("%1"))
	{
		count++;
		emit annotation(note.arg(count), tc, ac);
	}
	else
	{
		emit annotation(note, tc, ac);
	}
}

@ A few methods are available to indicate which temperature series the
annotation should be applied to, which column in a table view the annotation
should be entered in, and what text should be in the annotation.

@<AnnotationButton Implementation@>=
void AnnotationButton::setTemperatureColumn(int tempcolumn)
{
	tc = tempcolumn;
}

void AnnotationButton::setAnnotationColumn(int annotationcolumn)
{
	ac = annotationcolumn;
}

void AnnotationButton::setAnnotation(const QString &annotation)
{
	note = annotation;
}

@ Finally, in the case of counting annotations, there should be a way to reset
the number used in the annotation.

@<AnnotationButton Implementation@>=
void AnnotationButton::resetCount()
{
	count = 0;
}

@ A script constructor is needed to allow an |AnnotationButton| to be created
from a script.

@<Function prototypes for scripting@>=
QScriptValue constructAnnotationButton(QScriptContext *context,
                                       QScriptEngine *engine);
void setAnnotationButtonProperties(QScriptValue value, QScriptEngine *engine);

@ In order to use this, the engine needs to be informed of the function.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructAnnotationButton);
value = engine->newQMetaObject(&AnnotationButton::staticMetaObject,
                               constructor);
engine->globalObject().setProperty("AnnotationButton", value);

@ The implementation is trivial.

@<Functions for scripting@>=
QScriptValue constructAnnotationButton(QScriptContext *context,
                                       QScriptEngine *engine)
{
	QScriptValue object =
		engine->newQObject(new AnnotationButton(argument<QString>(0, context)));
	setAnnotationButtonProperties(object, engine);
	return object;
}

void setAnnotationButtonProperties(QScriptValue value, QScriptEngine *engine)
{
	setQPushButtonProperties(value, engine);
}

@* A spin box for annotations.

\noindent While the annotation button is adequate for most log annotation tasks,
there are some times where the log should contain a small number of numerical
observations where it is inconvenient or cost prohibitive to enable automated
logging. For these tasks, a spin box that produces an appropriate annotation may
be useful.

@<Class declarations@>=
class AnnotationSpinBox : public QDoubleSpinBox@/
{@t\1@>@/
	Q_OBJECT@;
	QString pretext;
	QString posttext;
	int tc;
	int ac;
	bool change;
	public:
		AnnotationSpinBox(const QString &pret, const QString &postt,
		                  QWidget *parent = NULL);@/
	@t\4@>public slots@t\kern-3pt@>:@/
		void setPretext(const QString &pret);
		void setPosttext(const QString &postt);
		void setTemperatureColumn(int tempcolumn);
		void setAnnotationColumn(int annotationcolumn);
		void annotate();
		void resetChange();
	signals:@/
		void annotation(QString annotation, int tempcolumn,
		                int notecolumn);@t\2@>@/
}@t\kern-3pt@>;

@ Setting up a new annotation spin box begins with the constructor. This takes
two strings specifying optional text that may appear before or after the
numerical value of the spin box in the annotation. No spaces are placed between
the text and the numerical values, so if such spacing is required, it must be
included in the relevant string.

This function also sets up the behavior for firing annotation events. An
annotation should be fired when the user presses enter while the spin box has
focus. This implementation will also attempt to fire an annotation when the
spin box loses focus. No annotation is fired if the value of the spin box has
not been changed since the previous annotation event.

@<AnnotationSpinBox Implementation@>=
AnnotationSpinBox::AnnotationSpinBox(const QString &pret,
                                     const QString &postt,@|
                                     QWidget *parent)
	: QDoubleSpinBox(parent), pretext(pret), posttext(postt)@/
{
	resetChange();
	connect(this, SIGNAL(editingFinished()), this, SLOT(annotate()));
	connect(this, SIGNAL(valueChanged(double)), this, SLOT(resetChange()));
}

@ The |resetChange()| signal just sets a boolean which is checked prior to
sending an annotation. This is called automatically when the value of the spin
box is changed, but it should also be called when a batch is finished in case
the first required annotation is the same as the last required annotation from
the previous batch.

@<AnnotationSpinBox Implementation@>=
void AnnotationSpinBox::resetChange()@t\2\2@>@/
{@t\1@>@/
	change = true;@t\2@>@/
}

@ The annotation slot is responsible for determining if an annotation should be
sent. The current implementation is to only attempt to send such a signal when
the |editingFinished()| signal is emitted, however this could also be connected
to other signals.

@<AnnotationSpinBox Implementation@>=
void AnnotationSpinBox::annotate()@t\2\2@>@/
{@t\1@>@/
	if(change)@/
	{@t\1@>@/
		change = false;@/
		emit annotation(QString("%1%2%3").arg(pretext).
		                     arg(value()).arg(posttext), tc, ac);@t\2@>@/
	}@t\2@>@/
}

@ These methods set various properties of the annotation.

@<AnnotationSpinBox Implementation@>=
void AnnotationSpinBox::setTemperatureColumn(int tempcolumn)
{
	tc = tempcolumn;
}

void AnnotationSpinBox::setAnnotationColumn(int annotationcolumn)
{
	ac = annotationcolumn;
}

void AnnotationSpinBox::setPretext(const QString &pret)
{
	pretext = pret;
}

void AnnotationSpinBox::setPosttext(const QString &postt)
{
	posttext = postt;
}

@ Two functions are needed to interface |AnnotationSpinBox| with the host
environment. Additional functions are required for setting up inheritance
properly.

@<Function prototypes for scripting@>=
QScriptValue constructAnnotationSpinBox(QScriptContext *context,
                                        QScriptEngine *engine);
void setAnnotationSpinBoxProperties(QScriptValue value, QScriptEngine *engine);
void setQDoubleSpinBoxProperties(QScriptValue value, QScriptEngine *engine);
void setQAbstractSpinBoxProperties(QScriptValue value, QScriptEngine *engine);

@ The first of these is passed into the host environment.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructAnnotationSpinBox);
value = engine->newQMetaObject(&AnnotationSpinBox::staticMetaObject,
                               constructor);
engine->globalObject().setProperty("AnnotationSpinBox", value);

@ The script constructor creates a new object and passes it to a function that
is responsible for setting up properties in the inheritance chain.

@<Functions for scripting@>=
QScriptValue constructAnnotationSpinBox(QScriptContext *context,
                                        QScriptEngine *engine)
{
	QScriptValue object = engine->newQObject(new AnnotationSpinBox(
	     argument<QString>(0, context), argument<QString>(1, context)));
	setAnnotationSpinBoxProperties(object, engine);
	return object;
}

void setAnnotationSpinBoxProperties(QScriptValue value, QScriptEngine *engine)
{
	setQDoubleSpinBoxProperties(value, engine);
}

void setQDoubleSpinBoxProperties(QScriptValue value, QScriptEngine *engine)
{
	setQAbstractSpinBoxProperties(value, engine);
}

void setQAbstractSpinBoxProperties(QScriptValue value, QScriptEngine *engine)
{
	setQWidgetProperties(value, engine);
}

@** A digital timer.

\noindent Before \pn{} was a data logger, it was a simple digital timer written
because there were no shops in Racine that could sell a simple dual digital
count up timer at a time when my first timer was malfunctioning. After
attempting to purchase a replacement device at several stores that have sold
such devices in the past, I decided to spend a couple hours writing my own
timer.

For historical reasons, the |TimerDisplay| class is considerably more functional
than \pn{} requires. Those needing only a digital timer can extract the code for
this class and use it in a timer application. This should work on any platform
supported by Qt.

@<Class declarations@>=
class TimerDisplay : public QLCDNumber@/
{@t\1@>@/
	Q_OBJECT@/
	@<TimerDisplay Properties@>@;
	@t\4@>private slots@t\kern-3pt@>:@/
		void updateTime();
		void setCountUpMode();
		void setCountDownMode();
		void setClockMode();
	public:@/
		TimerDisplay(QWidget *parent = NULL);
		~TimerDisplay();
		enum TimerMode
		{
			CountUp,
			CountDown,
			Clock
		};
		QString value();
		QTime seconds();
		TimerMode mode();
		bool isRunning();
		QTime resetValue();
		QString displayFormat();
		bool autoReset();@/
	@t\4@>public slots@t\kern-3pt@>:@/
		void setTimer(QTime value = QTime(0, 0, 0));
		void setMode(TimerMode mode);
		void startTimer();
		void stopTimer();
		void copyTimer();
		void setResetValue(QTime value = QTime(0, 0, 0));
		void reset();
		void setDisplayFormat(QString format);
		void setAutoReset(bool reset);
		void updateDisplay();
	signals:@/
		void valueChanged(QTime);
		void runStateChanged(bool);@/
	private:@/
		@<TimerDisplay Private Variables@>@;@t\2@>@/
}@t\kern-3pt@>;

@ Qt provides a property system based on its meta-object system. This allows for
a number of advanced features which \pn{} does not use. The properties available
for the TimerDisplay class exist for historical reasons, but there are some
plans for future development which may make use of them. The properties may also
be useful for someone using this class in another program.

@<TimerDisplay Properties@>=
Q_PROPERTY(QTime seconds READ seconds WRITE setTimer)@/
Q_PROPERTY(TimerMode mode READ mode WRITE setMode)@/
Q_PROPERTY(bool running READ isRunning)@/
Q_PROPERTY(QTime resetValue READ resetValue WRITE setResetValue)@/
Q_PROPERTY(QString displayFormat READ displayFormat WRITE setDisplayFormat)@/
Q_PROPERTY(bool autoReset READ autoReset WRITE setAutoReset)@/

@ A number of private variables are used to implement this class.

@<TimerDisplay Private Variables@>=
QTime s;
QTime r;
QTimer clock;
TimerDisplay::TimerMode m;
bool running;
bool ar;
QAction *startAction;
QAction *stopAction;
QAction *resetAction;
QString f;
QTime relative;
QTime base;

@ |TimerDisplay| is a specialization of |QLCDNumber| designed for time keeping
purposes. It sets up a timer that fires roughly every half second to see if it
needs to update itself. The constructor sets this up, but does not start the
timer. The class provides three actions which can be used to start, stop, or
reset the timer. These actions are also set up in the constructor.

By default, the timer will display its time in hours, minutes, and seconds. This
can be changed as is done with the batch timer (it is expected that nobody will
want to spend an hour or more to roast a batch of coffee). The display style is
also changed to a sensible default, but this can be changed with the usual
|QLCDNumber| methods.

@<TimerDisplay Implementation@>=
TimerDisplay::TimerDisplay(QWidget *parent) : QLCDNumber(8, parent),
	s(QTime(0, 0, 0)), r(QTime(0, 0, 0)), clock(NULL),@/ m(TimerDisplay::CountUp),
	running(false), ar(false), startAction(new QAction(tr("Start"), NULL)),@/
	stopAction(new QAction(tr("Stop"), NULL)),
	resetAction(new QAction(tr("Reset"), NULL)),@/ f(QString("hh:mm:ss")),
	relative(QTime::currentTime()), base(QTime(0, 0, 0))@/
{
	connect(startAction, SIGNAL(triggered(bool)), this, SLOT(startTimer()));
	connect(stopAction, SIGNAL(triggered(bool)), this, SLOT(stopTimer()));
	connect(resetAction, SIGNAL(triggered(bool)), this, SLOT(reset()));
	clock.setInterval(500);
	clock.setSingleShot(false);
	connect(&clock, SIGNAL(timeout()), this, SLOT(updateTime()));
	setSegmentStyle(Filled);
	updateDisplay();
}

@ The complicated bits are all in the |updateTime()| method. The behavior of
this function depends on the current |TimerMode| of the display.

@<TimerDisplay Implementation@>=
void TimerDisplay::updateTime()
{
	QTime time;
	int cseconds = 0;
	int oseconds = 0;
	int r = 0;
	QTime nt = QTime(0, 0, 0);
	int n = 0;
	int bseconds = 0;
	switch(m)@/
	{@t\1@>@/
		case TimerDisplay::CountUp:@/
			@<Check for Timer Increment@>;
			break;
		case TimerDisplay::CountDown:@/
			@<Check for Timer Decrement@>;
			break;
		case TimerDisplay::Clock:@/
			@<Check for Clock Change@>;
			break;
		default:@/
			Q_ASSERT_X(false, "updateTime", "invalid timer mode");
			break;@t\2@>@/
	}
	updateDisplay();
}

@ To have the timer count up, we calculate the value that the timer should
indicate and compare it to the time indicated. If there is a difference, we
update the time to the new value and send emit a signal.

@<Check for Timer Increment@>=
@<Load seconds since base time into r@>@;
nt = nt.addSecs(r);
if(nt != s)
{
	s = nt;
	emit valueChanged(s);
}

@ Here we want to calculate the number of seconds in the current time, the
number of seconds in a base time, and the difference between the two. The
value loaded into oseconds could probably be cached.

@<Load seconds since base time into r@>=
#define TIMETOINT(t) ((t.hour() * 60 * 60) + (t.minute() * 60) + (t.second()))

time = QTime::currentTime();
cseconds = TIMETOINT(time);
oseconds = TIMETOINT(relative);
r = cseconds - oseconds;

@ The logic for a count down timer is very similar to the logic for a count up
timer. A key difference is that we don't want to continue counting down if the
timer has already reached 0.

@<Check for Timer Decrement@>=
if(s > QTime(0, 0, 0))@/
{@/
	@<Load seconds since base time into r@>@;
	bseconds = TIMETOINT(base);
	n = bseconds - r;
	nt = nt.addSecs(n);
	if(nt != s)
	{
		s = nt;
		emit valueChanged(s);
	}
}

@ The clock mode is the simplest case as it just needs to find out if the time
has changed.

@<Check for Clock Change@>=
time = QTime::currentTime();
if(time != s)
{
	s = time;
	emit valueChanged(s);
}

@ When counting up or down, it is important to record the time at which the
timer starts. The clock that triggers time updates must also be started. The
timer also needs to reset its value if that behavior is desired.

@<TimerDisplay Implementation@>=
#define TIMESUBTRACT(t1, t2) (t1.addSecs(-(TIMETOINT(t2))).addSecs(-t2.msec()))

void TimerDisplay::startTimer()@t\2\2@>@/
{@t\1@>@/
	if(!running)@/
	{@t\1@>@/
		relative = QTime::currentTime();
		if(ar)@/
		{
			reset();
		}
		else
		{
			relative = TIMESUBTRACT(relative, s);
		}
		if(m == Clock)@/
		{
			updateTime();
		}
		base = s;
		clock.start();@/
		running = true;
		emit runStateChanged(true);@t\2@>@/
	}@t\2@>@/
}

@ Stopping the timer is a little simpler. Remember to stop the clock so we
aren't updating senselessly.

@<TimerDisplay Implementation@>=
void TimerDisplay::stopTimer()@t\2\2@>@/
{@t\1@>@/
	if(running)@/
	{@t\1@>@/
		clock.stop();@/
		running = false;
		emit runStateChanged(false);@t\2@>@/
	}@t\2@>@/
}

@ The clock is also stopped in the destructor.

@<TimerDisplay Implementation@>=
TimerDisplay::~TimerDisplay()
{
	clock.stop();
}

@ The rest of the functions are trivial. There are functions for changing the
timer mode:

@<TimerDisplay Implementation@>=
void TimerDisplay::setCountUpMode()
{
	m = TimerDisplay::CountUp;
}

void TimerDisplay::setCountDownMode()
{
	m = TimerDisplay::CountDown;
}

void TimerDisplay::setClockMode()
{
	m = TimerDisplay::Clock;
}

@ There are a few functions to obtain information about the state of the timer.

@<TimerDisplay Implementation@>=
QString TimerDisplay::value()
{
	return s.toString(f);
}

QTime TimerDisplay::seconds()
{
	return s;
}

TimerDisplay::TimerMode TimerDisplay::mode()
{
	return m;
}

bool TimerDisplay::isRunning()
{
	return running;
}

QTime TimerDisplay::resetValue()
{
	return r;
}

QString TimerDisplay::displayFormat()
{
	return f;
}

bool TimerDisplay::autoReset()
{
	return ar;
}

@ There are also some functions for setting aspects of the timer state.

@<TimerDisplay Implementation@>=
void TimerDisplay::setTimer(QTime value)
{
	if(value.isValid())
	{
		s = value;
		updateDisplay();
		emit valueChanged(value);
	}
}

void TimerDisplay::setMode(TimerDisplay::TimerMode mode)
{
	m = mode;
}

void TimerDisplay::setResetValue(QTime value)
{
	r = value;
}

void TimerDisplay::setDisplayFormat(QString format)
{
	f = format;
	setNumDigits(format.length());
}

void TimerDisplay::setAutoReset(bool reset)
{
	ar = reset;
}

@ |TimerDisplay| supports using the system clipboard to copy the current timer
value.

@<TimerDisplay Implementation@>=
void TimerDisplay::copyTimer()
{
	QApplication::clipboard()->setText(value());
}

@ Resetting the timer is simple. We don'@q'@>t reset the timer if it is still running
mainly to prevent accidents.

@<TimerDisplay Implementation@>=
void TimerDisplay::reset()
{
	if(!running)
	{
		s = r;
		updateDisplay();
	}
}

@ Finally, there is the function for changing the text of the display to the
current time value.

@<TimerDisplay Implementation@>=
void TimerDisplay::updateDisplay()
{
	display(value());
}

@ Exposing |TimerDisplay| to the host environment is simple.

@<Function prototypes for scripting@>=
QScriptValue constructTimerDisplay(QScriptContext *context,
                                   QScriptEngine *engine);
void setTimerDisplayProperties(QScriptValue value, QScriptEngine *engine);

@ The engine must be informed of the script constructor.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructTimerDisplay);
value = engine->newQMetaObject(&TimerDisplay::staticMetaObject, constructor);
engine->globalObject().setProperty("TimerDisplay", value);

@ The implementation of these functions is trivial.

@<Functions for scripting@>=
QScriptValue constructTimerDisplay(QScriptContext *, QScriptEngine *engine)
{
	QScriptValue object = engine->newQObject(new TimerDisplay);
	setTimerDisplayProperties(object, engine);
	return object;
}

void setTimerDisplayProperties(QScriptValue value, QScriptEngine *engine)
{
	setQLCDNumberProperties(value, engine);
}


@** The Human Computer Interface.

\noindent A few classes are required for putting the rest of the program
together in a way that it can be used by a human. There is a layout class for
arranging widgets in a way that is not simple with the layouts provided by Qt.
There are classes for labeling the various indicators. There are also window
classes that put all of this together in a useful and usable way. One of these
classes is currently depreciated.

@* The PackLayout Class.

\noindent The |PackLayout| class provides functionality similar to the
|QBoxLayout| class in Qt. It allows the construction of a row or column of
widgets. Each item will take up space along the orientation of the layout equal
to its size hint except for the last widget which will take up all remaining
space. Widgets will be resized in the direction perpendicular to the orientation
of the layout to use all available space.

This class was originally written with the |WidgetDecorator| class which we will
get to later in mind, but it has found use in other places where the left or top
most widgets should not be resized.

By default, a new |PackLayout| will arrange widgets horizontally. This can be
changed with a call to |setOrientation()|.

@<Class declarations@>=
class PackLayout : public QLayout@/
{@/
	int doLayout(const QRect &rect, bool testOnly) const;@/
	QList<QLayoutItem *> itemList;@/
	Qt::Orientations@, orientation;@/
	public:@/
		PackLayout(QWidget *parent, int margin = 0, int spacing = -1);
		PackLayout(int spacing = -1);
		~PackLayout();
		void addItem(QLayoutItem *item);
		Qt::Orientations@, expandingDirections() const;
		bool hasHeightForWidth() const;
		int heightForWidth(int width) const;
		int count() const;
		QLayoutItem *itemAt(int index) const;
		QSize minimumSize() const;
		void setGeometry(const QRect &rect);
		void setOrientation(Qt::Orientations direction);
		QSize sizeHint() const;
		QLayoutItem *takeAt(int index);
};

@ The interesting portion of this class is in |doLayout()|. This function goes
over the items in the layout and sets the geometry appropriately.

The seemingly odd choice of returning |y| at the end of this function (indeed of
having a return value at all) is to allow this function to provide the return
value needed in |heightForWidth()|.

If |testOnly| is set to |true|, |y| will be calculated, but the widget geometry
will not be changed.

@<PackLayout Implementation@>=
int PackLayout::doLayout(const QRect &rect, bool testOnly) const
{
	int x = rect.x();
	int y = rect.y();
	QLayoutItem *item;
	if(orientation == Qt::Horizontal)
	{
		@<Lay the widgets out horizontally@>@;
	}
	else
	{
		@<Lay the widgets out vertically@>@;
	}
	return y;
}

@ To lay the widgets out horizontally, we go over each item in the list taking
the width of the size hint and spacing into account unless the item is the last
item in the list, in which case the right of the widget needs to be at the end
of the available space. We use the foreach construction that Qt provides to
iterate over each item in the list in much the same way as foreach constructions
are used in languages that support them directly.

@<Lay the widgets out horizontally@>=
foreach(item, itemList)
{
	int nextX = x + item->sizeHint().width() + spacing();
	int right = x + item->sizeHint().width();
	if(item == itemList.last())
	{
		right = rect.right();
	}
	int bottom = rect.bottom();
	if(!testOnly)
	{
		item->setGeometry(QRect(QPoint(x, y), QPoint(right, bottom)));
	}
	x = nextX;
}

@ Laying out the widgets vertically is very similar.

@<Lay the widgets out vertically@>=
foreach(item, itemList)
{
	int nextY = y + item->sizeHint().height() + spacing();
	int bottom = y + item->sizeHint().height();
	if(item == itemList.last())
	{
		bottom = rect.bottom();
	}
	int right = rect.right();
	if(!testOnly)
	{
		item->setGeometry(QRect(QPoint(x, y), QPoint(right, bottom)));
	}
	y = nextY;
}

@ As a layout class, there are a number of things the class should be able to do
in order to play nicely with other classes. One of these is determining the
minimum size of the layout. The minimum size of the layout is equal to the space
required for each item in the layout plus the margin space. The margin space
will be equal to twice the specified margin in each direction to account for a
top, bottom, left, and right margin.

@<PackLayout Implementation@>=
QSize PackLayout::minimumSize() const
{
	QSize size;
	QLayoutItem *item;
	foreach(item, itemList)
	{
		if(orientation == Qt::Horizontal)
		{
			size += QSize(item->minimumSize().width(), 0);
			if(size.height() < item->minimumSize().height())
			{
				size.setHeight(item->minimumSize().height());
			}
		}
		else
		{
			size += QSize(0, item->minimumSize().height());
			if(size.width() < item->minimumSize().width())
			{
				size.setWidth(item->minimumSize().width());
			}
		}
	}
	size += QSize(2*margin(), 2*margin());
	return size;
}

@ |PackLayout| features two constructors. One allows for setting the margin,
spacing, and a parent widget at the time of construction. The other creates a
parentless layout which will have to be added to another widget or layout.

@<PackLayout Implementation@>=
PackLayout::PackLayout(QWidget *parent, int margin, int spacing) :
	QLayout(parent)@/
{
	setMargin(margin);
	setSpacing(spacing);
	setOrientation(Qt::Horizontal);
}

PackLayout::PackLayout(int spacing)
{
	setSpacing(spacing);
	setOrientation(Qt::Horizontal);
}

@ In Qt, items in a layout are owned by that layout. When the layout is
destroyed, all of the items in that layout must also be deleted.

@<PackLayout Implementation@>=
PackLayout::~PackLayout()
{
	QLayoutItem *item;
	while((item = takeAt(0)))
	{
		delete item;
	}
}

@ Deleting the items uses the |takeAt()| method to remove each widget from the
layout prior to deleting it. The item requested should exist, but if it doesn'@q'@>t,
|NULL| is returned.

@<PackLayout Implementation@>=
QLayoutItem* PackLayout::takeAt(int index)
{
	if(index >= 0 && index < itemList.size())
	{
		return itemList.takeAt(index);
	}
	else
	{
		return NULL;
	}
}

@ If we are interested in which item is in a particular position in the layout
but do not want to remove it from the layout, |itemAt()| provides that.

@<PackLayout Implementation@>=
QLayoutItem* PackLayout::itemAt(int index) const
{
	if(index >= 0 && index < itemList.size())
	{
		return itemList.at(index);
	}
	else
	{
		return NULL;
	}
}

@ A layout class is not very useful unless there is a way to get items into the
layout. The |QLayoutItem| class is designed in such a way that it is possible to
pass pointers to objects that inherit |QLayout| or |QWidget|.

The base |QLayout| class provides an |addWidget()| method that will use our
version of |addItem()|. That should be used when adding a widget to the layout.
The Qt documentation recommends also providing an |addLayout()| method so that
other code does not need to call this method, but that has not been provided
yet.

@<PackLayout Implementation@>=
void PackLayout::addItem(QLayoutItem *item)
{
	itemList.append(item);
}

@ It is sometimes useful to know how many items are in a layout.

@<PackLayout Implementation@>=
int PackLayout::count() const@;@/
{@/
	return itemList.size();@/
}

@ A few more functions are needed to make the layout class work well with other
classes. For more details, please consult the Qt Reference
Documentation\nfnote{Qt Reference Documentation\par\indent\hbox{%
\pdfURL{http://doc.trolltech.com/4.3/index.html}%
{http://doc.trolltech.com/4.3/index.html}}}

@<PackLayout Implementation@>=
Qt::Orientations PackLayout::expandingDirections() const
{
	return Qt::Vertical | Qt::Horizontal;
}

bool PackLayout::hasHeightForWidth() const@t\2\2@>@/
{@t\1@>@/
	return false;@t\2@>@/
}@/

int PackLayout::heightForWidth(int width) const
{
	return doLayout(QRect(0, 0, width, 0), true);
}

void PackLayout::setGeometry(const QRect &rect)
{
	QLayout::setGeometry(rect);
	doLayout(rect, false);
}

QSize PackLayout::sizeHint() const
{
	return minimumSize();
}

@ It was mentioned previously that this layout is capable of lining widgets up
in a row or presenting them in a column. This is done with the
|setOrientation()| method.

@<PackLayout Implementation@>=
void PackLayout::setOrientation(Qt::Orientations direction)
{
	orientation = direction;
	doLayout(geometry(), false);
}

@* The SceneButton Class.

\noindent Ordinarily, mouse down events that are passed from a |QGraphicsView|
to an interactive |QGraphicsScene| will continue to pass that click down to an
item in the scene. This class is used when we are interested in a click anywhere
in the view and it doesn'@q'@>t really matter where in the scene that click occurred
or even if there is a graphics item at that point. Any click passed to the
|SceneButton| will cause the scene to emit a signal containing the screen
coordinates of the click.

This was originally designed for use in the |WidgetDecorator| class. While the
functionality provided is not currently used, the original plan was to use this
to provide access to configuration options.

It is possible that this class is no longer necessary even if features it was
made for are implemented.

@<Class declarations@>=
class SceneButton : public QGraphicsScene@/
{@/
	Q_OBJECT@;
	public:@/
		SceneButton();
		~SceneButton();
	protected:@/
		void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
	signals:@/
		void clicked(QPoint pos);
};

@ The implementation is trivial.

@<SceneButton Implementation@>=
SceneButton::SceneButton() : QGraphicsScene()@/
{
	/* Nothing has to be done here. */
}

SceneButton::~SceneButton()
{
	/* Nothing has to be done here. */
}

void SceneButton::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	emit clicked(mouseEvent->buttonDownScreenPos(mouseEvent->button()));
}

@* The WidgetDecorator Class.

\noindent The |WidgetDecorator| class provides a way to label various widgets
while also providing additional options for interacting with them. The
decoration can exist to the left or atop the widget being decorated. When the
label is to the left of the widget, the label text is rotated.

This class is likely to change considerably in the future as features are added
that allow actions to be added to the decoration to allow various configuration
options.

@<Class declarations@>=
class WidgetDecorator : public QWidget@/
{
	Q_OBJECT@;
	PackLayout *layout;
	QGraphicsView *label;
	QGraphicsTextItem *text;
	SceneButton *scene;
	public:@/
		WidgetDecorator(QWidget *widget, const QString &labeltext,@|
						Qt::Orientations@, orientation = Qt::Horizontal,@|
						QWidget *parent = NULL, Qt::WindowFlags f = 0);
		~WidgetDecorator();
		void setBackgroundBrush(QBrush background);
		void setTextColor(QColor color);
};

@ Almost everything this class currently does is handled in the constructor.

@<WidgetDecorator Implementation@>=
WidgetDecorator::WidgetDecorator(QWidget *widget, const QString &labeltext,
									Qt::Orientations orientation,
									QWidget *parent, Qt::WindowFlags f)@/:
	QWidget(parent, f), label(new QGraphicsView()),
	scene(new SceneButton())@t\2@>@/
{
	layout = new PackLayout(this);
	layout->setOrientation(orientation);
	@<Prepare the graphics view@>@;
	@<Add the label to the scene@>@;
	@<Adjust the decoration width@>@;
	@<Pack widgets into the layout@>@;
}

@ The decoration is a |QGraphicsView|. To get this to look right, we need to
make sure there aren'@q'@>t any scroll bars and there shouldn'@q'@>t be a frame
surrounding it. While we'@q'@>re at it, we allow it to accept clicks, though this
functionality is not yet used.

@<Prepare the graphics view@>=
label->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
label->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
label->setFrameShape(QFrame::NoFrame);
label->setInteractive(true);

@ The |QGraphicsView| needs a scene to display anything. The scene consists of a
background which, by default is solid cyan. This can be changed later by setting
a different background brush. Text also needs to be added to the scene. If the
decoration is to the left of the widget, the text needs to be rotated.

@<Add the label to the scene@>=
scene->setBackgroundBrush(Qt::cyan);
text = scene->addText(labeltext);
if(orientation == Qt::Horizontal)
{
	text->rotate(270.0);
}
label->setScene(scene);

@ The decoration should have the text centered in the view. The widget should
also be no wider (or taller for horizontal orientation) than necessary for the
text.

The case for horizontal orientation here may seem a little strange, however the
dimensions of the bounding rectangle are not affected by rotation. This means
that even though we want the width of the rotated text, this is the same as the
height of the text.

@<Adjust the decoration width@>=
if(orientation == Qt::Horizontal)
{
	label->setMaximumWidth((int)(text->boundingRect().height() + 1));
}
else
{
	label->setMaximumHeight((int)(text->boundingRect().height() + 1));
}
label->centerOn(text);

@ Once the decoration is ready, the decoration and the widget being decorated
can be added to the layout. A minimum size for the compound widget is also
calculated.

@<Pack widgets into the layout@>=
layout->addWidget(label);
layout->addWidget(widget);
if(orientation == Qt::Horizontal)
{
	setMinimumSize(widget->sizeHint().width() + label->sizeHint().width(),
					widget->sizeHint().height());
}
else
{
	setMinimumSize(widget->sizeHint().width(),
					widget->sizeHint().height() + label->sizeHint().height());
}

@ As mentioned previously, it is possible to change the background pattern for
the decoration. It is also possible to change the color of the text.

@<WidgetDecorator Implementation@>=
void WidgetDecorator::setBackgroundBrush(QBrush background)
{
	scene->setBackgroundBrush(background);
}

void WidgetDecorator::setTextColor(QColor color)
{
	text->setDefaultTextColor(color);
}

@ Finally, there is a destructor.

@<WidgetDecorator Implementation@>=
WidgetDecorator::~WidgetDecorator()
{
	/* Nothing has to be done here. */
}

@ In order to create a decorated widget from a script, we need these functions.

@<Function prototypes for scripting@>=
void setWidgetDecoratorProperties(QScriptValue value, QScriptEngine *engine);
QScriptValue constructWidgetDecorator(QScriptContext *context,
                                      QScriptEngine *engine);

@ The scripting engine must be informed of this function.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructWidgetDecorator);
value = engine->newQMetaObject(&WidgetDecorator::staticMetaObject, constructor);
engine->globalObject().setProperty("WidgetDecorator", value);

@ The constructor is slightly more complex than other script constructors, but
still simple.

@<Functions for scripting@>=
QScriptValue constructWidgetDecorator(QScriptContext *context,
										QScriptEngine *engine)
{
	QWidget *widget = argument<QWidget *>(0, context);
	QString text = argument<QString>(1, context);
	Qt::Orientations@, orientation;
	switch(argument<int>(2, context))@/
	{@t\1@>@/
		case 2:@/
			orientation = Qt::Vertical;
			break;
		default:@/
			orientation = Qt::Horizontal;
			break;@t\2@>@/
	}
	QScriptValue object =
		engine->newQObject(new WidgetDecorator(widget, text, orientation));
	setWidgetDecoratorProperties(object, engine);
	return object;
}

void setWidgetDecoratorProperties(QScriptValue value, QScriptEngine *engine)
{
	setQWidgetProperties(value, engine);
}

@* The LogEditWindow Class.

\noindent This class will be depreciated in a future release once I have
confirmed that the class can be replaced by the configuration system. It has not
been updated to support new functionality added in version 1.2.3 and use of this
class is highly discouraged.

While the logging window provided in the example configuration is fine for
recording an existing roast, there are some who would like to be able to use
\pn{} to work with data collected with a manual logger. Different controls are
useful in such a case. The |LogEditWindow| provides this.

@<Class declarations@>=
class LogEditWindow : public QMainWindow@/
{@t\1@>@/
	Q_OBJECT@;
	QWidget *centralWidget;
	PackLayout *mainLayout;
	QHBoxLayout *addRowsLayout;
	QLabel *startTimeLabel;
	QTimeEdit *startTime;
	QLabel *endTimeLabel;
	QTimeEdit *endTime;
	QLabel *intervalLabel;
	QSpinBox *interval;
	QPushButton *addRows;
	QAction *saveXml;
	QAction *saveCsv;
	QAction *openXml;
	MeasurementModel *model;
	QTableView *log;@/
	@t\4@>private slots@t\kern-3pt@>:@/
		void addTheRows();
		void saveXML();
		void saveCSV();
		void openXML();@/
	protected:@/
		void closeEvent(QCloseEvent *event);@/
	public:@/
		LogEditWindow();@t\2@>@/
}@t\kern-3pt@>;

@ This window provides controls for adding rows to a measurement. Typically, the
data on a manual roast log will have measurements at regular intervals with the
possible exception of a few points where there are control changes or the end of
the batch. The routine for adding rows is capable of adding a single row, rows
in a range of times at regular intervals, or rows in a range of times at regular
intervals plus one time at the end.

@<LogEditWindow Implementation@>=
void LogEditWindow::addTheRows()
{
	QTime s = startTime->time();
	while(s < endTime->time())
	{
		model->newMeasurement(Measurement(0, s), 1);
		s = s.addSecs(interval->value());
	}
	model->newMeasurement(Measurement(0, endTime->time()), 1);
}

@ The window is prepared in its constructor.

@<LogEditWindow Implementation@>=
LogEditWindow::LogEditWindow() : QMainWindow(NULL),
	centralWidget(new QWidget(NULL)), mainLayout(new PackLayout(0)),@|
	addRowsLayout(new QHBoxLayout(NULL)),
	startTimeLabel(new QLabel("Start Time")),@|
	startTime(new QTimeEdit(QTime(0, 0, 0, 0))),@|
	endTimeLabel(new QLabel("End Time")),
	endTime(new QTimeEdit(QTime(0, 20, 0, 0))),@|
	intervalLabel(new QLabel("Interval (seconds)")),@|
	interval(new QSpinBox()),
	addRows(new QPushButton("Add Rows")),@|
	saveXml(new QAction(tr("Save Profile As..."), NULL)),@|
	saveCsv(new QAction(tr("Export CSV"), NULL)),@|
	openXml(new QAction(tr("Load Target Profile..."), NULL)),@|
	model(new MeasurementModel()),
	log(new QTableView())@/
{
	@<Restore editor window geometry from settings@>@;
	@<Set up the editor control bar@>@;
	@<Prepare the model@>@;
	@<Prepare the log table@>@;
	mainLayout->addItem(addRowsLayout);
	mainLayout->addWidget(log);
	centralWidget->setLayout(mainLayout);
	setCentralWidget(centralWidget);
	QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(openXml);
	connect(openXml, SIGNAL(triggered()), this, SLOT(openXML()));
	fileMenu->addAction(saveXml);
	connect(saveXml, SIGNAL(triggered()), this, SLOT(saveXML()));
	fileMenu->addAction(saveCsv);
	connect(saveCsv, SIGNAL(triggered()), this, SLOT(saveCSV()));
}

@ The window keeps its previous size and location in settings. These need to be
restored when a new window is created.

@<Restore editor window geometry from settings@>=
QSettings settings;
resize(settings.value("logSize", QSize(620,400)).toSize());
move(settings.value("logPos", QPoint(200,60)).toPoint());

@ When a new window is opened, it starts with an empty profile. If this is used
to manually enter a profile rather than edit an existing profile, rows will need
to be added. For this, we provide a set of controls where a start time, an end
time, and an interval in seconds is specified along with a button that, when
pressed, will produce a row in the model for the starting time, the ending time,
and regularly spaced times between the two. If only a single row is needed, this
can be produced by setting the start and end times the same.

@<Set up the editor control bar@>=
mainLayout->setOrientation(Qt::Vertical);
addRowsLayout->addSpacing(10);
addRowsLayout->addWidget(startTimeLabel);
addRowsLayout->addWidget(startTime);
addRowsLayout->addSpacing(10);
startTime->setDisplayFormat("mm:ss");
addRowsLayout->addWidget(endTimeLabel);
addRowsLayout->addWidget(endTime);
addRowsLayout->addSpacing(10);
endTime->setDisplayFormat("mm:ss");
addRowsLayout->addWidget(intervalLabel);
addRowsLayout->addWidget(interval);
addRowsLayout->addSpacing(10);
interval->setRange(0, 60);
interval->setValue(30);
addRowsLayout->addWidget(addRows);
addRowsLayout->addSpacing(10);
connect(addRows, SIGNAL(clicked()), this, SLOT(addTheRows()));

@ The model will have three columns: Time, Temperature, and Annotation. This
probably should not be hard coded.

@<Prepare the model@>=
model->setHeaderData(0, Qt::Horizontal, "Time");
model->setHeaderData(1, Qt::Horizontal, "Temperature");
model->setHeaderData(2, Qt::Horizontal, "Annotation");
model->clear();

@ The profile is presented in a table view. The columns should be wide enough to
contain a label, the data contained in the column, and an editor delegate.

@<Prepare the log table@>=
log->setModel(model);
log->setColumnWidth(0, 100);
log->setColumnWidth(1, 100);
log->setColumnWidth(2, 100);

@ Most users will want to save a profile after they'@q'@>ve edited it. We also
provide CSV export here. Note that this class only supports logs with a single
temperature and a single annotation column. As the class is considered
depreciated, it will not be extended to support arbitrarily many columns.

@<LogEditWindow Implementation@>=
void LogEditWindow::saveXML()
{
	QSettings settings;
	QString lastDir = settings.value("lastDirectory").toString();
	QString filename = QFileDialog::getSaveFileName(this, tr("Save Log As..."),
						lastDir, "", 0);
	QFile file(filename);
	XMLOutput writer(model, &file, 0);
	writer.addTemperatureColumn("Temperature", 1);
	writer.addAnnotationColumn("Annotation", 2);
	if(writer.output())
	{
		QFileInfo info(filename);
		QDir directory = info.dir();
		lastDir = directory.path();
		settings.setValue("lastDirectory", lastDir);
	}
}

void LogEditWindow::saveCSV()
{
	QSettings settings;
	QString lastDir = settings.value("lastDirectory").toString();
	QString filename = QFileDialog::getSaveFileName(this, tr("Export As..."),
						lastDir, "", 0);
	QFile file(filename);
	CSVOutput writer(model, &file, 0);
	writer.addTemperatureColumn("Temperature", 1);
	writer.addAnnotationColumn("Annotation", 2);
	if(writer.output())
	{
		QFileInfo info(filename);
		QDir directory = info.dir();
		lastDir = directory.path();
		settings.setValue("lastDirectory", lastDir);
	}
}

@ Some may want to open a previously saved profile, for example, to adjust the
position of an annotation. Note that this class is not appropriate for editing
profiles with more than one temperature column.

@<LogEditWindow Implementation@>=
void LogEditWindow::openXML()
{
	QSettings settings;
	QString lastDir = settings.value("lastDirectory").toString();
	QString filename = QFileDialog::getOpenFileName(this, tr("Open XML Log..."),
						lastDir, "", 0);
	if(filename.isNull())
	{
		return;
	}
	QFile file(filename);
	XMLInput reader(&file, 1);
	connect(&reader, SIGNAL(measure(Measurement, int)),
			model, SLOT(newMeasurement(Measurement, int)));
	connect(&reader, SIGNAL(annotation(QString, int, int)),
			model, SLOT(newAnnotation(QString, int, int)));
	if(reader.input())
	{
		QFileInfo info(filename);
		setWindowTitle(QString(tr("%1 - %2")).@|
			arg(QCoreApplication::applicationName()).arg(info.baseName()));
		QDir directory = info.dir();
		lastDir = directory.path();
		settings.setValue("lastDirectory", lastDir);
	}
}

@ The window should remember its last size and position, so we store this
information in settings when the window is closed.

@<LogEditWindow Implementation@>=
void LogEditWindow::closeEvent(QCloseEvent *event)
{
	QSettings settings;
	settings.setValue("logSize", size());
	settings.setValue("logPos", pos());
	event->accept();
}

@ One function is required to instantiate this class from a script.

@<Function prototypes for scripting@>=
QScriptValue constructLogEditWindow(QScriptContext *context,
                                    QScriptEngine *engine);

@ The engine must be informed of this function.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructLogEditWindow);
value = engine->newQMetaObject(&LogEditWindow::staticMetaObject, constructor);
engine->globalObject().setProperty("LogEditWindow", value);

@ The constructor just creates the window and passes it back to the engine.

@<Functions for scripting@>=
QScriptValue constructLogEditWindow(QScriptContext *, QScriptEngine *engine)
{
	QScriptValue object = engine->newQObject(new LogEditWindow);
	return object;
}

@** File IO.

\noindent So far, the data is all stored in memory. It is often useful to save
data to a file or read back previously saved data. Presently, two formats are
supported: an XML format which can also be read back in and CSV which can easily
be used with many external tools.

File IO is handled by a few classes: one per input format and one per output
format. The classes in the following sections should be simple enough to follow
that it should be clear how to extend \pn{} to support other formats if needed.

Should additional output formats be required, it may be beneficial to
reimplement the serializers as subclasses of a new abstract serializer class in
order to share common code among them where reusing \cweb{} chunks is not an
appropriate technique.

@* XML Output.

\noindent An XML format has been chosen as the native format for \pn{} because
of Qt'@q'@>s excellent support for reading and writing such documents. Using this
capability is less error prone than developing a new, more compact format.
Another reason to choose XML is that it becomes quite easy to modify saved data
in a text editor and still end up with something \pn{} will understand.

The structure of the file we will produce is simple, however it has been
modified from a simpler structure that was used in versions of Typica prior to
1.2.3. How to read these files can be determined by the document type found at
the start of the file. At the start of the file, there should be one or more
{\tt <tempseries>} elements and one or more {\tt <noteseries>} elements. These
are empty elements with a {\tt name} attribute which can be used to label the
column in a view. Once these column declarations have been written, a
{\tt <roast>} element is produced which contains a set of zero or more
{\tt <tuple>} elements. Each tuple contains one {\tt <time>} element containing
the time of the measurement relative to the start of the batch and optionally
one or more {\tt <temperature>} and {\tt <annotation>} elements containing
measurement and annotation data associated with that time. The
{\tt <temperature>} and {\tt <annotation>} elements have a {\tt series}
attribute where the value of the attribute matches the {\tt name} attribute of a
{\tt <tempseries>} or {\tt <noteseries>} element which allows each measurement
to be placed in the correct data series regardless of element ordering in the
document.

There are certain oddities about this format compared with other XML based
formats. The order of some elements in the current implementation affects the
behavior of the program and there is no longer a proper root element. This
format may be extended in future versions of \pn{} to support additional
functionality or to improve the robustness of the format. Should such
modifications occur, an effort should be made to ensure that \pn{} continues to
support the import of old data.

As of version 1.0.8, this class is derived from |QObject| for easier integration
with the scripting engine.

The |temperatureColumns| and |annotationColumns| member data structures are
currently a |QMap| rather than a |QHash| because the number of data series in a
single file is likely to be small enough that the difference in lookup time
should be negligeable and the ability to iterate over the keys in the |QMap| in
sorted order is useful.

@<Class declarations@>=
class XMLOutput : public QObject@/
{@/
	Q_OBJECT@;@/
	MeasurementModel *data;
	QIODevice *out;
	int time;
	QMap<int, QString> temperatureColumns;
	QMap<int, QString> controlColumns;
	QMap<int, QString> annotationColumns;
	public:@/
		XMLOutput(MeasurementModel *model, QIODevice *device, int timec = 0);
		void addTemperatureColumn(const QString &series, int column);
		void addControlColumn(const QString &series, int column);
		void addAnnotationColumn(const QString &series, int column);
		void setModel(MeasurementModel *model);
		void setTimeColumn(int column);
		void setDevice(QIODevice *device);
		bool output();
};

@ The interesting part of this class is the |output| routine. This goes over the
data in the model and constructs an appropriate XML document. If the operation
fails, the function returns |false|, otherwise it returns |true|.

@<XMLOutput Implementation@>=
bool XMLOutput::output()@t\2\2@>@/
{@t\1@>@/
	if(!out->open(QIODevice::WriteOnly | QIODevice::Text))@/
	{@t\1@>@/
		return false;@t\2@>@/
	}@/
	QXmlStreamWriter xmlout(out);
	xmlout.writeStartDocument("1.0");
	xmlout.writeDTD("<!DOCTYPE roastlog3.0>");
	xmlout.writeStartElement("roastlog");
	@<Output the column declarations@>@;
	xmlout.writeStartElement("roast");
	bool oresult;
	for(int i = 0; i < data->rowCount(); i++)@/
	{
		@<Check if row should be output@>@;
		if(oresult)
		{
			@<Output tuple element@>@;
		}
	}
	xmlout.writeEndElement();
	xmlout.writeEndElement();
	xmlout.writeEndDocument();
	out->close();@/
	return true;@t\2@>@/
}

@ Temperature column declarations are output before annotation column
declarations. Within each category, column declarations are output in order by
column number.

@<Output the column declarations@>=
foreach(int c, temperatureColumns.keys())
{
	xmlout.writeStartElement("tempseries");
	xmlout.writeAttribute("name", temperatureColumns.value(c));
	xmlout.writeEndElement();
}
foreach(int c, controlColumns.keys())
{
	xmlout.writeStartElement("controlseries");
	xmlout.writeAttribute("name", controlColumns.value(c));
	xmlout.writeEndElement();
}
foreach(int c, annotationColumns.keys())
{
	xmlout.writeStartElement("noteseries");
	xmlout.writeAttribute("name", annotationColumns.value(c));
	xmlout.writeEndElement();
}

@ When checking a row in the model to determine if it contains values that need
to be written, we want to know if any of the temperature or annotation columns
contain a value. If at least one of these columns is not empty for this row, we
need to output a tuple for that row.

@<Check if row should be output@>=
oresult = false;@/
foreach(int c, temperatureColumns.keys())@/
{@t\1@>@/
	if(data->data(data->index(i, c), Qt::DisplayRole).isValid() &&
	   !(data->data(data->index(i, c), Qt::DisplayRole).toString().isEmpty()))@/
	{@t\1@>@/
		oresult = true;
		break;@t\2@>@/
	}@t\2@>@/
}@/
foreach(int c, controlColumns.keys())
{
	if(data->data(data->index(i, c), Qt::DisplayRole).isValid() &&
	         !(data->data(data->index(i, c), Qt::DisplayRole).toString().isEmpty()))
	{
		oresult = true;
		break;
	}
}
if(oresult == false)@/
{@t\1@>@/
	foreach(int c, annotationColumns.keys())@/
	{@t\1@>@/
		if(data->data(data->index(i, c), Qt::DisplayRole).isValid() &&
		   !(data->data(data->index(i, c), Qt::DisplayRole).toString().
		                isEmpty()))@/
		{@t\1@>@/
			oresult = true;
			break;@t\2@>@/
		}@t\2@>@/
	}@t\2@>@/
}

@ Now that we know that values from the current row should be output, we can
produce a {\tt <tuple>} element, a {\tt <time>} element for that tuple, and then
iterate over the set of columns we might want to output, producing an
appropriate element for each non-empty column for that row.

@<Output tuple element@>=
xmlout.writeStartElement("tuple");
xmlout.writeTextElement("time", data->data(data->index(i, time),
                                           Qt::DisplayRole).toString());
foreach(int c, temperatureColumns.keys())@/
{
	if(data->data(data->index(i, c), Qt::DisplayRole).isValid() &&
	   !(data->data(data->index(i, c), Qt::DisplayRole).toString().isEmpty()))@/
	{
		xmlout.writeStartElement("temperature");
		xmlout.writeAttribute("series", temperatureColumns.value(c));
		if(data->data(data->index(i, c), Qt::UserRole).toMap().contains("relative"))
		{
			if(data->data(data->index(i, c), Qt::UserRole).toMap().value("relative").toBool() == true)
			{
				xmlout.writeAttribute("relative", "true");
			}
		}
		xmlout.writeCharacters(data->data(data->index(i, c), Qt::DisplayRole).
		                                  toString());
		xmlout.writeEndElement();
	}
}
foreach(int c, controlColumns.keys())
{
	if(data->data(data->index(i, c), Qt::DisplayRole).isValid() &&
	         !(data->data(data->index(i, c), Qt::DisplayRole).toString().isEmpty()))
	{
		xmlout.writeStartElement("control");
		xmlout.writeAttribute("series", controlColumns.value(c));
		xmlout.writeCharacters(data->data(data->index(i, c), Qt::DisplayRole).toString());
		xmlout.writeEndElement();
	}
}
foreach(int c, annotationColumns.keys())@/
{
	if(data->data(data->index(i, c), Qt::DisplayRole).isValid() &&
	   !(data->data(data->index(i, c), Qt::DisplayRole).toString().isEmpty()))@/
	{
		xmlout.writeStartElement("annotation");
		xmlout.writeAttribute("series", annotationColumns.value(c));
		xmlout.writeCharacters(data->data(data->index(i, c), Qt::DisplayRole).
		                                  toString());
		xmlout.writeEndElement();
	}
}
xmlout.writeEndElement();

@ The rest of the class just initializes the private member data.

@<XMLOutput Implementation@>=
XMLOutput::XMLOutput(MeasurementModel *model, QIODevice *device, int timec)
	: QObject(NULL), data(model), out(device), time(timec)@/
{
	/* Nothing has to be done here. */
}@;

void XMLOutput::setModel(MeasurementModel *model)
{
	data = model;
}

void XMLOutput::setTimeColumn(int column)
{
	time = column;
}

void XMLOutput::setDevice(QIODevice *device)
{
	out = device;
}

@ As of version 1.2.3, the old |setTemperatureColumn()| and
|setAnnotationColumn()| methods have been replaced with the
|addTemperatureColumn()| and |addAnnotationColumn()| methods respectively. The
main difference is that the new methods take a column name in addition to a
number and it is now possible to specify multiple columns of each category for
export.

@<XMLOutput Implementation@>=
void XMLOutput::addTemperatureColumn(const QString &series, int column)
{
	temperatureColumns.insert(column, series);
}

void XMLOutput::addControlColumn(const QString &series, int column)
{
	controlColumns.insert(column, series);
}

void XMLOutput::addAnnotationColumn(const QString &series, int column)
{
	annotationColumns.insert(column, series);
}

@* XML Input.

\noindent Once model data can be saved to a file, it is useful to be able to
read that data back in. This is a little different from reading data out of a
model as more than one object is potentially interested in the data. Instead, we
emit signals for measurements and annotations. This class has been modified to
support both the current (as of version 1.2.3) output of the |XMLOutput| class
and the older version. If changes are made to |XMLOutput| this class may also
need to be modified.

The main differences in the current version of this class are that the first
column is specified rather than specifying temperature and annotation columns
separately and additional signals are emitted to allow views to prepare for an
arbitrary number of columns.

The |newTemperatureColumn| and |newAnnotationColumn| signals can be used to set
up column headers while the |lastColumn| signal can be used to shift live data
streams to unoccupied columns.

@<Class declarations@>=
class XMLInput : public QObject@/
{
	Q_OBJECT@;
	int firstc;
	QIODevice *in;
	public:@/
		XMLInput(QIODevice *input, int c);
		void setFirstColumn(int column);
		void setDevice(QIODevice *device);
		bool input();
	signals:@/
		void measure(Measurement, int);
		void annotation(QString, int, int);
		void newTemperatureColumn(int, QString);
		void newAnnotationColumn(int, QString);
		void lastColumn(int);
};

@ The main point of interest here is the |input()| method. If the file is read
successfully, |true| is returned. Otherwise, |false| is returned.

@<XMLInput Implementation@>=
bool XMLInput::input()@t\2\2@>@/
{@t\1@>@/
	if(!in->open(QIODevice::ReadOnly | QIODevice::Text))@/
	{@t\1@>@/
		return false;@t\2@>@/
	}@/
	QXmlStreamReader xmlin(in);
	QMap<QString, int> temperatureColumns;
	QMap<QString, int> annotationColumns;
	int nextColumn = firstc;
	@<Read column declarations@>@;
	QTime timeval = QTime();
	double tempval = 0;
	QString noteval = QString();
	int column;
	int counter = 0;@/
	while(!xmlin.atEnd())@/
	{@/
		@<Read XML file@>@;
	}@/
	return true;@t\2@>@/
}

@ A data file may or may not contain elements that specify the name of a column.
In order to determine how to proceed, we should check the doctype of the input
file. This should be the first element of the input file encountered.

\danger There is not nearly enough error checking here.
\endanger

@<Read column declarations@>=
while(!xmlin.isDTD())
{
	xmlin.readNext();
}
if(xmlin.isDTD())
{
	if(xmlin.text() == "<!DOCTYPE roastlog>")
	{
		@<Emit old format column specification@>@;
	}
	else
	{
		xmlin.readNext();
		@<Scan for column declarations and emit@>@;
	}
}

@ Old format data will not have column declarations. This means that we must
produce a default set of signals rather than waiting to read elements describing
the columns.

@<Emit old format column specification@>=
emit newTemperatureColumn(firstc, "Bean");
emit newAnnotationColumn(firstc + 1, "Note");
emit lastColumn(firstc + 1);

@ The current format will have column declarations prior to the {\tt <roast>}
element. We can just read until we hit that element and emit the appropriate
signals as elements are encountered.

@<Scan for column declarations and emit@>=
while(xmlin.name() != "roast")
{
	if(xmlin.isStartElement())
	{
		if((xmlin.name() == "tempseries") || (xmlin.name() == "controlseries"))
		{
			temperatureColumns.insert(xmlin.attributes().value("name").
									                     toString(),
									  nextColumn);
			emit newTemperatureColumn(nextColumn,
			                          xmlin.attributes().value("name").
									                     toString());
			nextColumn++;
		}
		else if(xmlin.name() == "noteseries")
		{
			annotationColumns.insert(xmlin.attributes().value("name").
			                         toString(), nextColumn);
			emit newAnnotationColumn(nextColumn,
			                         xmlin.attributes().value("name").
									                    toString());
			nextColumn++;
		}
	}
	xmlin.readNext();
}
emit lastColumn(nextColumn - 1);

@ Now we are ready to read measurements from the file. When encountering a
{\tt <time>} element, we record the time and move on. For {\tt <temperature>}
and {\tt <annotation>} elements, we emit the appropriate signal. This is handled
slightly differently depending on which version of the file format is being
used. Note that there is not nearly enough error checking here and we are
basically ignoring {\tt <tuple>} elements.

Due to the typically large number of measurements taken over the course of a
roast and the amount of time often taken to process these measurements when they
are read from a file, there is a need to periodically pass control back to the
event loop to remain responsive to user input.

@<Read XML file@>=
xmlin.readNext();
if(xmlin.isStartElement())
{
	@<Read measurement data@>@;
}
counter++;
if(counter % 100 == 0)
{
	QCoreApplication::processEvents();
}

@ When reading start elements, it is safe to ignore {\tt <tuple>} and
{\tt <roast>}. Technically, this means that the program can read certain types
of invalid data. The Robustness Principle\nfnote{``Be liberal in what you
accept, and conservative in what you send,'' --- Robert Braden, {\it RFC 1122
\S 1.2.2}} is generally applicable to any type of data exchange. That said,
malformed data is not guaranteed readable in the future, even if it does work
now.

\danger One set of test input caused this code to emit an empty annotation for
every measurement. This is the reason for wrapping the annotation signal
emission to check for this. The detected annotation elements were not present in
the input stream and I have absolutely no idea where the program came up with
them. \endanger

@<Read measurement data@>=
if(xmlin.name() == "time")
{
	timeval = QTime::fromString(xmlin.readElementText(), "mm:ss.zzz");
}
else if(xmlin.name() == "temperature")
{
	column = xmlin.attributes().value("series").toString().isEmpty() ?
	         firstc : temperatureColumns.value(xmlin.attributes().
			                                   value("series").toString());
	bool relative = false;
	if(xmlin.attributes().value("relative") == "true")
	{
		relative = true;
	}
	tempval = xmlin.readElementText().toDouble();
	Measurement measurement(tempval, timeval);
	if(relative)
	{
		measurement.insert("relative", true);
	}
	emit measure(measurement, column);
}
else if(xmlin.name() == "control")
{
	column = xmlin.attributes().value("series").toString().isEmpty() ?
	         firstc : temperatureColumns.value(xmlin.attributes().
	                                                   value("series").toString());
	tempval = xmlin.readElementText().toDouble();
	Measurement measurement(tempval, timeval, Units::Unitless);
	emit measure(measurement, column);
}
else if(xmlin.name() == "annotation")
{
	column = xmlin.attributes().value("series").toString().isEmpty() ?
	         firstc + 1 : annotationColumns.value(xmlin.attributes().
			                                      value("series").toString());
	noteval = xmlin.readElementText();
	if(!noteval.isEmpty())
	{
		emit annotation(noteval, firstc, column);
	}
}

@ The other methods just set the private member data.

@<XMLInput Implementation@>=
XMLInput::XMLInput(QIODevice *input, int c) :
	firstc(c), in(input)@/
{@/
	/* Nothing has to be done here. */
}

void XMLInput::setFirstColumn(int column)
{
	firstc = column;
}

void XMLInput::setDevice(QIODevice *device)
{
	in = device;
}

@ In order to allow scripts to instantiate the |XMLInput| class, we need a
constructor and a wrapper around the |input()| method.

@<Function prototypes for scripting@>=
QScriptValue constructXMLInput(QScriptContext *context, QScriptEngine *engine);
QScriptValue XMLInput_input(QScriptContext *context, QScriptEngine *engine);

@ The script constructor is passed to the scripting engine.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructXMLInput);
value = engine->newQMetaObject(&XMLInput::staticMetaObject, constructor);
engine->globalObject().setProperty("XMLInput", value);

@ The implementation should seem familiar.

@<Functions for scripting@>=
QScriptValue constructXMLInput(QScriptContext *context, QScriptEngine *engine)
{
	QIODevice *device = argument<QIODevice *>(0, context);
	QScriptValue object = engine->newQObject(new XMLInput(&*device,
											     argument<int>(1, context)));
	object.setProperty("input", engine->newFunction(XMLInput_input));
	return object;
}

QScriptValue XMLInput_input(QScriptContext *context, QScriptEngine *)
{
	XMLInput *self = getself<@[XMLInput *@]>(context);
	self->input();
	return QScriptValue();
}

@* CSV Output.

\noindent While XML is convenient for \pn{}, other programs may not handle this
format well. For this purpose, we use a text file with comma separated values.
Data in this format can easily be handled by shell scripts, simple programs, and
any spreadsheet (though some may handle the time column poorly).

We do not need to concern ourselves with reading data in this format back in,
but there is no reason a class could not be written to do this.

The structure of this class is very similar to the |XMLOutput| class.

@<Class declarations@>=
class CSVOutput@/
{@/
	MeasurementModel *data;
	QIODevice *out;
	int time;
	QMap<int, QString> temperatureColumns;
	QMap<int, QString> controlColumns;
	QMap<int, QString> annotationColumns;@/
	public:@/
		CSVOutput(MeasurementModel *model, QIODevice *device, int timec = 0);
		void addTemperatureColumn(const QString &series, int column);
		void addControlColumn(const QString &series, int column);
		void addAnnotationColumn(const QString &series, int column);
		void setModel(MeasurementModel *model);
		void setTimeColumn(int column);
		void setDevice(QIODevice *device);
		bool output();@/
};

@ Very little needs to be done to output the data. We open the output stream
and, if the output stream was successfully opened, we look for measurements and
output the text, remembering to output a comma between items and a newline after
each record. If the data is successfully output, |true| is returned, otherwise
we return |false|.

The comparably simple structure of the CSV format allows us to just fling the
data onto a text stream.

@<CSVOutput Implementation@>=
bool CSVOutput::output()@t\2\2@>@/
{@t\1@>@/
	if(!out->open(QIODevice::WriteOnly | QIODevice::Text))@/
	{@t\1@>@/
		return false;@t\2@>@/
	}@/
	QTextStream output(out);
	@<Output CSV column headers@>@;
	bool oresult;
	for(int i = 0; i < data->rowCount(); i++)@/
	{
		@<Check if row should be output@>@;
		if(oresult)
		{
			@<Output CSV row@>@;
		}
	}
	out->close();@/
	return true;@t\2@>@/
}

@ Before writing the data, we output a row containing the name of each column.

@<Output CSV column headers@>=
output << "Time";
foreach(int c, temperatureColumns.keys())
{
	output << ',' << temperatureColumns.value(c);
}
foreach(int c, controlColumns.keys())
{
	output << ',' << controlColumns.value(c);
}
foreach(int c, annotationColumns.keys())
{
	output << ',' << annotationColumns.value(c);
}
output << '\n';

@ Once the header information has been written, we can proceed to output the
real data. The algorithm for doing this has been changed as of version 1.2.3
with the result that most uses will now produce more delimiters than the same
data in previous versions. This should have no impact on the ability of other
programs to interact with data produced by \pn{}. The code to handle output in
this way is much easier to read. A future version might once again suppress
superfluous commas, however the presence of these commas is not considered a
serious issue at this time.

@<Output CSV row@>=
output << data->data(data->index(i, time), Qt::DisplayRole).toString();
foreach(int c, temperatureColumns.keys())
{
	output << ',' << data->data(data->index(i, c), Qt::DisplayRole).toString();
}
foreach(int c, controlColumns.keys())
{
	output << ',' << data->data(data->index(i, c), Qt::DisplayRole).toString();
}
foreach(int c, annotationColumns.keys())
{
	output << ',' << data->data(data->index(i, c), Qt::DisplayRole).toString();
}
output << '\n';

@ The rest of the class just initializes the private member data. See notes
on the implementation of |XMLOutput|.

@<CSVOutput Implementation@>=
CSVOutput::CSVOutput(MeasurementModel *model, QIODevice *device, int timec) :
	data(model), out(device), time(timec)@/
{
	/* Nothing has to be done here. */
}@;

void CSVOutput::setModel(MeasurementModel *model)
{
	data = model;
}

void CSVOutput::setTimeColumn(int column)
{
	time = column;
}

void CSVOutput::addTemperatureColumn(const QString &series, int column)
{
	temperatureColumns.insert(column, series);
}

void CSVOutput::addControlColumn(const QString &series, int column)
{
	controlColumns.insert(column, series);
}

void CSVOutput::addAnnotationColumn(const QString &series, int column)
{
	annotationColumns.insert(column, series);
}

void CSVOutput::setDevice(QIODevice *device)
{
	out = device;
}

@i webview.w

@* The Application class.

The |Application| class represents the \pn{} program. It is responsible for
setting up the settings object and localization in addition to the normal
responsibilities of |QApplication|. In addition to declaring the class, we also
define a macro that returns the |Application| instance.

@<Class declarations@>=
#define AppInstance (qobject_cast<@[Application *@]>(qApp))

class NodeInserter;
class DeviceTreeModel;
class Application : public QApplication@/
{@/
	@[Q_OBJECT@]@;
	public:@/
		Application(int &argc, char **argv);
		QDomDocument* configuration();
		@<Device configuration members@>@;
		QSqlDatabase database();
		QScriptEngine *engine;@/
	@[public slots@]:@/
		@<Extended Application slots@>@;
	private:@/
		@<Application private data members@>@;
		QDomDocument conf;
};

@ The constructor for this class handles a few things that had previously been
handled in |main()|.

@<Application Implementation@>=
Application::Application(int &argc, char **argv) : QApplication(argc, argv)@/
{
	@<Allow use of the default QSettings constructor@>@;
	@<Load translation objects@>@;
	@<Register meta-types@>@;
	@<Register top level device configuration nodes@>@;
}

@ We use |QSettings| objects throughout \pn{} to remember details such as the
size and position of windows and the most recently used directory. To simplify
the creation of these objects, we specify some details up front. This allows us
to use the default constructor rather than specifying these things every time we
need an object.

@<Allow use of the default QSettings constructor@>=
setOrganizationName("Wilson's Coffee & Tea");
setOrganizationDomain("wilsonscoffee.com");
setApplicationName(PROGRAM_NAME);

@ Much of the user visible text in \pn{} is wrapped in a call to |tr()|. Such
text can be replaced with translated text based on the user'@q'@>s locale. For more
details, see the Qt Linguist manual.

@<Load translation objects@>=
QTranslator base;
if(base.load(QString("qt_%1").arg(QLocale::system().name())))
{
	installTranslator(&base);
}
QTranslator app;
if(app.load(QString("%1_%2").arg("Typica").arg(QLocale::system().name())))
{
	installTranslator(&app);
}

@ We also want to be able to access the application instance from within the
scripting engine. We don'@q'@>t need to be able to create new instances, just access
the one that already exists.

@<Set up the scripting engine@>=
value = engine->newQObject(AppInstance);
engine->globalObject().setProperty("Application", value);

@ The |configuration()| method provides access to an XML document containing the
current application configuration. The object is populated in |main()|.

@<Application Implementation@>=
QDomDocument* Application::configuration()
{
	return &conf;
}

@ The |database()| method provides access to a database connection for use by
database aware widgets.

@<Application Implementation@>=
QSqlDatabase Application::database()
{
	QString connectionName;
	QSqlDatabase connection = QSqlDatabase::database();
	do
	{
		connectionName = QUuid::createUuid().toString();
	} while (QSqlDatabase::connectionNames().contains(connectionName));
	return QSqlDatabase::cloneDatabase(connection, connectionName);
}

@** Table editor for ordered arrays with SQL relations.

\noindent A database in use at Wilson's Coffee \char'046~Tea stores information
for a roasting log and uses entered information to adjust inventory tracking
tables. This roasting log connects the use of unroasted coffee with the creation
of roasted coffee. In order to support roasting coffee from more than one lot at
the same time, the columns that specify the types of coffee used and the amount
of each coffee are entered as ordered arrays in which the first entry in the
array specifying an unroasted coffee is associated with the first entry in the
array specifying the amount of coffee used. While most batches will involve only
a single unroasted coffee, the database has no limitation on the number of
coffees that may be roasted in a single batch. An additional characteristic of
this table is that the database requires an identification number for unroasted
coffee items, but it would be better to provide a list of acceptable items with
human readable names.

A scrollable area containing a table view which can provide the necessary input
delegates (such as a combo box for SQL relations) and validators which ensures
that there is always at least one empty row available for input with convenience
functions for extracting the arrays needed for database insertion would be ideal
for this.

To get this, we need a simple table model based on |QStandardItemModel|
or |QAbstractItemModel|. The model should ensure that there is always at least
one empty row available for editing. It should also provide a function for
obtaining a string that presents all values from a specified column with a given
role as an array literal suitable for binding to an SQL query.

A class based on |QComboBox| providing options selected from an SQL query will
be needed. This can be used as a standalone widget elsewhere, but here it is
also needed as an editor class for a column delegate. Another delegate class
allows input in another column to be constrained by a |QValidator| (in this case
a |QDoubleValidator|).

A class based on |QTableView| brings all of these classes together and presents
them to the user.

@* A table model for producing SQL array literals.

\noindent This is a simple table model which provides two somewhat unusual
features. First, it always provides at least one empty row at the end of the
data. Second, it provides SQL array literals for columns in the model.

\danger At some point I would like to replace this model and |MeasurementModel|
with an improved table model suitable to replace both. Some preliminary design
work suggests that this improvement simplifies \pn{} considerably both
internally and in the data flow configuration. This has not yet been done due to
development time constraints.\endanger

@<Class declarations@>=
class SaltModel : public QAbstractItemModel@/
{
	Q_OBJECT@t\2\2@>@/
	QList<QList<QMap<int, QVariant> > > modelData;
	QStringList hData;
	int colcount;@t\1\1@>@/
	public:@/
		SaltModel(int columns);
		~SaltModel();
		int rowCount(const QModelIndex &parent = QModelIndex()) const;
		int columnCount(const QModelIndex &parent = QModelIndex()) const;
		bool setHeaderData(int section, Qt::Orientation@, orientation,
		                   const QVariant &value, int role = Qt::DisplayRole);
		QVariant data(const QModelIndex &index, int role) const;
		bool setData(const QModelIndex &index, const QVariant &value,
		             int role = Qt::EditRole);
		Qt::ItemFlags@, flags(const QModelIndex &index) const;
		QVariant headerData(int section, Qt::Orientation@, orientation,
		                    int role = Qt::DisplayRole) const;
		QModelIndex index(int row, int column,
		                  const QModelIndex &parent = QModelIndex()) const;
		QModelIndex parent(const QModelIndex &index) const;
		QString arrayLiteral(int column, int role) const;
		QString quotedArrayLiteral(int column, int role) const;
};

@ The only unique methods in this class are the |arrayLiteral| and
|quotedArrayLiteral| methods. These take a column number and a data role and
produce a SQL array literal for every entry in that column with the specified
role. The string will take the form of
{\tt{'\LB row 1, row 2, }}$\dots$ {\tt{row N\RB '}}.

This is done simply by starting with a string identifying the start of an array
literal, looping over the rows in the model while appending any data found along
with the commas to separate values. If any data is found, the extra comma and
space are removed from the constructed string. Finally, text marking the end of
the array literal is added.

The |arrayLiteral| method is appropriate where the expected values are numeric.
The |quotedArrayLiteral| method is appropriate where the expected values are
text. The values in the array will have quotation marks around them for the
|quotedArrayLiteral|. Note that when binding these values to placeholders in a
SQL query the leading and trailing single quote characters should be removed.

\danger The way this method is currently used is quite harmless. Data from one
column is integer data obtained as a result of a previous database query and
data from the other column is restricted by the view to numeric data. Please
note, however, that it would be extremely stupid to use code such as this when
user input cannot be controlled so tightly. Were this model used with a view
that allows general text input, it would be trivial to construct an SQL
injection attack.

\medskip

\centerline{\includegraphics[width=6in]{exploits_of_a_mom}}

\smallskip

\centerline{Figure \secno: An Example of an SQL injection attack.\nfnote{%
Comic copyright Randall Munroe. Original can be found at:~%
\pdfURL{%
http://xkcd.com/327/}%
{http://xkcd.com/327/}}}

\medskip

\endanger

@<SaltModel Implementation@>=
QString SaltModel::arrayLiteral(int column, int role) const
{
	QString literal = "'{";
	for(int i = 0; i < rowCount(); i++)
	{
		QString datum = data(index(i, column), role).toString();
		if(!datum.isEmpty())
		{
			literal.append(datum);
			literal.append(", ");
		}
	}
	if(literal.size() > 2)
	{
		literal.chop(2);
	}
	literal.append("}'");
	return literal;
}

QString SaltModel::quotedArrayLiteral(int column, int role) const
{
	QString literal = "'{";
	for(int i = 0; i < rowCount(); i++)
	{
		QString datum = data(index(i, column), role).toString();
		if(!datum.isEmpty())
		{
			literal.append("\"");
			literal.append(datum);
			literal.append("\", ");
		}
	}
	if(literal.size() > 2)
	{
		literal.chop(2);
	}
	literal.append("}'");
	return literal;
}

@ No entries in this model have children.

@<SaltModel Implementation@>=
QModelIndex SaltModel::parent(const QModelIndex &) const
{
	return QModelIndex();
}

@ The |setData()| method is called by delegates on views when the user enters
new data. This method must check to determine if the data is being entered in
the last row to increase the size of the table.

The end of this function may seem a little strange. Why not simply look up the
map and insert information directly into the model data? Well, as of this
writing, that doesn't work. There are two ways around that problem. One is to
have the lists store references and dereference the real data. The other option
is to obtain a copy of the row, then a copy of the cell, update the cell, then
replace the old value of the cell in the copy of the row, then replace the old
values of the row in the real data. The other option would probably be more
efficient, but this does work.

@<SaltModel Implementation@>=
bool SaltModel::setData(const QModelIndex &index, const QVariant &value,
                        int role)@t\2\2@>@/
{@t\1@>@/
	@<Check that the SaltModel index is valid@>@;
	if(!valid)@/
	{@t\1@>@/
		return false;@t\2@>@/
	}
	if(index.row() == modelData.size() - 1)@/
	{
		beginInsertRows(QModelIndex(), modelData.size(), modelData.size());
		@<Expand the SaltModel@>@;
		endInsertRows();
	}
	QList<QMap<int, QVariant> > row = modelData.at(index.row());
	QMap<int, QVariant> cell = row.at(index.column());
	cell.insert(role, value);
	if(role == Qt::EditRole)@/
	{
		cell.insert(Qt::DisplayRole, value);
	}
	row.replace(index.column(), cell);
	modelData.replace(index.row(), row);
	emit dataChanged(index, index);@/
	return true;@t\2@>@/
}

@ Some model operations require checking that a model index is valid. This
chunk is used in these cases.

@<Check that the SaltModel index is valid@>=
bool valid = false;@/
if(index.isValid())@/
{@t\1@>@/
	if(index.row() < modelData.size())@/
	{@t\1@>@/
		if(index.column() < colcount)@/
		{@t\1@>@/
			valid = true;@t\2@>@/
		}@t\2@>@/
	}@t\2@>@/
}

@ When data is modified in the last row of the table, the model must be expanded
to allow for additional data.

@<Expand the SaltModel@>=
QList<QMap<int, QVariant> > newRow;
QMap<int, QVariant> defaults;
for(int i = 0; i < colcount; i++)
{
	newRow.append(defaults);
}
modelData.append(newRow);

@ The number of columns in the table is specified in the model constructor.

@<SaltModel Implementation@>=
SaltModel::SaltModel(int columns) : QAbstractItemModel(), colcount(columns)
{
	for(int i = 0; i < columns; i++)
	{
		hData << "";
	}
	@<Expand the SaltModel@>@;
}

@ The destructor doesn't need to do anything.

@<SaltModel Implementation@>=
SaltModel::~SaltModel()
{
	/* Nothing needs to be done here. */
}

@ A pair of methods provide the number of rows and columns in the model. No
entries in the model have children, so the parent should always be the invisible
root object.

@<SaltModel Implementation@>=
int SaltModel::rowCount(const QModelIndex &parent) const
{
	return (parent == QModelIndex() ? modelData.size() : 0);
}

int SaltModel::columnCount(const QModelIndex &parent) const
{
	return (parent == QModelIndex() ? colcount : 0);
}

@ The model maintains header data for labeling the model columns.

@<SaltModel Implementation@>=
bool SaltModel::setHeaderData(int section, Qt::Orientation@, orientation,@|
                              const QVariant &value, int)@t\2\2@>@/
{@t\1@>@/
	if(orientation == Qt::Horizontal && section < colcount)@/
	{@t\1@>@/
		hData.replace(section, value.toString());@/
		emit headerDataChanged(orientation, section, section);@/
		return true;@t\2@>@/
	}@/
	return false;@t\2@>@/
}

@ Views need to be able to retrieve model and header data.

@<SaltModel Implementation@>=
QVariant SaltModel::data(const QModelIndex &index, int role) const
{
	@<Check that the SaltModel index is valid@>@;
	if(!valid)
	{
		return QVariant();
	}
	QList<QMap<int,QVariant> > row = modelData.at(index.row());
	QMap<int,QVariant> cell = row.at(index.column());
	return cell.value(role, QVariant());
}

QVariant SaltModel::headerData(int section, Qt::Orientation@, orientation,
                               int role) const
{
	if(orientation == Qt::Horizontal && role == Qt::DisplayRole &&
	   section < colcount)
	{
		return QVariant(hData.at(section));
	}
	return QVariant();
}

@ Views need to know certain details such as if an item in the view can be
altered by the view. For this model, all valid indices can be edited.

@<SaltModel Implementation@>=
Qt::ItemFlags SaltModel::flags(const QModelIndex &index) const
{
	@<Check that the SaltModel index is valid@>@;
	if(valid)
	{
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
	}
	return 0;
}

@ So far, many of the methods use model indices. The model is responsible for
creating these.

@<SaltModel Implementation@>=
QModelIndex SaltModel::index(int row, int column,
                             const QModelIndex &parent) const
{
	if(parent == QModelIndex())
	{
		if(row < modelData.size() && column < colcount)
		{
			return createIndex(row, column);
		}
	}
	return QModelIndex();
}

@* A Delegate for SQL Relations.

\noindent The first column of the table view being described is responsible for
providing item numbers to the database. Requiring that these numbers be entered
directly is prone to not particularly user friendly and almost encourages input
errors. These item numbers, however, refer to the items table in the database
which includes, among other details, a human readable text string naming the
item. This delegate provides the user with a drop down menu from which such a
string may be selected with this information provided by the database itself.
When the user selects an item, it informs the model not only of the text string
in the display role, but also of the id number in a user data role which can
later be queried in order to properly craft the appropriate query.

This is implemented with two classes. The first is a |QComboBox| which queries
the database and maintains a mapping of id to text. This is made its own widget
as it is useful without being turned into a delegate. The second class provides
this widget as a delegate and handles communications between it and the model.

@<Class declarations@>=
class SqlComboBox : public QComboBox@/
{@t\1@>@/
	Q_OBJECT@;
	int dataColumn;
	int displayColumn;
	bool dataColumnShown;
	public:@/
		SqlComboBox();
		~SqlComboBox();
		SqlComboBox* clone(QWidget *parent);@/
	@t\4@>public slots@t\kern-3pt@>:@/
		void addNullOption();
		void addSqlOptions(QString query);
		void setDataColumn(int column);
		void setDisplayColumn(int column);
		void showData(bool show);@t\2@>@/
}@t\kern-3pt@>;

@ In order to make this class work a little more nicely as an item delegate,
the |clone()| method has been provided to create a new object with the same
options as a prototype.

@<SqlComboBox Implementation@>=
SqlComboBox* SqlComboBox::clone(QWidget *parent)
{
	SqlComboBox *widget = new SqlComboBox();
	widget->setParent(parent);
	for(int i = 0; i < count(); i++)
	{
		widget->addItem(itemText(i), itemData(i));
	}
	return widget;
}

@ When using this class, we must first decide if the data column is shown. If
this is desired, the entries displayed will contain both the value from the
display column followed by the value from the data column. This can be useful in
cases where the same text is used for two different items.

@<SqlComboBox Implementation@>=
void SqlComboBox::showData(bool show)
{
	dataColumnShown = show;
}

@ Next, there is a need to know if the NULL value may legally be selected. Where
this is the case, we generally want this to be inserted first. As the
|QComboBox| supports storing both display and user data, much of the code is a
thin wrapper around calls to the base class.

@<SqlComboBox Implementation@>=
void SqlComboBox::addNullOption()
{
	addItem(tr("Unknown"), QVariant(QVariant::String));
}

@ Typically, the SQL query used to populate this widget will request two columns
of data. One column is used as the display data, the other as user data. This is
done to present a human readable string where a database query needs an
identification number. By default, column |0| is used in both roles. If this
is not desired, the methods to change that must be called before specifying the
query.

@<SqlComboBox Implementation@>=
void SqlComboBox::setDataColumn(int column)
{
	dataColumn = column;
}

void SqlComboBox::setDisplayColumn(int column)
{
	displayColumn = column;
}

@ Once the widget is properly configured, we can run the SQL query and populate
the combo box with the results.

@<SqlComboBox Implementation@>=
void SqlComboBox::addSqlOptions(QString query)
{
	SqlQueryConnection *dbquery = new SqlQueryConnection;
	if(!dbquery->exec(query))
	{
		QSqlError error = dbquery->lastError();
		qDebug() << error.databaseText();
		qDebug() << error.driverText();
		qDebug() << error.text();
		qDebug() << dbquery->lastQuery();
		/* Throw an error here, please. */
	}
	while(dbquery->next())
	{
		QString displayValue(dbquery->value(displayColumn).toString());
		QString dataValue(dbquery->value(dataColumn).toString());
		if(dataColumnShown)
		{
			displayValue.append(QString(" (%1)").arg(dataValue));
		}
		addItem(displayValue, dataValue);
	}
	delete dbquery;
}

@ The constructor initializes some private member data. A size policy is also
set on the pop up. This allows the pop up to appear wider than the combo box to
allow more data to appear. On Linux this appears to also change the text elide
mode to something that is conveniently more appropriate for the use cases in
Typica. Note that this was not enough of a change to force the pop up to be
wide enough to contain all of the text for especially long items, but if the
combo box is wide enough the pop up will match that width.

The destructor is trivial.

@<SqlComboBox Implementation@>=
SqlComboBox::SqlComboBox() :
	dataColumn(0), displayColumn(0), dataColumnShown(false)
{
	view()->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

SqlComboBox::~SqlComboBox()
{
	/* Nothing needs to be done here. */
}

@ To use this class as an editor delegate in a model we wrap the class in a
|QItemDelegate|.

@<Class declarations@>=
class SqlComboBoxDelegate : public QItemDelegate@/
{
	Q_OBJECT@;
	SqlComboBox *delegate;
	public:@/
		SqlComboBoxDelegate(QObject *parent = NULL);
		QWidget *createEditor(QWidget *parent,
		                      const QStyleOptionViewItem &option,@|
							  const QModelIndex &index) const;
		void setEditorData(QWidget *editor, const QModelIndex &index) const;
		void setModelData(QWidget *editor, QAbstractItemModel *model,@|
		                  const QModelIndex &index) const;
		void setWidget(SqlComboBox *widget);
		virtual QSize sizeHint() const;
		void updateEditorGeometry(QWidget *editor,
		                          const QStyleOptionViewItem &option,@|
								  const QModelIndex &index) const;
};

@ Rather than set the values for the combo box through the delegate class, we
create the editor and pass it in to the delegate.

@<SqlComboBoxDelegate Implementation@>=
void SqlComboBoxDelegate::setWidget(SqlComboBox *widget)
{
	delegate = widget;
}

@ When a view requests this delegate, we simply return the widget that was
previously passed in.

@<SqlComboBoxDelegate Implementation@>=
QWidget* SqlComboBoxDelegate::createEditor(QWidget *parent,@|
                                           const QStyleOptionViewItem &,
										   const QModelIndex &) const
{
	return delegate->clone(parent);
}

@ To set the appropriate editor data, we check the value in the model and
attempt to set the value to match that.

@<SqlComboBoxDelegate Implementation@>=
void SqlComboBoxDelegate::setEditorData(QWidget *editor,
                                        const QModelIndex &index) const
{
	SqlComboBox *self = qobject_cast<SqlComboBox *>(editor);
	self->setCurrentIndex(self->findData(
								index.model()->data(index,
													Qt::UserRole).toString()));
}

@ When setting the model data, we need to specify both the display role and the
user data role.

@<SqlComboBoxDelegate Implementation@>=
void SqlComboBoxDelegate::setModelData(QWidget *editor,@|
                                       QAbstractItemModel *model,
                                       const QModelIndex &index) const
{
	SqlComboBox *self = qobject_cast<SqlComboBox *>(editor);
	model->setData(index, self->itemData(self->currentIndex(), Qt::UserRole),
	               Qt::UserRole);
	model->setData(index, self->currentText(), Qt::DisplayRole);
}

@ This is needed to play nicely with the model view architecture.

@<SqlComboBoxDelegate Implementation@>=
void SqlComboBoxDelegate::updateEditorGeometry(QWidget *editor,
											const QStyleOptionViewItem &option,
											const QModelIndex &) const
{
	editor->setGeometry(option.rect);
}

@ When this delegate is used in a table view, we want to be able to provide a
size hint that can be used to resize the column in order to fit the delegate.

@<SqlComboBoxDelegate Implementation@>=
QSize SqlComboBoxDelegate::sizeHint() const
{
	return delegate->sizeHint();
}

@ Finally, we need a constructor.

@<SqlComboBoxDelegate Implementation@>=
SqlComboBoxDelegate::SqlComboBoxDelegate(QObject *parent)
	: QItemDelegate(parent)@/
{
	/* Nothing needs to be done here. */
}

@** The main program.

The |main()| function is where program execution starts. Most of the work
required here is taken care of for us by the |Application| object.

The odd handling of argc is required to prevent segmentation faults in the Linux
build.

@<The main program@>=
int main(int argc, char **argv)@/
{@/
	int *c = &argc;
	Application app(*c, argv);
	@<Set up icons@>@;
	@<Set up fonts@>@;

	QSettings settings;

	@<Register device configuration widgets@>@;
	@<Prepare the database connection@>@;
	@<Load the application configuration@>@;
	@<Set up the scripting engine@>@;
	app.engine = engine;
	@<Find and evaluate starting script@>@;

	int retval = app.exec();
	delete engine;
	return retval;@/
}

@ \pn{} 1.4 introduces the ability to use icons in certain interface elements.
Some commonly desired public domain graphics are provided by the Tango Desktop
Project. We also set an application level default window icon.

@<Set up icons@>=
QStringList themeSearchPath = QIcon::themeSearchPaths();
themeSearchPath.append(":/resources/icons/tango");
QIcon::setThemeSearchPaths(themeSearchPath);
QIcon::setThemeName(":/resources/icons/tango");
app.setWindowIcon(QIcon(":/resources/icons/appicons/logo.svg"));

@ Similarly some elements make use of a special font which is loaded from
resource data.

There has been a report of a bug which I have not been able to reproduce and
which the original reporter has not yet gotten back to me with the results of
a test, so I have opted for an alternate approach which does not preclude the
use of the earlier plan but which may solve the matter. This brings in the
TeX Gyre Pagella font and sets this as the default standard font for all web
views.

@<Set up fonts@>=
QFile entypo(":/resources/fonts/entypo.ttf");
entypo.open(QIODevice::ReadOnly);
QFontDatabase::addApplicationFontFromData(entypo.readAll());
entypo.close();
QFontDatabase::addApplicationFont(":/resources/fonts/texgyrepagella-regular.otf");
QFontDatabase::addApplicationFont(":/resources/fonts/texgyrepagella-bold.otf");
QFontDatabase::addApplicationFont(":/resources/fonts/texgyrepagella-bolditalic.otf");
QFontDatabase::addApplicationFont(":/resources/fonts/texgyrepagella-italic.otf");
QWebSettings::globalSettings()->setFontFamily(QWebSettings::StandardFont, "Tex Gyre Pagella");

@ Some widgets provided by \pn{} require access to a database in order to work.
To simplify using these widgets, the application will request information
needed to connect to a database. The use of two distinct |if| blocks rather than
an |if|$\dots$|else| construction is used because the data from settings can be
changed if an attempt to connect to the database fails.

@<Prepare the database connection@>=
if(settings.value("database/exists", "false").toString() == "true")
{
	@<Try connecting to the database@>@;
}
if(settings.value("database/exists", "false").toString() == "false")
{
	@<Prompt for database connection information@>@;
}


@ In order to connect to the database, we need five pieces of information: the
name of a database driver (PostgreSQL is recommended for now), the host name of
the computer running the database, the name of the database, the name of the
user connecting to the database, and that user's password. This information will
be stored in the user settings for the application so that the database
connection can be established without prompting the user next time. A class is
provided to gather this information.

@<Class declarations@>=
class SqlConnectionSetup : public QDialog@/
{@t\1@>@/
	Q_OBJECT@;
	public:@/
		SqlConnectionSetup();
		~SqlConnectionSetup();@/
	@t\4@>public slots@t\kern-3pt@>:@/
		void testConnection();
	private:@/
		QFormLayout *formLayout;
		QComboBox *driver;
		QLineEdit *hostname;
		QLineEdit *dbname;
		QLineEdit *user;
		QLineEdit *password;
		QVBoxLayout *layout;
		QHBoxLayout *buttons;
		QPushButton *cancelButton;
		QPushButton *connectButton;@t\2@>@/
}@t\kern-3pt@>;

@ The constructor sets up this widget. The destructor does nothing.

@<SqlConnectionSetup implementation@>=
SqlConnectionSetup::SqlConnectionSetup() :
	formLayout(new QFormLayout), driver(new QComboBox), hostname(new QLineEdit),
	dbname(new QLineEdit), user(new QLineEdit), password(new QLineEdit),
	layout(new QVBoxLayout), buttons(new QHBoxLayout),
	cancelButton(new QPushButton(tr("Cancel"))),
	connectButton(new QPushButton(tr("Connect")))@/
{
	driver->addItem("PostgreSQL", "QPSQL");
	formLayout->addRow(tr("Database driver:"), driver);
	formLayout->addRow(tr("Host name:"), hostname);
	formLayout->addRow(tr("Database name:"), dbname);
	formLayout->addRow(tr("User name:"), user);
	password->setEchoMode(QLineEdit::Password);
	formLayout->addRow(tr("Password:"), password);
	layout->addLayout(formLayout);
	buttons->addStretch(1);
	buttons->addWidget(cancelButton);
	connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(reject()));
	buttons->addWidget(connectButton);
	layout->addLayout(buttons);
	connect(connectButton, SIGNAL(clicked(bool)), this, SLOT(testConnection()));
	setLayout(layout);
	setModal(true);
}

SqlConnectionSetup::~SqlConnectionSetup()
{
	/* Nothing needs to be done here. */
}

@ The |testConnection()| method checks if the information provided can be used
to open a new database connection.

@<SqlConnectionSetup implementation@>=
void SqlConnectionSetup::testConnection()
{
	QSqlDatabase database =
		QSqlDatabase::addDatabase(driver->itemData(driver->currentIndex()).
		                          toString());
	database.setConnectOptions("application_name=Typica");
	database.setHostName(hostname->text());
	database.setDatabaseName(dbname->text());
	database.setUserName(user->text());
	database.setPassword(password->text());
	if(database.open())
	{
		QSettings settings;
		settings.setValue("database/exists", "true");
		settings.setValue("database/driver",
		                  driver->itemData(driver->currentIndex()).toString());
		settings.setValue("database/hostname", hostname->text());
		settings.setValue("database/dbname", dbname->text());
		settings.setValue("database/user", user->text());
		settings.setValue("database/password", password->text());
		accept();
	}
	else
	{
		QMessageBox::information(this, tr("Database connection failed"),
		                         tr("Failed to connect to database."));
	}
}

@ In order to prompt for connection information, we simply create a
|SqlConnectionSetup| object and call |exec()|. When control returns, the
settings will either contain appropriate connection information or we have to
give up on getting that information from the user for now.

@<Prompt for database connection information@>=
SqlConnectionSetup dialog;
dialog.exec();

@ If we have connected to a database in the previous running of the application,
we try to connect to the same database automatically rather than prompt the
user. If the connection attempt fails, we can fall back on asking the user for
help.

@<Try connecting to the database@>=
QSqlDatabase database =
	QSqlDatabase::addDatabase(settings.value("database/driver").toString());
database.setConnectOptions("application_name=Typica");
database.setHostName(settings.value("database/hostname").toString());
database.setDatabaseName(settings.value("database/dbname").toString());
database.setUserName(settings.value("database/user").toString());
database.setPassword(settings.value("database/password").toString());
if(!database.open())
{
	settings.setValue("database/exists", "false");
}

@** Viewing a record of batches.

\noindent It is frequently useful to present a table view with the results of a
SQL query and have a way of interacting with that view to obtain more details
related to a given record in that table. For this purpose, \pn{} provides a
widget based on |QTableView| which presents information from a
|QSqlQueryModel|. The table emits signals when an entry in the table is double
clicked. One of these contains the data from the first column of that row and
is suitable for use when a primary key is presented in that column and this is
sufficient for the desired drill down. The other signal provides the row number
which can be used along with a reference to the table to obtain the data in any
column.

This class also automatically persists column widths when these are changed.

@<Class declarations@>=
class SqlQueryView : public QTableView@/
{@t\1@>@/
	Q_OBJECT@;
	public:@/
		SqlQueryView(QWidget *parent = NULL);
		void setQuery(const QString &query);
		bool setHeaderData(int section, Qt::Orientation@, orientation,
						   const QVariant &value, int role);
		Q_INVOKABLE QVariant data(int row, int column,
								  int role = Qt::DisplayRole);@/
	signals:@/
		void openEntry(QString key);
		void openEntryRow(int row);@t\2@>@/
	protected:@/
		virtual void showEvent(QShowEvent *event);
	private slots@t\kern-3pt@>:@t\1@>@/
		void openRow(const QModelIndex &index);
		void persistColumnResize(int column, int oldsize, int newsize);@t\2@>@/
}@t\kern-3pt@>;

@ The constructor sets up the communication between the model and the view and
also provides the connection needed to notice when columns change size to
persist that preference.

@<SqlQueryView implementation@>=
SqlQueryView::SqlQueryView(QWidget *parent) : QTableView(parent)
{
	setModel(new QSqlQueryModel);
	connect(this, SIGNAL(doubleClicked(QModelIndex)),
	        this, SLOT(openRow(QModelIndex)));
	connect(horizontalHeader(), SIGNAL(sectionResized(int, int, int)),
	        this, SLOT(persistColumnResize(int, int, int)));
}

@ Column width persistance requires two methods. First we have a slot
method which is called when a column width is changed. This is saved with
|QSettings| under a key utilizing the name of the window, the name of the
table, and the column number.

@<SqlQueryView implementation@>=
void SqlQueryView::persistColumnResize(int column, int, int newsize)
{
	@<Save updated column size@>@;
}

@ The body of this function has been split out so that it can be shared with
other table views without the need to introduce a new common base class.

@<Save updated column size@>=
QSettings settings;
@<Obtain top level widget@>@;
settings.setValue(QString("columnWidths/%1/%2/%3").
                         arg(topLevelWidget->objectName()).
	                     arg(objectName()).arg(column),
				  QVariant(newsize));

@ To determine which window a given table is in, we just follow
|parentWidget()| until there isn't one. It is possible that the table view
will also be the window, however this is not advised as it is easier for the
settings key to be non-unique in such a case.

@<Obtain top level widget@>=
QWidget *topLevelWidget = this;
while(topLevelWidget->parentWidget())
{
	topLevelWidget = topLevelWidget->parentWidget();
}

@ We restore column widths in response to a show event. One of these should be
received just before the widget is shown so the widget should appear correctly.

@<SqlQueryView implementation@>=
void SqlQueryView::showEvent(QShowEvent *event)
{
	@<Restore table column widths@>@;
	event->accept();
}

@ Similarly, most of the body of this method has also been split into a chunk
so that it might be shared with other classes.

@<Restore table column widths@>=
QSettings settings;
@<Obtain top level widget@>
QString baseKey =
	QString("columnWidths/%1/%2").arg(topLevelWidget->objectName()).
	                               arg(objectName());
for(int i = 0; i < model()->columnCount(); i++)
{
	QString key = QString("%1/%2").arg(baseKey).arg(i);
	if(settings.contains(key))
	{
		setColumnWidth(i, settings.value(key).toInt());
	}
}

@ A slot is required for obtaining the information to send out in our signals.

@<SqlQueryView implementation@>=
void SqlQueryView::openRow(const QModelIndex &index)
{
	emit openEntry(((QSqlQueryModel *)model())->record(index.row()).value(0).toString());
	emit openEntryRow(index.row());
}

@ The other functions are wrappers around model methods.

\danger |setQuery()| leaks database connections.

@<SqlQueryView implementation@>=
void SqlQueryView::setQuery(const QString &query)
{
	QSqlDatabase database = AppInstance->database();
	database.open();
	QSqlQuery q(query, database);
	((QSqlQueryModel*)model())->setQuery(q);
}

bool SqlQueryView::setHeaderData(int section, Qt::Orientation@, orientation,
                                 const QVariant &value, int role)
{
	return model()->setHeaderData(section, orientation, value, role);
}

@ A method is also provided to allow scripts to access the data.

@<SqlQueryView implementation@>=
QVariant SqlQueryView::data(int row, int column, int role)
{
	return model()->data(model()->index(row, column), role);
}

@ To use this class, it is useful to expose it to the host environment.

@<Function prototypes for scripting@>=
void setSqlQueryViewProperties(QScriptValue value, QScriptEngine *engine);
QScriptValue constructSqlQueryView(QScriptContext *context,
                                   QScriptEngine *engine);
QScriptValue SqlQueryView_setQuery(QScriptContext *context,
                                   QScriptEngine *engine);
QScriptValue SqlQueryView_setHeaderData(QScriptContext *context,
                                        QScriptEngine *engine);

@ The script constructor is passed to the host environment.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructSqlQueryView);
value = engine->newQMetaObject(&SqlQueryView::staticMetaObject, constructor);
engine->globalObject().setProperty("SqlQueryView", value);

@ Next we construct the view, add properties to access its methods from the host
environment, and pass that back.

@<Functions for scripting@>=
QScriptValue constructSqlQueryView(QScriptContext *, QScriptEngine *engine)
{
	QScriptValue object = engine->newQObject(new SqlQueryView);
	setSqlQueryViewProperties(object, engine);
	return object;
}

void setSqlQueryViewProperties(QScriptValue value, QScriptEngine *engine)
{
	setQTableViewProperties(value, engine);
	value.setProperty("setHeaderData",
	                  engine->newFunction(SqlQueryView_setHeaderData));
	value.setProperty("setQuery", engine->newFunction(SqlQueryView_setQuery));
}

@ The properties added are simplified wrappers around the class methods.

@<Functions for scripting@>=
QScriptValue SqlQueryView_setQuery(QScriptContext *context, QScriptEngine *)
{
	SqlQueryView *self = getself<SqlQueryView *>(context);
	QString query = argument<QString>(0, context);
	self->setQuery(query);
	self->reset();
	return QScriptValue();
}

QScriptValue SqlQueryView_setHeaderData(QScriptContext *context,
                                        QScriptEngine *)
{
	SqlQueryView *self = getself<SqlQueryView *>(context);
	int section = argument<int>(0, context);
	QString data = argument<QString>(1, context);
	self->setHeaderData(section, Qt::Horizontal, data, Qt::DisplayRole);
	return QScriptValue();
}

@** Reporting.

\noindent \pn{} version 1.4 added a new type of menu which is designed to
handle reports. This makes extensive use of the previously existing reporting
system at present which makes modifying existing reports to work with the new
system very simple. Further changes may be introduced in the future that
substantially depart from this in order to simplify report files.

Previously to add a new report to a configuration, you needed to create the
report, add an {\tt <include>} tag in the main configuration file to bring that
report into the application configuration, then in any window with a Reports
menu you would need to add the report to that menu in its configuration file
and write a small bit of JavaScript to obtain a reference to that new menu
item and create the report when that menu item is triggered. This is highly
repetetive, error prone, and with the new approach it is not needed at all.

To add a new report to a configuration using the new approach one need only
save the new report file in the appropriate directory and \pn{} will detect
this, add it to any Reports menus that may exist, and handle all of the details
of generating these reports on demand.

The Reports menu is created in a configuration as a {\tt <menu>} element with
three attributes. The {\tt name} attribute as usual is the name of the menu
item. The {\tt type} attribute will have a value of {\tt "reports"} and the
{\tt src} attribute will indicate the directory to search for reports to
populate that menu. This allows for multiple Reports menus with different
reports in each menu if desired.

Reports are added to the menu in the order of the file names in the reports
directory.

\danger While it should not be an issue with the limited number of reports
presently distributed with Typica, the approach taken to implementing this menu
type is highly inefficient. There are many optimizations available if this
becomes problematic.\endanger

@<Populate reports menu@>=
QSettings settings;
QDir directory(QString("%1/%2").arg(settings.value("config").toString()).
                                arg(element.attribute("src")));
directory.setFilter(QDir::Files);
directory.setSorting(QDir::Name);
QStringList nameFilter;
nameFilter << "*.xml";
directory.setNameFilters(nameFilter);
QFileInfoList reportFiles = directory.entryInfoList();
for(int i = 0; i < reportFiles.size(); i++)
{
	QFileInfo reportFile = reportFiles.at(i);
	@<Add report to reports menu@>@;
}

@ The menu items themselves are a subclass of |QAction| which holds all of the
information needed to respond to its activation by generating the appropriate
report.

@<Class declarations@>=
class ReportAction : public QAction
{
	Q_OBJECT
	public:
		ReportAction(const QString &fileName, const QString &reportName,
		             QObject *parent = NULL);
	private slots:
		void createReport();
	private:
		QString reportFile;
};

@ The constructor receives the name of the report file which is used to
generate the report when needed and the name of the report which is used as the
name presented in the menu.

@<ReportAction implementation@>=
ReportAction::ReportAction(const QString &fileName, const QString &reportName,
                           QObject *parent) :
	QAction(reportName, parent), reportFile(fileName)
{
	connect(this, SIGNAL(triggered()), this, SLOT(createReport()));
}

@ The slot method is responsible for creating the new report. This is very
similar to the old approach and reuses much of the same code. Of particular
note is the |targetID| variable. This is set to facilitate window geometry
management, though this should probably be set from the {\tt id} attribute
of the {\tt <window>} element in the file to preserve window geometry
settings if the configuration is moved to another location in the file
system.

@<ReportAction implementation@>=
void ReportAction::createReport()
{
	QFile file(reportFile);
	QDomDocument document;
	if(file.open(QIODevice::ReadOnly))
	{
		document.setContent(&file, true);
		QDomElement element = document.documentElement();
		QScriptEngine *engine = AppInstance->engine;
		QScriptContext *context = engine->pushContext();
		QScriptValue object;
		QString targetID = reportFile;
		@<Display the window@>@;
		file.close();
		engine->popContext();
	}
}

@ With the |ReportAction| available, we are now ready to add reports to the
Reports menu. To do this we check each file in the given directory to determine
if it is a report file, obtain the report title and location within the menu
hierarchy from the file data, create the actions, and add them to the menu.

@<Add report to reports menu@>=
QString path = reportFile.absoluteFilePath();
QFile file(path);
if(file.open(QIODevice::ReadOnly))
{
	QDomDocument document;
	document.setContent(&file, true);
	QDomElement root = document.documentElement();
	QDomNode titleNode = root.elementsByTagName("reporttitle").at(0);
	if(!titleNode.isNull())
	{
		QDomElement titleElement = titleNode.toElement();
		QString title = titleElement.text();
		if(!title.isEmpty())
		{
			QStringList hierarchy = title.split(":->");
			QMenu *insertionPoint = menu;
			@<Traverse report menu hierarchy@>
			ReportAction *action = new ReportAction(path, hierarchy.last());
			insertionPoint->addAction(action);
		}
	}
}

@ \pn{} allows the Reports menu to contain arbitrarily deep menu hierarchies.
It is advised to keep these hierarchies shallow.

@<Traverse report menu hierarchy@>=
for(int j = 0; j < hierarchy.size() - 1; j++)
{
	QObjectList menuList = insertionPoint->children();
	bool menuFound = false;
	for(int k = 0; k < menuList.size(); k++)
	{
		QMenu *currentItem = qobject_cast<QMenu*>(menuList.at(k));
		if(currentItem)
		{
			if(currentItem->title() == hierarchy.at(j))
			{
				menuFound = true;
				insertionPoint = currentItem;
				break;
			}
		}
	}
	if(!menuFound)
	{
		insertionPoint = insertionPoint->addMenu(hierarchy.at(j));
	}
}

@ \noindent The reporting functionality in \pn{} is based on the Scribe framework
in Qt. This brings several benefits, including making it easy to print reports
or save reports as plain text or HTML.

Reports are specified in the \pn{}'s configuration document and can include both
static elements and elements that are populated by external data such as the
result of a SQL query.

@<Function prototypes for scripting@>=
void addReportToLayout(QDomElement element, QStack<QWidget *> *widgetStack,
                       QStack<QLayout *> *layoutStack);

@ When adding a report to a layout, we must not only add the widget to the
layout, but also construct the document.

@<Functions for scripting@>=
void addReportToLayout(QDomElement element, QStack<QWidget *> *,@|
                       QStack<QLayout *> *layoutStack)
{
	QTextEdit *widget = new QTextEdit;
	if(element.hasAttribute("id"))
	{
		widget->setObjectName(element.attribute("id"));
	}
	QBoxLayout *layout = qobject_cast<QBoxLayout *>(layoutStack->top());
	layout->addWidget(widget);
	QTextDocument *document = new QTextDocument;
	QFont defaultFont;
	defaultFont.setPointSize(11);
	document->setDefaultFont(defaultFont);
	QTextCursor cursor(document);
	@<Construct report document@>@;
	widget->setDocument(document);
}

@ Several child elements are allowed under the {\tt <report>} element. These
should be processed in order to produce the final report document.

@<Construct report document@>=
QDomNodeList children = element.childNodes();
for(int i = 0; i < children.count(); i++)
{
	QDomNode current;
	QDomElement currentElement;
	current = children.at(i);
	if(current.isElement())
	{
		currentElement = current.toElement();
		@<Process report document elements@>@;
	}
}

@ If any custom styling for HTML content is required, a {\tt <style>} element
should be placed in the report description before any such content.

@<Process report document elements@>=
if(currentElement.tagName() == "style")
{
	document->setDefaultStyleSheet(currentElement.text());
}

@ One common need is the ability to insert static text, such as the title of the
report. In order to simplify formatting, the text can be interpreted as HTML.
Note that to avoid having HTML tags eaten by the parser, the text of this
element should be a CDATA section.

@<Process report document elements@>=
if(currentElement.tagName() == "html")
{
	cursor.insertHtml(currentElement.text());
}

@ If no special formatting is needed, a plain text element can be used. This
might be extended in the future to allow attributes for specifying the character
formatting to be used with the text.

@<Process report document elements@>=
if(currentElement.tagName() == "text")
{
	cursor.insertText(currentElement.text());
}

@ One of the more interesting elements of a report is the {\tt <table>} element.
This is an element which can change its contents in response to changes in user
controls.

@<Process report document elements@>=
if(currentElement.tagName() == "table")
{
	QTextFrame *frame = cursor.insertFrame(QTextFrameFormat());
	ReportTable *table = new ReportTable(frame, currentElement);
	table->setParent(widget);
	if(currentElement.hasAttribute("id"))
	{
		table->setObjectName(currentElement.attribute("id"));
	}
}

@ The |ReportTable| class is responsible for parsing {\tt <table>} child
elements and inserting the table into the document at the correct location.

@<Class declarations@>=
class ReportTable : public QObject@/
{@t\1@>@/
	Q_OBJECT@;
	QTextFrame *area;
	QDomElement configuration;
	QMap<QString, QVariant> bindings;
	public:@/
		ReportTable(QTextFrame *frame, QDomElement description);
		~ReportTable();
		@[Q_INVOKABLE@,@, void@]@, bind(QString placeholder, QVariant value);@t\2\2@>@/
	@t\4@>public slots@t\kern-3pt@>:@/
		void refresh();@t\2@>@/
}@t\kern-3pt@>;

@ The |ReportTable| class takes a |QTextFrame| and |QDomElement| pointer in
its constructor. The former is used to establish the bounds of the table within
a document and the latter is used for generating the table contents.

@<ReportTable implementation@>=
ReportTable::ReportTable(QTextFrame *frame, QDomElement description) :
	area(frame), configuration(description)
{
	refresh();
}

ReportTable::~ReportTable()
{

}

@ In order to change the table contents based on user controls, the |bind()|
method allows a placeholder to be replaced with a value when evaluating a SQL
query.

@<ReportTable implementation@>=
void ReportTable::bind(QString placeholder, QVariant value)
{
	bindings.insert(placeholder, value);
}

@ All of the interesting work is done in the |refresh()| slot. This method
deletes the current content of the frame and creates a table based on the
description of the table in the configuration document.

@<ReportTable implementation@>=
void ReportTable::refresh()
{
	@<Delete current report table content@>@;
	int rows = 1;
	int columns = 1;
	int currentRow = 0;
	QTextTable *table = cursor.insertTable(rows, columns);
	@<Set table formatting@>@;
	@<Reconstruct report table content@>@;
	if(rows > 1)
	{
		table->removeRows(0, 1);
	}
}

@ Deleting the current content of the table involves using a cursor to select
everything in the frame and then removing that selection. There are more optimal
ways to do this but if there are performance problems with this, you may want to
reconsider what you are trying to do.

@<Delete current report table content@>=
QTextCursor cursor = area->firstCursorPosition();
while(cursor < area->lastCursorPosition())
{
	cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor);
}
cursor.removeSelectedText();

@ When creating a new table, we may need to alter the formatting of that table.
To do this, we get the current format, modify that based on attributes of the
{\tt <table>} element, and apply the modified copy to the newly constructed
table.

@<Set table formatting@>=
QTextTableFormat format = table->format();
format.setBorderStyle(QTextFrameFormat::BorderStyle_None);
if(configuration.hasAttribute("align"))
{
	if(configuration.attribute("align") == "center")
	{
		format.setAlignment(Qt::AlignHCenter);
	}
}
table->setFormat(format);

@ To reconstruct the table, we need to parse the description of the table.

@<Reconstruct report table content@>=
QDomNodeList children = configuration.childNodes();
for(int i = 0; i < children.count(); i++)
{
	QDomNode current;
	QDomElement currentElement;
	current = children.at(i);
	if(current.isElement())
	{
		currentElement = current.toElement();
		if(currentElement.tagName() == "query")
		{
			@<Add SQL query results to report table@>@;
		}
		else if(currentElement.tagName() == "row")
		{
			@<Add new row to report table@>@;
		}
	}
}

@ The text of a {\tt <query>} element will be the query desired in the table.
This might include placeholders that must be bound to values before the query is
executed. If query execution results in an error (as it will if it contains
placeholders that have not yet had values bound to them), there will be no
change to the table and the next child element, if any, will be processed.

@<Add SQL query results to report table@>=
SqlQueryConnection query;
query.prepare(currentElement.text());
foreach(QString key, bindings.uniqueKeys())
{
	if(currentElement.text().contains(key))
	{
		query.bindValue(key, bindings.value(key));
	}
}
query.exec();
if(!query.next())
{
	continue;
}
if(query.record().count() > columns)
{
	table->appendColumns(query.record().count() - columns);
}
do
{
	table->appendRows(1);
	rows++;
	currentRow++;
	for(int j = 0; j < query.record().count(); j++)
	{
		QTextTableCell cell = table->cellAt(currentRow, j);
		cursor = cell.firstCursorPosition();
		cursor.insertText(query.value(j).toString());
	}
} while(query.next());

@ It is sometimes desirable to add fixed data such as column headers to a table.
This is done with the {\tt <row>} element.

Technically, this isn't needed. The same results can be produced by using a
{\tt <query>} element to select constant data, but this approach saves a trip to
the database.

@<Add new row to report table@>=
table->appendRows(1);
currentRow++;
rows++;
QDomNodeList rowChildren = currentElement.childNodes();
int currentColumn = 0;
for(int j = 0; j < rowChildren.count(); j++)
{
	QDomNode node;
	QDomElement nodeElement;
	node = rowChildren.at(j);
	if(node.isElement())
	{
		nodeElement = node.toElement();
		if(nodeElement.tagName() == "cell")
		{
			if(currentColumn == columns)
			{
				table->appendColumns(1);
				columns++;
			}
			QTextTableCell cell = table->cellAt(currentRow, currentColumn);
			cursor = cell.firstCursorPosition();
			cursor.insertText(nodeElement.text());
			currentColumn++;
		}
	}
}

@ In order to expose report printing capabilities, we provide a property on
|QTextEdit| objects to handle this.

@<Function prototypes for scripting@>=
void setQTextEditProperties(QScriptValue value, QScriptEngine *engine);
QScriptValue QTextEdit_print(QScriptContext *context, QScriptEngine *engine);

@ This function is a trivial adaptation from the Qt documentation.

@<Functions for scripting@>=
QScriptValue QTextEdit_print(QScriptContext *context, QScriptEngine *)
{
	QTextEdit *self = getself<QTextEdit *>(context);
	QTextDocument *document = self->document();
	QPrinter printer;

	QPrintDialog printwindow(&printer, self);
	if(printwindow.exec() != QDialog::Accepted)
	{
		return QScriptValue();
	}
	document->print(&printer);
	return QScriptValue();
}

@ The host environment must be informed of this function.

@<Functions for scripting@>=
void setQTextEditProperties(QScriptValue value, QScriptEngine *engine)
{
	setQAbstractScrollAreaProperties(value, engine);
	value.setProperty("print", engine->newFunction(QTextEdit_print));
}

@** An area for repeated user interface elements.

\noindent There are multiple use cases in which it is useful to specify a
complex aggregation of user interface elements to be repeated arbitrarily many
times. For example, placing multiple copies of a cupping form in a single area
for conveniently entering observations for all coffees in a particular session
or providing any number of copies of the form for entering coffee purchase
information. The |FormArray| widget provides this capability, allowing the
XML portion of the configuration document to specify the form once and allowing
the host environment to access the copies.

Slots and the |Q_INVOKABLE| macro are used to simplify the use of this class
from the host environment.

@<Class declarations@>=
class FormArray : public QScrollArea@/
{@t\1@>@/
	Q_OBJECT@;
	QDomElement configuration;
	QWidget itemContainer;
	QVBoxLayout itemLayout;
	int maxwidth;
	int maxheight;
	public:@/
		FormArray(QDomElement description);
		@[Q_INVOKABLE@,@, QWidget*@] elementAt(int index);@t\2\2@>@/
		@[Q_INVOKABLE@,@, int@] elements();@t\2\2@>@/
	@t\4@>public slots@t\kern-3pt@>:@/
		void addElements(int copies = 1);
		void removeAllElements();
		void setMaximumElementWidth(int width);
		void setMaximumElementHeight(int height);@t\2@>@/
}@t\kern-3pt@>;

@ The |FormArray| is just a |QScrollArea| providing a view onto a |QWidget|
containing a layout which has arbitrarily many copies of a |QWidget| with
contents determined by the configuration document used to create the
|FormArray|.

@<FormArray implementation@>=
FormArray::FormArray(QDomElement description) : configuration(description),
	maxwidth(-1), maxheight(-1)@/
{
	setWidget(&itemContainer);
	itemContainer.setLayout(&itemLayout);
}

@ The |FormArray| was initially created by an XML element. A copy of this is
stored in the private variable |configuration|. This can have the same child
elements as {\tt <widget>}, allowing us to reuse the function for creating
populating the widget. When adding a new element, we must resize the
|itemContainer|, otherwise Qt will attempt to cram all widgets in the layout
into the same vertical space as was previously required. The result is not
attractive. We also set a minimum width just in case the newly created widget is
the first one added to the area.

@<FormArray implementation@>=
void FormArray::addElements(int copies)
{
	QStack<QWidget *> *widgetStack = new QStack<QWidget *>;
	QStack<QLayout *> *layoutStack = new QStack<QLayout *>;
	QWidget *widget;
	for(int i = 0; i < copies; i++)
	{
		widget = new QWidget;
		if(maxwidth > -1)
		{
			widget->setMaximumWidth(maxwidth);
		}
		if(maxheight > -1)
		{
			widget->setMaximumHeight(maxheight);
		}
		if(configuration.hasChildNodes())
		{
			widgetStack->push(widget);
			populateWidget(configuration, widgetStack, layoutStack);
			widgetStack->pop();
			widget->setMinimumHeight(widget->sizeHint().height());
			itemLayout.addWidget(widget);
			if(widget->sizeHint().height() > maxheight && maxheight > -1)
			{
				itemContainer.setMinimumHeight(maxheight * elements() + 50);
			}
			else
			{
				itemContainer.setMinimumHeight(itemContainer.sizeHint().height()
				                               + widget->sizeHint().height());
			}
			if(maxwidth > -1)
			{
				itemContainer.setMinimumWidth(maxwidth + 50);
			}
			else
			{
				itemContainer.setMinimumWidth(widget->sizeHint().width() + 50);
			}
		}
	}
}

@ In order to retrieve a widget from the area, we use the |elementAt()| method.
The pointer returned by this function can be used as the first argument to
|findChildObject()| in the host environment in order to find any widget in the
form.

@<FormArray implementation@>=
QWidget* FormArray::elementAt(int index)
{
	if(index < itemLayout.count())
	{
		QLayoutItem *item = itemLayout.itemAt(index);
		return item->widget();
	}
	else
	{
		return NULL;
	}
}

@ Removing all elements is trivial, however we must be sure to reset the size of
|itemContainer|.

@<FormArray implementation@>=
void FormArray::removeAllElements()
{
	while(itemLayout.count() > 0)
	{
		QLayoutItem *item;
		item = itemLayout.itemAt(0);
		item->widget()->hide();
		itemLayout.removeWidget(item->widget());
	}
	itemContainer.setMinimumHeight(0);
}

@ This just leaves a method for determining the number of elements already in
the view. This is equal to the number of items in the layout.

@<FormArray implementation@>=
int FormArray::elements()
{
	return itemLayout.count();
}

@ Some widgets do not behave well in a |FormArray| setting and will try to use
an excess of screen space. In these cases, constraining the size of the elements
can be beneficial. These just set private member variables which are used when
adding new elements.

@<FormArray implementation@>=
void FormArray::setMaximumElementWidth(int width)
{
	maxwidth = width;
}

void FormArray::setMaximumElementHeight(int height)
{
	maxheight = height;
}

@ In order to create an instance of this class from the configuration document,
a {\tt <formarray>} element is used. This can be added to any layout.

@<Function prototypes for scripting@>=
void addFormArrayToLayout(QDomElement element, QStack<QWidget *> *widgetStack,@|
                          QStack<QLayout *> *layoutStack);

@ Processing child elements is deferred until a call to
|FormArray::addElements()| has been made.

@<Functions for scripting@>=
void addFormArrayToLayout(QDomElement element, QStack<QWidget *> *,@|
                          QStack<QLayout *> *layoutStack)
{
	FormArray *widget = new FormArray(element);
	if(element.hasAttribute("id"))
	{
		widget->setObjectName(element.attribute("id"));
	}
	QBoxLayout *layout = qobject_cast<QBoxLayout *>(layoutStack->top());
	layout->addWidget(widget);
}

@** Scale widgets.

\noindent One of the most commonly used methods of documenting the properties of
a coffee is through a cupping form. Several such forms exist to meet different
needs, however most involve several scales which can be marked to determine some
aspect of a particular attribute. Some of these scales are scored values which,
when considered with other scored values produce a numerical representation of
the quality of a given coffee. Others are unscored values which serve to provide
additional documentation of a property. For example, when the SCAA cupping form
expanded to the current form of ten scored properties with defects subtracted
from the total, a second scale was added for the acidity property. The scored
scale is used for marking the quality of the acidity while another unscored
scale is used for marking the intensity of that acidity.

Previously, in order to enter cupping information in \pn{}, numeric entry fields
were used. While this was very efficient for transcribing paper cupping forms
(and this was, in fact, the principal use case for our prototype cupping form
database software), it is not a form that lends itself to convenient use at the
cupping table.

Two new widgets are therefore introduced which allows a cupper to simply click
at some point on the scale to record that impression. Unfortunately, this is
still something of a tradeoff. It is not quite so efficient as using a paper
form in my experience, however it is faster than transcribing a stack of cupping
forms, particularly when working with cuppers with ambiguous handwriting. By
moving data acquisition to the point of data generation, a more useful record
can be produced for use in aggregate analysis.

@* The Horizontal Scale.

\noindent Several cupping forms make use of 10 point scales for the quality of
various attributes. The |ScaleControl| widget provides such a scale. It
consists of a bar with major ticks at 0, 5, and 10 and minor ticks at integer
values within this range. The first click sets both the initial and final value
of the scale while subsequent clicks adjust only the final value. A pair of
controls at each end of the scale allows the user to adjust either of these
values to compensate for imprecision at the point of the click. The two values,
an initial unscored value and a final scored value, provide some limited
temporal documentation. That is, it documents how the perception of a coffee
changes as it cools.

The widget is implemented as a |QGraphicsView| subclass. Please note that the
scale widgets are not particularly robust. In order to support a broader range
of cupping forms, there are plans to extend this class to allow user defined
range and tick patterns and user defined colors for the indicators.

@<Class declarations@>=
class ScaleControl : public QGraphicsView@/
{@t\1@>@/
	Q_OBJECT@/
	Q_PROPERTY(double initialValue READ initialValue WRITE setInitialValue)@/
	Q_PROPERTY(double finalValue READ finalValue WRITE setFinalValue)@/
	@<ScaleControl private members@>@t\2\2@>@/
	public:@/
		ScaleControl();
		double initialValue(void);
		double finalValue(void);
		virtual QSize sizeHint() const;@/
	@[public slots@]:@/
		void setInitialValue(double value);
		void setFinalValue(double value);@/
	signals:@/
		void initialChanged(double);
		void finalChanged(double);@/
	protected:@/
		virtual void mousePressEvent(QMouseEvent *event);
		virtual void mouseReleaseEvent(QMouseEvent *event);@t\2@>@/
}@t\kern-4pt@>;

@ The private variables available to instances of this class are used for
managing various aspects of the widget.

@<ScaleControl private members@>=
QGraphicsScene scene;
QGraphicsPolygonItem initialDecrement;
QGraphicsPolygonItem initialIncrement;
QGraphicsPolygonItem finalDecrement;
QGraphicsPolygonItem finalIncrement;
QGraphicsPolygonItem initialIndicator;
QGraphicsPolygonItem finalIndicator;
QGraphicsPathItem scaleLine;
QPolygonF left;
QPolygonF right;
QPolygonF down;
QPolygonF up;
QPainterPath scalePath;
QBrush initialBrush;
QBrush finalBrush;
double nonScoredValue;
double scoredValue;
bool initialSet;
bool finalSet;
bool scaleDown;

@ The constructor sets up the scene displayed by this widget. There is
considerable room for improvement here.

@<ScaleControl implementation@>=
ScaleControl::ScaleControl() : QGraphicsView(NULL, NULL), nonScoredValue(-1),
	scoredValue(-1), initialSet(false), finalSet(false), scaleDown(false)
{
	left << QPointF(0, 5) << QPointF(10, 0) << QPointF(10, 10) <<
	        QPointF(0, 5);
	right << QPointF(10, 5) << QPointF(0, 0) << QPointF(0, 10) <<
	         QPointF(10, 5);
	down << QPointF(0, 0) << QPointF(-5, -10) << QPointF(5, -10) <<
	        QPointF(0, 0);
	up << QPointF(0, 0) << QPointF(-5, 10) << QPointF(4, 10) << QPointF(0, 0);
	initialBrush.setColor(QColor(170, 170, 255));
	initialBrush.setStyle(Qt::SolidPattern);
	finalBrush.setColor(Qt::blue);
	finalBrush.setStyle(Qt::SolidPattern);
	initialDecrement.setPolygon(left);
	initialDecrement.setBrush(initialBrush);
	initialDecrement.setPos(0, 0);
	scene.addItem(&initialDecrement);
	initialIncrement.setPolygon(right);
	initialIncrement.setBrush(initialBrush);
	initialIncrement.setPos(122, 0);
	scene.addItem(&initialIncrement);
	finalDecrement.setPolygon(left);
	finalDecrement.setBrush(finalBrush);
	finalDecrement.setPos(0, 12);
	scene.addItem(&finalDecrement);
	finalIncrement.setPolygon(right);
	finalIncrement.setBrush(finalBrush);
	finalIncrement.setPos(122, 12);
	scene.addItem(&finalIncrement);
	scalePath.moveTo(0, 10);
	scalePath.lineTo(100, 10);
	scalePath.moveTo(0, 0);
	scalePath.lineTo(0, 20);
	scalePath.moveTo(10, 5);
	scalePath.lineTo(10, 15);
	scalePath.moveTo(20, 5);
	scalePath.lineTo(20, 15);
	scalePath.moveTo(30, 5);
	scalePath.lineTo(30, 15);
	scalePath.moveTo(40, 5);
	scalePath.lineTo(40, 15);
	scalePath.moveTo(50, 0);
	scalePath.lineTo(50, 20);
	scalePath.moveTo(60, 5);
	scalePath.lineTo(60, 15);
	scalePath.moveTo(70, 5);
	scalePath.lineTo(70, 15);
	scalePath.moveTo(80, 5);
	scalePath.lineTo(80, 15);
	scalePath.moveTo(90, 5);
	scalePath.lineTo(90, 15);
	scalePath.moveTo(100, 0);
	scalePath.lineTo(100, 20);
	scaleLine.setPath(scalePath);
	scaleLine.setPos(16, 1);
	scene.addItem(&scaleLine);
	setScene(&scene);
	initialIndicator.setPolygon(down);
	initialIndicator.setBrush(initialBrush);
	finalIndicator.setPolygon(up);
	finalIndicator.setBrush(finalBrush);
	setMinimumSize(sizeHint());
	setMaximumSize(sizeHint());
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setMinimumSize(sizeHint());
}

@ The size hint forces a smaller representation of the widget, making it easier
to arrange with other widgets.

@<ScaleControl implementation@>=
QSize ScaleControl::sizeHint() const
{
	return QSize(140, 30);
}

@ The methods for setting the values represented on the scale must ensure that
the appropriate indicator is drawn and position it appropriately.

@<ScaleControl implementation@>=
void ScaleControl::setInitialValue(double value)@t\2\2@>@/
{@t\1@>@/
	if(value >= 0 && value <= 10)@/
	{@t\1@>@/
		nonScoredValue = value;
		if(!initialSet)
		{
			scene.addItem(&initialIndicator);
		}
		initialSet = true;
		initialIndicator.setPos(value * 10 + 16, 10);
		emit initialChanged(value);
		if(!finalSet)
		{
			setFinalValue(value);
		}@t\2@>@/
	}@t\2@>@/
}@/@/

void ScaleControl::setFinalValue(double value)@t\2\2@>@/
{@t\1@>@/
	if(value >= 0 && value <= 10)@/
	{@t\1@>@/
		scoredValue = value;
		if(!finalSet)@/
		{
			scene.addItem(&finalIndicator);
		}
		finalSet = true;
		finalIndicator.setPos(value * 10 + 16, 11);
		emit finalChanged(value);@t\2@>@/
	}@t\2@>@/
}

@ These values can, of course, be retrieved programmatically.

@<ScaleControl implementation@>=
double ScaleControl::initialValue(void)
{
	return nonScoredValue;
}

double ScaleControl::finalValue(void)
{
	return scoredValue;
}

@ This only leaves the matter of handling interaction with the widget. A future
version of this class might split the various interface elements in the scene
into distinct classes capable of using the event propagation capabilities
provided by the graphics view framework, however with the current design, we
must do a little more work.

There are two events which must be accepted in order to register a click on a
given portion of the scale. One event is generated when the mouse button is
pressed.

@<ScaleControl implementation@>=
void ScaleControl::mousePressEvent(QMouseEvent *event)@t\2\2@>@/
{@t\1@>@/
	@<Check that the left button was pressed@>@;
	scaleDown = true;
	event->accept();@t\2@>@/
}

@ The primary action button on the mouse is the left button. While there might
be sensible interactions to provide in response to other buttons, these are not
presently supported.

@<Check that the left button was pressed@>=
if(event->button() != Qt::LeftButton)
{
	event->ignore();
	return;
}

@ Most of the click event handling is done in response to releasing the mouse
button. In this event handler we must determine if the click occurred in a
clickable portion of the scale and take the appropriate action in response.

@<ScaleControl implementation@>=
void ScaleControl::mouseReleaseEvent(QMouseEvent *event)@t\2\2@>@/
{@t\1@>@/
	@<Check that the left button was pressed@>@;
	if(!scaleDown)
	{
		event->ignore();
		return;
	}
	scaleDown = false;
	QPointF sceneCoordinate = mapToScene(event->x(), event->y());
	@<Handle clicks in the decrement controls@>@;
	@<Handle clicks in the increment controls@>@;
	@<Handle clicks in the scale area@>@;
	event->ignore();
	return;@t\2@>@/
}

@ As currently implemented, each horizontal pixel position represents a value
evenly divisible by $0.1$. It is, however, quite common to see vaues with a
$.25$ or $.75$ after the whole number on cupping forms. In order to make it
possible to select such values without vastly increasing the length of the
scale, the increment and decrement controls adjust the represented value by
$0.05$.

@<Handle clicks in the decrement controls@>=
if(sceneCoordinate.x() >= 0 && sceneCoordinate.x() <= 10)
{
	if(sceneCoordinate.y() >= 0 && sceneCoordinate.y() <= 10)
	{
		if(initialSet)
		{
			setInitialValue(nonScoredValue - 0.05);
		}
		event->accept();
		return;
	}
	else if(sceneCoordinate.y() >= 12 && sceneCoordinate.y() <= 22)
	{
		if(finalSet)
		{
			setFinalValue(scoredValue - 0.05);
			event->accept();
			return;
		}
	}
}

@ Incrementing represented values is done in the same manner as decrementing
them.

@<Handle clicks in the increment controls@>=
else if(sceneCoordinate.x() >= 122 && sceneCoordinate.x() <= 132)
{
	if(sceneCoordinate.y() >= 0 && sceneCoordinate.y() <= 10)
	{
		if(initialSet)
		{
			setInitialValue(nonScoredValue + 0.05);
			event->accept();
			return;
		}
	}
	else if(sceneCoordinate.y() >= 12 && sceneCoordinate.y() <= 22)
	{
		if(finalSet)
		{
			setFinalValue(scoredValue + 0.05);
			event->accept();
			return;
		}
	}
}

@ When handling clicks in the scale area, there is a difference between the
first click and any subsequent click.

@<Handle clicks in the scale area@>=
double relativeX = sceneCoordinate.x() - 16;
if(initialSet)
{
	if(relativeX >= 0 && relativeX <= 100)
	{
		setFinalValue(relativeX / 10.0);
		event->accept();
		return;
	}
}
else
{
	if(relativeX >= 0 && relativeX <= 100)
	{
		setInitialValue(relativeX / 10.0);
		event->accept();
		return;
	}
}

@* The Vertical Scale.

\noindent In addition to the horizontal scale, there is also a vertical scale.
The implementation of this class is in some ways a bit simpler as only one value
must be retained. While there is no prohibition on using this scale for scored
values (and this might enable a rather compact representation which might be
useful in some applications), its intent is for unscored values which are less
likely to change over time. If the dry aroma of a coffee changes significantly
during a cupping session, you are most likely waiting far too long to pour the
water.

@<Class declarations@>=
class IntensityControl : public QGraphicsView
{
	Q_OBJECT
	Q_PROPERTY(double value READ value WRITE setValue)
	QGraphicsScene scene;
	QGraphicsPolygonItem decrement;
	QGraphicsPolygonItem increment;
	QGraphicsPolygonItem indicator;
	QGraphicsPathItem scaleLine;
	QPolygonF left;
	QPolygonF up;
	QPolygonF down;
	QPainterPath scalePath;
	QBrush theBrush;
	double theValue;
	bool valueSet;
	bool scaleDown;
	public:
		IntensityControl();
		double value();
		virtual QSize sizeHint() const;
	public slots:
		void setValue(double val);
	signals:
		void valueChanged(double);
	protected:
		virtual void mousePressEvent(QMouseEvent *event);
		virtual void mouseReleaseEvent(QMouseEvent *event);
};

@ Note the similarity between this constructor and the the |ScaleControl|
constructor.

@<IntensityControl implementation@>=
IntensityControl::IntensityControl() : QGraphicsView(NULL, NULL), theValue(-1),
	valueSet(false), scaleDown(false)
{
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	left << QPointF(0, 0) << QPointF(10, -5) << QPointF(10, 5) << QPointF(0, 0);
	down << QPointF(0, 0) << QPointF(10, 0) << QPointF(5, 10) << QPointF(0, 0);
	up << QPointF(0, 10) << QPointF(10, 10) << QPointF(5, 0) << QPointF(0, 10);
	theBrush.setColor(Qt::blue);
	theBrush.setStyle(Qt::SolidPattern);
	increment.setPolygon(up);
	increment.setBrush(theBrush);
	increment.setPos(0, 0);
	scene.addItem(&increment);
	decrement.setPolygon(down);
	decrement.setBrush(theBrush);
	decrement.setPos(0, 122);
	scene.addItem(&decrement);
	scalePath.moveTo(5, 0);
	scalePath.lineTo(5, 100);
	scalePath.moveTo(0, 0);
	scalePath.lineTo(10, 0);
	scalePath.moveTo(0, 10);
	scalePath.lineTo(10, 10);
	scalePath.moveTo(0, 20);
	scalePath.lineTo(10, 20);
	scalePath.moveTo(0, 30);
	scalePath.lineTo(10, 30);
	scalePath.moveTo(0, 40);
	scalePath.lineTo(10, 40);
	scalePath.moveTo(0, 50);
	scalePath.lineTo(10, 50);
	scalePath.moveTo(0, 60);
	scalePath.lineTo(10, 60);
	scalePath.moveTo(0, 70);
	scalePath.lineTo(10, 70);
	scalePath.moveTo(0, 80);
	scalePath.lineTo(10, 80);
	scalePath.moveTo(0, 90);
	scalePath.lineTo(10, 90);
	scalePath.moveTo(0, 100);
	scalePath.lineTo(10, 100);
	scaleLine.setPath(scalePath);
	scaleLine.setPos(0, 16);
	scene.addItem(&scaleLine);
	setScene(&scene);
	indicator.setPolygon(left);
	indicator.setBrush(theBrush);
	setMinimumSize(sizeHint());
	setMaximumSize(sizeHint());
}

@ Once again, the size hint reduces the default size of the widget.

@<IntensityControl implementation@>=
QSize IntensityControl::sizeHint() const
{
	return QSize(25, 160);
}

@ To support a more intuitive numerical representation, higher values should map
to higher positions on the scale. This is contrary to the coordinate system
provided by Qt, so the code setting the position of the indicator on the scale
must account for this.

During testing of this class, I found that it was impossible to select the
values 0 or 10 either through a click or with the increment or decrement
controls. Adding two additional execution branches corrects this issue.

@<IntensityControl implementation@>=
void IntensityControl::setValue(double val)
{
	if(val >= 0 && val <= 10)
	{
		theValue = val;
		if(!valueSet)
		{
			scene.addItem(&indicator);
		}
		valueSet = true;
		indicator.setPos(6, (100 - (val * 10)) + 16);
		emit(valueChanged(val));
	}
	else if(val < 1)
	{
		setValue(0);
	}
	else
	{
		setValue(10);
	}
}

double IntensityControl::value()
{
	return theValue;
}

@ Mouse event handling is similar as well. The mouse press event simply notes
that the button has been pressed.

@<IntensityControl implementation@>=
void IntensityControl::mousePressEvent(QMouseEvent *event)
{
	@<Check that the left button was pressed@>@;
	scaleDown = true;
	event->accept();
}

@ Since there are fewer clickable areas there are fewer regions to check while
handling the mouse release event. Just as the |setValue()| method must
compensate for a mismatch between the scale and the underlying coordinate
system, so must click handling in the scale area take this into consideration
when determining which value the click intends.

@<IntensityControl implementation@>=
void IntensityControl::mouseReleaseEvent(QMouseEvent *event)
{
	@<Check that the left button was pressed@>@;
	if(!scaleDown)
	{
		event->ignore();
		return;
	}
	scaleDown = false;
	QPointF sceneCoordinate = mapToScene(event->x(), event->y());
	if(sceneCoordinate.x() >= 0 && sceneCoordinate.x() <= 16)
	{
		if(sceneCoordinate.y() >= 0 && sceneCoordinate.y() <= 10)
		{
			if(valueSet)
			{
				setValue(theValue + 0.05);
			}
			event->accept();
			return;
		}
		else if(sceneCoordinate.y() >= 122 && sceneCoordinate.y() <= 132)
		{
			if(valueSet)
			{
				setValue(theValue - 0.05);
			}
			event->accept();
			return;
		}
		else if(sceneCoordinate.y() >= 16 && sceneCoordinate.y() <= 116)
		{
			setValue(10 - ((sceneCoordinate.y() - 16) / 10.0));
			event->accept();
			return;
		}
	}
}

@* Scripting the Scale Widgets.

\noindent Scale widgets can be added through the configuration system with
{\tt <hscale>} and {\tt <vscale>} elements. These can be added to layouts.

@<Function prototypes for scripting@>=
void addScaleControlToLayout(QDomElement element,
                             QStack<QWidget *> *widgetStack,
							 QStack<QLayout *> *layoutStack);
void addIntensityControlToLayout(QDomElement element,
                                 QStack<QWidget *> *widgetStack,
								 QStack<QLayout *> *layoutStack);

@ Adding these widgets is done in the same way as adding other widgets.

@<Functions for scripting@>=
void addScaleControlToLayout(QDomElement element, QStack<QWidget *> *,
                             QStack<QLayout *> *layoutStack)
{
	ScaleControl *scale = new ScaleControl;
	if(element.hasAttribute("id"))
	{
		scale->setObjectName(element.attribute("id"));
	}
	QBoxLayout *layout = qobject_cast<QBoxLayout *>(layoutStack->top());
	layout->addWidget(scale);
}

void addIntensityControlToLayout(QDomElement element, QStack<QWidget *> *,
                                 QStack<QLayout *> *layoutStack)
{
	IntensityControl *scale = new IntensityControl;
	if(element.hasAttribute("id"))
	{
		scale->setObjectName(element.attribute("id"));
	}
	QBoxLayout *layout = qobject_cast<QBoxLayout *>(layoutStack->top());
	layout->addWidget(scale);
}



@** Device Configuration.

\noindent Starting in \pn{} 1.4, all supported measurement hardware is
available from the same build and it is possible to use multiple devices from
differernt vendors at the same time. In previous versions, there were very few
available hardware configurations and a small number of example configuration
documents covered the needs of most people using the software. As more hardware
is supported and more people with distinct needs start using \pn{}, that
approach becomes unsustainable and the need for in-program configuration
becomes increasingly pronounced.

Device configuration is coupled to configuration of the logging window and
it is possible to configure multiple different roasters with different hardware
and other customizations of the logging window specific to a particular
machine.

The core of this is the use of an XML document saved with |QSettings| under
the |"DeviceConfiguration"| key. Within the root {\tt <DeviceConfiguration>}
element there are two grouping elements: {\tt <devices>} and
{\tt <references>}. The terminology was developed at a time when it was
thought that hardware configuration and logging view configuration would be
decoupled from each other, however the benefits of combining these far
outweighed the minor loss of flexibility with this approach.

Within the {\tt <devices>} tag there are arbitrarily many {\tt <node>} tags
which themselves may contain {\tt <node>} tags nested to any depth. Each of
these has two attributes, a {\tt name} attribute which specifies the display
text used to represent that node and a {\tt reference} attribute with a
unique value. Typica will generate a UUID for each node to use as the unique
value but this is not strictly required. The {\tt name} attribute does not
need to be unique and will generally be supplied by the person using the
software. The top level {\tt node} elements represent a coffee roaster and
the sub-elements can represent hardware, annotation controls, and possibly
other configurable features.

Within the {\tt <references>} tag there are as many {\tt <reference>} tags as
there are {\tt <node>} tags. Each of these has an {\tt id} attribute which
matches the {\tt reference} attribute in a {\tt <node>} tag and a {\tt driver}
attribute which is used to determine which class should be used to interact
with these settings. In the case of device configuration, this allows a
determination of which class should be used to generate an editor for settings
related to that node. Within each {\tt <reference>} tag is an arbitrary number
of {\tt <attribute>} tags with {\tt name} and {\tt value} attributes. Code for
providing the settings widgets and device interfaces can use these for any
desired purpose, but it is common to have one {\tt <attribute>} tag per setting
appropriate for a given node and possibly more to identify the concept a
particular node represents.

The global |Application| object is extended to maintain a |QDomDocument|
representation of this XML document.

@<Application private data members@>=
QDomDocument deviceConfigurationDocument;

@ Two methods are also provided for interacting with this document. The
|deviceConfiguration()| method returns a pointer to the private data member,
loading the XML from |QSettings| if required and creating a new document with
no {\tt <node>} tags if the document does not exist in settings. The
|saveDeviceConfiguration()| method serializes the |QDomDocument| to settings.

@<Device configuration members@>=
QDomDocument deviceConfiguration();

@ The method for saving should be a slot so a model representing this data
can persist changes through the signals and slots mechanism rather than
requiring the calls to be explicitn.

@<Extended Application slots@>=
void saveDeviceConfiguration();

@ Serializing the current configuration is trivial.

@<Application Implementation@>=
void Application::saveDeviceConfiguration()
{
	QSettings settings;
	settings.setValue("DeviceConfiguration",
	                  QVariant(deviceConfigurationDocument.toByteArray()));
}

@ Producing a pointer to a loaded configuration only slightly more complicated.
If the configuration has been previously loaded we just return the pointer.
Otherwise, we attempt to load the document.

@<Application Implementation@>=
QDomDocument Application::deviceConfiguration()
{
	if(deviceConfigurationDocument.isNull())
	{
		@<Load device configuration document from settings@>@;
	}
	return deviceConfigurationDocument;
}

@ In most cases a document will already exist in settings, but we must verify
this and create a new document if it does not exist. We also clear device
configuration settings if the configuration document is invalid.

@<Load device configuration document from settings@>=
QSettings settings;
QByteArray document = settings.value("DeviceConfiguration").toByteArray();
QString etext;
int eline;
int ecol;
if(document.length() == 0)
{
	qDebug() << "Loaded settings length is 0. Creating new configuration.";
	@<Create device configuration document@>@;
}
else
{
	if(!deviceConfigurationDocument.setContent(document, false,
	                                           &etext, &eline, &ecol))
	{
		@<Report configuration loading error@>@;
		@<Create device configuration document@>@;
	}
}

@ Rather than generate the empty device configuration programmatically, we keep
an empty device configuration document as a resource.

@<Create device configuration document@>=
QFile emptyDocument(":/resources/xml/EmptyDeviceConfiguration.xml");
emptyDocument.open(QIODevice::ReadOnly);
if(!deviceConfigurationDocument.setContent(&emptyDocument, false,
                                           &etext, &eline, &ecol))
{
	@<Report configuration loading error@>@;
}
else
{
	saveDeviceConfiguration();
}

@ There isn't really anything that can be done if the device configuration data
is corrupt, but an error message can be produced if the program happens to have
access to a debugging console.

@<Report configuration loading error@>=
qDebug() << QString(tr("An error occurred loading device configuration."));
qDebug() << QString(tr("Line %1, Column %2")).arg(eline).arg(ecol);
qDebug() << etext;

@* Model and view for device configuration hierarchy.

\noindent When manipulating device configuration data, it can be useful to
present the device hierarchy in a tree view. To do this, we use two classes to
produce a tree model. This is slightly extended and modified from an example
in the Qt documentation.\nfnote{Simple DOM Model Example:\par\indent\pdfURL{%
http://doc.qt.nokia.com/4.7-snapshot/itemviews-simpledommodel.html}
{http://doc.qt.nokia.com/4.7-snapshot/itemviews-simpledommodel.html}}

Our model uses the |DeviceTreeModelNode| class to cache the |QDomNode|
instances with the data we want.

@<Class declarations@>=
class DeviceTreeModelNode
{
	public:
		DeviceTreeModelNode(QDomNode &node, int row,
		                    DeviceTreeModelNode *parent = NULL);
		~DeviceTreeModelNode();
		DeviceTreeModelNode *child(int index);
		DeviceTreeModelNode *parent();
		QDomNode node() const;
		int row();
	private:
		QDomNode domNode;
		QHash<int, DeviceTreeModelNode*> children;
		int rowNumber;
		DeviceTreeModelNode *parentItem;
};

@ Implementation of this helper class is trivial.

@<DeviceTreeModelNode implementation@>=
DeviceTreeModelNode::DeviceTreeModelNode(QDomNode &node, int row,
                                         DeviceTreeModelNode *parent)
	: domNode(node), rowNumber(row), parentItem(parent)
{
	/* Nothing needs to be done here. */
}

DeviceTreeModelNode::~DeviceTreeModelNode()
{
	QHash<int, DeviceTreeModelNode *>::iterator@, i;
	for(i = children.begin(); i != children.end(); i++)
	{
		delete i.value();
	}
}

DeviceTreeModelNode *DeviceTreeModelNode::parent()
{
	return parentItem;
}

int DeviceTreeModelNode::row()
{
	return rowNumber;
}

QDomNode DeviceTreeModelNode::node() const
{
	return domNode;
}

DeviceTreeModelNode *DeviceTreeModelNode::child(int index)
{
	if(children.contains(index))
	{
		return children[index];
	}
	if(index >= 0 && index < domNode.childNodes().count())
	{
		QDomNode childNode = domNode.childNodes().item(index);
		DeviceTreeModelNode *childItem = new DeviceTreeModelNode(childNode,
		                                                         index, this);
		children[index] = childItem;
		return childItem;
	}
	return NULL;
}

@ The model class provides a single column representation of the {\tt devices}
section of the device configuration document. It provides methods for editing
the name of any node, for adding new nodes to the model, for deleting any node
in the model, and for obtaining the {\tt reference} element corresponding to
a given node.

@<Class declarations@>=
class DeviceTreeModel : public QAbstractItemModel@/
{@/
	@[Q_OBJECT@]@;
	public:@/
		DeviceTreeModel(QObject *parent = NULL);
		~DeviceTreeModel();
		QVariant data(const QModelIndex &index, int role) const;
		Qt::ItemFlags flags(const QModelIndex &index) const;
		QVariant headerData(int section, Qt::Orientation orientation,
		                    int role = Qt::DisplayRole) const;
		QModelIndex index(int row, int column,
		                  const QModelIndex &parent = QModelIndex()) const;
		QModelIndex parent(const QModelIndex &child) const;
		int rowCount(const QModelIndex &parent = QModelIndex()) const;
		int columnCount(const QModelIndex &parent = QModelIndex()) const;
		bool setData(const QModelIndex &index, const QVariant &value,
		             int role);
		bool removeRows(int row, int count, const QModelIndex &parent);
		QDomElement referenceElement(const QString &id);
	@[public slots@]:@/
		void newNode(const QString &name, const QString &driver,
		             const QModelIndex &parent);
	private:@/
		QDomDocument document;
		DeviceTreeModelNode *root;
		QDomNode referenceSection;
		QDomNode treeRoot;
};

@ In the constructor we locate the {\tt devices} and {\tt references} sections
of the passed in document. Our tree of cached |QDomNode| elements starts with
the former and is expanded as needed.

@<DeviceTreeModel implementation@>=
DeviceTreeModel::DeviceTreeModel(QObject *parent)
	: QAbstractItemModel(parent)
{
	document = AppInstance->deviceConfiguration();
	QDomNodeList elements = document.elementsByTagName("devices");
	if(elements.size() != 1)
	{
		qDebug() << "Unexpected result when loading device map.";
	}
	treeRoot = elements.at(0);
	root = new DeviceTreeModelNode(treeRoot, 0);
	elements = document.elementsByTagName("references");
	if(elements.size() != 1)
	{
		qDebug() << "No references section. Creating.";
		referenceSection = document.createElement("references");
		document.appendChild(referenceSection);
	}
	else
	{
		referenceSection = elements.at(0);
	}
	connect(this, SIGNAL(dataChanged(QModelIndex, QModelIndex)),
	        AppInstance, SLOT(saveDeviceConfiguration()));
	connect(this, SIGNAL(modelReset()),
	        AppInstance, SLOT(saveDeviceConfiguration()));
	connect(this, SIGNAL(rowsInserted(QModelIndex, int, int)),
	        AppInstance, SLOT(saveDeviceConfiguration()));
}

@ We only provide a single column for our model, so |columnCount()| can simply
return a constant. The |rowCount()| method can return a variety of values
depending on the parent node.

@<DeviceTreeModel implementation@>=
int DeviceTreeModel::columnCount(const QModelIndex &) const
{
	return 1;
}

int DeviceTreeModel::rowCount(const QModelIndex &parent) const
{
	if(parent.column() > 0)
	{
		return 0;
	}
	@<Get parent item from index@>@;
	return parentItem->node().childNodes().count();
}

@ If an invalid index is passed as the parent index, we assume the parent to
be the root element.

@<Get parent item from index@>=
DeviceTreeModelNode *parentItem;
if(!parent.isValid())
{
	parentItem = root;
}
else
{
	parentItem = static_cast<DeviceTreeModelNode *>(parent.internalPointer());
}

@ As seen in |rowCount()|, we keep a pointer to the cached node in our model
indices.

@<DeviceTreeModel implementation@>=
QModelIndex DeviceTreeModel::index(int row, int column,
                                   const QModelIndex &parent) const
{
	if(!hasIndex(row, column, parent))
	{
		return QModelIndex();
	}
	@<Get parent item from index@>@;
	DeviceTreeModelNode *childItem = parentItem->child(row);
	if(childItem)
	{
		return createIndex(row, column, childItem);
	}
	return QModelIndex();
}

@ We can also request an index for the parent of a given index.

@<DeviceTreeModel implementation@>=
QModelIndex DeviceTreeModel::parent(const QModelIndex &child) const
{
	if(!child.isValid())
	{
		return QModelIndex();
	}
	DeviceTreeModelNode *childItem =
		static_cast<DeviceTreeModelNode *>(child.internalPointer());
	DeviceTreeModelNode *parentItem = childItem->parent();
	if(!parentItem || parentItem == root)
	{
		return QModelIndex();
	}
	return createIndex(parentItem->row(), 0, parentItem);
}

@ All items should be enabled, selectable, and editable.

@<DeviceTreeModel implementation@>=
Qt::ItemFlags DeviceTreeModel::flags(const QModelIndex &index) const
{
	if(!index.isValid())
	{
		return 0;
	}
	return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

@ Each node in the model maintains two pieces of information. One is the
display value for the node which is held in the {\tt name} attribute of the
corresponding XML element. The other is a reference ID held in the
{\tt reference} attribute.

@<DeviceTreeModel implementation@>=
QVariant DeviceTreeModel::data(const QModelIndex &index, int role) const
{
	if(!index.isValid())
	{
		return QVariant();
	}
	if(role != Qt::DisplayRole && role != Qt::UserRole && role != Qt::EditRole)
	{
		return QVariant();
	}
	DeviceTreeModelNode *item =
		static_cast<DeviceTreeModelNode *>(index.internalPointer());
	QDomNode node = item->node();
	QDomElement element = node.toElement();
	switch(role)
	{
		case Qt::DisplayRole:@/
		case Qt::EditRole:@/
			return QVariant(element.attribute("name"));
		case Qt::UserRole:@/
			return QVariant(element.attribute("reference"));
		default:@/
			return QVariant();
	}
	return QVariant();
}

@ The reference value is managed by the model and should never be changed. The
display value for a node is, however, editable. These changes must propagate
back to the XML document underlying the model.

@<DeviceTreeModel implementation@>=
bool DeviceTreeModel::setData(const QModelIndex &index,
                              const QVariant &value, int)@;@/
{@t\1@>@/
	if(!index.isValid())@/
	{@t\1@>@/
		return false;@t\2@>@/
	}@/
	DeviceTreeModelNode *item =
		static_cast<DeviceTreeModelNode *>(index.internalPointer());
	QDomNode node = item->node();
	QDomElement element = node.toElement();
	element.setAttribute("name", value.toString());
	emit dataChanged(index, index);@;
	return true;@t\2@>@/
}

@ A custom method is provided for adding new nodes to the model. This generates
the two XML elements needed for the node. The |name| parameter is the display
name of the new node, the |driver| parameter is used as the value for the
{\tt driver} attribute in the {\tt reference} element which will be used to
determine what classes are used to work with that data.

@<DeviceTreeModel implementation@>=
void DeviceTreeModel::newNode(const QString &name, const QString &driver,
                              const QModelIndex &parent)
{
	QString referenceID = QUuid::createUuid().toString();
	@<Get parent item from index@>@;
	QDomNode parentNode = parentItem->node();
	int newRowNumber = rowCount(parent);
	beginInsertRows(parent, newRowNumber, newRowNumber);
	QDomElement deviceElement = document.createElement("node");
	deviceElement.setAttribute("name", name);
	deviceElement.setAttribute("reference", referenceID);
	parentNode.appendChild(deviceElement);
	QDomElement referenceElement = document.createElement("reference");
	referenceElement.setAttribute("id", referenceID);
	referenceElement.setAttribute("driver", driver);
	referenceSection.appendChild(referenceElement);
	endInsertRows();
}

@ We can also delete nodes. When deleting a node, both XML elements are
removed and our node cache is invalidated.

@<DeviceTreeModel implementation@>=
bool DeviceTreeModel::removeRows(int row, int count, const QModelIndex &parent)@t\2\2@>@/
{@t\1@>@/
	@<Get parent item from index@>@;
	QDomNode parentNode = parentItem->node();
	QDomNodeList childNodes = parentNode.childNodes();@;
	if(childNodes.size() < row + count)@/
	{@t\1@>@/
		return false;@t\2@>@/
	}@/
	beginRemoveRows(parent, row, row + count - 1);
	QList<QDomElement> removalList;
	for(int i = row; i < row + count; i++)
	{
		removalList.append(childNodes.at(i).toElement());
	}
	QDomElement element;
	QDomElement reference;
	for(int i = 0; i < count; i++)
	{
		element = removalList.at(i);
		if(element.hasAttribute("reference"))
		{
			reference = referenceElement(element.attribute("reference"));
			if(!reference.isNull())
			{
				referenceSection.removeChild(reference);
			}
		}
		parentNode.removeChild(element);
	}
	endRemoveRows();
	beginResetModel();
	delete root;
	root = new DeviceTreeModelNode(treeRoot, 0);
	endResetModel();@;
	return true;@t\2@>@/
}

@ Another custom method obtains the {\tt reference} element for a given
reference ID.

@<DeviceTreeModel implementation@>=
QDomElement DeviceTreeModel::referenceElement(const QString &id)
{
	QDomNodeList childNodes = referenceSection.childNodes();
	QDomElement element;
	for(int i = 0; i < childNodes.size(); i++)
	{
		element = childNodes.at(i).toElement();
		if(element.hasAttribute("id"))
		{
			if(element.attribute("id") == id)
			{
				return element;
			}
		}
	}
	return QDomElement();
}

@ We don't want any headers, so |headerData()| is very simple.

@<DeviceTreeModel implementation@>=
QVariant DeviceTreeModel::headerData(int, Qt::Orientation, int) const
{
	return QVariant();
}

@ The destructor destroys the node cache. The destructor for the top level node
will recursively destroy all child nodes.

@<DeviceTreeModel implementation@>=
DeviceTreeModel::~DeviceTreeModel()
{
	delete root;
}

@ Exposing this class to the host environment allows a number of interesting
possibilities. Setting the model to a combo box, for example, allows the
selection of top level nodes representing a particular coffee roaster. It is
also useful to have the ability to traverse a specified sub-tree of the model
to set up a logging view that matches the configuration for such a selected
roaster.

@<Function prototypes for scripting@>=
QScriptValue constructDeviceTreeModel(QScriptContext *context,
                                      QScriptEngine *engine);
void setDeviceTreeModelProperties(QScriptValue value, QScriptEngine *engine);
void setQAbstractItemModelProperties(QScriptValue value, QScriptEngine *engine);
QScriptValue DeviceTreeModel_referenceElement(QScriptContext *context,
                                              QScriptEngine *engine);
QScriptValue QAbstractItemModel_data(QScriptContext *context, QScriptEngine *engine);
QScriptValue QAbstractItemModel_index(QScriptContext *context, QScriptEngine *engine);
QScriptValue QAbstractItemModel_rowCount(QScriptContext *context, QScriptEngine *engine);
QScriptValue QAbstractItemModel_hasChildren(QScriptContext *context, QScriptEngine *engine);

@ The constructor is trivial.

@<Functions for scripting@>=
QScriptValue constructDeviceTreeModel(QScriptContext *, QScriptEngine *engine)
{
	QScriptValue object = engine->newQObject(new DeviceTreeModel);
	setDeviceTreeModelProperties(object, engine);
	return object;
}

@ As usual the host environment is informed of this constructor.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructDeviceTreeModel);
value = engine->newQMetaObject(&DeviceTreeModel::staticMetaObject,
                               constructor);
engine->globalObject().setProperty("DeviceTreeModel", value);

@ A number of properties are set to allow script code to traverse the model.
Most of these properties are properly members of |QAbstractItemModel| and
the code is written to allow any models that may be exposed to the host
environment in the future to make use of these as well. Note that this is not
a full set of functionality but only what I needed to implement a particular
feature set.

@<Functions for scripting@>=
void setDeviceTreeModelProperties(QScriptValue value, QScriptEngine *engine)
{
	setQAbstractItemModelProperties(value, engine);
	value.setProperty("referenceElement",
	                  engine->newFunction(DeviceTreeModel_referenceElement));
}

void setQAbstractItemModelProperties(QScriptValue value, QScriptEngine *engine)
{
	setQObjectProperties(value, engine);
	value.setProperty("data", engine->newFunction(QAbstractItemModel_data));
	value.setProperty("index", engine->newFunction(QAbstractItemModel_index));
	value.setProperty("rowCount", engine->newFunction(QAbstractItemModel_rowCount));
	value.setProperty("hasChildren", engine->newFunction(QAbstractItemModel_hasChildren));
}

@ The wrapped call to |referenceElement| does a little more than might be
expected. Rather than returning a |QDomElement| and leaving it up to script
code to traverse the sub-tree, we create a |QVariantMap| which in script code
is translated as an object with the keys as properties of the object containing
the values of those keys. This is populated by first specifying a {\tt driver}
key with its value from the {\tt driver} attribute of the {\tt reference} node.
We then examine the {\tt <attribute>} sub-elements and use the {\tt name}
attribute as keys and the {\tt value} attribute as values to fill out the rest
of the map.

@<Functions for scripting@>=
QScriptValue DeviceTreeModel_referenceElement(QScriptContext *context,
                                              QScriptEngine *engine)
{
	DeviceTreeModel *model = getself<DeviceTreeModel *>(context);
	QDomElement referenceElement = model->referenceElement(argument<QString>(0, context));
	QDomNodeList configData = referenceElement.elementsByTagName("attribute");
	QDomElement node;
	QVariantMap retval;
	retval.insert("driver", referenceElement.attribute("driver"));
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		retval.insert(node.attribute("name"), node.attribute("value"));
	}
	return engine->toScriptValue(retval);
}

QScriptValue QAbstractItemModel_data(QScriptContext *context, QScriptEngine *engine)
{
	QAbstractItemModel *model = getself<QAbstractItemModel *>(context);
	QModelIndex index = argument<QModelIndex>(0, context);
	int role = argument<int>(1, context);
	return engine->toScriptValue(model->data(index, role));
}

QScriptValue QAbstractItemModel_index(QScriptContext *context, QScriptEngine *engine)
{
	QAbstractItemModel *model = getself<QAbstractItemModel *>(context);
	int row = 0;
	int column = 0;
	QModelIndex index;
	if(context->argumentCount() > 1)
	{
		row = argument<int>(0, context);
		column = argument<int>(1, context);
	}
	if(context->argumentCount() > 2)
	{
		index = argument<QModelIndex>(2, context);
	}
	QModelIndex retval = model->index(row, column, index);
	return engine->toScriptValue(retval);
}

QScriptValue QAbstractItemModel_rowCount(QScriptContext *context,
                                         QScriptEngine *)
{
	QAbstractItemModel *model = getself<QAbstractItemModel *>(context);
	QModelIndex index;
	if(context->argumentCount() == 1)
	{
		index = argument<QModelIndex>(0, context);
	}
	return QScriptValue(model->rowCount(index));
}

QScriptValue QAbstractItemModel_hasChildren(QScriptContext *context,
                                            QScriptEngine *engine)
{
	QAbstractItemModel *model = getself<QAbstractItemModel *>(context);
	QModelIndex index;
	if(context->argumentCount() == 1)
	{
		index = argument<QModelIndex>(0, context);
	}
	return QScriptValue(engine, model->hasChildren(index));
}

@ Some additional work is needed to handle |QModelIndex| appropriately. First
we declare |QModelIndex| as a metatype.

@<Class declarations@>=
Q_DECLARE_METATYPE(QModelIndex)

@ Next we need a pair of functions to convert |QModelIndex| to and from script
values.

@<Function prototypes for scripting@>=
QScriptValue QModelIndex_toScriptValue(QScriptEngine *engine, const QModelIndex &index);
void QModelIndex_fromScriptValue(const QScriptValue &value, QModelIndex &index);

@ These are implemented thusly.

@<Functions for scripting@>=
QScriptValue QModelIndex_toScriptValue(QScriptEngine *engine, const QModelIndex &index)
{
	QVariant var;
	var.setValue(index);
	QScriptValue object = engine->newVariant(var);
	return object;
}

void QModelIndex_fromScriptValue(const QScriptValue &value, QModelIndex &index)
{
	index = value.toVariant().value<QModelIndex>();
}

@ Finally we register this with the engine.

@<Set up the scripting engine@>=
qScriptRegisterMetaType(engine, QModelIndex_toScriptValue, QModelIndex_fromScriptValue);

@* Device Configuration Widgets.

\noindent Each node in the {\tt devices} section of the |DeviceTreeModel| is
associated with a {\tt reference} element that provides a driver string which
can be used to identify the classes used to interact with the device
configuration data. An example of this is selecting which widget to use when
selecting a node in a configuration window. These widgets must be registered
to the appropriate driver string in advance. This is currently handled through
the |Application| instance, though it would probably be better to split this
into its own class at some point in the future.

@<Application private data members@>=
QHash<QString, QMetaObject> deviceConfigurationWidgets;

@ Two methods register widgets and retrieve an instance of the appropriate
widget for a given node in the device configuration model.

@<Device configuration members@>=
void registerDeviceConfigurationWidget(QString driver, QMetaObject widget);
QWidget* deviceConfigurationWidget(DeviceTreeModel *model,
                                   const QModelIndex &index);

@ Registration is a simple wrapper around the underlying |QHash|.

@<Application Implementation@>=
void Application::registerDeviceConfigurationWidget(QString driver,
                                                     QMetaObject widget)
{
	deviceConfigurationWidgets.insert(driver, widget);
}

@ Obtaining the configuration widget for a given node involves looking up the
reference element, extracting the driver string, looking up the associated
meta-object, and returning a new instance of that object.

As there is no concept of an invalid |QMetaObject| we default to the static
meta-object for a |QWidget| if a widget for the specified driver string is not
registered and check for this prior to creating a new instance of the
configuration widget.

@<Application Implementation@>=
QWidget* Application::deviceConfigurationWidget(DeviceTreeModel *model,
                                                const QModelIndex &index)
{
	QVariant nodeReference = index.data(Qt::UserRole);
	QDomElement referenceElement = model->referenceElement(
		model->data(index, Qt::UserRole).toString());
	QMetaObject metaObject =
		deviceConfigurationWidgets.value(referenceElement.attribute("driver"),
		                                 QWidget::staticMetaObject);
	QWidget *editor;
	if(metaObject.className() == QWidget::staticMetaObject.className())
	{
		editor = NULL;
	}
	else
	{
		editor = qobject_cast<QWidget *>(
					metaObject.newInstance(Q_ARG(DeviceTreeModel *, model),
									       Q_ARG(QModelIndex, index)));
	}
	return editor;
}

@ Every node type should have an associated editor and the editors for nodes
which can have child nodes should be able to handle creating these child nodes.
This leaves the problem of creating the top level nodes. For this we must have
a way to register three key pieces of information: the text which should appear
for selecting a new top level node to add to the configuration, the default
name for a node of that type, and the registered driver string associated with
that node type. The most likely use for this information is in constructing a
menu. |QAction| seems like a good fit, but this cannot pass all of the
required information. Part of the chosen solution is a |QAction| subclass
which takes all three pieces of information and provides a new signal to
supply the information needed to add a new top level node.

@<Class declarations@>=
class NodeInserter : public QAction@/
{@/
	@[Q_OBJECT@]@;
	public:@/
		NodeInserter(const QString &title, const QString &name,
		             const QString &driver, QObject *parent = NULL);
	signals:@/
		void triggered(QString name, QString driver);
	@[private slots@]:@/
		void onTriggered();
	private:@/
		QString defaultNodeName;
		QString driverString;
};

@ The constructor saves the information that will later be emitted and connects
the |triggered()| signal from |QAction| to a private slot which emits our new
|triggered()| signal.

@<NodeInserter implementation@>=
NodeInserter::NodeInserter(const QString &title, const QString &name,
                           const QString &driver, QObject *parent) :
	QAction(title, parent), defaultNodeName(name), driverString(driver)
{
	connect(this, SIGNAL(triggered()), this, SLOT(onTriggered()));
}

void NodeInserter::onTriggered()
{
	emit triggered(defaultNodeName, driverString);
}

@ An interface for adding top level nodes to the device configuration needs to
be able to access a list of these actions so we make this available through the
|Application| instance. Once again, it would be better to split device
configuration registration data to a separate class and there should be
accessors around this.

Note that this terminology was introduced when it was assumed that device
configuration and logging view configuration would be separate. It is likely
that a future code cleanup will remove this in favor of handling the top level
of the device configuration hierarchy (under roaster specification) in the same
way that sub-nodes are handled.

@<Device configuration members@>=
QList<NodeInserter *> topLevelNodeInserters;

@ With this done, we can now produce a window which allows someone to easily
edit the device configuration.

As of version 1.6 this class is no longer a window but just a |QWidget| which
is inserted into another more general settings window. The name of the class
should be changed in a future version to reflect this change.

@<Class declarations@>=
class DeviceConfigurationWindow : public QWidget
{
	@[Q_OBJECT@]@;
	public:@/
		DeviceConfigurationWindow();
	@[public slots@]:@/
		void addDevice();
		void removeNode();
		void newSelection(const QModelIndex &index);
	@[private slots@]:@/
		void resizeColumn();
	private:@/
		QDomDocument document;
		DeviceTreeModel *model;
		QTreeView *view;
		QScrollArea *configArea;
};

@ This window consists of two main panels separated by a splitter. The left
panel presents a tree view of the current device configuration and a set of
controls that allows someone to either add a new top level node to the
configuration or delete any node in the configuration along with all of its
child nodes.

The right panel provides a |QScrollArea|. When a node is selected from the tree
view, the appropriate configuration widget will be inserted into that area.

When a configuration widget adds a new node to the device model, the parent
node (which should be the currently selected node but the code does not assume
this) is expanded to show the new child node if it has not already been
expanded.

@<DeviceConfigurationWindow implementation@>=
DeviceConfigurationWindow::DeviceConfigurationWindow() : QWidget(NULL),
	view(new QTreeView), configArea(new QScrollArea)
{
	QSplitter *splitter = new QSplitter;
	QWidget *leftWidget = new QWidget;
	leftWidget->setMinimumWidth(200);
	QVBoxLayout *left = new QVBoxLayout;
	view->setAnimated(true);
	view->setSelectionMode(QAbstractItemView::SingleSelection);
	document = AppInstance->deviceConfiguration();
	model = new DeviceTreeModel;
	view->setModel(model);
	view->setTextElideMode(Qt::ElideNone);
	view->expandAll();
	view->resizeColumnToContents(0);
	connect(model, SIGNAL(modelReset()), view, SLOT(expandAll()));
	QHBoxLayout *treeButtons = new QHBoxLayout;
	QToolButton *addDeviceButton = new QToolButton;
	addDeviceButton->setIcon(QIcon::fromTheme("list-add"));
	addDeviceButton->setToolTip(tr("New Roaster"));
	connect(addDeviceButton, SIGNAL(clicked()),
	        this, SLOT(addDevice()));
	QToolButton *removeNodeButton = new QToolButton;
	removeNodeButton->setIcon(QIcon::fromTheme("list-remove"));
	removeNodeButton->setToolTip(tr("Delete Selection"));
	connect(removeNodeButton, SIGNAL(clicked()), this, SLOT(removeNode()));
	treeButtons->addWidget(addDeviceButton);
	treeButtons->addWidget(removeNodeButton);
	left->addWidget(view);
	left->addLayout(treeButtons);
	leftWidget->setLayout(left);
	splitter->addWidget(leftWidget);
	configArea->setMinimumWidth(580);
	configArea->setMinimumHeight(460);
	splitter->addWidget(configArea);
	QVBoxLayout *centralLayout = new QVBoxLayout;
	centralLayout->addWidget(splitter);
	setLayout(centralLayout);
	connect(view, SIGNAL(activated(QModelIndex)),
	        this, SLOT(newSelection(QModelIndex)));
	connect(view, SIGNAL(clicked(QModelIndex)),
	        this, SLOT(newSelection(QModelIndex)));
	connect(model, SIGNAL(rowsInserted(QModelIndex, int, int)),
	        view, SLOT(expand(QModelIndex)));
	connect(model, SIGNAL(rowsInserted(QModelIndex, int, int)),
	        this, SLOT(resizeColumn()));
	connect(model, SIGNAL(rowsRemoved(QModelIndex, int, int)),
	        this, SLOT(resizeColumn()));
}

@ Adding a new top level node to the model is just a matter of extracting the
required information from the signal requesting that addition.

@<DeviceConfigurationWindow implementation@>=
void DeviceConfigurationWindow::addDevice()
{
	model->newNode(tr("New Roaster"), "roaster", QModelIndex());
}

@ Removing the currently selected node is also simple.

@<DeviceConfigurationWindow implementation@>=
void DeviceConfigurationWindow::removeNode()
{
	QModelIndex index = view->currentIndex();
	if(index.isValid())
	{
		int row = index.row();
		QModelIndex parent = index.parent();
		model->removeRow(row, parent);
	}
}

@ Due to most of the required logic being implemented in
|Application::deviceConfigurationWidget()|, inserting the proper editor in the
right area is also trivial.

@<DeviceConfigurationWindow implementation@>=
void DeviceConfigurationWindow::newSelection(const QModelIndex &index)
{
	QWidget *editor = AppInstance->deviceConfigurationWidget(model, index);
	if(editor)
	{
		configArea->setWidget(editor);
		editor->show();
	}
}

@ As nodes are added deeper in the device hierarchy or as nodes obtain longer
names, the nodes names may be elided by default rather than indicate that the
view can be scrolled horizontally. There has been feedback that this behavior
is not preferred so instead as the model data changes we expand the column
instead.

@<DeviceConfigurationWindow implementation@>=
void DeviceConfigurationWindow::resizeColumn()
{
	view->resizeColumnToContents(0);
}

@ At least for the initial testing of this feature it will be useful if we can
instantiate this from the host environment. For this we at least require a
constructor.

Now that this widget is available through a more general settings window it may
be better to remove direct access to this class from the host environment.

@<Function prototypes for scripting@>=
QScriptValue constructDeviceConfigurationWindow(QScriptContext *context,
                                                QScriptEngine *engine);

@ The constructor is trivial.

@<Functions for scripting@>=
QScriptValue constructDeviceConfigurationWindow(QScriptContext *,
                                                QScriptEngine *engine)
{
	QScriptValue object = engine->newQObject(new DeviceConfigurationWindow);
	return object;
}

@ Finally we inform the host environment of this constructor.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructDeviceConfigurationWindow);
value = engine->newQMetaObject(&DeviceConfigurationWindow::staticMetaObject,
                               constructor);
engine->globalObject().setProperty("DeviceConfigurationWindow", value);

@* A Common Base Class for Device Configuration Widgets.

\noindent There are certain operations that are very commonly required
among device configuration widgets. These common elements have been implemented
in a base class.

@<Class declarations@>=
class BasicDeviceConfigurationWidget : public QWidget
{
	@[Q_OBJECT@]@;
	public:@/
		BasicDeviceConfigurationWidget(DeviceTreeModel *model,
		                               const QModelIndex &index);
	@[public slots@]:@/
		void insertChildNode(const QString &name, const QString &driver);
		void updateAttribute(const QString &name, const QString &value);
	protected:@/
		DeviceTreeModel *deviceModel;
		QModelIndex currentNode;
};

@ The constructor just passes its arguments to a pair of protected data
members. These are commonly required in subclasses but need not be exposed
outside of this branch of the object hierarchy.

@<BasicDeviceConfigurationWidget implementation@>=
BasicDeviceConfigurationWidget::BasicDeviceConfigurationWidget(
	DeviceTreeModel *model, const QModelIndex &index)
	: QWidget(NULL), deviceModel(model), currentNode(index)
{
	/* Nothing needs to be done here. */
}

@ The |updateAttribute()| method sets the value property of an attribute
element of a given name that is a child of the current node, creating the
element if it does not exist.

@<BasicDeviceConfigurationWidget implementation@>=
void BasicDeviceConfigurationWidget::updateAttribute(const QString &name,
                                                     const QString &value)
{
	QDomElement referenceElement = deviceModel->referenceElement(
		deviceModel->data(currentNode, Qt::UserRole).toString());
	QDomNodeList configData = referenceElement.elementsByTagName("attribute");
	QDomElement node;
	bool found = false;
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		if(node.attribute("name") == name)
		{
			node.setAttribute("value", value);
			found = true;
			break;
		}
	}
	if(!found)
	{
		node = AppInstance->deviceConfiguration().createElement("attribute");
		node.setAttribute("name", name);
		node.setAttribute("value", value);
		referenceElement.appendChild(node);
	}
	AppInstance->saveDeviceConfiguration();
}

@ The |insertChildNode()| method constructs a new node with the specified name
and driver as a child of the current node. Node insertion is a generic
operation that does not require any knowledge of the configuration options that
will be presented in that node.

@<BasicDeviceConfigurationWidget implementation@>=
void BasicDeviceConfigurationWidget::insertChildNode(const QString &name,
                                                     const QString &driver)
{
	deviceModel->newNode(name, driver, currentNode);
}

@** Configuration of Top Level Roaster Nodes.

\noindent The first configuration widget required is one for defining a coffee
roaster. This stores the identification number that will be used for machine
references in the database and also provides controls for adding all of the
required child nodes for hardware and configurable elements of the logging
window that may vary from one machine to the next.

All of the configuration widgets follow a similar pattern. One important detail
to note is that these configuration widgets are instantiated through Qt'@q'@>s
meta-object system. All of these constructors take a |DeviceTreeModel *| and a
|QModelIndex &| as arguments and they are marked as |Q_INVOKABLE|.

@<Class declarations@>=
class RoasterConfWidget : public BasicDeviceConfigurationWidget
{
	@[Q_OBJECT@]@;
	public:@/
		@[Q_INVOKABLE@]@, RoasterConfWidget(DeviceTreeModel *model,
		                                    const QModelIndex &index);
	@[private slots@]:@/
		void updateRoasterId(int id);
};

@ Aside from the ID number used to identify the roaster in the database we also
need controls to add child nodes. In order to limit the number of options in
menus for adding child nodes, these are organized into groups that are
available through different controls.

@<RoasterConfWidget implementation@>=
RoasterConfWidget::RoasterConfWidget(DeviceTreeModel *model, const QModelIndex &index)
: BasicDeviceConfigurationWidget(model, index)
{
	QVBoxLayout *layout = new QVBoxLayout;
	QPushButton *addDeviceButton = new QPushButton(tr("Add Device"));
	QMenu *deviceMenu = new QMenu;
	NodeInserter *insertAction;
	foreach(insertAction, AppInstance->topLevelNodeInserters)
	{
		connect(insertAction, SIGNAL(triggered(QString, QString)),
		        this, SLOT(insertChildNode(QString, QString)));
		deviceMenu->addAction(insertAction);
	}
	addDeviceButton->setMenu(deviceMenu);
	layout->addWidget(addDeviceButton);
	QPushButton *addAnnotationControlButton = new QPushButton(tr("Add Annotation Control"));
	QMenu *annotationMenu = new QMenu;
	NodeInserter *basicButtonInserter = new NodeInserter(tr("Annotation Button"), tr("Annotation Button"), "annotationbutton");
	NodeInserter *countingButtonInserter = new NodeInserter(tr("Counting Button"), tr("Counting Button"), "reconfigurablebutton");
	NodeInserter *spinBoxInserter = new NodeInserter(tr("Numeric Entry"), tr("Numeric Entry"), "annotationspinbox");
	NodeInserter *freeAnnotationInserter = new NodeInserter(tr("Free Text"),
	                                                        tr("Free Text"),
	                                                        "freeannotation");
	annotationMenu->addAction(basicButtonInserter);
	annotationMenu->addAction(countingButtonInserter);
	annotationMenu->addAction(spinBoxInserter);
	annotationMenu->addAction(freeAnnotationInserter);
	connect(basicButtonInserter, SIGNAL(triggered(QString, QString)),
	        this, SLOT(insertChildNode(QString, QString)));
	connect(countingButtonInserter, SIGNAL(triggered(QString, QString)),
	        this, SLOT(insertChildNode(QString, QString)));
	connect(spinBoxInserter, SIGNAL(triggered(QString, QString)),
	        this, SLOT(insertChildNode(QString, QString)));
	connect(freeAnnotationInserter, SIGNAL(triggered(QString, QString)),
	        this, SLOT(insertChildNode(QString, QString)));
	addAnnotationControlButton->setMenu(annotationMenu);
	layout->addWidget(addAnnotationControlButton);
	QPushButton *advancedButton = new QPushButton(tr("Advanced Features"));
	QMenu *advancedMenu = new QMenu;
	NodeInserter *linearsplineinserter = new NodeInserter(tr("Linear Spline Interpolated Series"), tr("Linear Spline Interpolated Series"), "linearspline");
	advancedMenu->addAction(linearsplineinserter);
	NodeInserter *translationinserter = new NodeInserter(tr("Profile Translation"), tr("Profile Translation"), "translation");
	advancedMenu->addAction(translationinserter);
	connect(linearsplineinserter, SIGNAL(triggered(QString, QString)), this, SLOT(insertChildNode(QString, QString)));
	connect(translationinserter, SIGNAL(triggered(QString, QString)), this, SLOT(insertChildNode(QString, QString)));
	@<Add node inserters to advanced features menu@>@;
	advancedButton->setMenu(advancedMenu);
	layout->addWidget(advancedButton);
	QHBoxLayout *idLayout = new QHBoxLayout;
	QLabel *idLabel = new QLabel(tr("Machine ID for database:"));
	idLayout->addWidget(idLabel);
	QSpinBox *id = new QSpinBox;
	idLayout->addWidget(id);
	layout->addLayout(idLayout);
	@<Get device configuration data for current node@>@;
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		if(node.attribute("name") == "databaseid")
		{
			id->setValue(node.attribute("value").toInt());
			break;
		}
	}
	updateRoasterId(id->value());
	connect(id, SIGNAL(valueChanged(int)), this, SLOT(updateRoasterId(int)));
	setLayout(layout);
}

@ Iterating over the configuration data associated with the current node is
required in nearly every configuration widget. The specifics of the loop
vary, but there is likely a better way to generalize that. Until then,
obtaining a |QDomNodeList| with the required data to iterate over has been
split off as its own chunk to reduce the risk of errors associated with typing
the same code many times.

@<Get device configuration data for current node@>=
QDomElement referenceElement =
	model->referenceElement(model->data(index, Qt::UserRole).toString());
QDomNodeList configData = referenceElement.elementsByTagName("attribute");
QDomElement node;

@ We need to propagate changes to the ID number field to the device
configuration document. The |updateAttribute()| method in the base class
makes this trivial.

@<RoasterConfWidget implementation@>=
void RoasterConfWidget::updateRoasterId(int id)
{
	updateAttribute("databaseid", QString("%1").arg(id));
}

@ Finally we must register the configuration widget so that it can be
instantiated at the appropriate time.

@<Register device configuration widgets@>=
app.registerDeviceConfigurationWidget("roaster", RoasterConfWidget::staticMetaObject);

@** Configuration for NI-DAQmx Base devices.

\noindent The primary concern in supporting hardware that communicates through
NI-DAQmx Base is in configurations using a single NI USB 9211 (for NI-DAQmx
Base 2.x) or NI USB 9211A (for NI-DAQmx Base 3.x), but if it is reasonable to
do so I'@q'@>d like to later add support for multiple device configurations and
limited support for other devices including the ability to use devices with
voltage inputs for non-temperature measurement data. The top priority, however,
is in continuing to support hardware that people are already using with Typica.

In order to more easily implement these future plans, device configuration is
handled with three configuration tiers. The top level configuration node
indicates that we are using NI-DAQmx Base. Here we can add a child node
representing either a NI USB 9211 or NI USB 9211A. From a configuration
perspective these are identical with the default node name as the only
difference. From the device configuration we can specify the device identifier
and add channels to the device. In the channel nodes we specify the
thermocouple type.

@<Class declarations@>=
class NiDaqMxBaseDriverConfWidget : public BasicDeviceConfigurationWidget
{
	@[Q_OBJECT@]@;
	public:@/
		@[Q_INVOKABLE@]@, NiDaqMxBaseDriverConfWidget(DeviceTreeModel *model,@|
		                                        const QModelIndex &index);
};

@ There is very little to configure here so there isn'@q'@>t much for the
constructor to do. We do need to keep a reference to the node we are
configuring so that child nodes can later be added. At present, no real
configuration data other than the existence of the node is required so
there is no need to read any configuration data here.

@<NiDaqMxBaseDriverConfWidget implementation@>=
NiDaqMxBaseDriverConfWidget::NiDaqMxBaseDriverConfWidget(
	DeviceTreeModel *model, const QModelIndex &index) :
	BasicDeviceConfigurationWidget(model, index)
{
	QHBoxLayout *layout = new QHBoxLayout;
	QToolButton *addDeviceButton = new QToolButton;
	addDeviceButton->setText(tr("Add Device"));
	NodeInserter *add9211 = new NodeInserter("NI USB 9211", "NI USB 9211",
	                                         "nidaqmxbase9211series");
	NodeInserter *add9211a = new NodeInserter("NI USB 9211A", "NI USB 9211A",
	                                          "nidaqmxbase9211series");
	connect(add9211, SIGNAL(triggered(QString, QString)),
	        this, SLOT(insertChildNode(QString, QString)));
	connect(add9211a, SIGNAL(triggered(QString, QString)),
	        this, SLOT(insertChildNode(QString, QString)));
	QMenu *deviceMenu = new QMenu;
	deviceMenu->addAction(add9211);
	deviceMenu->addAction(add9211a);
	addDeviceButton->setMenu(deviceMenu);
	addDeviceButton->setPopupMode(QToolButton::InstantPopup);
	layout->addWidget(addDeviceButton);
	setLayout(layout);
}

@ Both the NI USB 9211 and NI USB 9211A are identical from a configuration
perspective. The only difference is the version of NI-DAQmx Base required for
use. As the API does not provide a way of determining which version is
installed, ensuring that the appropriate software is installed without
conflicts is left as an exercise for the person attempting to use \pn{}.

@<Class declarations@>=
class NiDaqMxBase9211ConfWidget : public BasicDeviceConfigurationWidget
{
	Q_OBJECT
	public:
		Q_INVOKABLE NiDaqMxBase9211ConfWidget(DeviceTreeModel *device,
		                                      const QModelIndex &index);
	private slots:
		void addChannel();
		void updateDeviceId(const QString &newId);
};

@ There are two controls required in a configuration widget for this device.
The first is the device identifier (for example, "Dev1"), the second is a
button for adding channels to the device. On a generic device we would also
need to set the clock rate, but with this hardware it is possible to determine
the maximum clock rate from the channels defined.

@<NiDaqMxBase9211ConfWidget implementation@>=
NiDaqMxBase9211ConfWidget::NiDaqMxBase9211ConfWidget(DeviceTreeModel *model,
                                                     const QModelIndex &index)
	: BasicDeviceConfigurationWidget(model, index)
{
	QVBoxLayout *layout = new QVBoxLayout;
	QHBoxLayout *deviceIdLayout = new QHBoxLayout;
	QLabel *label = new QLabel(tr("Device ID:"));
	QLineEdit *deviceId = new QLineEdit;
	deviceIdLayout->addWidget(label);
	deviceIdLayout->addWidget(deviceId);
	QPushButton *addChannelButton = new QPushButton(tr("Add Channel"));
	layout->addLayout(deviceIdLayout);
	layout->addWidget(addChannelButton);
	@<Get device configuration data for current node@>@;
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		if(node.attribute("name") == "deviceID")
		{
			deviceId->setText(node.attribute("value", "Dev1"));
			break;
		}
	}
	updateDeviceId(deviceId->text());
	connect(addChannelButton, SIGNAL(clicked()),
	        this, SLOT(addChannel()));
	connect(deviceId, SIGNAL(textEdited(QString)),
	        this, SLOT(updateDeviceId(QString)));
	setLayout(layout);
}

@ Updating the attribute tag under the reference element associated with the
current node is handled in the base class so we just need to pass in the
appropriate name value pair.

@<NiDaqMxBase9211ConfWidget implementation@>=
void NiDaqMxBase9211ConfWidget::updateDeviceId(const QString &newId)
{
	updateAttribute("deviceID", newId);
}

@ Adding channels is just like adding any other sort of node.

@<NiDaqMxBase9211ConfWidget implementation@>=
void NiDaqMxBase9211ConfWidget::addChannel()
{
	insertChildNode(tr("Thermocouple channel"), "ni9211seriestc");
}

@ Finally, we need a configuration widget to handle our thermocouple channels.
Ordinarily we would need three pieces of information for each channel. First
there is the thermocouple channel. Previously this was left implied by the
order of requests for a new channel, but more flexible configuration options
become possible with a more explicit specification. Since this widget is device
specific, all of the options can be easily enumerated to match markings on the
device. Next is the thermocouple type. Many options are supported, but I would
like to ensure that the most commonly used choices are listed first. The other
piece of information that DAQmx or DAQmx Base require is the measurement unit.
As all of Typica'@q'@>s internal operations are in Fahrenheit there is no need to
make this configurable so long as everything else that can display temperature
measurements can perform the appropriate conversions.

Note that as there are no configuration differences between the various
device combinations using an NI 9211 module with regard to thermocouple channel
configuration, we can use this widget with all device combinations that make
use of such a module.

@<Class declarations@>=
class Ni9211TcConfWidget : public BasicDeviceConfigurationWidget
{
	@[Q_OBJECT@]@/
	public:@/
		Q_INVOKABLE Ni9211TcConfWidget(DeviceTreeModel *device,
		                               const QModelIndex &index);
	@[private slots@]:@/
		void updateThermocoupleType(const QString &type);
		void updateColumnName(const QString &name);
};

@ This follows the same pattern of previous device configuration widgets. The
constructor provides the required configuration controls and slot methods
catch configuration changes and update the underlying XML document
appropriately.

@<Ni9211TcConfWidget implementation@>=
Ni9211TcConfWidget::Ni9211TcConfWidget(DeviceTreeModel *model,
                                       const QModelIndex &index) :
	BasicDeviceConfigurationWidget(model, index)
{
	QFormLayout *layout = new QFormLayout;
	QLineEdit *columnName = new QLineEdit;
	layout->addRow(tr("Column Name:"), columnName);
	QComboBox *typeSelector = new QComboBox;
	typeSelector->addItem("J");
	typeSelector->addItem("K");
	typeSelector->addItem("T");
	typeSelector->addItem("B");
	typeSelector->addItem("E");
	typeSelector->addItem("N");
	typeSelector->addItem("R");
	typeSelector->addItem("S");
	layout->addRow(tr("Thermocouple Type:"), typeSelector);
	setLayout(layout);
	@<Get device configuration data for current node@>@;
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		if(node.attribute("name") == "type")
		{
			typeSelector->setCurrentIndex(
				typeSelector->findText(node.attribute("value")));
		}
		else if(node.attribute("name") == "columnname")
		{
			columnName->setText(node.attribute("value"));
		}
	}
	updateThermocoupleType(typeSelector->currentText());
	updateColumnName(columnName->text());
	connect(typeSelector, SIGNAL(currentIndexChanged(QString)),
	        this, SLOT(updateThermocoupleType(QString)));
	connect(columnName, SIGNAL(textEdited(QString)), this, SLOT(updateColumnName(QString)));
}

@ Two slots are used to pass configuration changes back to the underlying XML
representation.

@<Ni9211TcConfWidget implementation@>=
void Ni9211TcConfWidget::updateThermocoupleType(const QString &type)
{
	updateAttribute("type", type);
}

void Ni9211TcConfWidget::updateColumnName(const QString &name)
{
	updateAttribute("columnname", name);
}

@ These three widgets need to be registered so the configuration widget can
instantiate them when the nodes are selected.

@<Register device configuration widgets@>=
app.registerDeviceConfigurationWidget("nidaqmxbase",
	NiDaqMxBaseDriverConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("nidaqmxbase9211series",
	NiDaqMxBase9211ConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("ni9211seriestc",
	Ni9211TcConfWidget::staticMetaObject);

@ Furthermore, we should create the NodeInserter objects for adding top level
nodes to the configuration. Preferably we would only allow top level nodes to
be inserted when all prerequisite software is available.

@<Register top level device configuration nodes@>=
NodeInserter *inserter = new NodeInserter(tr("NI DAQmx Base Device"),
                                          tr("NI DAQmx Base"),
										  "nidaqmxbase", NULL);
topLevelNodeInserters.append(inserter);

@** Configuration of NI-DAQmx devices.

\noindent The other main class of hardware currently supported in Typica is a
small set of devices that require NI-DAQmx. This includes a few combinations of
the NI 9211 in different carriers and the NI USB TC01. Additional hardware may
be added to this set in the future.

The approach here is very similar to the approach used to configure NI-DAQmx
Base devices, starting with a widget for adding child device nodes.

@<Class declarations@>=
class NiDaqMxDriverConfWidget : public BasicDeviceConfigurationWidget
{
	@[Q_OBJECT@]@;
	public:
		@[Q_INVOKABLE@]@, NiDaqMxDriverConfWidget(DeviceTreeModel *model,
		                                          const QModelIndex &index);
};

@ Under our driver node we want to have the ability to insert device specific
child nodes.

@<NiDaqMxDriverConfWidget implementation@>=
NiDaqMxDriverConfWidget::NiDaqMxDriverConfWidget(DeviceTreeModel *model,
                                                 const QModelIndex &index)
: BasicDeviceConfigurationWidget(model, index)
{
	QHBoxLayout *layout = new QHBoxLayout;
	QToolButton *addDeviceButton = new QToolButton;
	addDeviceButton->setText(tr("Add Device"));
	NodeInserter *add9211a = new NodeInserter("NI USB 9211A", "NI USB 9211A",
	                                          "nidaqmx9211series");
	NodeInserter *addtc01 = new NodeInserter("NI USB TC01", "NI USB TC01",
	                                         "nidaqmxtc01");
	connect(add9211a, SIGNAL(triggered(QString, QString)),
	        this, SLOT(insertChildNode(QString, QString)));
	connect(addtc01, SIGNAL(triggered(QString, QString)),
	        this, SLOT(insertChildNode(QString, QString)));
	QMenu *deviceMenu = new QMenu;
	deviceMenu->addAction(add9211a);
	deviceMenu->addAction(addtc01);
	addDeviceButton->setMenu(deviceMenu);
	addDeviceButton->setPopupMode(QToolButton::InstantPopup);
	layout->addWidget(addDeviceButton);
	setLayout(layout);
}

@ Devices based on the 9211 module are essentially the same aside from device
naming convention. Configuring these is very similar to configuring similar
devices when using NI-DAQmx Base.

@<Class declarations@>=
class NiDaqMx9211ConfWidget : public BasicDeviceConfigurationWidget
{
	@[Q_OBJECT@]@;
	public:@/
		@[Q_INVOKABLE@]@, NiDaqMx9211ConfWidget(DeviceTreeModel *model,
		                                        const QModelIndex &index);
	@[private slots@]:@/
		void addChannel();
		void updateDeviceId(const QString &newId);
};

@ Implementation is essentially identical to the NI-DAQmx Base class. It is
likely that there will be differences if this is ever extended to support
automatic detection of connected hardware. While NI-DAQmx Base does not
provide a way to query device identifiers, it uses a consistent naming scheme
by which device identifiers can be discovered. While NI-DAQmx lacks the same
consistency in device identifiers, it does provide a way to query that
information.

@<NiDaqMx9211ConfWidget implementation@>=
NiDaqMx9211ConfWidget::NiDaqMx9211ConfWidget(DeviceTreeModel *model,
                                             const QModelIndex &index)
: BasicDeviceConfigurationWidget(model, index)
{
	QVBoxLayout *layout = new QVBoxLayout;
	QHBoxLayout *deviceIdLayout = new QHBoxLayout;
	QLabel *label = new QLabel(tr("Device ID:"));
	QLineEdit *deviceId = new QLineEdit;
	deviceIdLayout->addWidget(label);
	deviceIdLayout->addWidget(deviceId);
	QPushButton *addChannelButton = new QPushButton(tr("Add Channel"));
	layout->addLayout(deviceIdLayout);
	layout->addWidget(addChannelButton);
	@<Get device configuration data for current node@>@;
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		if(node.attribute("name") == "deviceID")
		{
			deviceId->setText(node.attribute("value","Dev1"));
			break;
		}
	}
	updateDeviceId(deviceId->text());
	connect(addChannelButton, SIGNAL(clicked()), this, SLOT(addChannel()));
	connect(deviceId, SIGNAL(textEdited(QString)),
	        this, SLOT(updateDeviceId(QString)));
	setLayout(layout);
}

void NiDaqMx9211ConfWidget::updateDeviceId(const QString &newId)
{
	updateAttribute("deviceID", newId);
}

void NiDaqMx9211ConfWidget::addChannel()
{
	insertChildNode(tr("Thermocouple channel"), "ni9211seriestc");
}

@ There is no need to create a configuration widget specific to the 9211 module
used in NI-DAQmx. The widget already used for NI-DAQmx Base can be used without
modification.

Configuring Typica for use with the NI USB-TC01 can be slightly simplified as
the device only has a single thermocouple channel. We can configure this without
requiring another node.

@<Class declarations@>=
class NiDaqMxTc01ConfWidget : public BasicDeviceConfigurationWidget
{
	@[Q_OBJECT@]@;
	public:@/
		@[Q_INVOKABLE@]@, NiDaqMxTc01ConfWidget(DeviceTreeModel *model,
		                                        const QModelIndex &index);
	@[private slots@]:@/
		void updateDeviceId(const QString &newId);
		void updateThermocoupleType(const QString &type);
		void updateColumnName(const QString &name);
};

@ The implementation is similar to the other configuration widgets.

@<NiDaqMxTc01ConfWidget implementation@>=
NiDaqMxTc01ConfWidget::NiDaqMxTc01ConfWidget(DeviceTreeModel *model,
                                             const QModelIndex &index)
: BasicDeviceConfigurationWidget(model, index)
{
	QFormLayout *layout = new QFormLayout;
	QLineEdit *deviceId = new QLineEdit;
	layout->addRow(tr("Device ID:"), deviceId);
	QLineEdit *columnName = new QLineEdit;
	layout->addRow(tr("Column Name:"), columnName);
	QComboBox *typeSelector = new QComboBox;
	typeSelector->addItem("J");
	typeSelector->addItem("K");
	typeSelector->addItem("T");
	typeSelector->addItem("B");
	typeSelector->addItem("E");
	typeSelector->addItem("N");
	typeSelector->addItem("R");
	typeSelector->addItem("S");
	layout->addRow(tr("Thermocouple Type:"), typeSelector);
	@<Get device configuration data for current node@>@;
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		if(node.attribute("name") == "deviceID")
		{
			deviceId->setText(node.attribute("value"));
		}
		else if(node.attribute("name") == "type")
		{
			typeSelector->setCurrentIndex(typeSelector->findText(node.attribute("value")));
		}
		else if(node.attribute("name") == "columnname")
		{
			columnName->setText(node.attribute("value"));
		}
	}
	updateDeviceId(deviceId->text());
	updateThermocoupleType(typeSelector->currentText());
	updateColumnName(columnName->text());
	connect(deviceId, SIGNAL(textEdited(QString)), this, SLOT(updateDeviceId(QString)));
	connect(typeSelector, SIGNAL(currentIndexChanged(QString)), this, SLOT(updateThermocoupleType(QString)));
	connect(columnName, SIGNAL(textEdited(QString)), this, SLOT(updateColumnName(QString)));
	setLayout(layout);
}

void NiDaqMxTc01ConfWidget::updateDeviceId(const QString &newId)
{
	updateAttribute("deviceID", newId);
}

void NiDaqMxTc01ConfWidget::updateThermocoupleType(const QString &type)
{
	updateAttribute("type", type);
}

void NiDaqMxTc01ConfWidget::updateColumnName(const QString &name)
{
	updateAttribute("columnname", name);
}

@ These configuration widgets need to be registered so they can be instantiated
in response to node selections.

@<Register device configuration widgets@>=
app.registerDeviceConfigurationWidget("nidaqmx", NiDaqMxDriverConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("nidaqmx9211series", NiDaqMx9211ConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("nidaqmxtc01", NiDaqMxTc01ConfWidget::staticMetaObject);

@ A |NodeInserter| for the driver configuration widget is also needed. Note that
at present NI DAQmx is only available on Windows so we do not bother to show
the option on other platforms. It would be generally preferable to replace this
with a check at runtime to determine if the required library exists. That could
be done with anything that requires third party installed code, leaving by
default only those options which have no external dependencies.

@<Register top level device configuration nodes@>=
#ifdef Q_OS_WIN32
inserter = new NodeInserter(tr("NI DAQmx Device"), tr("NI DAQmx"), "nidaqmx", NULL);
topLevelNodeInserters.append(inserter);
#endif

@** Configuration of Serial Port Devices.

\noindent It is possible to communicate with a number of devices through a
serial port. To do this, the appropriate settings for opening the port are
required and the communications protocol understood by the device must be
known. Serial port communications are provided by QextSerialPort. That
project was released under the MIT license.\nfnote{See the license text for
more information.} Additional headers are required.

@<Header files to include@>=
#include "qextserialport.h"
#include "qextserialenumerator.h"

@ Some custom widgets are provided which allow selecting the relevant
connection options from combo boxes. First there is a widget for selecting
the desired serial port. The drop down is pre-populated with any serial ports
that could be automatically detected, but the field can also be edited to
other values as may be required if the hardware is not connected during
configuration.

@<Class declarations@>=
class PortSelector : public QComboBox
{
	Q_OBJECT
	public:
		PortSelector(QWidget *parent = NULL);
	private slots:
		void addDevice(QextPortInfo port);
	private:
		QextSerialEnumerator *lister;
};

@ The implementation is trivial.

@<PortSelector implementation@>=
PortSelector::PortSelector(QWidget *parent) : QComboBox(parent),
	lister(new QextSerialEnumerator)
{
	QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
	QextPortInfo port;
	foreach(port, ports)
	{
		addItem(port.portName);
	}
	lister->setUpNotifications();
	connect(lister, SIGNAL(deviceDiscovered(QextPortInfo)),
	        this, SLOT(addDevice(QextPortInfo)));
	setEditable(true);
}

void PortSelector::addDevice(QextPortInfo port)
{
	addItem(port.portName);
}

@ Next is a widget which allows selecting the baud rate. Only rates supported
by the current operating system are available to select.

A later version of QextSerialPort than is used by \pn{} provides a helper
class which can be used more conveniently to create this sort of control. As
this is not yet available to \pn{}, we instead copy the |enum| specifying
the appropriate values into the class and use Qt's meta-object system to
populate the combo box based on the values in that |enum|.

@<Class declarations@>=
class BaudSelector : public QComboBox
{
	Q_OBJECT
	Q_ENUMS(BaudRateType)
	public:
		BaudSelector(QWidget *parent = NULL);
		enum BaudRateType
		{
#if defined(Q_OS_UNIX) || defined(qdoc)
			BAUD50 = 50,                //POSIX ONLY
			BAUD75 = 75,                //POSIX ONLY
			BAUD134 = 134,              //POSIX ONLY
			BAUD150 = 150,              //POSIX ONLY
			BAUD200 = 200,              //POSIX ONLY
			BAUD1800 = 1800,            //POSIX ONLY
#if defined(B76800) || defined(qdoc)
			BAUD76800 = 76800,          //POSIX ONLY
#endif
#if (defined(B230400) && defined(B4000000)) || defined(qdoc)
			BAUD230400 = 230400,        //POSIX ONLY
			BAUD460800 = 460800,        //POSIX ONLY
			BAUD500000 = 500000,        //POSIX ONLY
			BAUD576000 = 576000,        //POSIX ONLY
			BAUD921600 = 921600,        //POSIX ONLY
			BAUD1000000 = 1000000,      //POSIX ONLY
			BAUD1152000 = 1152000,      //POSIX ONLY
			BAUD1500000 = 1500000,      //POSIX ONLY
			BAUD2000000 = 2000000,      //POSIX ONLY
			BAUD2500000 = 2500000,      //POSIX ONLY
			BAUD3000000 = 3000000,      //POSIX ONLY
			BAUD3500000 = 3500000,      //POSIX ONLY
			BAUD4000000 = 4000000,      //POSIX ONLY
#endif
#endif
#if defined(Q_OS_WIN) || defined(qdoc)
			BAUD14400 = 14400,          //WINDOWS ONLY
			BAUD56000 = 56000,          //WINDOWS ONLY
			BAUD128000 = 128000,        //WINDOWS ONLY
			BAUD256000 = 256000,        //WINDOWS ONLY
#endif
			BAUD110 = 110,
			BAUD300 = 300,
			BAUD600 = 600,
			BAUD1200 = 1200,
			BAUD2400 = 2400,
			BAUD4800 = 4800,
			BAUD9600 = 9600,
			BAUD19200 = 19200,
			BAUD38400 = 38400,
			BAUD57600 = 57600,
			BAUD115200 = 115200
		};
};

@ As the |enum| values are identical to the baud rates represented, we only
the numeric values, ignoring the names which are rather ugly.

@<BaudSelector implementation@>=
BaudSelector::BaudSelector(QWidget *parent) : QComboBox(parent)
{
	QMetaObject meta = BaudSelector::staticMetaObject;
	QMetaEnum type = meta.enumerator(meta.indexOfEnumerator("BaudRateType"));
	for(int i = 0; i < type.keyCount(); i++)
	{
		addItem(QString("%1").arg(type.value(i)));
	}
}

@ This same technique is used in a widget for selecting parity.

@<Class declarations@>=
class ParitySelector : public QComboBox
{
	Q_OBJECT
	Q_ENUMS(ParityType)
	public:
		ParitySelector(QWidget *parent = NULL);
		enum ParityType
		{
			PAR_NONE,
			PAR_ODD,
			PAR_EVEN,
#if defined(Q_OS_WIN) || defined(qdoc)
			PAR_MARK,               //WINDOWS ONLY
#endif
			PAR_SPACE
		};
};

@ Implementation is similar to |BaudSelector| but as the values have no
apparent relation to what is represented we present the value names, placing
the corresponding value in the user data space associated with each entry.
The names here are ugly and not amenable to localization so this approach
should be reconsidered later.

@<ParitySelector implementation@>=
ParitySelector::ParitySelector(QWidget *parent) : QComboBox(parent)
{
	QMetaObject meta = ParitySelector::staticMetaObject;
	QMetaEnum type = meta.enumerator(meta.indexOfEnumerator("ParityType"));
	for(int i = 0; i < type.keyCount(); i++)
	{
		addItem(QString(type.key(i)), QVariant(type.value(i)));
	}
}

@ Similarly, we have a widget for selecting a method for flow control.

@<Class declarations@>=
class FlowSelector : public QComboBox
{
	Q_OBJECT
	Q_ENUMS(FlowType)
	public:
		FlowSelector(QWidget *parent = NULL);
		enum FlowType
		{
			FLOW_OFF,
			FLOW_HARDWARE,
			FLOW_XONXOFF
		};
};

@ Implementation follows the same pattern as in |ParitySelector|.

@<FlowSelector implementation@>=
FlowSelector::FlowSelector(QWidget *parent) : QComboBox(parent)
{
	QMetaObject meta = FlowSelector::staticMetaObject;
	QMetaEnum type = meta.enumerator(meta.indexOfEnumerator("FlowType"));
	for(int i = 0; i < type.keyCount(); i++)
	{
		addItem(QString(type.key(i)), QVariant(type.value(i)));
	}
}

@ We assume that the number of data bits will always be 8, though it may be
useful to later provide a control for selecting this for use with other devices
where this may not be assumed or for the sake of completion. This only leaves
specifying the number of stop bits.

@<Class declarations@>=
class StopSelector : public QComboBox
{
	Q_OBJECT
	Q_ENUMS(StopBitsType)
	public:
		StopSelector(QWidget *parent = NULL);
		enum StopBitsType
		{
			STOP_1,
#if defined(Q_OS_WIN) || defined(qdoc)
			STOP_1_5,	//WINDOWS ONLY
#endif
			STOP_2
		};
};

@ Implementation should be familiar by now.

@<StopSelector implementation@>=
StopSelector::StopSelector(QWidget *parent) : QComboBox(parent)
{
	QMetaObject meta = StopSelector::staticMetaObject;
	QMetaEnum type = meta.enumerator(meta.indexOfEnumerator("StopBitsType"));
	for(int i = 0; i < type.keyCount(); i++)
	{
		addItem(QString(type.key(i)), QVariant(type.value(i)));
	}
}

@** Configuration of Serial Devices Using Modbus RTU.

\noindent One protocol that is used across a broad class of devices is called
Modbus RTU. This protocol allows multiple devices to be chained together on a
two wire bus which can be connected to a single serial port. The communication
protocol involves a single message which is sent from a master device (in this
case the computer running Typica) to a slave device (the device we would like
to obtain information from) which is followed by a response message from the
slave to the master. After a brief wait the master can then send another
message to any slave on the bus and this process repeats. Every outgoing
message provides a station address to identify which slave on the bus should
respond, a function code to identify which of a broad class of operations has
been requested, the required data for the function specified, and a cyclic
redundancy check to validate the message.

@** A Spin Box with Hexadecimal Representation.

\noindent Common convention for communications documentation for devices that
use Modbus RTU is that relative addresses are specified in hexadecimal
representation. In order to simplify initial device configuration, it would be
best that input widgets both accept input in base 16 and display values as a
four digit hexadecimal value.

@<Class declarations@>=
class ShortHexSpinBox : public QSpinBox
{
	Q_OBJECT
	public:
		ShortHexSpinBox(QWidget *parent = NULL);
		virtual QValidator::State validate(QString &input, int &pos) const;
	protected:
		virtual int valueFromText(const QString &text) const;
		virtual QString textFromValue(int value) const;
};

@ For this we can set some new defaults in the constructor and must override
three methods.

@<ShortHexSpinBox implementation@>=
ShortHexSpinBox::ShortHexSpinBox(QWidget *parent) : QSpinBox(parent)
{
	setMinimum(0);
	setMaximum(0xFFFF);
	setPrefix("0x");
	setMinimumWidth(65);
}

QValidator::State ShortHexSpinBox::validate(QString &input, int &) const
{
	if(input.size() == 2)
	{
		return QValidator::Intermediate;
	}
	bool okay;
	input.toInt(&okay, 16);
	if(okay)
	{
		return QValidator::Acceptable;
	}
	return QValidator::Invalid;
}

int ShortHexSpinBox::valueFromText(const QString &text) const
{
	return text.toInt(NULL, 16);
}

QString ShortHexSpinBox::textFromValue(int value) const
{
	QString retval;
	retval.setNum(value, 16);
	while(retval.size() < 4)
	{
		retval.prepend("0");
	}
	return retval.toUpper();
}

@** Configuration Widgets for Modbus RTU Devices.

\noindent While the top level configuration widgets seen so far have not had
any configuration details beyond the ability to add devices under the driver,
in the case of a serial port with Modbus RTU devices it is reasonable to
provide the connection details which will be shared by all devices on the bus.

@<Class declarations@>=
class ModbusRtuPortConfWidget : public BasicDeviceConfigurationWidget
{
	@[Q_OBJECT@]@;
	public:
		@[Q_INVOKABLE@]@, ModbusRtuPortConfWidget(DeviceTreeModel *model,
		                                          const QModelIndex &index);
	@[private slots@]:@/
		void updatePort(const QString &newPort);
		void updateBaudRate(const QString &newRate);
		void updateParity(const QString &newParity);
		void updateFlowControl(const QString &newFlow);
		void updateStopBits(const QString &newStopBits);
};

@ Aside from the extra information compared with other configuration widgets
previously described, there is nothing surprising about the implementation.

@<ModbusRtuPortConfWidget implementation@>=
ModbusRtuPortConfWidget::ModbusRtuPortConfWidget(DeviceTreeModel *model,
                                                 const QModelIndex &index)
: BasicDeviceConfigurationWidget(model, index)
{
	QFormLayout *layout = new QFormLayout;
	QToolButton *addDeviceButton = new QToolButton;
	addDeviceButton->setText(tr("Add Device"));
	NodeInserter *addModbusRtuDevice = new NodeInserter("Modbus RTU Device",
	                                                    "Modbus RTU Device",
														"modbusrtudevice");
	connect(addModbusRtuDevice, SIGNAL(triggered(QString, QString)),
	        this, SLOT(insertChildNode(QString, QString)));
	QMenu *deviceMenu = new QMenu;
	deviceMenu->addAction(addModbusRtuDevice);
	addDeviceButton->setMenu(deviceMenu);
	addDeviceButton->setPopupMode(QToolButton::InstantPopup);
	layout->addRow(QString(), addDeviceButton);
	PortSelector *port = new PortSelector;
	layout->addRow(tr("Port:"), port);
	connect(port, SIGNAL(currentIndexChanged(QString)),
	        this, SLOT(updatePort(QString)));
	connect(port, SIGNAL(editTextChanged(QString)),
	        this, SLOT(updatePort(QString)));
	BaudSelector *rate = new BaudSelector;
	layout->addRow(tr("Baud:"), rate);
	connect(rate, SIGNAL(currentIndexChanged(QString)),
	        this, SLOT(updateBaudRate(QString)));
	ParitySelector *parity = new ParitySelector;
	layout->addRow(tr("Parity:"), parity);
	connect(parity, SIGNAL(currentIndexChanged(QString)),
	        this, SLOT(updateParity(QString)));
	FlowSelector *flow = new FlowSelector;
	layout->addRow(tr("Flow Control:"), flow);
	connect(flow, SIGNAL(currentIndexChanged(QString)),
	        this, SLOT(updateFlowControl(QString)));
	StopSelector *stop = new StopSelector;
	layout->addRow(tr("Stop Bits:"), stop);
	connect(stop, SIGNAL(currentIndexChanged(QString)),
	        this, SLOT(updateStopBits(QString)));
	@<Get device configuration data for current node@>@;
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		if(node.attribute("name") == "port")
		{
			int j = port->findText(node.attribute("value"));
			if(j >= 0)
			{
				port->setCurrentIndex(j);
			}
			else
			{
				port->insertItem(0, node.attribute("value"));
				port->setCurrentIndex(0);
			}
		}
		else if(node.attribute("name") == "baudrate")
		{
			rate->setCurrentIndex(rate->findText(node.attribute("value")));
		}
		else if(node.attribute("name") == "parity")
		{
			parity->setCurrentIndex(parity->findText(node.attribute("value")));
		}
		else if(node.attribute("name") == "flowcontrol")
		{
			flow->setCurrentIndex(flow->findText(node.attribute("value")));
		}
		else if(node.attribute("name") == "stopbits")
		{
			stop->setCurrentIndex(stop->findText(node.attribute("value")));
		}
	}
	updatePort(port->currentText());
	updateBaudRate(rate->currentText());
	updateParity(parity->currentText());
	updateFlowControl(flow->currentText());
	updateStopBits(stop->currentText());
	setLayout(layout);
}

void ModbusRtuPortConfWidget::updatePort(const QString &newPort)
{
	updateAttribute("port", newPort);
}

void ModbusRtuPortConfWidget::updateBaudRate(const QString &newRate)
{
	updateAttribute("baudrate", newRate);
}

void ModbusRtuPortConfWidget::updateParity(const QString &newParity)
{
	updateAttribute("parity", newParity);
}

void ModbusRtuPortConfWidget::updateFlowControl(const QString &newFlow)
{
	updateAttribute("flowcontrol", newFlow);
}

void ModbusRtuPortConfWidget::updateStopBits(const QString &newStopBits)
{
	updateAttribute("stopbits", newStopBits);
}

@ From here we need to provide a widget for configuring a particular device.
At a minimum this would require setting the station number to a value between
0 and 255. Zero is typically the broadcast address which reaches all devices
on the bus and is not generally recommended for use except in particular
circumstances. There are, however, a number of settings that influence all of
the currently supported child nodes and these settings are in the device
configuration widget instead of requiring that information to be duplicated
across multiple child nodes.

The Modbus RTU protocol is very general in scope and leaves many of the
details of how to do certain things up to the manufacturer. For rudimentary
support of devices using this protocol, the documentation for several devices
was consulted and a test rig with one device was set up. There are a number of
assumptions made for this initial support and to better support additional
device classes it may become necessary to expand on what is provided initially.
The primary focus presently is on the use of PID controllers as temperature
indicators with the ability to modify a set value in the case where this is
used as a controller rather than just a display.

All of the devices studied prior to adding this support made use of scaled
integer representation. In order to correctly determine the measured process
value it is necessary to know the unit of the measurement and the position of
the decimal point. It is generally possible to query this information, however
it may be useful to provide a way to specify fixed values in the event that a
device exposes these details in a way that is incompatible with my assumptions.

@<Class declarations@>=
class ModbusRtuDeviceConfWidget : public BasicDeviceConfigurationWidget
{
	@[Q_OBJECT@]@;
	public:@/
		@[Q_INVOKABLE@]@, ModbusRtuDeviceConfWidget(DeviceTreeModel *model,
		                                            const QModelIndex &index);
	@[private slots@]:@/
		void updateStationNumber(int newStation);
		void updateFixedUnit(bool newFixed);
		void updateFixedDecimal(bool newFixed);
		void updateUnit(const QString &newUnit);
		void updateUnitAddress(int newAddress);
		void updateValueF(int newValue);
		void updateValueC(int newValue);
		void updatePrecisionAddress(int newAddress);
		void updatePrecisionValue(int newValue);
	private:@/
		QStackedLayout *unitSpecificationLayout;
		QStackedLayout *decimalSpecificationLayout;
};

@ This widget has a number of differences from previous configuration widgets.
Perhaps most significantly there are controls which do not provide a text based
signal on state change. We also set certain controls as disabled when the
provided values are not relevant to operations such as when switching between
fixed decimal position and looking up decimal position from the device. Aside
from these details the widget operates according to the same principles as the
other widgets already seen.

@<ModbusRtuDeviceConfWidget implementation@>=
ModbusRtuDeviceConfWidget::ModbusRtuDeviceConfWidget(DeviceTreeModel *model,
                                                     const QModelIndex &index)
: BasicDeviceConfigurationWidget(model, index),
	unitSpecificationLayout(new QStackedLayout),
	decimalSpecificationLayout(new QStackedLayout)
{
	QVBoxLayout *layout = new QVBoxLayout;
	QToolButton *addChannelButton = new QToolButton;
	addChannelButton->setText(tr("Add Channel"));
	NodeInserter *addTemperaturePV = new NodeInserter("Temperature Process Value",
	                                                  "Temperature Process Value",
													  "modbustemperaturepv");
	NodeInserter *addTemperatureSV = new NodeInserter("Temperature Set Value",
	                                                  "Temperature Set Value",
													  "modbustemperaturesv");
	connect(addTemperaturePV, SIGNAL(triggered(QString, QString)),
	        this, SLOT(insertChildNode(QString, QString)));
	connect(addTemperatureSV, SIGNAL(triggered(QString, QString)),
	        this, SLOT(insertChildNode(QString, QString)));
	QMenu *channelMenu = new QMenu;
	channelMenu->addAction(addTemperaturePV);
	channelMenu->addAction(addTemperatureSV);
	addChannelButton->setMenu(channelMenu);
	addChannelButton->setPopupMode(QToolButton::InstantPopup);
	layout->addWidget(addChannelButton);
	QHBoxLayout *stationLayout = new QHBoxLayout;
	QLabel *stationLabel = new QLabel(tr("Station:"));
	QSpinBox *stationNumber = new QSpinBox;
	stationNumber->setMinimum(0);
	stationNumber->setMaximum(255);
	stationLayout->addWidget(stationLabel);
	stationLayout->addWidget(stationNumber);
	layout->addLayout(stationLayout);
	QCheckBox *fixedUnit = new QCheckBox(tr("Fixed Temperature Unit"));
	layout->addWidget(fixedUnit);
	QWidget *fixedUnitPlaceholder = new QWidget(this);
	QHBoxLayout *fixedUnitLayout = new QHBoxLayout;
	QLabel *fixedUnitLabel = new QLabel(tr("Temperature Unit:"));
	QComboBox *fixedUnitSelector = new QComboBox;
	fixedUnitSelector->addItem("Fahrenheit");
	fixedUnitSelector->addItem("Celsius");
	fixedUnitLayout->addWidget(fixedUnitLabel);
	fixedUnitLayout->addWidget(fixedUnitSelector);
	fixedUnitPlaceholder->setLayout(fixedUnitLayout);
	unitSpecificationLayout->addWidget(fixedUnitPlaceholder);
	QWidget *queriedUnitPlaceholder = new QWidget(this);
	QFormLayout *queriedUnitLayout = new QFormLayout;
	ShortHexSpinBox *unitAddress = new ShortHexSpinBox;
	queriedUnitLayout->addRow(tr("Function 0x03 Unit Address:"), unitAddress);
	QSpinBox *valueF = new QSpinBox;
	valueF->setMinimum(0);
	valueF->setMaximum(65535);
	queriedUnitLayout->addRow(tr("Value for Fahrenheit"), valueF);
	QSpinBox *valueC = new QSpinBox;
	valueC->setMinimum(0);
	valueC->setMaximum(65535);
	queriedUnitLayout->addRow(tr("Value for Celsius"), valueC);
	queriedUnitPlaceholder->setLayout(queriedUnitLayout);
	unitSpecificationLayout->addWidget(queriedUnitPlaceholder);
	layout->addLayout(unitSpecificationLayout);
	QCheckBox *fixedPrecision = new QCheckBox(tr("Fixed Precision"));
	layout->addWidget(fixedPrecision);
	QWidget *fixedPrecisionPlaceholder = new QWidget(this);
	QFormLayout *fixedPrecisionLayout = new QFormLayout;
	QSpinBox *fixedPrecisionValue = new QSpinBox;
	fixedPrecisionValue->setMinimum(0);
	fixedPrecisionValue->setMaximum(9);
	fixedPrecisionLayout->addRow("Places after the decimal point:",
	                             fixedPrecisionValue);
	fixedPrecisionPlaceholder->setLayout(fixedPrecisionLayout);
	decimalSpecificationLayout->addWidget(fixedPrecisionPlaceholder);
	QWidget *queriedPrecisionPlaceholder = new QWidget(this);
	QFormLayout *queriedPrecisionLayout = new QFormLayout;
	ShortHexSpinBox *precisionAddress = new ShortHexSpinBox;
	queriedPrecisionLayout->addRow("Function 0x03 Decimal Position Address:",
	                                    precisionAddress);
	queriedPrecisionPlaceholder->setLayout(queriedPrecisionLayout);
	decimalSpecificationLayout->addWidget(queriedPrecisionPlaceholder);
	layout->addLayout(decimalSpecificationLayout);
	@<Get device configuration data for current node@>@;
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		if(node.attribute("name") == "station")
		{
			stationNumber->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "fixedunit")
		{
			if(node.attribute("value") == "true")
			{
				fixedUnit->setCheckState(Qt::Checked);
			}
			else if(node.attribute("value") == "false")
			{
				fixedUnit->setCheckState(Qt::Unchecked);
			}
		}
		else if(node.attribute("name") == "fixedprecision")
		{
			fixedPrecisionValue->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "unit")
		{
			fixedUnitSelector->setCurrentIndex(fixedUnitSelector->findText(node.attribute("value")));
		}
		else if(node.attribute("name") == "unitaddress")
		{
			unitAddress->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "fvalue")
		{
			valueF->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "cvalue")
		{
			valueC->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "precisionaddress")
		{
			precisionAddress->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "precision")
		{
			fixedPrecisionValue->setValue(node.attribute("value").toInt());
		}
	}
	updateStationNumber(stationNumber->value());
	updateFixedUnit(fixedUnit->isChecked());
	updateFixedDecimal(fixedPrecision->isChecked());
	updateUnit(fixedUnitSelector->currentText());
	updateUnitAddress(unitAddress->value());
	updateValueF(valueF->value());
	updateValueC(valueC->value());
	updatePrecisionAddress(precisionAddress->value());
	updatePrecisionValue(fixedPrecisionValue->value());
	connect(stationNumber, SIGNAL(valueChanged(int)),
	        this, SLOT(updateStationNumber(int)));
	connect(fixedUnitSelector, SIGNAL(currentIndexChanged(QString)),
	        this, SLOT(updateUnit(QString)));
	connect(unitAddress, SIGNAL(valueChanged(int)),
	        this, SLOT(updateUnitAddress(int)));
	connect(valueF, SIGNAL(valueChanged(int)),
	        this, SLOT(updateValueF(int)));
	connect(valueC, SIGNAL(valueChanged(int)),
	        this, SLOT(updateValueC(int)));
	connect(fixedUnit, SIGNAL(toggled(bool)),
	        this, SLOT(updateFixedUnit(bool)));
	connect(fixedPrecision, SIGNAL(toggled(bool)),
	        this, SLOT(updateFixedDecimal(bool)));
	connect(fixedPrecisionValue, SIGNAL(valueChanged(int)),
	        this, SLOT(updatePrecisionValue(int)));
	connect(precisionAddress, SIGNAL(valueChanged(int)),
	        this, SLOT(updatePrecisionAddress(int)));
	setLayout(layout);
}

void ModbusRtuDeviceConfWidget::updateStationNumber(int newStation)
{
	updateAttribute("station", QString("%1").arg(newStation));
}

void ModbusRtuDeviceConfWidget::updateFixedUnit(bool newFixed)
{
	if(newFixed)
	{
		unitSpecificationLayout->setCurrentIndex(0);
		updateAttribute("fixedunit", "true");
	}
	else
	{
		unitSpecificationLayout->setCurrentIndex(1);
		updateAttribute("fixedunit", "false");
	}
}

void ModbusRtuDeviceConfWidget::updateFixedDecimal(bool newFixed)
{
	if(newFixed)
	{
		decimalSpecificationLayout->setCurrentIndex(0);
		updateAttribute("fixedprecision", "true");
	}
	else
	{
		decimalSpecificationLayout->setCurrentIndex(1);
		updateAttribute("fixedprecision", "false");
	}
}

void ModbusRtuDeviceConfWidget::updateUnit(const QString &newUnit)
{
	updateAttribute("unit", newUnit);
}

void ModbusRtuDeviceConfWidget::updateUnitAddress(int newAddress)
{
	updateAttribute("unitaddress", QString("%1").arg(newAddress));
}

void ModbusRtuDeviceConfWidget::updateValueF(int newValue)
{
	updateAttribute("fvalue", QString("%1").arg(newValue));
}

void ModbusRtuDeviceConfWidget::updateValueC(int newValue)
{
	updateAttribute("cvalue", QString("%1").arg(newValue));
}

void ModbusRtuDeviceConfWidget::updatePrecisionAddress(int newAddress)
{
	updateAttribute("precisionaddress", QString("%1").arg(newAddress));
}

void ModbusRtuDeviceConfWidget::updatePrecisionValue(int newValue)
{
	updateAttribute("precision", QString("%1").arg(newValue));
}

@ Initial Modbus RTU support is very limited and only considers temperature
process and set values. While in some cases it would be possible to cleverly
adapt this support to broader categories this is an area that must be extended
later to cover at least unitless control values and on/off status values. It
would be ideal to cover a broad range of useful properties. To read process
values we need to know the address that the current process value can be read
from.

@<Class declarations@>=
class ModbusRtuDeviceTPvConfWidget : public BasicDeviceConfigurationWidget
{
	@[Q_OBJECT@]@/
	public:@/
		@[Q_INVOKABLE@]@, ModbusRtuDeviceTPvConfWidget(DeviceTreeModel *model,
		                                               const QModelIndex &index);
	@[private slots@]:@/
		void updateAddress(int newAddress);
};

@ This requires only a single field to store the address to query the current
process value.

@<ModbusRtuDeviceTPvConfWidget implementation@>=
ModbusRtuDeviceTPvConfWidget::ModbusRtuDeviceTPvConfWidget(DeviceTreeModel *model,
                                                           const QModelIndex &index)
: BasicDeviceConfigurationWidget(model, index)
{
	QFormLayout *layout = new QFormLayout;
	ShortHexSpinBox *address = new ShortHexSpinBox;
	layout->addRow(tr("Function 0x04 Process Value Address"), address);
	@<Get device configuration data for current node@>@;
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		if(node.attribute("name") == "address")
		{
			address->setValue(node.attribute("value").toInt());
			break;
		}
	}
	updateAddress(address->value());
	connect(address, SIGNAL(valueChanged(int)), this, SLOT(updateAddress(int)));
	setLayout(layout);
}

void ModbusRtuDeviceTPvConfWidget::updateAddress(int newAddress)
{
	updateAttribute("address", QString("%1").arg(newAddress));
}

@ Set values are slightly more complicated as we may want either a fixed range
or the ability to query the device for its current allowed range, but nothing
is here that hasn'@q'@>t been seen elsewhere.

@<Class declarations@>=
class ModbusRtuDeviceTSvConfWidget : public BasicDeviceConfigurationWidget
{
	@[Q_OBJECT@]@;
	public:@/
		@[Q_INVOKABLE@]@, ModbusRtuDeviceTSvConfWidget(DeviceTreeModel *model,
		                                               const QModelIndex &index);
	@[private slots@]:@/
		void updateReadAddress(int newAddress);
		void updateWriteAddress(int newAddress);
		void updateFixedRange(bool fixed);
		void updateLower(const QString &lower);
		void updateUpper(const QString &upper);
		void updateLowerAddress(int newAddress);
		void updateUpperAddress(int newAddress);
	private:
		QStackedLayout *boundsLayout;
};

@ Upper and lower bounds when operating on a fixed range are still subject to
decimal position rules in the parent node. It may be a good idea to enforce
this, however at present the person configuring the system is trusted to know
what they are doing.

@<ModbusRtuDeviceTSvConfWidget implementation@>=
ModbusRtuDeviceTSvConfWidget::ModbusRtuDeviceTSvConfWidget(DeviceTreeModel *model,
                                                           const QModelIndex &index)
: BasicDeviceConfigurationWidget(model, index), boundsLayout(new QStackedLayout)
{
	QVBoxLayout *layout = new QVBoxLayout;
	QFormLayout *addressLayout = new QFormLayout;
	ShortHexSpinBox *readAddress = new ShortHexSpinBox;
	ShortHexSpinBox *writeAddress = new ShortHexSpinBox;
	addressLayout->addRow(tr("Function 0x04 Read Set Value Address:"), readAddress);
	addressLayout->addRow(tr("Function 0x06 Write Set Value Address:"), writeAddress);
	layout->addLayout(addressLayout);
	QCheckBox *fixedRange = new QCheckBox(tr("Fixed Set Value Range"));
	layout->addWidget(fixedRange);
	QWidget *queriedRangePlaceholder = new QWidget(this);
	QFormLayout *queriedRangeLayout = new QFormLayout;
	ShortHexSpinBox *lowerAddress = new ShortHexSpinBox;
	ShortHexSpinBox *upperAddress = new ShortHexSpinBox;
	queriedRangeLayout->addRow(tr("Function 0x03 Minimum Set Value Address"),
	                           lowerAddress);
	queriedRangeLayout->addRow(tr("Function 0x03 Maximum Set Value Address"),
	                           upperAddress);
	queriedRangePlaceholder->setLayout(queriedRangeLayout);
	boundsLayout->addWidget(queriedRangePlaceholder);
	QWidget *fixedRangePlaceholder = new QWidget(this);
	QFormLayout *fixedRangeLayout = new QFormLayout;
	QLineEdit *fixedLower = new QLineEdit;
	QLineEdit *fixedUpper = new QLineEdit;
	fixedRangeLayout->addRow(tr("Minimum Set Value:"), fixedLower);
	fixedRangeLayout->addRow(tr("Maximum Set Value:"), fixedUpper);
	fixedRangePlaceholder->setLayout(fixedRangeLayout);
	boundsLayout->addWidget(fixedRangePlaceholder);
	layout->addLayout(boundsLayout);
	@<Get device configuration data for current node@>@;
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		if(node.attribute("name") == "readaddress")
		{
			readAddress->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "writeaddress")
		{
			writeAddress->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "fixedrange")
		{
			if(node.attribute("value") == "true")
			{
				fixedRange->setCheckState(Qt::Checked);
			}
			else if(node.attribute("value") == "false")
			{
				fixedRange->setCheckState(Qt::Unchecked);
			}
		}
		else if(node.attribute("name") == "fixedlower")
		{
			fixedLower->setText(node.attribute("value"));
		}
		else if(node.attribute("name") == "fixedupper")
		{
			fixedUpper->setText(node.attribute("value"));
		}
		else if(node.attribute("name") == "loweraddress")
		{
			lowerAddress->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "upperaddress")
		{
			upperAddress->setValue(node.attribute("value").toInt());
		}
	}
	updateReadAddress(readAddress->value());
	updateWriteAddress(writeAddress->value());
	updateFixedRange(fixedRange->isChecked());
	updateLower(fixedLower->text());
	updateUpper(fixedUpper->text());
	updateLowerAddress(lowerAddress->value());
	updateUpperAddress(upperAddress->value());
	connect(readAddress, SIGNAL(valueChanged(int)),
	        this, SLOT(updateReadAddress(int)));
	connect(writeAddress, SIGNAL(valueChanged(int)),
	        this, SLOT(updateWriteAddress(int)));
	connect(fixedRange, SIGNAL(toggled(bool)), this, SLOT(updateFixedRange(bool)));
	connect(fixedLower, SIGNAL(textChanged(QString)),
	        this, SLOT(updateLower(QString)));
	connect(fixedUpper, SIGNAL(textChanged(QString)),
	        this, SLOT(updateUpper(QString)));
	connect(lowerAddress, SIGNAL(valueChanged(int)),
	        this, SLOT(updateLowerAddress(int)));
	connect(upperAddress, SIGNAL(valueChanged(int)),
	        this, SLOT(updateUpperAddress(int)));
	setLayout(layout);
}

void ModbusRtuDeviceTSvConfWidget::updateReadAddress(int newAddress)
{
	updateAttribute("readaddress", QString("%1").arg(newAddress));
}

void ModbusRtuDeviceTSvConfWidget::updateWriteAddress(int newAddress)
{
	updateAttribute("writeaddress", QString("%1").arg(newAddress));
}

void ModbusRtuDeviceTSvConfWidget::updateFixedRange(bool fixed)
{
	if(fixed)
	{
		updateAttribute("fixedrange", "true");
		boundsLayout->setCurrentIndex(1);
	}
	else
	{
		updateAttribute("fixedrange", "false");
		boundsLayout->setCurrentIndex(0);
	}
}

void ModbusRtuDeviceTSvConfWidget::updateLower(const QString &lower)
{
	updateAttribute("fixedlower", lower);
}

void ModbusRtuDeviceTSvConfWidget::updateUpper(const QString &upper)
{
	updateAttribute("fixedupper", upper);
}

void ModbusRtuDeviceTSvConfWidget::updateLowerAddress(int newAddress)
{
	updateAttribute("loweraddress", QString("%1").arg(newAddress));
}

void ModbusRtuDeviceTSvConfWidget::updateUpperAddress(int newAddress)
{
	updateAttribute("upperaddress", QString("%1").arg(newAddress));
}

@ The configuration widgets need to be registered.

@<Register device configuration widgets@>=
app.registerDeviceConfigurationWidget("modbusrtuport", ModbusRtuPortConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("modbusrtudevice", ModbusRtuDeviceConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("modbustemperaturepv", ModbusRtuDeviceTPvConfWidget::staticMetaObject);
app.registerDeviceConfigurationWidget("modbustemperaturesv", ModbusRtuDeviceTSvConfWidget::staticMetaObject);

@ A |NodeInserter| for the driver configuration widget is also needed. Note
that this is temporarily disabled. These configuration widgets will become
useful when I rearchitect the Modbus RTU support in a future release.

@<Register top level device configuration nodes@>=
#if 0
inserter = new NodeInserter(tr("Modbus RTU Port"), tr("Modbus RTU Port"), "modbusrtuport", NULL);
topLevelNodeInserters.append(inserter);
#endif

@** Configuration of Annotation Controls.

\noindent Aside from the details of hardware devices, the logging view must
also be able to set up log annotation controls. A few different control types
are offered. These include simple push buttons which insert a fixed annotation
when activated, push buttons which insert a value that includes a number which
is incremented every time the button is pressed, free text entry fields, and
numeric entry fields.

The basic push button control should allow configuration of both the button
text and the annotation text.

@<Class declarations@>=
class AnnotationButtonConfWidget : public BasicDeviceConfigurationWidget
{
	@[Q_OBJECT@]@;
	public:@/
		@[Q_INVOKABLE@]@, AnnotationButtonConfWidget(DeviceTreeModel *model, const QModelIndex &index);
	@[private slots@]:@/
		void updateButtonText(const QString &text);
		void updateAnnotationText(const QString &text);
};

@ The constructor sets up the controls for editing this data.

@<AnnotationButtonConfWidget implementation@>=
AnnotationButtonConfWidget::AnnotationButtonConfWidget(DeviceTreeModel *model, const QModelIndex &index)
: BasicDeviceConfigurationWidget(model, index)
{
	QFormLayout *layout = new QFormLayout;
	QLineEdit *buttonTextEdit = new QLineEdit;
	QLineEdit *annotationTextEdit = new QLineEdit;
	layout->addRow(tr("Button Text:"), buttonTextEdit);
	layout->addRow(tr("Annotation Text:"), annotationTextEdit);
	@<Get device configuration data for current node@>@;
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		if(node.attribute("name") == "buttontext")
		{
			buttonTextEdit->setText(node.attribute("value"));
		}
		else if(node.attribute("name") == "annotationtext")
		{
			annotationTextEdit->setText(node.attribute("value"));
		}
	}
	updateButtonText(buttonTextEdit->text());
	updateAnnotationText(annotationTextEdit->text());
	connect(buttonTextEdit, SIGNAL(textEdited(QString)), this, SLOT(updateButtonText(QString)));
	connect(annotationTextEdit, SIGNAL(textEdited(QString)), this, SLOT(updateAnnotationText(QString)));
	setLayout(layout);
}

@ The slots are implemented trivially.

@<AnnotationButtonConfWidget implementation@>=
void AnnotationButtonConfWidget::updateButtonText(const QString &text)
{
	updateAttribute("buttontext", text);
}

void AnnotationButtonConfWidget::updateAnnotationText(const QString &text)
{
	updateAttribute("annotationtext", text);
}

@ The control must be registered.

@<Register device configuration widgets@>=
app.registerDeviceConfigurationWidget("annotationbutton", AnnotationButtonConfWidget::staticMetaObject);

@ Closely related to the previous control is one which provides parameterized
text. Technically this is not needed as both this and the previous
configuration control map to the same widget in the logging view and
parameterized annotation text can be used with either. The reason for
separating these is to indicate that it should be possible to change the text
and reset the number without altering the default configuration or requiring a
reinitialization of the logging view.

@<Class declarations@>=
class ReconfigurableAnnotationButtonConfWidget : public BasicDeviceConfigurationWidget
{
	@[Q_OBJECT@]@/
	public:@/
		@[Q_INVOKABLE@] ReconfigurableAnnotationButtonConfWidget(DeviceTreeModel *model, const QModelIndex &index);
	@[private slots@]:@/
		void updateButtonText(const QString &text);
		void updateAnnotationText(const QString &text);
};

@ The key difference in implementation is the addition of some documentation on
how to specify a numeric placeholder in the annotation text.

@<AnnotationButtonConfWidget implementation@>=
ReconfigurableAnnotationButtonConfWidget::ReconfigurableAnnotationButtonConfWidget(DeviceTreeModel *model, const QModelIndex &index)
: BasicDeviceConfigurationWidget(model, index)
{
	QFormLayout *layout = new QFormLayout;
	QLineEdit *buttonTextEdit = new QLineEdit;
	QLineEdit *annotationTextEdit = new QLineEdit;
	layout->addRow(tr("Button Text:"), buttonTextEdit);
	layout->addRow(tr("Annotation Text:"), annotationTextEdit);
	@<Get device configuration data for current node@>@;
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		if(node.attribute("name") == "buttontext")
		{
			buttonTextEdit->setText(node.attribute("value"));
		}
		else if(node.attribute("name") == "annotationtext")
		{
			annotationTextEdit->setText(node.attribute("value"));
		}
	}
	updateButtonText(buttonTextEdit->text());
	updateAnnotationText(annotationTextEdit->text());
	connect(buttonTextEdit, SIGNAL(textEdited(QString)), this, SLOT(updateButtonText(QString)));
	connect(annotationTextEdit, SIGNAL(textEdited(QString)), this, SLOT(updateAnnotationText(QString)));
	QTextEdit *documentation = new QTextEdit;
	documentation->setHtml(tr("If the <b>Annotation Text</b> contains <tt>%1</tt>, this will be replaced in the annotation with a number that increments each time the button is pressed."));
	documentation->setReadOnly(true);
	layout->addRow("", documentation);
	setLayout(layout);
}

void ReconfigurableAnnotationButtonConfWidget::updateButtonText(const QString &text)
{
	updateAttribute("buttontext", text);
}

void ReconfigurableAnnotationButtonConfWidget::updateAnnotationText(const QString &text)
{
	updateAttribute("annotationtext", text);
}

@ The control must be registered as usual.

@<Register device configuration widgets@>=
app.registerDeviceConfigurationWidget("reconfigurablebutton", ReconfigurableAnnotationButtonConfWidget::staticMetaObject);

@ While it is generally better to have all measurements logged automatically,
many roasters would like to keep track of infrequently altered control
variables which have not been set up for automated logging. A reading from the
manometer after a fuel adjustment, for example, is frequently not available by
automated means. In cases such as this, providing for numeric annotation entry
may be desired. The |AnnotationSpinBox| provides for this. There are a few
details that are important in this. First is a label to better indicate to the
operator what values in this control represent. The range of allowed values and
the number of decimal places is important. This control also allows the
specification of text to precede and/or follow the numeric value and this must
be configurable.

@<Class declarations@>=
class NoteSpinConfWidget : public BasicDeviceConfigurationWidget
{
	@[Q_OBJECT@]@;
	public:@/
		@[Q_INVOKABLE@]@, NoteSpinConfWidget(DeviceTreeModel *model, const QModelIndex &index);
	@[private slots@]:@/
		void updateLabel(const QString &text);
		void updateMinimum(const QString &minimum);
		void updateMaximum(const QString &maximum);
		void updatePrecision(int precision);
		void updatePretext(const QString &text);
		void updatePosttext(const QString &text);
};

@ There is nothing new in the implementation of note.

@<NoteSpinConfWidget implementation@>=
NoteSpinConfWidget::NoteSpinConfWidget(DeviceTreeModel *model, const QModelIndex &index)
: BasicDeviceConfigurationWidget(model, index)
{
	QFormLayout *layout = new QFormLayout;
	QLineEdit *labelEdit = new QLineEdit;
	layout->addRow(tr("Control Label: "), labelEdit);
	QLineEdit *minimumEdit = new QLineEdit;
	layout->addRow(tr("Minimum Value: "), minimumEdit);
	QLineEdit *maximumEdit = new QLineEdit;
	layout->addRow(tr("Maximum Value: "), maximumEdit);
	QSpinBox *precisionEdit = new QSpinBox;
	precisionEdit->setMinimum(0);
	precisionEdit->setMaximum(9);
	layout->addRow(tr("Precision"), precisionEdit);
	QLineEdit *pretext = new QLineEdit;
	layout->addRow(tr("Prefix text"), pretext);
	QLineEdit *posttext = new QLineEdit;
	layout->addRow(tr("Suffix text"), posttext);
	@<Get device configuration data for current node@>@;
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		if(node.attribute("name") == "label")
		{
			labelEdit->setText(node.attribute("value"));
		}
		else if(node.attribute("name") == "minimum")
		{
			minimumEdit->setText(node.attribute("value"));
		}
		else if(node.attribute("name") == "maximum")
		{
			maximumEdit->setText(node.attribute("value"));
		}
		else if(node.attribute("name") == "precision")
		{
			precisionEdit->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "pretext")
		{
			pretext->setText(node.attribute("value"));
		}
		else if(node.attribute("name") == "posttext")
		{
			posttext->setText(node.attribute("value"));
		}
	}
	updateLabel(labelEdit->text());
	updateMinimum(minimumEdit->text());
	updateMaximum(maximumEdit->text());
	updatePrecision(precisionEdit->value());
	updatePretext(pretext->text());
	updatePosttext(posttext->text());
	connect(labelEdit, SIGNAL(textEdited(QString)), this, SLOT(updateLabel(QString)));
	connect(minimumEdit, SIGNAL(textEdited(QString)), this, SLOT(updateMinimum(QString)));
	connect(maximumEdit, SIGNAL(textEdited(QString)), this, SLOT(updateMaximum(QString)));
	connect(precisionEdit, SIGNAL(valueChanged(int)), this, SLOT(updatePrecision(int)));
	connect(pretext, SIGNAL(textEdited(QString)), this, SLOT(updatePretext(QString)));
	connect(posttext, SIGNAL(textEdited(QString)), this, SLOT(updatePosttext(QString)));
	setLayout(layout);
}

void NoteSpinConfWidget::updateLabel(const QString &text)
{
	updateAttribute("label", text);
}

void NoteSpinConfWidget::updateMinimum(const QString &minimum)
{
	updateAttribute("minimum", minimum);
}

void NoteSpinConfWidget::updateMaximum(const QString &maximum)
{
	updateAttribute("maximum", maximum);
}

void NoteSpinConfWidget::updatePrecision(int precision)
{
	updateAttribute("precision", QString("%1").arg(precision));
}

void NoteSpinConfWidget::updatePretext(const QString &text)
{
	updateAttribute("pretext", text);
}

void NoteSpinConfWidget::updatePosttext(const QString &text)
{
	updateAttribute("posttext", text);
}

@ Configuration widget registration is as usual.

@<Register device configuration widgets@>=
app.registerDeviceConfigurationWidget("annotationspinbox", NoteSpinConfWidget::staticMetaObject);

@i freeannotation.w

@i settings.w

@** Communicating with a Device through Modbus RTU.

\noindent The classes described here need to be further generalized to support
communications with multiple devices on the same port. The interface is based
on the |DAQ| class but extended to support additional functionality.

@<Class declarations@>=
class ModbusRTUDevice : public QObject
{
	@[Q_OBJECT@]@;
	public:@/
		ModbusRTUDevice(DeviceTreeModel *model, const QModelIndex &index);
		~ModbusRTUDevice();
		void queueMessage(QByteArray request, QObject *object, const char *callback);
		@[Q_INVOKABLE@]@, double SVLower();
		@[Q_INVOKABLE@]@, double SVUpper();
		@[Q_INVOKABLE@]@, int decimals();
		QList<Channel*> channels;
	@[public slots@]:@/
		void outputSV(double sv);
	@[signals@]:@/
		void SVLowerChanged(double);
		void SVUpperChanged(double);
		void SVDecimalChanged(int);
		void queueEmpty();
	@[private slots@]:@/
		void dataAvailable();
		void sendNextMessage();
		void decimalResponse(QByteArray response);
		void unitResponse(QByteArray response);
		void svlResponse(QByteArray response);
		void svuResponse(QByteArray response);
		void requestMeasurement();
		void mResponse(QByteArray response);
		void ignore(QByteArray response);
	private:@/
		QextSerialPort *port;
		QByteArray responseBuffer;
		QList<QByteArray> messageQueue;
		QList<QObject *> retObjQueue;
		QList<char *> callbackQueue;
		quint16 calculateCRC(QByteArray data);
		QTimer *messageDelayTimer;
		int delayTime;
		char station;
		int decimalPosition;
		int valueF;
		int valueC;
		bool unitIsF;
		double outputSVLower;
		double outputSVUpper;
		QByteArray outputSVStub;
		QByteArray pvStub;
		QByteArray svStub;
		QByteArray mStub;
		quint16 pvaddress;
		quint16 svaddress;
		bool svenabled;
		bool readingsv;
		double savedpv;
		bool waiting;
};

@ The constructor reads its configuration from the configuration sub-tree of the
port node. This was adapted from a prototype implementation which used
|QSettings| to store this data. Note that this will only process the first
device specified on the port, the first process value on that device, and the
first set value on that device. A much more versatile architecture has been
planned for a future release which allows multiple devices per bus and
arbitrarily many monitored addresses per device. Communications are initiated
immediately upon construction.

@<ModbusRTUDevice implementation@>=
ModbusRTUDevice::ModbusRTUDevice(DeviceTreeModel *model, const QModelIndex &index)
: QObject(NULL), messageDelayTimer(new QTimer), unitIsF(true), readingsv(false),
	waiting(false)
{
	QDomElement portReferenceElement = model->referenceElement(model->data(index,
		Qt::UserRole).toString());
	QDomNodeList portConfigData = portReferenceElement.elementsByTagName("attribute");
	QDomElement node;
	QVariantMap attributes;
	for(int i = 0; i < portConfigData.size(); i++)
	{
		node = portConfigData.at(i).toElement();
		attributes.insert(node.attribute("name"), node.attribute("value"));
	}
	port = new QextSerialPort(attributes.value("port").toString(),
	                          QextSerialPort::EventDriven);
	int baudRate = attributes.value("baud").toInt();
	port->setBaudRate((BaudRateType)baudRate);
	double temp = ((double)(1) / (double)(baudRate)) * 48;
	delayTime = (int)(temp * 3000);
	messageDelayTimer->setSingleShot(true);
	connect(messageDelayTimer, SIGNAL(timeout()), this, SLOT(sendNextMessage()));
	port->setDataBits(DATA_8);
	port->setParity((ParityType)attributes.value("parity").toInt());
	port->setStopBits((StopBitsType)attributes.value("stop").toInt());
	port->setFlowControl((FlowType)attributes.value("flow").toInt());
	connect(port, SIGNAL(readyRead()), this, SLOT(dataAvailable()));
	port->open(QIODevice::ReadWrite);
	station = (char)attributes.value("station").toInt();
	if(attributes.value("decimalQuery") == "true")
	{
		decimalPosition = 0;
		QByteArray message;
		message.append(station);
		message.append((char)0x03);
		quint16 address = (quint16)attributes.value("decimalAddress").toInt();
		char *addressBytes = (char*)&address;
		message.append(addressBytes[1]);
		message.append(addressBytes[0]);
		message.append((char)0x00);
		message.append((char)0x01);
		queueMessage(message, this, "decimalResponse(QByteArray)");
	}
	else
	{
		decimalPosition = attributes.value("decimalPosition").toInt();
	}
	valueF = attributes.value("valueF").toInt();
	valueC = attributes.value("valueC").toInt();
	if(attributes.value("unitQuery") == "true")
	{
		QByteArray message;
		message.append(station);
		message.append((char)0x03);
		quint16 address = (quint16)attributes.value("unitAddress").toInt();
		char *addressBytes = (char*)&address;
		message.append(addressBytes[1]);
		message.append(addressBytes[0]);
		message.append((char)0x00);
		message.append((char)0x01);
		queueMessage(message, this, "unitResponse(QByteArray)");
	}
	else
	{
		if(attributes.value("fixedUnit") == "Celsius")
		{
			unitIsF = false;
		}
	}
	if(attributes.value("sVWritable") == "true")
	{
		if(attributes.value("deviceLimit") == "true")
		{
			QByteArray lmessage;
			lmessage.append(station);
			lmessage.append((char)0x03);
			quint16 laddress = (quint16)attributes.value("sVLowerAddr").toInt();
			char *addressBytes = (char*)&laddress;
			lmessage.append(addressBytes[1]);
			lmessage.append(addressBytes[0]);
			lmessage.append((char)0x00);
			lmessage.append((char)0x01);
			queueMessage(lmessage, this, "svlResponse(QByteArray)");
			QByteArray umessage;
			umessage.append(station);
			umessage.append((char)0x03);
			quint16 uaddress = (quint16)attributes.value("sVUpperAddr").toInt();
			addressBytes = (char*)&uaddress;
			umessage.append(addressBytes[1]);
			umessage.append(addressBytes[0]);
			umessage.append((char)0x00);
			umessage.append((char)0x01);
			queueMessage(umessage, this, "svuResponse(QByteArray)");
		}
		else
		{
			outputSVLower = attributes.value("sVLower").toDouble();
			outputSVUpper = attributes.value("sVUpper").toDouble();
		}
		outputSVStub.append(station);
		outputSVStub.append((char)0x06);
		quint16 address = (quint16)attributes.value("sVOutputAddr").toInt();
		char *addressBytes = (char*)&address;
		outputSVStub.append(addressBytes[1]);
		outputSVStub.append(addressBytes[0]);
	}
	Channel *pv = new Channel;
	channels.append(pv);
	pvStub.append(station);
	pvStub.append((char)0x04);
	pvaddress = (quint16)attributes.value("pVAddress").toInt();
	char *pvac = (char*)&pvaddress;
	pvStub.append(pvac[1]);
	pvStub.append(pvac[0]);
	pvStub.append((char)0x00);
	pvStub.append((char)0x01);
	svenabled = attributes.value("sVEnabled").toBool();
	if(svenabled)
	{
		Channel *sv = new Channel;
		channels.append(sv);
		svStub.append(station);
		svStub.append((char)0x04);
		svaddress = (quint16)attributes.value("sVReadAddress").toInt();
		char *svac = (char*)&svaddress;
		svStub.append(svac[1]);
		svStub.append(svac[0]);
		svStub.append((char)0x00);
		svStub.append((char)0x01);
		if(svaddress - pvaddress == 1)
		{
			mStub.append(station);
			mStub.append((char)0x04);
			mStub.append(pvac[1]);
			mStub.append(pvac[0]);
			mStub.append((char)0x00);
			mStub.append((char)0x02);
		}
	}
	connect(this, SIGNAL(queueEmpty()), this, SLOT(requestMeasurement()));
	requestMeasurement();
}

double ModbusRTUDevice::SVLower()
{
	return outputSVLower;
}

double ModbusRTUDevice::SVUpper()
{
	return outputSVUpper;
}

int ModbusRTUDevice::decimals()
{
	return decimalPosition;
}

void ModbusRTUDevice::decimalResponse(QByteArray response)
{
	quint16 temp;
	char *tchar = (char*)&temp;
	tchar[1] = response.at(3);
	tchar[0] = response.at(4);
	decimalPosition = temp;
	emit SVDecimalChanged(decimalPosition);
	qDebug() << "Received decimal response";
}

void ModbusRTUDevice::unitResponse(QByteArray response)
{
	quint16 temp;
	char *tchar = (char*)&temp;
	tchar[1] = response.at(3);
	tchar[0] = response.at(4);
	int value = temp;
	if(value == valueF)
	{
		unitIsF = true;
	}
	else
	{
		unitIsF = false;
	}
}

void ModbusRTUDevice::svlResponse(QByteArray response)
{
	quint16 temp;
	char *tchar = (char*)&temp;
	tchar[1] = response.at(3);
	tchar[0] = response.at(4);
	outputSVLower = (double)temp;
	for(int i = 0; i < decimalPosition; i++)
	{
		outputSVLower /= 10;
	}
	emit SVLowerChanged(outputSVLower);
}

void ModbusRTUDevice::svuResponse(QByteArray response)
{
	quint16 temp;
	char *tchar = (char*)&temp;
	tchar[1] = response.at(3);
	tchar[0] = response.at(4);
	outputSVUpper = (double)temp;
	for(int i = 0; i < decimalPosition; i++)
	{
		outputSVUpper /= 10;
	}
	emit SVUpperChanged(outputSVUpper);
}

void ModbusRTUDevice::requestMeasurement()
{
	if(mStub.length() > 0)
	{
		queueMessage(mStub, this, "mResponse(QByteArray)");
	}
	else
	{
		queueMessage(pvStub, this, "mResponse(QByteArray)");
		if(svenabled)
		{
			queueMessage(svStub, this, "mResponse(QByteArray)");
		}
	}
}

void ModbusRTUDevice::mResponse(QByteArray response)
{
	QTime time = QTime::currentTime();
	if(response.at(2) == 0x04)
	{
		@<Process PV and SV@>@;
	}
	else
	{
		@<Process PV or SV@>@;
	}
}

@ There are two ways that we might request measurement data. All of the
devices I've seen documented provide function 0x4 addresses for PV and SV
such that SV can be obtained from the address immediately after the address
from which we obtain PV. In this case we request both values at the same time.

@<Process PV and SV@>=
quint16 pv;
quint16 sv;
char *pvBytes = (char*)&pv;
char *svBytes = (char*)&sv;
pvBytes[1] = response.at(3);
pvBytes[0] = response.at(4);
svBytes[1] = response.at(5);
svBytes[0] = response.at(6);
double pvOut = (double)pv;
double svOut = (double)sv;
for(int i = 0; i < decimalPosition; i++)
{
	pvOut /= 10;
	svOut /= 10;
}
if(!unitIsF)
{
	pvOut = pvOut * 9 / 5 + 32;
	svOut = svOut * 9 / 5 + 32;
}
Measurement pvm(pvOut, time, Units::Fahrenheit);
Measurement svm(svOut, time, Units::Fahrenheit);
channels.at(0)->input(pvm);
channels.at(1)->input(svm);

@ When not measuring PV and SV at the same time, there are two possibilities.
One possibility is that SV is not enabled and we will only be reading from PV.
The other possibility is that we are alternating between reading PV and SV.

@<Process PV or SV@>=
quint16 value;
char *valueBytes = (char*)&value;
valueBytes[1] = response.at(3);
valueBytes[0] = response.at(4);
double valueOut = (double)value;
for(int i = 0; i < decimalPosition; i++)
{
	valueOut /= 10;
}
if(!unitIsF)
{
	valueOut = valueOut * 9 / 5 + 32;
}
if(!svenabled)
{
	Measurement vm(valueOut, time, Units::Fahrenheit);
	channels.at(0)->input(vm);
}
else
{
	if(readingsv)
	{
		Measurement pvm(savedpv, time, Units::Fahrenheit);
		Measurement svm(valueOut, time, Units::Fahrenheit);
		channels.at(0)->input(pvm);
		channels.at(1)->input(svm);
		readingsv = false;
	}
	else
	{
		savedpv = valueOut;
		readingsv = true;
	}
}

@ The destructor should close the port.

@<ModbusRTUDevice implementation@>=
ModbusRTUDevice::~ModbusRTUDevice()
{
	messageDelayTimer->stop();
	port->close();
}

@ When data is available it should be read into a buffer. The start of the
buffer should always be the start of a response and there should never be
more than one response in the buffer at a time. It is, however, likely that
this buffer will have incomplete data. This means that we must determine when
the full response is available before passing the complete response along to
the appropriate method. If the response has not been received in full, nothing
is done. We'll be notified of more data shortly.

When the message we see the response for was queued, a callback was also
registered to handle the response. Once we have the complete message, we pass
the response along to the callback that was registered for that message,
remove the message and callback information from the message queue, and start
a timer which will trigger sending the next message after a safe amount of
time has passed.

@<ModbusRTUDevice implementation@>=
void ModbusRTUDevice::dataAvailable()
{
	if(messageDelayTimer->isActive())
	{
		messageDelayTimer->stop();
	}
	responseBuffer.append(port->readAll());
	@<Check Modbus RTU message size@>@;
	if(calculateCRC(responseBuffer) == 0)
	{
		QObject *object = retObjQueue.at(0);
		char *method = callbackQueue.at(0);
		QMetaMethod metamethod = object->metaObject()->
			method(object->metaObject()->
				indexOfMethod(QMetaObject::normalizedSignature(method)));
		metamethod.invoke(object, Qt::QueuedConnection,
		                  Q_ARG(QByteArray, responseBuffer));
		messageQueue.removeAt(0);
		retObjQueue.removeAt(0);
		callbackQueue.removeAt(0);
		messageDelayTimer->start(delayTime);
	}
	else
	{
		qDebug() << "CRC failed";
	}
	waiting = false;
	responseBuffer.clear();
}

@ In Modbus RTU, a response message starts with one byte identifying the device
the message was sent from, one byte indicating the function, a variable number
of bytes with the response data, and two bytes used to verify that the response
was correctly received. In the event of a normal response, messages will be at
least six bytes long, but in the event of an error it is possible for a message
to be five bytes long.

Messages with a function number of 0x01 or 0x02 will be 6 bytes in length.
Messages with a function number of 0x03 or 0x04 will be at least 7 bytes in
length with the total length determined by the sum of 5 and the value in the
fifth byte. Messages with a function number of 0x05, 0x06, or 0x10 will be 8
bytes in length. Messages with a function number greater than 0x80 will be five
bytes in length.

@<Check Modbus RTU message size@>=
if(responseBuffer.size() < 5)
{
	return;
}
switch(responseBuffer.at(1))
{
	case 0x01:
	case 0x02:
		if(responseBuffer.size() < 6)
		{
			return;
		}
		responseBuffer = responseBuffer.left(6);
		break;
	case 0x03:
	case 0x04:
		if(responseBuffer.size() < 5 + responseBuffer.at(2))
		{
			return;
		}
		responseBuffer = responseBuffer.left(5 + responseBuffer.at(2));
		break;
	case 0x05:
	case 0x06:
	case 0x10:
		if(responseBuffer.size() < 8)
		{
			return;
		}
		responseBuffer = responseBuffer.left(8);
		break;
}

@ When sending and receiving messages, it is necessary to calculate a 16 bit
cyclic redundancy check code. The algorithm used to calculate this is specified
by the Modbus RTU protocol documentation. When sending a message, |data| should
be the message to send except for the CRC bytes which will be appended once
this method calculates them. When receiving a message, passing the complete
message back through this method should result in a return value of |0|. Any
other value indicates an error.

@<ModbusRTUDevice implementation@>=
quint16 ModbusRTUDevice::calculateCRC(QByteArray data)
{
	quint16 retval = 0xFFFF;
    int i = 0;
    while(i < data.size())
    {
        retval ^= 0x00FF & (quint16)data.at(i);
        for(int j = 0; j < 8; j++)
        {
            if(retval & 1)
            {
                retval = (retval >> 1) ^ 0xA001;
            }
            else
            {
                retval >>= 1;
            }
        }
        i++;
    }
    return retval;
}

@ When preparing an instance of ModbusRTUDevice, several messages may need to
be sent to the device in order to determine important details such as how
measurement data should be interpreted. During normal operation, messages
might be sent interactively between regular messages to acquire data. When
queueing a message, we also specify an object and method the response should be
sent to.

@<ModbusRTUDevice implementation@>=
void ModbusRTUDevice::queueMessage(QByteArray request, QObject *object,
                                   const char *callback)
{
	messageQueue.append(request);
	retObjQueue.append(object);
	callbackQueue.append(const_cast<char*>(callback));
	if(messageQueue.size() == 1 && !(messageDelayTimer->isActive()))
	{
		sendNextMessage();
	}
}

void ModbusRTUDevice::sendNextMessage()
{
	if(messageQueue.size() > 0 && !waiting)
	{
		QByteArray message = messageQueue.at(0);
		quint16 crc = calculateCRC(message);
		char *check = (char*)&crc;
		message.append(check[0]);
		message.append(check[1]);
		port->write(message);
		messageDelayTimer->start(delayTime);
		waiting = true;
	}
	else
	{
		emit queueEmpty();
	}
}

void ModbusRTUDevice::outputSV(double value)
{
	for(int i = 0; i < decimalPosition; i++)
	{
		value *= 10;
	}
	quint16 outval = (quint16)value;
	QByteArray message(outputSVStub);
	char *valBytes = (char*)&outval;
	message.append(valBytes[1]);
	message.append(valBytes[0]);
	queueMessage(message, this, "ignore(QByteArray)");
}

@ We don't care about the response when sending a new SV.

@<ModbusRTUDevice implementation@>=
void ModbusRTUDevice::ignore(QByteArray)
{
	return;
}

@ This class must be exposed to the host environment.

@<Function prototypes for scripting@>=
QScriptValue constructModbusRTUDevice(QScriptContext *context, QScriptEngine *engine);
QScriptValue ModbusRTUDevice_pVChannel(QScriptContext *context, QScriptEngine *engine);
QScriptValue ModbusRTUDevice_sVChannel(QScriptContext *context, QScriptEngine *engine);
void setModbusRTUDeviceProperties(QScriptValue value, QScriptEngine *engine);

@ The host environment is informed of the constructor.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructModbusRTUDevice);
value = engine->newQMetaObject(&ModbusRTUDevice::staticMetaObject, constructor);
engine->globalObject().setProperty("ModbusRTUDevice", value);

@ The constructor takes the configuration model and the index to the device of
interest as arguments rather than provide a large number of property setters to
handle initialization.

@<Functions for scripting@>=
QScriptValue constructModbusRTUDevice(QScriptContext *context, QScriptEngine *engine)
{
	QScriptValue object;
	if(context->argumentCount() == 2)
	{
		object = engine->newQObject(new ModbusRTUDevice(argument<DeviceTreeModel *>(0, context),
		                                                argument<QModelIndex>(1, context)),
									QScriptEngine::ScriptOwnership);
		setModbusRTUDeviceProperties(object, engine);
	}
	else
	{
		context->throwError("Incorrect number of arguments passed to "@|
			"ModbusRTUDevice constructor. This takes the configuration model "@|
			"and an index.");
	}
	return object;
}

@ The host environment needs a way to gain access to the channel objects.

@<Functions for scripting@>=
QScriptValue ModbusRTUDevice_pVChannel(QScriptContext *context, QScriptEngine *engine)
{
	ModbusRTUDevice *self = getself<ModbusRTUDevice *>(context);
	QScriptValue object;
	if(self)
	{
		if(self->channels.size() > 0)
		{
			object = engine->newQObject(self->channels.at(0));
			setChannelProperties(object, engine);
		}
	}
	return object;
}

QScriptValue ModbusRTUDevice_sVChannel(QScriptContext *context, QScriptEngine *engine)
{
	ModbusRTUDevice *self = getself<ModbusRTUDevice *>(context);
	QScriptValue object;
	if(self)
	{
		if(self->channels.size() > 1)
		{
			object = engine->newQObject(self->channels.at(1));
			setChannelProperties(object, engine);
		}
	}
	return object;
}

@ These methods are set as properties when the object is created.

@<Functions for scripting@>=
void setModbusRTUDeviceProperties(QScriptValue value, QScriptEngine *engine)
{
	setQObjectProperties(value, engine);
	value.setProperty("pVChannel", engine->newFunction(ModbusRTUDevice_pVChannel));
	value.setProperty("sVChannel", engine->newFunction(ModbusRTUDevice_sVChannel));
}

@* Modbus RTU device configuration widget.

\noindent This class was minimally adapted from a prototype implementation to
use the new configuration system introduced in \pn{} 1.4.

With all of the custom widgets for specifying a device configuration in place,
we can proceed to combine these in a form. As all of the options might use more
screen space than is available we make this scrollable. Some reorganization of
this will be done prior to release to enable the use of multiple devices on the
port which may obviate the need for this, but as there are those who prefer to
have a small screen it may be better to leave the scroll area in place even
after such a change.

@<Class declarations@>=
class ModbusConfigurator : public BasicDeviceConfigurationWidget
{
	@[Q_OBJECT@]
	public:@/
		Q_INVOKABLE ModbusConfigurator(DeviceTreeModel *model, const QModelIndex &index);
	@[private slots@]:@/
		void updatePort(const QString &newPort);
		void updateBaudRate(const QString &newRate);
		void updateParity(const QString &newParity);
		void updateFlowControl(const QString &newFlow);
		void updateStopBits(const QString &newStopBits);
		void updateStation(int station);
		void updateFixedDecimal(bool fixed);
		void updateDecimalAddress(int address);
		void updateDecimalPosition(int position);
		void updateFixedUnit(bool fixed);
		void updateUnitAddress(int address);
		void updateValueForF(int value);
		void updateValueForC(int value);
		void updateUnit(const QString &newUnit);
		void updatePVAddress(int address);
		void updateSVEnabled(bool enabled);
		void updateSVReadAddress(int address);
		void updateDeviceLimit(bool query);
		void updateSVLowerAddress(int address);
		void updateSVUpperAddress(int address);
		void updateSVLower(double value);
		void updateSVUpper(double value);
		void updateSVWritable(bool canWriteSV);
		void updateSVWriteAddress(int address);
		void updatePVColumnName(const QString &name);
		void updateSVColumnName(const QString &name);
	private:@/
		PortSelector *port;
		BaudSelector *baud;
		ParitySelector *parity;
		FlowSelector *flow;
		StopSelector *stop;
		QSpinBox *station;
		QCheckBox *decimalQuery;
		ShortHexSpinBox *decimalAddress;
		QSpinBox *decimalPosition;
		QCheckBox *unitQuery;
		ShortHexSpinBox *unitAddress;
		QSpinBox *valueF;
		QSpinBox *valueC;
		QComboBox *fixedUnit;
		ShortHexSpinBox *pVAddress;
		QCheckBox *sVEnabled;
		ShortHexSpinBox *sVReadAddress;
		QCheckBox *deviceLimit;
		ShortHexSpinBox *sVLowerAddr;
		ShortHexSpinBox *sVUpperAddr;
		QDoubleSpinBox *sVLower;
		QDoubleSpinBox *sVUpper;
		QCheckBox *sVWritable;
		ShortHexSpinBox *sVOutputAddr;
		QLineEdit *pVColumnName;
		QLineEdit *sVColumnName;
};

@ Implementation.

@<ModbusConfigurator implementation@>=
ModbusConfigurator::ModbusConfigurator(DeviceTreeModel *model, const QModelIndex &index)
: BasicDeviceConfigurationWidget(model, index),
	port(new PortSelector), baud(new BaudSelector), parity(new ParitySelector),
	flow(new FlowSelector), stop(new StopSelector), station(new QSpinBox),
	decimalQuery(new QCheckBox(tr("Enable"))),
	decimalAddress(new ShortHexSpinBox), decimalPosition(new QSpinBox),
	unitQuery(new QCheckBox(tr("Enable"))),
	unitAddress(new ShortHexSpinBox), valueF(new QSpinBox),
	valueC(new QSpinBox), fixedUnit(new QComboBox),
	pVAddress(new ShortHexSpinBox),
	sVEnabled(new QCheckBox(tr("Enable"))),
	sVReadAddress(new ShortHexSpinBox),
	deviceLimit(new QCheckBox(tr("Enable"))),
	sVLowerAddr(new ShortHexSpinBox), sVUpperAddr(new ShortHexSpinBox),
	sVLower(new QDoubleSpinBox), sVUpper(new QDoubleSpinBox),
	sVWritable(new QCheckBox(tr("Enable"))),
	sVOutputAddr(new ShortHexSpinBox),
	pVColumnName(new QLineEdit), sVColumnName(new QLineEdit)
{
	QHBoxLayout *layout = new QHBoxLayout;
	QWidget *form = new QWidget;
	QHBoxLayout *masterLayout = new QHBoxLayout;
	QVBoxLayout *portAndDeviceLayout = new QVBoxLayout;
	QVBoxLayout *seriesLayout = new QVBoxLayout;
	QFormLayout *serialSection = new QFormLayout;
	serialSection->addRow(QString(tr("Port:")), port);
	serialSection->addRow(QString(tr("Baud rate:")), baud);
	serialSection->addRow(QString(tr("Parity:")), parity);
	serialSection->addRow(QString(tr("Flow control:")), flow);
	serialSection->addRow(QString(tr("Stop bits:")), stop);
	QGroupBox *serialSectionBox = new QGroupBox(tr("Serial Port Configuration"));
	serialSectionBox->setLayout(serialSection);
	portAndDeviceLayout->addWidget(serialSectionBox);
	QFormLayout *deviceSection = new QFormLayout;
	station->setMinimum(1);
	station->setMaximum(255);
	decimalPosition->setMinimum(0);
	decimalPosition->setMaximum(9);
	valueF->setMinimum(0);
	valueF->setMaximum(0xFFFF);
	valueC->setMinimum(0);
	valueC->setMaximum(0xFFFF);
	fixedUnit->addItem(tr("Fahrenheit"), QVariant(QString("F")));
	fixedUnit->addItem(tr("Celsius"), QVariant(QString("C")));
	deviceSection->addRow(tr("Station:"), station);
	deviceSection->addRow(tr("Decimal position from device:"), decimalQuery);
	deviceSection->addRow(tr("Decimal position relative address:"), decimalAddress);
	deviceSection->addRow(tr("Fixed decimal position:"), decimalPosition);
	deviceSection->addRow(tr("Measurement unit from device:"), unitQuery);
	deviceSection->addRow(tr("Current unit relative address:"), unitAddress);
	deviceSection->addRow(tr("Value for Fahrenheit:"), valueF);
	deviceSection->addRow(tr("Value for Celsius:"), valueC);
	deviceSection->addRow(tr("Fixed unit:"), fixedUnit);
	QGroupBox *deviceSectionBox = new QGroupBox(tr("Device Configuration"));
	deviceSectionBox->setLayout(deviceSection);
	portAndDeviceLayout->addWidget(deviceSectionBox);
	QFormLayout *pVSection = new QFormLayout;
	pVSection->addRow(tr("Value relative address:"), pVAddress);
	pVSection->addRow(tr("PV column name:"), pVColumnName);
	QGroupBox *processValueBox = new QGroupBox(tr("Process Value"));
	processValueBox->setLayout(pVSection);
	seriesLayout->addWidget(processValueBox);
	QFormLayout *sVSection = new QFormLayout;
	sVLower->setDecimals(1);
	sVLower->setMinimum(0.0);
	sVLower->setMaximum(999.9);
	sVUpper->setDecimals(1);
	sVUpper->setMinimum(0.0);
	sVUpper->setMaximum(999.9);
	sVSection->addRow(tr("Set value:"), sVEnabled);
	sVSection->addRow(tr("Read relative address:"), sVReadAddress);
	sVSection->addRow(tr("SV column name:"), sVColumnName);
	sVSection->addRow(tr("Limits from device:"), deviceLimit);
	sVSection->addRow(tr("Lower limit relative address:"), sVLowerAddr);
	sVSection->addRow(tr("Upper limit relative address:"), sVUpperAddr);
	sVSection->addRow(tr("Lower limit:"), sVLower);
	sVSection->addRow(tr("Upper limit:"), sVUpper);
	sVSection->addRow(tr("Output set value:"), sVWritable);
	sVSection->addRow(tr("Output relative address:"), sVOutputAddr);
	QGroupBox *setValueBox = new QGroupBox(tr("Set Value"));
	setValueBox->setLayout(sVSection);
	seriesLayout->addWidget(setValueBox);
	masterLayout->addLayout(portAndDeviceLayout);
	masterLayout->addLayout(seriesLayout);
	form->setLayout(masterLayout);
	@<Get device configuration data for current node@>@;
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		if(node.attribute("name") == "port")
		{
			QString portname = node.attribute("value");
			int idx = port->findText(portname);
			if(idx >= 0)
			{
				port->setCurrentIndex(idx);
			}
			else
			{
				port->addItem(portname);
			}
		}
		else if(node.attribute("name") == "baud")
		{
			baud->setCurrentIndex(baud->findText(node.attribute("value")));
		}
		else if(node.attribute("name") == "parity")
		{
			parity->setCurrentIndex(parity->findData(node.attribute("value")));
		}
		else if(node.attribute("name") == "flow")
		{
			flow->setCurrentIndex(flow->findData(node.attribute("value")));
		}
		else if(node.attribute("name") == "stop")
		{
			stop->setCurrentIndex(stop->findData(node.attribute("value")));
		}
		else if(node.attribute("name") == "station")
		{
			station->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "decimalQuery")
		{
			if(node.attribute("value") == "true")
			{
				decimalQuery->setChecked(true);
			}
			else
			{
				decimalQuery->setChecked(false);
			}
		}
		else if(node.attribute("name") == "decimalAddress")
		{
			decimalAddress->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "decimalPosition")
		{
			decimalPosition->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "unitQuery")
		{
			if(node.attribute("value") == "true")
			{
				unitQuery->setChecked(true);
			}
			else
			{
				unitQuery->setChecked(false);
			}
		}
		else if(node.attribute("name") == "unitAddress")
		{
			unitAddress->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "valueF")
		{
			valueF->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "valueC")
		{
			valueC->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "fixedUnit")
		{
			fixedUnit->setCurrentIndex(fixedUnit->findText(node.attribute("value")));
		}
		else if(node.attribute("name") == "pVAddress")
		{
			pVAddress->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "sVEnabled")
		{
			if(node.attribute("value") == "true")
			{
				sVEnabled->setChecked(true);
			}
			else
			{
				sVEnabled->setChecked(false);
			}
		}
		else if(node.attribute("name") == "sVReadAddress")
		{
			sVReadAddress->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "deviceLimit")
		{
			if(node.attribute("value") == "true")
			{
				deviceLimit->setChecked(true);
			}
			else
			{
				deviceLimit->setChecked(false);
			}
		}
		else if(node.attribute("name") == "sVLowerAddr")
		{
			sVLowerAddr->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "sVUpperAddr")
		{
			sVUpperAddr->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "sVLower")
		{
			sVLower->setValue(node.attribute("value").toDouble());
		}
		else if(node.attribute("name") == "sVUpper")
		{
			sVUpper->setValue(node.attribute("value").toDouble());
		}
		else if(node.attribute("name") == "sVWritable")
		{
			if(node.attribute("value") == "true")
			{
				sVWritable->setChecked(true);
			}
			else
			{
				sVWritable->setChecked(false);
			}
		}
		else if(node.attribute("name") == "sVOutputAddr")
		{
			sVOutputAddr->setValue(node.attribute("value").toInt());
		}
		else if(node.attribute("name") == "pvcolname")
		{
			pVColumnName->setText(node.attribute("value"));
		}
		else if(node.attribute("name") == "svcolname")
		{
			sVColumnName->setText(node.attribute("value"));
		}
	}
	updatePort(port->currentText());
	updateBaudRate(baud->currentText());
	updateParity(parity->itemData(parity->currentIndex()).toString());
	updateFlowControl(flow->itemData(flow->currentIndex()).toString());
	updateStopBits(stop->itemData(stop->currentIndex()).toString());
	updateStation(station->value());
	updateFixedDecimal(decimalQuery->isChecked());
	updateDecimalAddress(decimalAddress->value());
	updateDecimalPosition(decimalPosition->value());
	updateFixedUnit(unitQuery->isChecked());
	updateUnitAddress(unitAddress->value());
	updateValueForF(valueF->value());
	updateValueForC(valueC->value());
	updateUnit(fixedUnit->currentText());
	updatePVAddress(pVAddress->value());
	updateSVEnabled(sVEnabled->isChecked());
	updateSVReadAddress(sVReadAddress->value());
	updateDeviceLimit(deviceLimit->isChecked());
	updateSVLowerAddress(sVLowerAddr->value());
	updateSVUpperAddress(sVUpperAddr->value());
	updateSVLower(sVLower->value());
	updateSVUpper(sVUpper->value());
	updateSVWritable(sVWritable->isChecked());
	updateSVWriteAddress(sVOutputAddr->value());
	updatePVColumnName(pVColumnName->text());
	updateSVColumnName(sVColumnName->text());
	connect(port, SIGNAL(currentIndexChanged(QString)), this, SLOT(updatePort(QString)));
	connect(port, SIGNAL(editTextChanged(QString)), this, SLOT(updatePort(QString)));
	connect(baud, SIGNAL(currentIndexChanged(QString)), this, SLOT(updateBaudRate(QString)));
	connect(parity, SIGNAL(currentIndexChanged(QString)), this, SLOT(updateParity(QString)));
	connect(flow, SIGNAL(currentIndexChanged(QString)), this, SLOT(updateFlowControl(QString)));
	connect(stop, SIGNAL(currentIndexChanged(QString)), this, SLOT(updateStopBits(QString)));
	connect(station, SIGNAL(valueChanged(int)), this, SLOT(updateStation(int)));
	connect(decimalQuery, SIGNAL(toggled(bool)), this, SLOT(updateFixedDecimal(bool)));
	connect(decimalAddress, SIGNAL(valueChanged(int)), this, SLOT(updateDecimalAddress(int)));
	connect(decimalPosition, SIGNAL(valueChanged(int)), this, SLOT(updateDecimalPosition(int)));
	connect(unitQuery, SIGNAL(toggled(bool)), this, SLOT(updateFixedUnit(bool)));
	connect(unitAddress, SIGNAL(valueChanged(int)), this, SLOT(updateUnitAddress(int)));
	connect(valueF, SIGNAL(valueChanged(int)), this, SLOT(updateValueForF(int)));
	connect(valueC, SIGNAL(valueChanged(int)), this, SLOT(updateValueForC(int)));
	connect(fixedUnit, SIGNAL(currentIndexChanged(QString)), this, SLOT(updateUnit(QString)));
	connect(pVAddress, SIGNAL(valueChanged(int)), this, SLOT(updatePVAddress(int)));
	connect(sVEnabled, SIGNAL(toggled(bool)), this, SLOT(updateSVEnabled(bool)));
	connect(sVReadAddress, SIGNAL(valueChanged(int)), this, SLOT(updateSVReadAddress(int)));
	connect(deviceLimit, SIGNAL(toggled(bool)), this, SLOT(updateDeviceLimit(bool)));
	connect(sVLowerAddr, SIGNAL(valueChanged(int)), this, SLOT(updateSVLowerAddress(int)));
	connect(sVUpperAddr, SIGNAL(valueChanged(int)), this, SLOT(updateSVUpperAddress(int)));
	connect(sVLower, SIGNAL(valueChanged(double)), this, SLOT(updateSVLower(double)));
	connect(sVUpper, SIGNAL(valueChanged(double)), this, SLOT(updateSVUpper(double)));
	connect(sVWritable, SIGNAL(toggled(bool)), this, SLOT(updateSVWritable(bool)));
	connect(sVOutputAddr, SIGNAL(valueChanged(int)), this, SLOT(updateSVWriteAddress(int)));
	connect(pVColumnName, SIGNAL(textEdited(QString)), this, SLOT(updatePVColumnName(QString)));
	connect(sVColumnName, SIGNAL(textEdited(QString)), this, SLOT(updateSVColumnName(QString)));
	layout->addWidget(form);
	setLayout(layout);
}

void ModbusConfigurator::updatePort(const QString &newPort)
{
	updateAttribute("port", newPort);
}

void ModbusConfigurator::updateBaudRate(const QString &newRate)
{
	updateAttribute("baud", newRate);
}

void ModbusConfigurator::updateParity(const QString &)
{
	updateAttribute("parity", parity->itemData(parity->currentIndex()).toString());
}

void ModbusConfigurator::updateFlowControl(const QString &)
{
	updateAttribute("flow", flow->itemData(flow->currentIndex()).toString());
}

void ModbusConfigurator::updateStopBits(const QString &)
{
	updateAttribute("stop", stop->itemData(stop->currentIndex()).toString());
}

void ModbusConfigurator::updateStation(int station)
{
	updateAttribute("station", QString("%1").arg(station));
}

void ModbusConfigurator::updateFixedDecimal(bool fixed)
{
	updateAttribute("decimalQuery", fixed ? "true" : "false");
}

void ModbusConfigurator::updateDecimalAddress(int address)
{
	updateAttribute("decimalAddress", QString("%1").arg(address));
}

void ModbusConfigurator::updateDecimalPosition(int position)
{
	updateAttribute("decimalPosition", QString("%1").arg(position));
}

void ModbusConfigurator::updateFixedUnit(bool fixed)
{
	updateAttribute("unitQuery", fixed ? "true" : "false");
}

void ModbusConfigurator::updateUnitAddress(int address)
{
	updateAttribute("unitAddress", QString("%1").arg(address));
}

void ModbusConfigurator::updateValueForF(int value)
{
	updateAttribute("valueF", QString("%1").arg(value));
}

void ModbusConfigurator::updateValueForC(int value)
{
	updateAttribute("valueC", QString("%1").arg(value));
}

void ModbusConfigurator::updateUnit(const QString &newUnit)
{
	updateAttribute("fixedUnit", newUnit);
}

void ModbusConfigurator::updatePVAddress(int address)
{
	updateAttribute("pVAddress", QString("%1").arg(address));
}

void ModbusConfigurator::updateSVEnabled(bool enabled)
{
	updateAttribute("sVEnabled", enabled ? "true" : "false");
}

void ModbusConfigurator::updateSVReadAddress(int address)
{
	updateAttribute("sVReadAddress", QString("%1").arg(address));
}

void ModbusConfigurator::updateDeviceLimit(bool query)
{
	updateAttribute("deviceLimit", query ? "true" : "false");
}

void ModbusConfigurator::updateSVLowerAddress(int address)
{
	updateAttribute("sVLowerAddr", QString("%1").arg(address));
}

void ModbusConfigurator::updateSVUpperAddress(int address)
{
	updateAttribute("sVUpperAddr", QString("%1").arg(address));
}

void ModbusConfigurator::updateSVLower(double value)
{
	updateAttribute("sVLower", QString("%1").arg(value));
}

void ModbusConfigurator::updateSVUpper(double value)
{
	updateAttribute("sVUpper", QString("%1").arg(value));
}

void ModbusConfigurator::updateSVWritable(bool canWriteSV)
{
	updateAttribute("sVWritable", canWriteSV ? "true" : "false");
}

void ModbusConfigurator::updateSVWriteAddress(int address)
{
	updateAttribute("sVOutputAddr", QString("%1").arg(address));
}

void ModbusConfigurator::updatePVColumnName(const QString &name)
{
	updateAttribute("pvcolname", name);
}

void ModbusConfigurator::updateSVColumnName(const QString &name)
{
	updateAttribute("svcolname", name);
}

@ This is registered with the configuration system.

@<Register device configuration widgets@>=
app.registerDeviceConfigurationWidget("modbusrtu", ModbusConfigurator::staticMetaObject);

@ A |NodeInserter| for the driver configuration widget is also needed.

@<Register top level device configuration nodes@>=
inserter = new NodeInserter(tr("Modbus RTU Device"), tr("Modbus RTU Device"), "modbusrtu", NULL);
topLevelNodeInserters.append(inserter);

@* Configuration widget for a calibrated data series.

\noindent This control is used for adding a |LinearSplineInterpolator| to the
logging view.

@<Class declarations@>=
class LinearSplineInterpolationConfWidget : public BasicDeviceConfigurationWidget
{
	@[Q_OBJECT@]@/
	public:@/
		@[Q_INVOKABLE@]@, LinearSplineInterpolationConfWidget(DeviceTreeModel *model,
		                                                      const QModelIndex &index);
	@[private slots@]:@/
		void updateSourceColumn(const QString &source);
		void updateDestinationColumn(const QString &dest);
		void updateKnots();
	private:@/
		SaltModel *knotmodel;
};

@ This is configured by specifying a source column name, a destination column
name, and a two column table. Note that while we only have one widget handling
the mapping data, we store each column of the table in its own attribute.

@<LinearSplineInterpolationConfWidget implementation@>=
LinearSplineInterpolationConfWidget::LinearSplineInterpolationConfWidget(DeviceTreeModel *model, const QModelIndex &index)
: BasicDeviceConfigurationWidget(model, index), knotmodel(new SaltModel(2))
{
	QFormLayout *layout = new QFormLayout;
	QLineEdit *source = new QLineEdit;
	layout->addRow(tr("Source column name:"), source);
	QLineEdit *destination = new QLineEdit;
	layout->addRow(tr("Destination column name:"), destination);
	knotmodel->setHeaderData(0, Qt::Horizontal, "Input");
	knotmodel->setHeaderData(1, Qt::Horizontal, "Output");
	QTableView *mappingTable = new QTableView;
	mappingTable->setModel(knotmodel);
	NumericDelegate *delegate = new NumericDelegate;
	mappingTable->setItemDelegate(delegate);
	layout->addRow(tr("Mapping data:"), mappingTable);
	@<Get device configuration data for current node@>@;
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		if(node.attribute("name") == "source")
		{
			source->setText(node.attribute("value"));
		}
		else if(node.attribute("name") == "destination")
		{
			destination->setText(node.attribute("value"));
		}
		else if(node.attribute("name") == "sourcevalues")
		{
			@<Convert numeric array literal to list@>@;
			int column = 0;
			@<Populate model column from list@>@;

		}
		else if(node.attribute("name") == "destinationvalues")
		{
			@<Convert numeric array literal to list@>@;
			int column = 1;
			@<Populate model column from list@>@;
		}
	}
	updateSourceColumn(source->text());
	updateDestinationColumn(destination->text());
	updateKnots();
	connect(source, SIGNAL(textEdited(QString)), this, SLOT(updateSourceColumn(QString)));
	connect(destination, SIGNAL(textEdited(QString)), this, SLOT(updateDestinationColumn(QString)));
	connect(knotmodel, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(updateKnots()));
	setLayout(layout);
}

@ The saved data will have come from a previous call to
|SaltModel::arrayLiteral()| to repopulate the model we need to strip off the
the start and end of the strings and split them back into separate elements.

@<Convert numeric array literal to list@>=
QString data = node.attribute("value");
if(data.length() > 3)
{
	data.chop(2);
	data = data.remove(0, 2);
}
QStringList itemList = data.split(",");

@ Once the saved string has been split, the values can be inserted into the
model.

@<Populate model column from list@>=
for(int i = 0; i < itemList.size(); i++)
{
	knotmodel->setData(knotmodel->index(i, column),
	                   QVariant(itemList.at(i).toDouble()),
                       Qt::DisplayRole);
}

@ When data in the table is changed we simply overwrite any previously saved
data with the current data.

@<LinearSplineInterpolationConfWidget implementation@>=
void LinearSplineInterpolationConfWidget::updateKnots()
{
	updateAttribute("sourcevalues", knotmodel->arrayLiteral(0, Qt::DisplayRole));
	updateAttribute("destinationvalues", knotmodel->arrayLiteral(1, Qt::DisplayRole));
}

void LinearSplineInterpolationConfWidget::updateSourceColumn(const QString &source)
{
	updateAttribute("source", source);
}

void LinearSplineInterpolationConfWidget::updateDestinationColumn(const QString &dest)
{
	updateAttribute("destination", dest);
}

@ The widget is registered with the configuration system.

@<Register device configuration widgets@>=
app.registerDeviceConfigurationWidget("linearspline", LinearSplineInterpolationConfWidget::staticMetaObject);

@* Profile Translation Configuration Widget.

\noindent Configuring profile translation requires knowing which column to use
for matching purposes and the value to match.

@<Class declarations@>=
class TranslationConfWidget : public BasicDeviceConfigurationWidget
{
	@[Q_OBJECT@]@;
	public:@/
		@[Q_INVOKABLE@]@, TranslationConfWidget(DeviceTreeModel *model, const QModelIndex &index);
	@[private slots@]:@/
		void updateMatchingColumn(const QString &column);
		void updateTemperature();
	private:@/
		QDoubleSpinBox *temperatureValue;
		QComboBox *unitSelector;
};

@ The constructor sets up our user interface.

@<TranslationConfWidget implementation@>=
TranslationConfWidget::TranslationConfWidget(DeviceTreeModel *model, const QModelIndex &index)
: BasicDeviceConfigurationWidget(model, index),
	temperatureValue(new QDoubleSpinBox), unitSelector(new QComboBox)
{
	unitSelector->addItem("Fahrenheit");
	unitSelector->addItem("Celsius");
	temperatureValue->setMinimum(0);
	temperatureValue->setMaximum(1000);
	QFormLayout *layout = new QFormLayout;
	QLineEdit *column = new QLineEdit;
	layout->addRow(tr("Column to match:"), column);
	layout->addRow(tr("Unit:"), unitSelector);
	layout->addRow(tr("Value:"), temperatureValue);
	@<Get device configuration data for current node@>@;
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		if(node.attribute("name") == "column")
		{
			column->setText(node.attribute("value"));
		}
		else if(node.attribute("name") == "unit")
		{
			unitSelector->setCurrentIndex(unitSelector->findText(node.attribute("value")));
		}
		else if(node.attribute("name") == "value")
		{
			temperatureValue->setValue(node.attribute("value").toDouble());
		}
	}
	updateMatchingColumn(column->text());
	updateTemperature();
	connect(column, SIGNAL(textEdited(QString)), this, SLOT(updateMatchingColumn(QString)));
	connect(unitSelector, SIGNAL(currentIndexChanged(QString)), this, SLOT(updateTemperature()));
	connect(temperatureValue, SIGNAL(valueChanged(double)), this, SLOT(updateTemperature()));
	setLayout(layout);
}

@ To update the temperature at which to match we save both the values of the
two widgets which control this and the value in Fahrenheit so we don'@q'@>t need to
run unit conversions during view initialization.

@<TranslationConfWidget implementation@>=
void TranslationConfWidget::updateTemperature()
{
	updateAttribute("unit", unitSelector->currentText());
	updateAttribute("value", QString("%1").arg(temperatureValue->value()));
	if(unitSelector->currentText() == "Fahrenheit")
	{
		updateAttribute("FValue", QString("%1").arg(temperatureValue->value()));
	}
	else
	{
		updateAttribute("FValue", QString("%1").arg(temperatureValue->value() * 9 / 5 + 32));
	}
}

void TranslationConfWidget::updateMatchingColumn(const QString &column)
{
	updateAttribute("column", column);
}

@ This is registered with the configuration system.

@<Register device configuration widgets@>=
app.registerDeviceConfigurationWidget("translation", TranslationConfWidget::staticMetaObject);

@i rate.w

@i dataqsdk.w

@i scales.w

@** Local changes.

\noindent This is the end of \pn{} as distributed by its author. It is expected
that some might have need of a program like \pn, but require some modification.
The patching capabilities of \cweb{} can be used to produce these local
modifications. This section is provided for those whose change requirements are
sufficiently extensive to require the introduction of new sections to the
program.

@** Index.

\noindent Following is a list of identifiers used in \pn, with underlined
entries pointing to where \cweb{} has guessed that the identifier was defined.
All references are to section numbers instead of page numbers.

\def\nullsec{--}
