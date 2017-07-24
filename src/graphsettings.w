@* Graph widget configuration.

\noindent There are many features of the graph in Typica which ought to be
configurable. Most of these cannot be configured until changes are made to the
graph widget. The original motivation for the class comes from a need to
configure secondary axes.

@<Class declarations@>=
class GraphSettingsWidget : public QWidget@/
{@/
	@[Q_OBJECT@]@;
	public:@/
		GraphSettingsWidget();
};

@ At present there are three types of data that the graph might present. This
will likely be expanded as support for additional unit types are added.

Different measurement categories are presently organized into different tabs.
This will potentially need to change later as more features are added and the
tab set becomes excessively large but for now this is the best that I can
think of. If anybody with UI design experience would like to propose something
better I would be glad to consider it.

@s GraphSettingsRelativeTab int

@<GraphSettingsWidget implementation@>=
GraphSettingsWidget::GraphSettingsWidget() : QWidget(NULL)
{
	QTabWidget *graphCategories = new QTabWidget;
	GraphSettingsRelativeTab *relative = new GraphSettingsRelativeTab;
	graphCategories->addTab(relative, tr("Relative Temperatures"));
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(graphCategories);
	setLayout(layout);
}

@ Relative temperature measurements are different from the absolute temperature
measurements that fall on the primary axis in that it is likely that negative
values will be presented. These may be important and should not be hidden off
the bottom of the graph, but the most important values will be in a relatively
small range of positive values. The particulars will depend on the settings
used to construct the relative values and the style of coffee roasting. It is
also possible to disable the graphing of relative temperature measurements.

@<Class declarations@>=
class GraphSettingsRelativeTab : public QWidget@/
{@/
	@[Q_OBJECT@]@;
	public:@/
		GraphSettingsRelativeTab();@/
	@[public slots@]:@/
		void updateEnableSetting(bool enable);
		void updateColorSetting(const QString &color);
		void updateAxisSetting(const QString &gridList);
		void updateUnit(int unit);
		void showColorPicker();@/
	private:@/
		QLineEdit *colorEdit;
};

@ The constructor sets up the interface and restores any previous values from
settings.

The default grid line position has been updated since version 1.8 to match the
number of grid lines present when viewing the graph in Fahrenheit and to
present a slightly wider range where most measurements are expected.

@<GraphSettingsWidget implementation@>=
GraphSettingsRelativeTab::GraphSettingsRelativeTab() : QWidget(NULL),
	colorEdit(new QLineEdit)
{
	QSettings settings;
	QVBoxLayout *layout = new QVBoxLayout;
	QCheckBox *enable = new QCheckBox(tr("Graph relative temperatures"));
	enable->setChecked(settings.value("settings/graph/relative/enable", true).toBool());
	updateEnableSetting(enable->isChecked());
	connect(enable, SIGNAL(toggled(bool)), this, SLOT(updateEnableSetting(bool)));
	layout->addWidget(enable);
	QHBoxLayout *colorLayout = new QHBoxLayout;
	QLabel *colorLabel = new QLabel(tr("Axis color:"));
	colorEdit->setText(settings.value("settings/graph/relative/color", "#000000").toString());
	updateColorSetting(colorEdit->text());
	connect(colorEdit, SIGNAL(textChanged(QString)), this, SLOT(updateColorSetting(QString)));
	QToolButton *colorPickerButton = new QToolButton();
	colorPickerButton->setIcon(QIcon::fromTheme("applications-graphics"));
	connect(colorPickerButton, SIGNAL(clicked()), this, SLOT(showColorPicker()));
	colorLayout->addWidget(colorLabel);
	colorLayout->addWidget(colorEdit);
	colorLayout->addWidget(colorPickerButton);
	colorLayout->addStretch();
	layout->addLayout(colorLayout);
	QHBoxLayout *unitLayout = new QHBoxLayout;
	QLabel *unitLabel = new QLabel(tr("Unit"));
	QComboBox *unitSelector = new QComboBox;
	unitSelector->addItem(tr("Fahrenheit"));
	unitSelector->addItem(tr("Celsius"));
	unitSelector->setCurrentIndex(settings.value("settings/graph/relative/unit", 0).toInt());
	updateUnit(unitSelector->currentIndex());
	connect(unitSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUnit(int)));
	unitLayout->addWidget(unitLabel);
	unitLayout->addWidget(unitSelector);
	unitLayout->addStretch();
	layout->addLayout(unitLayout);
	QHBoxLayout *axisLayout = new QHBoxLayout;
	QLabel *axisLabel = new QLabel(tr("Grid line positions (comma separated):"));
	QLineEdit *axisEdit = new QLineEdit;
	axisEdit->setText(settings.value("settings/graph/relative/grid", "-300, -100, 0, 30, 65, 100").toString());
	updateAxisSetting(axisEdit->text());
	connect(axisEdit, SIGNAL(textChanged(QString)), this, SLOT(updateAxisSetting(QString)));
	axisLayout->addWidget(axisLabel);
	axisLayout->addWidget(axisEdit);
	layout->addLayout(axisLayout);
	layout->addStretch();
	setLayout(layout);
}

@ A set of methods updates the settings as they are adjusted.

@<GraphSettingsWidget implementation@>=
void GraphSettingsRelativeTab::updateEnableSetting(bool enabled)
{
	QSettings settings;
	settings.setValue("settings/graph/relative/enable", enabled);
}

void GraphSettingsRelativeTab::updateColorSetting(const QString &color)
{
	QSettings settings;
	settings.setValue("settings/graph/relative/color", color);
}

void GraphSettingsRelativeTab::updateAxisSetting(const QString &gridList)
{
	QSettings settings;
	QString settingValue;
	QStringList points = gridList.split(QRegExp("[\\s,]+"), QString::SkipEmptyParts);
	QStringList numbers;
	foreach(QString text, points)
	{
		bool okay = @[false@];
		text.toDouble(&okay);
		if(okay)
		{
			numbers.append(text);
		}
	}
	numbers.removeDuplicates();
	settings.setValue("settings/graph/relative/grid", numbers.join(","));
}

void GraphSettingsRelativeTab::updateUnit(int unit)
{
	QSettings settings;
	settings.setValue("settings/graph/relative/unit", unit);
}

@ When selecting a color, it is possible to either type the color into the line
edit directly or use a color picker to select the color graphically. A tool
button displays a color picker and pushes the selected color into the line edit
which in turn updates the setting.

@<GraphSettingsWidget implementation@>=
void GraphSettingsRelativeTab::showColorPicker()
{
	QColor color = QColorDialog::getColor(QColor(colorEdit->text()), this);
	colorEdit->setText(color.name());
}