@* Advanced settings configuration.

\noindent Sometimes a feature has a sensible default that should be used the
vast majority of the time but sometimes requires some other setting to be
available in a reasonably accessible way.

@<Class declarations@>=
class AdvancedSettingsWidget : public QWidget@/
{@/
	@[Q_OBJECT@]@;
	public:@/
		AdvancedSettingsWidget();
	@[public slots:@]@/
		void enableDiagnosticLogging(bool enabled);
};

@ At present the advanced settings consist only of an option to redirect
diagnostic output to a file. This should normally be disabled as it supresses
console output and there is no mechanism within \pn{} for periodically removing
the files generated. It is, however, useful for producing a diagnostic file
that can be attached to an email if someone is encountering an issue that they
are not able to resolve on their own. It is especially useful on Microsoft
Windows where this output is not otherwise available unless Typica is run from
software development tools most people do not have installed.

@<AdvancedSettingsWidget implementation@>=
AdvancedSettingsWidget::AdvancedSettingsWidget() : QWidget(NULL)
{
	QSettings settings;
	QFormLayout *layout = new QFormLayout;
	QCheckBox *logDiagnostics = new QCheckBox;
	logDiagnostics->setCheckState(
		settings.value("settings/advanced/logging", false).toBool() ?
		Qt::Checked : Qt::Unchecked);
	connect(logDiagnostics, SIGNAL(toggled(bool)), this, SLOT(enableDiagnosticLogging(bool)));
	layout->addRow(tr("Enable diagnostic logging"), logDiagnostics);
	setLayout(layout);
}

@ Changes to this setting should take effect immediately. It should also be
written to |QSettings| so the feature can be correctly enabled or not. 

@<AdvancedSettingsWidget implementation@>=
void AdvancedSettingsWidget::enableDiagnosticLogging(bool enabled)
{
	QSettings settings;
	settings.setValue("settings/advanced/logging", enabled);
	if(enabled)
	{
		qInstallMsgHandler(messageFileOutput);
	}
	else
	{
		qInstallMsgHandler(0);
	}
}

@ Currently the implementation is brought into typica.cpp.

@<Class implementations@>=
@<AdvancedSettingsWidget implementation@>