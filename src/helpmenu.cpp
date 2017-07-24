/*207:*/
#line 36 "./helpmenu.w"

#include "helpmenu.h"
#include "abouttypica.h"
#include "licensewindow.h"

/*208:*/
#line 46 "./helpmenu.w"

HelpMenu::HelpMenu():QMenu()
{
setObjectName("helpMenu");
setTitle(tr("Help"));
QAction*aboutTypicaAction= new QAction(tr("About Typica"),this);
aboutTypicaAction->setObjectName("aboutTypicaAction");
addAction(aboutTypicaAction);
connect(aboutTypicaAction,SIGNAL(triggered()),this,SLOT(displayAboutTypica()));
#if 0
QAction*licenseAction= new QAction(tr("License Information"),this);
licenseAction->setObjectName("licenseAction");
addAction(licenseAction);
connect(licenseAction,SIGNAL(triggered()),this,SLOT(displayLicenseWindow()));
#endif
}

/*:208*//*209:*/
#line 66 "./helpmenu.w"

void HelpMenu::displayAboutTypica()
{
AboutTypica*aboutBox= new AboutTypica;
aboutBox->show();
}

/*:209*//*210:*/
#line 76 "./helpmenu.w"

void HelpMenu::displayLicenseWindow()
{
LicenseWindow*window= new LicenseWindow;
window->show();
}

#line 4826 "./typica.w"

#line 1 "./licensewindow.w"
/*:210*/
#line 41 "./helpmenu.w"


/*:207*/
