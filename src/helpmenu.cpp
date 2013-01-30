/*167:*/
#line 35 "./helpmenu.w"

#include "helpmenu.h"
#include "abouttypica.h"

/*168:*/
#line 47 "./helpmenu.w"

HelpMenu::HelpMenu():QMenu()
{
setObjectName("helpMenu");
setTitle(tr("Help"));
QAction*aboutTypicaAction= new QAction(tr("About Typica"),this);
aboutTypicaAction->setObjectName("aboutTypicaAction");
addAction(aboutTypicaAction);
connect(aboutTypicaAction,SIGNAL(triggered()),this,SLOT(displayAboutTypica()));
}

/*:168*//*169:*/
#line 61 "./helpmenu.w"

void HelpMenu::displayAboutTypica()
{
AboutTypica*aboutBox= new AboutTypica;
aboutBox->show();
}

#line 4031 "./typica.w"

/*:169*/
#line 39 "./helpmenu.w"


/*:167*/
