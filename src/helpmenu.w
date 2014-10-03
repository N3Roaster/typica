@* The Help Menu.

\noindent Every window has a help menu that is inserted at the end of any
configuration defined menus. At present this only serves to have a place to
hold the "About Typica" menu item which brings up an appropriate about box, but
there is the possibility that future developments will introduce other items
that should be included in this menu.

@<Insert help menu@>=
HelpMenu *helpMenu = new HelpMenu();
window->menuBar()->addMenu(helpMenu);

@ Since the help menu is represented by its own class, we must have a
declaration for that class. This is a trivial case.

@(helpmenu.h@>=
#include <QMenu>

#ifndef HelpMenuHeader
#define HelpMenuHeader

class HelpMenu : public QMenu
{
	Q_OBJECT
	public:
		HelpMenu();
	public slots:
		void displayAboutTypica();
		void displayFeedbackWizard();
};

#endif

@ Implementation is in a separate file.

@(helpmenu.cpp@>=
#include "helpmenu.h"
#include "abouttypica.h"
#include "feedback.h"

@<Help menu implementation@>@;

@ The constructor sets an object name for the menu so scripts are able to look
up the menu and add additional items. The "About Typica" menu item also has an
object name which can be used to provide custom handling if this is desired.
The |triggered()| signal from that item is immediately connected to a handler
for displaying an about box.

@<Help menu implementation@>=
HelpMenu::HelpMenu() : QMenu()
{
	setObjectName("helpMenu");
	setTitle(tr("Help"));
	QAction *aboutTypicaAction = new QAction(tr("About Typica"), this);
	aboutTypicaAction->setObjectName("aboutTypicaAction");
	addAction(aboutTypicaAction);
	connect(aboutTypicaAction, SIGNAL(triggered()), this, SLOT(displayAboutTypica()));
	QAction *sendFeedbackAction = new QAction(tr("Send Feedback"), this);
	sendFeedbackAction->setObjectName("sendFeedback");
	addAction(sendFeedbackAction);
	connect(sendFeedbackAction, SIGNAL(triggered()), this, SLOT(displayFeedbackWizard()));
}

@ When "About Typica" is selected from the menu, we display an about box. This
is also handled by a separate class.

@<Help menu implementation@>=
void HelpMenu::displayAboutTypica()
{
	AboutTypica *aboutBox = new AboutTypica;
	aboutBox->show();
}

@ A feedback wizard is also available from the Help menu.

@<Help menu implementation@>=
void HelpMenu::displayFeedbackWizard()
{
	FeedbackWizard *window = new FeedbackWizard;
	window->show();
}

