/*204:*/
#line 36 "./helpmenu.w"

#include "helpmenu.h"
#include "abouttypica.h"
#include "licensewindow.h"

/*205:*/
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

/*:205*//*206:*/
#line 66 "./helpmenu.w"

void HelpMenu::displayAboutTypica()
{
AboutTypica*aboutBox= new AboutTypica;
aboutBox->show();
}

/*:206*//*207:*/
#line 76 "./helpmenu.w"

void HelpMenu::displayLicenseWindow()
{
LicenseWindow*window= new LicenseWindow;
window->show();
}

#line 4771 "./typica.w"

#line 1 "./licensewindow.w"
/*:207*/
#line 41 "./helpmenu.w"


/*:204*/
