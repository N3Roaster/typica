/*181:*/
#line 16 "./helpmenu.w"

#include <QMenu> 

#ifndef HelpMenuHeader
#define HelpMenuHeader

class HelpMenu:public QMenu
{
Q_OBJECT
public:
HelpMenu();
public slots:
void displayAboutTypica();
void displayFeedbackWizard();
};

#endif

/*:181*/
