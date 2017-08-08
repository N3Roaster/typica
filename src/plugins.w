@** Simple Plugins.

\noindent The original motivation for this feature is to provide a simple way
to allow importing data from other data logging applications. The problem is
that there are huge differences in the data formats exported by different
applications, sometimes there are differences that depend on how the other
application was configured which cannot be reliably determined in an automated
fashion, and if a substantial number of import plugins were created, any given
person using Typica would be unlikely to ever use most of them.

Based on these concerns, I wanted something that would make it easy to create
new import plugins without the need to create a new build of Typica every time,
I wanted it to be relatively easy for people to modify example import plugins
to suit the data they wanted to import, and I wanted it to be easy for people
to hide plugins that they were not required.

This is handled in a way similar to reports. A new directory is provided with
the \pn{} configuration which contains files with script code. A menu item is
available that will examine the files in that folder to populate its sub-menu.

@<Process plugin item@>=
QMenu *pluginMenu = new QMenu(menu);
if(itemElement.hasAttribute("id"))
{
	pluginMenu->setObjectName(itemElement.attribute("id"));
}
if(itemElement.hasAttribute("title"))
{
	pluginMenu->setTitle(itemElement.attribute("title"));
}
if(itemElement.hasAttribute("src"))
{
	QSettings settings;
	QString pluginDirectory = QString("%1/%2").
		arg(settings.value("config").toString()).
		arg(itemElement.attribute("src"));
	QDir directory(pluginDirectory);
	directory.setFilter(QDir::Files);
	directory.setSorting(QDir::Name);
	QStringList nameFilter;
	nameFilter << "*.js";
	directory.setNameFilters(nameFilter);
	QFileInfoList pluginFiles = directory.entryInfoList();
	for(int k = 0; k < pluginFiles.size(); k++)
	{
		PluginAction *pa = new PluginAction(pluginFiles.at(k), pluginMenu);
		if(itemElement.hasAttribute("preRun"))
		{
			pa->setPreRun(itemElement.attribute("preRun"));
		}
		if(itemElement.hasAttribute("postRun"))
		{
			pa->setPostRun(itemElement.attribute("postRun"));
		}
		pluginMenu->addAction(pa);
	}
}
menu->addMenu(pluginMenu);

@ The sub-menu items are a subclass of |QAction| which holds all of the
information needed to respond to its activation.

@<Class declarations@>=
class PluginAction : public QAction
{
	Q_OBJECT
	Q_PROPERTY(QString preRun READ preRun WRITE setPreRun);
	Q_PROPERTY(QString postRun READ postRun WRITE setPostRun);
	public:
		PluginAction(const QFileInfo &info, QObject *parent);
		QString preRun();
		QString postRun();
	public slots:
		void setPreRun(const QString &script);
		void setPostRun(const QString &script);
	private slots:
		void runScript();
	private:
		QString pluginFile;
		QString preRunScript;
		QString postRunScript;
};

@ The constructor takes a |QFileInfo| and uses that to extract the path of the
file used to respond to the action activation as well as the text that should
be used in the menu text. It also takes a |QObject*| parent which should be the
|QMenu| the |PluginAction| will be placed in.

Everything interesting happens in |runScript()| which is called when the action
is triggered.

@<PluginAction implementation@>=
PluginAction::PluginAction(const QFileInfo &info, QObject *parent) :
	QAction(parent), preRunScript(""), postRunScript("")
{
	pluginFile = info.absoluteFilePath();
	setText(info.baseName());
	connect(this, SIGNAL(triggered()), this, SLOT(runScript()));
}

void PluginAction::runScript()
{
	QFile file(pluginFile);
	if(file.open(QIODevice::ReadOnly))
	{
		QScriptEngine *engine = AppInstance->engine;
		QScriptContext *context = engine->pushContext();
		if(parent()->dynamicPropertyNames().contains("activationObject"))
		{
			QScriptValue activationObject =
				parent()->property("activationObject").value<QScriptValue>();
			context->setActivationObject(activationObject);
		}
		QString script(file.readAll());
		QScriptValue retval = engine->evaluate(preRunScript + script + postRunScript, pluginFile);
		if(engine->hasUncaughtException())
		{
			qDebug() << "Uncaught exception: " <<
				engine->uncaughtException().toString() <<
				" in " << pluginFile << " line: " <<
				engine->uncaughtExceptionLineNumber();
		}
		engine->popContext();
		file.close();
	}
}

@ Pre-run and post-run scripts can be set to handle boilerplate that would
otherwise need to be included in all plugins.

@<PluginAction implementation@>=
QString PluginAction::preRun()
{
	return preRunScript;
}

QString PluginAction::postRun()
{
	return postRunScript;
}

void PluginAction::setPreRun(const QString &script)
{
	preRunScript = script;
}

void PluginAction::setPostRun(const QString &script)
{
	postRunScript = script;
}

@ In order to get the activation object in this way, we need to allow a
|QScriptValue| to be stored in a |QVariant|.

@<Class declarations@>=
Q_DECLARE_METATYPE(QScriptValue)

@ This is added to the list of class implementations.

@<Class implementations@>=
@<PluginAction implementation@>

