@** A window for program configuration.

\noindent A previous version of Typica introduced a window specifically for
configuring the measurement pipeline in Typica. This is a fairly limited subset
of things that should be more easily configurable in Typica. Starting with
version 1.6 that window has been converted into a widget that is available
through a tab in a more general configuration window with other tabs available
for settings that do not logically belong with a single part of the measurement
pipeline.

@<Class declarations@>=
class SettingsWindow : public QMainWindow@/
{@/
	@[Q_OBJECT@]@;
	public:@/
		SettingsWindow();
};

@ The constructor takes care of the initial interface setup. Most of the
functionality is delegated to more specialized widgets that are available
through a set of tabs.

@s QTabWidget int
@s GraphSettingsWidget int

@<SettingsWindow implementation@>=
SettingsWindow::SettingsWindow() : QMainWindow(NULL)
{
	QTabWidget *settingsTab = new QTabWidget;
	DeviceConfigurationWindow *deviceSettings = new DeviceConfigurationWindow;
	settingsTab->addTab(deviceSettings, tr("Roasters"));
	GraphSettingsWidget *graphSettings = new GraphSettingsWidget;
	settingsTab->addTab(graphSettings, tr("Graph"));
	AdvancedSettingsWidget *advancedSettings = new AdvancedSettingsWidget;
	settingsTab->addTab(advancedSettings, tr("Advanced"));
	setCentralWidget(settingsTab);
}

@ This widget is made available to the host environment for access wherever
appropriate.

@<Function prototypes for scripting@>=
QScriptValue constructSettingsWindow(QScriptContext *context, QScriptEngine *engine);

@ The constructor is trivial.

@<Functions for scripting@>=
QScriptValue constructSettingsWindow(QScriptContext *, QScriptEngine *engine)
{
	QScriptValue object = engine->newQObject(new SettingsWindow);
	return object;
}

@ The host environment is informed of this as usual.

@<Set up the scripting engine@>=
constructor = engine->newFunction(constructSettingsWindow);
value = engine->newQMetaObject(&DeviceConfigurationWindow::staticMetaObject, constructor);
engine->globalObject().setProperty("SettingsWindow", value);

@i graphsettings.w

@i advancedsettings.w