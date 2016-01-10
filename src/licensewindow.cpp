/*209:*/
#line 36 "./licensewindow.w"

/*213:*/
#line 97 "./licensewindow.w"

#include "licensewindow.h"

#include <QSplitter> 
#include <QListWidget> 
#include <QVariant> 
#include <QUrl> 

#line 4773 "./typica.w"

/*:213*/
#line 37 "./licensewindow.w"

/*210:*/
#line 43 "./licensewindow.w"

LicenseWindow::LicenseWindow()
:QMainWindow(NULL),view(new QWebView)
{
QSplitter*split= new QSplitter;
QListWidget*projects= new QListWidget;

/*212:*/
#line 79 "./licensewindow.w"

QListWidgetItem*item= new QListWidgetItem("Typica",projects);
item->setData(Qt::UserRole,QVariant(QUrl("qrc:/resources/html/licenses/typica.html")));
projects->setCurrentItem(item);
setWebView(item,NULL);
item= new QListWidgetItem("d3.js",projects);
item->setData(Qt::UserRole,QVariant(QUrl("qrc:/resources/html/licenses/d3.html")));
item= new QListWidgetItem("Entypo",projects);
item->setData(Qt::UserRole,QVariant(QUrl("qrc:/resources/html/licenses/entypo.html")));
item= new QListWidgetItem("Tango Desktop Project",projects);
item->setData(Qt::UserRole,QVariant(QUrl("qrc:/resources/html/licenses/tango.html")));
item= new QListWidgetItem("QextSerialPort",projects);
item->setData(Qt::UserRole,QVariant(QUrl("qrc:/resources/html/licenses/qextserialport.html")));
item= new QListWidgetItem("Qt",projects);
item->setData(Qt::UserRole,QVariant(QUrl("qrc:/resources/html/licenses/qt.html")));

/*:212*/
#line 50 "./licensewindow.w"

connect(projects,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
this,SLOT(setWebView(QListWidgetItem*,QListWidgetItem*)));

split->addWidget(projects);
split->addWidget(view);
setCentralWidget(split);
}

/*:210*//*211:*/
#line 64 "./licensewindow.w"

void LicenseWindow::setWebView(QListWidgetItem*current,QListWidgetItem*)
{
view->load(current->data(Qt::UserRole).toUrl());
}

/*:211*/
#line 38 "./licensewindow.w"


/*:209*/
