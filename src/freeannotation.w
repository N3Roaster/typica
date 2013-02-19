@* Free text annotation control configuration.

\noindent Some roasting firms like to be able to provide arbitrary text as an
annotation in addition to or instead of fixed form annotations. There is very
little to configure for an annotation control that facilitates that
functionality. The existence and position of the control is implicit in the
existence of a node representing the control in the configuration. An optional
label next to the control is the only configurable option at present. A
configuration widget and associated registrations to integrate with the
configuration system is still required.

@<Class declarations@>=
class FreeAnnotationConfWidget : public BasicDeviceConfigurationWidget
{
	Q_OBJECT
	public:
		Q_INVOKABLE FreeAnnotationConfWidget(DeviceTreeModel *model, const QModelIndex &index);
	private slots:
		void updateLabel(const QString &text);
};

@ The constructor should seem familiar by now.

@<FreeAnnotationConfWidget implementation@>=
FreeAnnotationConfWidget::FreeAnnotationConfWidget(DeviceTreeModel *model,
                                                   const QModelIndex &index)
	: BasicDeviceConfigurationWidget(model, index)
{
	QFormLayout *layout = new QFormLayout;
	QLineEdit *labelEdit = new QLineEdit;
	layout->addRow(tr("Label Text:"), labelEdit);
	@<Get device configuration data for current node@>@;
	for(int i = 0; i < configData.size(); i++)
	{
		node = configData.at(i).toElement();
		if(node.attribute("name") == "labeltext")
		{
			labelEdit->setText(node.attribute("value"));
		}
	}
	updateLabel(labelEdit->text());
	connect(labelEdit, SIGNAL(textEdited(QString)),
	        this, SLOT(updateLabel(QString)));
	setLayout(layout);
}

@ The update slot is trivial.

@<FreeAnnotationConfWidget implementation@>=
void FreeAnnotationConfWidget::updateLabel(const QString &text)
{
	updateAttribute("labeltext", text);
}

@ There is nothing unusual in the control registration.

@<Register device configuration widgets@>=
app.registerDeviceConfigurationWidget("freeannotation",
                                      FreeAnnotationConfWidget::staticMetaObject);