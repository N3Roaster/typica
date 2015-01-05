@* Presenting License Information.

\noindent Typica has its own copyright and license information, but it also
relies on other projects which have their own copyright and license information
which must be preserved, but it is better to present this information in a way
that someone interested can quickly examine the license of any particular work.

I would like to present this as a two panel window where the left side contains a
list of the various projects and the right side contains a web view. Clicking
an item in the list on the left should bring up the appropriate license
document on the right.

@(licensewindow.h@>=
#include <QMainWindow>
#include <QListWidgetItem>
#include <QWebView>

#ifndef TypicaLicenseHeader
#define TypicaLicenseHeader

class LicenseWindow : public QMainWindow@/
{
	@[Q_OBJECT@]@;
	public:@/
		LicenseWindow();
	@[private slots@]:@/
		void setWebView(QListWidgetItem *current, QListWidgetItem *);
	private:@/
		QWebView *view;
};

#endif

@ Implementation is in a separate file.

@(licensewindow.cpp@>=
@<License window headers@>@;
@<License window implementation@>@;

@ The constructor is responsible for setting up the structure of the window and
setting its initial content.

@<License window implementation@>=
LicenseWindow::LicenseWindow()
	: QMainWindow(NULL), view(new QWebView)
{
	QSplitter *split = new QSplitter;
	QListWidget *projects = new QListWidget;

	@<Add items to license list@>@;
	connect(projects, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
            this, SLOT(setWebView(QListWidgetItem*, QListWidgetItem*)));

	split->addWidget(projects);
	split->addWidget(view);
	setCentralWidget(split);
}

@ Each item in the |projects| list contains a |QUrl| pointing to an HTML
document in the resources compiled in with \pn{}. When an item in the list is
selected, the appropriate document is loaded in the web view. The previously
selected item is unused.

@<License window implementation@>=
void LicenseWindow::setWebView(QListWidgetItem *current, QListWidgetItem *)
{
	view->load(current->data(Qt::UserRole).toUrl());
}

@ Each item in the list provides the name of the project to display in the list
and the location of the relevant license. This section must be updated any time
the external projects used changes. At present only projects which are used
directly by \pn{} are included here but it would not be a bad idea to audit
projects that are used indirectly and include these as well. The item with
the license for \pn{} is the initial selection and the web view is set
appropriately here as the |currentItemChanged| signal is not connected until
after this code executes.

@<Add items to license list@>=
QListWidgetItem *item = new QListWidgetItem("Typica", projects);
item->setData(Qt::UserRole, QVariant(QUrl("qrc:/resources/html/licenses/typica.html")));
projects->setCurrentItem(item);
setWebView(item, NULL);
item = new QListWidgetItem("d3.js", projects);
item->setData(Qt::UserRole, QVariant(QUrl("qrc:/resources/html/licenses/d3.html")));
item = new QListWidgetItem("Entypo", projects);
item->setData(Qt::UserRole, QVariant(QUrl("qrc:/resources/html/licenses/entypo.html")));
item = new QListWidgetItem("Tango Desktop Project", projects);
item->setData(Qt::UserRole, QVariant(QUrl("qrc:/resources/html/licenses/tango.html")));
item = new QListWidgetItem("QextSerialPort", projects);
item->setData(Qt::UserRole, QVariant(QUrl("qrc:/resources/html/licenses/qextserialport.html")));
item = new QListWidgetItem("Qt", projects);
item->setData(Qt::UserRole, QVariant(QUrl("qrc:/resources/html/licenses/qt.html")));

@ Several headers are required.

@<License window headers@>=
#include "licensewindow.h"

#include <QSplitter>
#include <QListWidget>
#include <QVariant>
#include <QUrl>

