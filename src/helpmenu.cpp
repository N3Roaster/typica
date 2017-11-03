/*208:*/
#line 36 "./helpmenu.w"

#include "helpmenu.h"
#include "abouttypica.h"
#include "licensewindow.h"

/*209:*/
#line 46 "./helpmenu.w"

HelpMenu::HelpMenu():QMenu()
{
setObjectName("helpMenu");
setTitle(tr("Help"));
QAction*aboutTypicaAction= new QAction(tr("About Typica"),this);
aboutTypicaAction->setObjectName("aboutTypicaAction");
addAction(aboutTypicaAction);
connect(aboutTypicaAction,SIGNAL(triggered()),this,SLOT(displayAboutTypica()));

QAction*licenseAction= new QAction(tr("License Information"),this);
licenseAction->setObjectName("licenseAction");
addAction(licenseAction);
connect(licenseAction,SIGNAL(triggered()),this,SLOT(displayLicenseWindow()));

}

/*:209*//*210:*/
#line 66 "./helpmenu.w"

void HelpMenu::displayAboutTypica()
{
AboutTypica*aboutBox= new AboutTypica;
aboutBox->show();
}

/*:210*//*211:*/
#line 76 "./helpmenu.w"

void HelpMenu::displayLicenseWindow()
{
LicenseWindow*window= new LicenseWindow;
window->show();
}

#line 4895 "./typica.w"

#line 1 "./licensewindow.w"
/*:211*/
#line 41 "./helpmenu.w"


/*:208*/
