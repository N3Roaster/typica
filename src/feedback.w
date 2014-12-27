@* The Feedback Wizard.

\noindent While the About Typica window includes a link for sending email, this
is not as obvious as a Send Feedback option from the Help menu. It also does
not provide an adequate amount of prompting for feedback to be useful.

This functionality is provided in the form of a |QWizard| and five
|QWizardPage|s to guide people through the feedback process.

@(feedback.h@>=
#include <QWizard>
#include <QComboBox>
#include <QTextEdit>
#include <QLabel>

#ifndef FeedbackHeader
#define FeedbackHeader

class FeedbackWizard : public QWizard
{
	Q_OBJECT
	public:
		FeedbackWizard();
	private slots:
		void setCommentInstructions(int index);
	private:
		QComboBox *feedbackType;
		QLabel *commentInstructions;
		QTextEdit *comment;
};

#endif

@ Implementation is in a separate file.

@(feedback.cpp@>=
#include "feedback.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QWizardPage>

@<Feedback wizard implementation@>@;

@ The feedback wizard constructor is responsible for setting up its appearance,
adding pages, and ensuring connections for properly responding to input are set
up.

@<Feedback wizard implementation@>=
FeedbackWizard::FeedbackWizard() : QWizard()
{
	@<Set wizard graphics@>@;
	@<Set feedback wizard pages@>@;
}

@ At present we do not have any custom graphics for wizards. If we did, they
would go here.

@<Set wizard graphics@>=
/* Nothing needs to be done here. */

@ The first page presented is an introduction page where we would like to know
what sort of feedback is going to be provided. This is selected in a
|QComboBox| which wil be used to update information on later pages.

@<Set feedback wizard pages@>=
QWizardPage *introPage = new QWizardPage;
introPage->setTitle(tr("Send Feedback"));
introPage->setSubTitle("Select the type of feedback you wish to provide");
setPixmap(QWizard::LogoPixmap, QPixmap(":/resources/icons/appicons/logo48.png"));
QLabel *page1prompt = new QLabel(tr("What sort of feedback would you like to provide?"));
feedbackType = new QComboBox;
feedbackType->addItem(tr("Bug Report"));
feedbackType->addItem(tr("Comment"));
feedbackType->addItem(tr("Feature Request"));
feedbackType->addItem(tr("Question"));
QVBoxLayout *page1layout = new QVBoxLayout;
page1layout->addStretch();
page1layout->addWidget(page1prompt);
page1layout->addWidget(feedbackType);
page1layout->addStretch();
introPage->setLayout(page1layout);
addPage(introPage);
connect(feedbackType, SIGNAL(currentIndexChanged(int)), this, SLOT(setCommentInstructions(int)));
commentInstructions = new QLabel;
commentInstructions->setWordWrap(true);
setCommentInstructions(0);

@ The selection on the first page influences the instructions provided on the
second page.

@<Feedback wizard implementation@>=
void FeedbackWizard::setCommentInstructions(int index)
{
	switch(index)
	{
		case 0:
			commentInstructions->setText(tr("Please provide as complete a description of the issue as possible. Useful information includes step by step instructions for replicating the issue, the resulting behavior, and what you expected."));
			break;
		case 1:
			commentInstructions->setText(tr("If you would like action to occur based on your comment, please be specific."));
			break;
		case 2:
			commentInstructions->setText(tr("Please try to be as clear as possible about what you want, where you believe this would fit in with what is already provided, and provide a description of why this would be useful."));
			break;
		case 3:
			commentInstructions->setText(tr("Please be specific and provide any information that you think might be useful in answering your question."));
			break;
		default:
			commentInstructions->setText("");
			break;
	}
}

@ The second page provides both guidance on writing feedback and an area for typing this.

@<Set feedback wizard pages@>=
QWizardPage *commentPage = new QWizardPage;
commentPage->setTitle(tr("Send Feedback"));
commentPage->setSubTitle(tr("Your feedback is appreciated"));
comment = new QTextEdit;
QVBoxLayout *page2layout = new QVBoxLayout;
page2layout->addStretch();
page2layout->addWidget(commentInstructions);
page2layout->addWidget(comment);
page2layout->addStretch();
commentPage->setLayout(page2layout);
addPage(commentPage);