@** Typica User Management.

\noindent Starting in version 1.8, the concepts of database user and \pn{} user
are separated. This means that there must be controls for creating new users
and for selecting the user to log in as. Other management interfaces can be
implemented in configuration scripts.

@* Application extensions for user handling.

\noindent In order to present information about the currently logged in user
globally, it was decided to provide a few methods in |Application| that can be
used to report and change the current user.

The first of these simply reports the currently logged in user.

@<Application Implementation@>=
QString Application::currentTypicaUser()
{
	return currentUser;
}

@ Next is a method that can be used to force the login of a specified user
without checking for an entered password. This is used for users that are set
to login automatically.

@<Application Implementation@>=
void Application::setCurrentTypicaUser(const QString &user)
{
	currentUser = user;
	emit userChanged(currentUser);
}

@ A login method is provided which determines if a user exists that matches the
user name and password specified and reports if the login attempt was
successful.

@<Application Implementation@>=
bool Application::login(const QString &user, const QString &password)
{
	SqlQueryConnection h;
	QSqlQuery *dbquery = h.operator->();
	dbquery->prepare("SELECT 1 FROM typica_users WHERE name = :name AND password = :password AND active = TRUE");
	dbquery->bindValue(":name", user);
	dbquery->bindValue(":password", password);
	dbquery->exec();
	if(dbquery->next())
	{
		currentUser = user;
		emit userChanged(currentUser);
		return true;
	}
	return false;
}

@ A convenience method is also provided to attempt an automatic login if one is
specified in the database.

@<Application Implementation@>=
bool Application::autoLogin()
{
	SqlQueryConnection h;
	QSqlQuery *dbquery = h.operator->();
	dbquery->exec("SELECT name FROM typica_users WHERE auto_login = TRUE");
	if(dbquery->next())
	{
		currentUser = dbquery->value(0).toString();
		emit userChanged(currentUser);
		return true;
	}
	return false;
}

@* Login dialog.

\noindent If there are no users set to log in automatically or any time a user
change is requested, a login dialog should be presented.

@<Class declarations@>=
class LoginDialog : public QDialog
{
	Q_OBJECT
	public:
		LoginDialog();
	public slots:
		void attemptLogin();
	private:
		QLineEdit *user;
		QLineEdit *password;
		QLabel *warning;
		QPushButton *login;
};

@ The constructor sets up the interface.

@<LoginDialog implementation@>=
LoginDialog::LoginDialog() : QDialog(),
	user(new QLineEdit), password(new QLineEdit),
	warning(new QLabel(tr("Log in failed."))),
	login(new QPushButton(tr("Log In")))
{
	setModal(true);
	QVBoxLayout *mainLayout = new QVBoxLayout;
	warning->setVisible(false);
	password->setEchoMode(QLineEdit::Password);
	QFormLayout *form = new QFormLayout;
	form->addRow(tr("Name:"), user);
	form->addRow(tr("Password:"), password);
	form->addRow(warning);
	QHBoxLayout *buttonBox = new QHBoxLayout;
	buttonBox->addStretch();
	buttonBox->addWidget(login);
	mainLayout->addLayout(form);
	mainLayout->addLayout(buttonBox);
	connect(login, SIGNAL(clicked()), this, SLOT(attemptLogin()));
	setLayout(mainLayout);
}

@ The log in button attempts to log in with the specified credentials.

@<LoginDialog implementation@>=
void LoginDialog::attemptLogin()
{
	if(AppInstance->login(user->text(), password->text()))
	{
		accept();
	}
	else
	{
		warning->setVisible(true);
	}
}

@ Scripts must be able to create login dialogs.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructLoginDialog);
value = engine->newQMetaObject(&LoginDialog::staticMetaObject, constructor);
engine->globalObject().setProperty("LoginDialog", value);

@ The constructor is trivial.

@<Functions for scripting@>=
QScriptValue constructLoginDialog(QScriptContext *, QScriptEngine *engine)
{
	QScriptValue object = engine->newQObject(new LoginDialog);
	return object;
}

@ A function prototype is required.

@<Function prototypes for scripting@>=
QScriptValue constructLoginDialog(QScriptContext *context, QScriptEngine *engine);

@* Currently logged in user.

\noindent Every main window in \pn{} should be able to report on the currently
logged in user and it should be possible to bring up an interface to switch
users. An easy way to do this is through a widget inserted into the status bar
of every window that listens for user change data from the |Application|
instance.

@<Class declarations@>=
class UserLabel : public QLabel
{
	Q_OBJECT
	public:
		UserLabel();
	public slots:
		void updateLabel(const QString &user);
	protected:
		void mouseReleaseEvent(QMouseEvent *event);
};

@ On first instantiation, the constructor sets the displayed text to indicate
the currently logged in user and starts listening for user change events.

@<UserLabel implementation@>=
UserLabel::UserLabel() : QLabel()
{
	setTextFormat(Qt::PlainText);
	updateLabel(AppInstance->currentTypicaUser());
	connect(AppInstance, SIGNAL(userChanged(QString)),
	        this, SLOT(updateLabel(QString)));
}

@ When the currently logged in user changes, the label text updates itself.

@<UserLabel implementation@>=
void UserLabel::updateLabel(const QString &user)
{
	setText(QString(tr("Current operator: %1").arg(user)));
}

@ In order to handle clicks, |mouseReleaseEvent()| is implemented.

@<UserLabel implementation@>=
void UserLabel::mouseReleaseEvent(QMouseEvent *)
{
	LoginDialog *dialog = new LoginDialog;
	dialog->exec();
}

@* User Creation.

\noindent The first time \pn{} is started with a database connection and a
multi-user aware configuration there will not be any user records in the
database. An interface for adding new users is provided.

@<Class declarations@>=
class NewTypicaUser: public QDialog
{
	Q_OBJECT
	public:
		NewTypicaUser();
	public slots:
		void createAndReset();
		void createAndClose();
		void validate();
		void cancelValidate();
	private:
		void createNewUser();
		QLineEdit *userField;
		QLineEdit *passwordField;
		QCheckBox *autoLogin;
		QPushButton *saveAndCloseButton;
		QPushButton *saveAndNewButton;
		QPushButton *cancelButton;
};

@ The constructor sets up the dialog.

@<NewTypicaUser implementation@>=
NewTypicaUser::NewTypicaUser() : QDialog(),
	userField(new QLineEdit), passwordField(new QLineEdit),
	autoLogin(new QCheckBox(tr("Log in automatically"))),
	saveAndCloseButton(new QPushButton(tr("Save and Close"))),
	saveAndNewButton(new QPushButton(tr("Save and Create Another"))),
	cancelButton(new QPushButton(tr("Cancel")))
{
	setModal(true);
	QVBoxLayout *mainLayout = new QVBoxLayout;
	QFormLayout *form = new QFormLayout;
	QHBoxLayout *buttons = new QHBoxLayout;
	form->addRow(tr("Name:"), userField);
	passwordField->setEchoMode(QLineEdit::Password);
	form->addRow(tr("Password:"), passwordField);
	form->addRow(autoLogin);
	buttons->addWidget(cancelButton);
	buttons->addStretch();
	buttons->addWidget(saveAndNewButton);
	buttons->addWidget(saveAndCloseButton);
	mainLayout->addLayout(form);
	mainLayout->addLayout(buttons);
	setLayout(mainLayout);
	setWindowTitle(tr("Create New User"));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
	connect(saveAndCloseButton, SIGNAL(clicked()), this, SLOT(createAndClose()));
	connect(saveAndNewButton, SIGNAL(clicked()), this, SLOT(createAndReset()));
	connect(userField, SIGNAL(textChanged(QString)), this, SLOT(validate()));
}

@ Slots handle basic operation.

@<NewTypicaUser implementation@>=
void NewTypicaUser::createAndReset()
{
	createNewUser();
	userField->setText("");
	passwordField->setText("");
	autoLogin->setChecked(false);
}

void NewTypicaUser::createAndClose()
{
	createNewUser();
	accept();
}

void NewTypicaUser::createNewUser()
{
	SqlQueryConnection h;
	QSqlQuery *dbquery = h.operator->();
	dbquery->prepare("INSERT INTO typica_users (name, password, active, auto_login) VALUES (:name, :password, true, :auto)");
	dbquery->bindValue(":name", userField->text());
	dbquery->bindValue(":password", passwordField->text());
	dbquery->bindValue(":auto", autoLogin->isChecked());
	dbquery->exec();
	cancelButton->setEnabled(true);
}

void NewTypicaUser::validate()
{
	if(!userField->text().isEmpty())
	{
		saveAndCloseButton->setEnabled(true);
		saveAndNewButton->setEnabled(true);
	}
	else
	{
		saveAndCloseButton->setEnabled(false);
		saveAndNewButton->setEnabled(false);
	}
}

void NewTypicaUser::cancelValidate()
{
	SqlQueryConnection h;
	QSqlQuery *dbquery = h.operator->();
	dbquery->exec("SELECT count(1) FROM typica_users");
	if(dbquery->next())
	{
		if(dbquery->value(0).toInt() > 0)
		{
			cancelButton->setEnabled(true);
			return;
		}
	}
	cancelButton->setEnabled(false);
}

@ This is exposted to the host environment in the usual way.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructNewTypicaUser);
value = engine->newQMetaObject(&NewTypicaUser::staticMetaObject, constructor);
engine->globalObject().setProperty("NewTypicaUser", value);

@ The constructor is trivial.

@<Functions for scripting@>=
QScriptValue constructNewTypicaUser(QScriptContext *, QScriptEngine *engine)
{
	QScriptValue object = engine->newQObject(new NewTypicaUser);
	return object;
}

@ A function prototype is required.

@<Function prototypes for scripting@>=
QScriptValue constructNewTypicaUser(QScriptContext *context, QScriptEngine *engine);

@ Add class implementations to generated source file.

@<Class implementations@>=
@<NewTypicaUser implementation@>
@<UserLabel implementation@>
@<LoginDialog implementation@>