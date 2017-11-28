@* Data entry for degree of roast data.

\noindent Widgets for entering roast color data change appearance depending on
the current configuration. It should always be possible to enter data manually,
but if communications with the hardware producing these measurements is
possible, there will also be a button available to run the samples directly
from \pn{}.

@<Class declarations@>=
class RoastColorEdit : public QWidget@/
{@/
    @[Q_OBJECT@]@;
    @[Q_PROPERTY(QString value READ value WRITE setValue)@]@;
    public:@/
        RoastColorEdit();
        QString value();
    @[public slots@]:@/
        void setValue(const QString &color);
    @[private slots@]:@/
        void readColor();
        void measureFinished();
        void readFinished();
    private:
        QLineEdit *edit;
        QNetworkReply *networkReply;
};

@ The constructor fills the widget with a |QLineEdit| or with that and a
|QPushButton|, connecting the clicked signal as appropriate.

@<RoastColorEdit implementation@>=
RoastColorEdit::RoastColorEdit() : edit(new QLineEdit)
{
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(edit);
    QSettings settings;
    if(settings.value("settings/color/javalytics/enable", false).toBool())
    {
        QPushButton *button = new QPushButton(tr("Measure"));
        layout->addWidget(button);
        connect(button, SIGNAL(clicked()), this, SLOT(readColor()));
    }
    setLayout(layout);
}

@ When the Measure button is clicked, two network operations are taken. First,
an HTTP POST request is sent to request running a new sample.

@<RoastColorEdit implementation@>=
void RoastColorEdit::readColor()
{
    QSettings settings;
    QUrl postData;
    postData.addQueryItem("calscale", settings.value("settings/color/javalytics/scale", 1).toString());
    postData.addQueryItem("webcontrol", "20");
    QNetworkRequest request(QUrl("http://" + settings.value("settings/color/javalytics/address", "192.168.1.10").toString() + "/index.zhtml"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    networkReply = AppInstance->network->post(request, postData.encodedQuery());
    connect(networkReply, SIGNAL(finished()), this, SLOT(measureFinished()));
}

@ When the device has responded to the POST request, it creates an HTTP GET
request to obtain the latest data.

@<RoastColorEdit implementation@>=
void RoastColorEdit::measureFinished()
{
    QSettings settings;
    networkReply->deleteLater();
    networkReply = AppInstance->network->get(QNetworkRequest(QUrl("http://" + settings.value("settings/color/javalytics/address", "192.168.1.10").toString() + "/data.csv")));
    connect(networkReply, SIGNAL(finished()), this, SLOT(readFinished()));
}

@ The GET request returns all of the data stored on the device as a CSV file,
but for this control we only care about getting the most recent measurement, so
the last line of the response is extracted. When split on commas the fields
contain the following:

\halign{\hfil # & # \hfil \cr
Field Number & Description \cr
0 & Date (MM/DD/YYYY) \cr
1 & Time (hh:mm:ss AP) \cr
2 & Result (the value of interest) \cr
3 & Scale \cr
4 & Custom field 1 \cr
5 & Custom field 2 \cr
6 & Custom field 3 \cr
7 & Custom field 4 \cr
8 & Batch number \cr
9 & Samples averaged \cr}

@<RoastColorEdit implementation@>=
void RoastColorEdit::readFinished()
{
    QByteArray response = networkReply->readAll();
    networkReply->deleteLater();
    networkReply = 0;
    if(response.size() == 0)
    {
        return;
    }
    QList<QByteArray> lines = response.split('\n');
    if(lines.last().size() == 0)
    {
        lines.removeLast();
    }
    if(lines.size() == 0)
    {
        return;
    }
    QList<QByteArray> fields = lines.last().split(',');
    if(fields.size() < 3)
    {
        return;
    }
    edit->setText(QString(fields.at(2)));
}

@ Two methods provide access to the |QLineEdit|.

@<RoastColorEdit implementation@>=
void RoastColorEdit::setValue(const QString &color)
{
    edit->setText(color);
}

QString RoastColorEdit::value()
{
    return edit->text();
}

@ This control can be added to a box layout.

@<Additional box layout elements@>=
else if(currentElement.tagName() == "roastcoloredit")
{
    QBoxLayout *layout = qobject_cast<QBoxLayout *>(layoutStack->top());
    RoastColorEdit *edit = new RoastColorEdit;
    if(currentElement.hasAttribute("id"))
    {
        edit->setObjectName(currentElement.attribute("id"));
    }
    layout->addWidget(edit);
}

@ The implementation goes into typica.cpp.

@<Class implementations@>=
@<RoastColorEdit implementation@>
