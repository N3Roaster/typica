/*182:*/
#line 36 "./helpmenu.w"

#include "helpmenu.h"
#include "abouttypica.h"
#include "feedback.h"

/*183:*/
#line 49 "./helpmenu.w"

HelpMenu::HelpMenu():QMenu()
{
setObjectName("helpMenu");
setTitle(tr("Help"));
QAction*aboutTypicaAction= new QAction(tr("About Typica"),this);
aboutTypicaAction->setObjectName("aboutTypicaAction");
addAction(aboutTypicaAction);
connect(aboutTypicaAction,SIGNAL(triggered()),this,SLOT(displayAboutTypica()));
QAction*sendFeedbackAction= new QAction(tr("Send Feedback"),this);
sendFeedbackAction->setObjectName("sendFeedback");
addAction(sendFeedbackAction);
connect(sendFeedbackAction,SIGNAL(triggered()),this,SLOT(displayFeedbackWizard()));
}

/*:183*//*184:*/
#line 67 "./helpmenu.w"

void HelpMenu::displayAboutTypica()
{
AboutTypica*aboutBox= new AboutTypica;
aboutBox->show();
}

/*:184*//*185:*/
#line 76 "./helpmenu.w"

void HelpMenu::displayFeedbackWizard()
{
FeedbackWizard*window= new FeedbackWizard;
window->show();
}

#line 4266 "./typica.w"

#line 1 "./feedback.w"
/*:185*/
#line 41 "./helpmenu.w"


/*:182*/
