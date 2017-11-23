@* Degree of roast analysis configuration.

\noindent \pn{} 1.9 adds support for communicating with the Javalytics
JAV-RDA-D degree of roast analyzer from Madison Instruments, and with it, the
ability to track roast color data. There are some settings that are specific to
this device which need to be configurable, but saving roast color data need not
be manufacturer specific and manual data entry options should be provided for
people choosing devices without a communications option.

If support for additional devices is added in the future, these settings may
need to be redesigned to better support competing options. There is also an
assumption that only one of these machines will be in use at one time from any
given instance of \pn{}.

@<Class declarations@>=
class ColorSettingsWidget : public QWidget@/
{@/
    @[Q_OBJECT@]@;
    public:@/
        ColorSettingsWidget();@/
    @[public slots@]:@/
        void updateEnable(bool enable);
        void updateAddress(const QString &address);
        void updateScale(int sccale);
};

@ There are several options available for configuring supported hardware, but
for the initial implementation the preference is to keep things as simple as
possible, adding support for additional features only as requested. As such,
the current options are whether to communicate with external hardware at all,
the IP address of the device, and the scale to request when taking measurements
from \pn{}.

Testing indicates that when batch numbering is enabled, it is still better to
not send an explicit batch number to the device. Sending a number that is equal
or lower than one used previously results in a silent failure while not sending
a number when this feature is enabled results in the next number in the
sequence being chosen automatically.

@<ColorSettingsWidget implementation@>=
ColorSettingsWidget::ColorSettingsWidget() : QWidget(NULL)
{
    QFormLayout *layout = new QFormLayout;
    QCheckBox *enable = new QCheckBox(tr("Enable Javalytics communication"));
    QSettings settings;
    enable->setChecked(settings.value("settings/color/javalytics/enable", false).toBool());
    QLineEdit *address = new QLineEdit();
    address->setText(settings.value("settings/color/javalytics/address", "192.168.1.10").toString());
    QSpinBox *scale = new QSpinBox();
    scale->setMinimum(1);
    scale->setMaximum(4);
    scale->setValue(settings.value("settings/color/javalytics/scale", 1).toInt());
    connect(enable, SIGNAL(toggled(bool)), this, SLOT(updateEnable(bool)));
    connect(address, SIGNAL(textChanged(QString)), this, SLOT(updateAddress(QString)));
    connect(scale, SIGNAL(valueChanged(int)), this, SLOT(updateScale(int)));
    layout->addRow(enable);
    layout->addRow(tr("IP Address:"), address);
    layout->addRow(tr("Scale Number:"), scale);
    updateEnable(enable->isChecked());
    updateAddress(address->text());
    updateScale(scale->value());
    setLayout(layout);
}

@ Trivial methods update the settings as their corresponding controls are
edited.

@<ColorSettingsWidget implementation@>=
void ColorSettingsWidget::updateEnable(bool enable)
{
    QSettings settings;
    settings.setValue("settings/color/javalytics/enable", enable);
}

void ColorSettingsWidget::updateAddress(const QString &address)
{
    QSettings settings;
    settings.setValue("settings/color/javalytics/address", address);
}

void ColorSettingsWidget::updateScale(int scale)
{
    QSettings settings;
    settings.setValue("settings/color/javalytics/scale", scale);
}

@ This is included in typica.cpp.

@<Class implementations@>=
@<ColorSettingsWidget implementation@>
