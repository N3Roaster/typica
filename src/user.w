@** Typica User Management.

\noindent Starting in version 1.8, the concepts of database user and \pn{} user
are separated. This means that there must be controls for creating new users
and for selecting the user to log in as. Other management interfaces can be
implemented in configuration scripts.

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

@ Add class implementation to generated source file.

@<Class implementations@>=
@<NewTypicaUser implementation@>