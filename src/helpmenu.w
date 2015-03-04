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
		void displayLicenseWindow();
};

#endif

@ Implementation is in a separate file.

@(helpmenu.cpp@>=
#include "helpmenu.h"
#include "abouttypica.h"
#include "licensewindow.h"

@<Help menu implementation@>@;

@ The constructor sets an object name for the menu so scripts are able to look
up the menu and add additional items.

@<Help menu implementation@>=
HelpMenu::HelpMenu() : QMenu()
{
	setObjectName("helpMenu");
	setTitle(tr("Help"));
	QAction *aboutTypicaAction = new QAction(tr("About Typica"), this);
	aboutTypicaAction->setObjectName("aboutTypicaAction");
	addAction(aboutTypicaAction);
	connect(aboutTypicaAction, SIGNAL(triggered()), this, SLOT(displayAboutTypica()));
#if 0
	QAction *licenseAction = new QAction(tr("License Information"), this);
	licenseAction->setObjectName("licenseAction");
	addAction(licenseAction);
	connect(licenseAction, SIGNAL(triggered()), this, SLOT(displayLicenseWindow()));
#endif
}

@ When "About Typica" is selected from the menu, we display an about box. This
is also handled by a separate class.

@<Help menu implementation@>=
void HelpMenu::displayAboutTypica()
{
	AboutTypica *aboutBox = new AboutTypica;
	aboutBox->show();
}

@ Similarly, the "License Information" menu item brings up a window with
appropriate information.

@<Help menu implementation@>=
void HelpMenu::displayLicenseWindow()
{
	LicenseWindow *window = new LicenseWindow;
	window->show();
}

