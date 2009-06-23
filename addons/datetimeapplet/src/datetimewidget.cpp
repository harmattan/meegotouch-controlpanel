#include "datetimewidget.h"
#include "dcpdatetime.h"
#include "dcpspaceritem.h"
#include "dcpbutton2.h"
#include "updatebutton.h"
#include "datetimetranslation.h"
#include "timezonedialog.h"
#include "dcptimezoneconf.h"
#include "dcptimezonedata.h"

#include <duitheme.h>
#include <duilayout.h>
#include <duilocale.h>
#include <duilabel.h>
#include <duilinearlayoutpolicy.h>
#include <duilabel.h>
#include <duibutton.h>
#include <duiscenemanager.h>
#include <duiseparator.h>
#include <QDateTime>
#include <QTimer>

// const QString cssDir = "/usr/share/duicontrolpanel/themes/style/"; // -> for dui>=0.8
const QString cssDir = "/usr/share/themes/dui/duicontrolpanel/"; // -> for dui<=0.7.5
const int widgetWidth = 100;

DateTimeWidget::DateTimeWidget(QGraphicsWidget *parent)
	    :DcpWidget(parent),
         m_Dlg(0)
{
    DuiTheme::loadCSS(cssDir + "datetimeapplet.css");
    setReferer(DcpDateTime::NoReferer);
    initWidget();
}

DateTimeWidget::~DateTimeWidget()
{
}

bool DateTimeWidget::back()
{
    if (m_Dlg) {
        m_Dlg->close();
        return false;
    } else {
        return DcpWidget::back();
    }
}

void DateTimeWidget::initWidget()
{
    // mainLayout
    DuiLayout *mainLayout = new DuiLayout(this);
    mainLayout->setAnimator(0);
    this->setLayout(mainLayout);
    DuiLinearLayoutPolicy *mainLayoutPolicy =
            new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    mainLayoutPolicy->setSpacing(0);

    // dateTimeLayout
    DuiLayout *dateTimeLayout = new DuiLayout(0);
    dateTimeLayout->setAnimator(0);
    DuiLinearLayoutPolicy *dateTimeLayoutPolicy =
            new DuiLinearLayoutPolicy(dateTimeLayout, Qt::Horizontal);
    dateTimeLayout->setPolicy(dateTimeLayoutPolicy);
    dateTimeLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    dateTimeLayoutPolicy->setSpacing(1);

    // m_DateButton
    m_DateButton = new DcpButton2(this);
    this->updateDateText();

    // m_TimeButton
    m_TimeButton = new DcpButton2(this);
    this->updateTimeText();

    // separator lines
    DuiSeparator* separator1 = new DuiSeparator(this);
    DuiSeparator* separator2 = new DuiSeparator(this);
    DuiSeparator* separator3 = new DuiSeparator(this);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimeText()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateDateText()));
    timer->start(1000);

    // m_TimeZoneButton
    m_TimeZoneButton = new DcpButton2(this);
    m_TimeZoneButton->setMinimumWidth(DuiSceneManager::instance()->visibleSceneRect().width()-30);
    connect(m_TimeZoneButton, SIGNAL(clicked()), this, SLOT(showTimeZoneDialog()));
    updateTimeZoneText();

    // m_AutomaticUpdateButton
    m_AutomaticUpdateButton = new UpdateButton(this);

    // simpleLabel
    DuiLabel *simpleLabel = new DuiLabel(DcpDateTime::SetDateTimeText, this);
    simpleLabel->setObjectName("SimpleLabel");
    simpleLabel->setAlignment(Qt::AlignCenter);

    // regionFormatButton
    m_RegionFormatButton = new DuiButton(DcpDateTime::RegionButtonText, this);
    m_RegionFormatButton->setObjectName("RegionFormatButton");
    m_RegionFormatButton->setMaximumWidth(310);
    m_RegionFormatButton->setMaximumHeight(60);
    m_RegionFormatButton->setMinimumHeight(60);

    // Add items to dateTimeLayoutPolicy
    dateTimeLayoutPolicy->addItemAtPosition(m_DateButton, 0, Qt::AlignLeft | Qt::AlignVCenter);
    dateTimeLayoutPolicy->addItemAtPosition(m_TimeButton, 1, Qt::AlignRight | Qt::AlignVCenter);

    // Add items to mainLayoutPolicy
    mainLayoutPolicy->addItemAtPosition(dateTimeLayout, 0, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(separator1, 1);
    mainLayoutPolicy->addItemAtPosition(m_TimeZoneButton, 2, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(separator2, 3);
    mainLayoutPolicy->addItemAtPosition(m_AutomaticUpdateButton, 4, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(separator3, 5);
    mainLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 5, 20, QSizePolicy::Expanding, QSizePolicy::Fixed),
            6, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(simpleLabel, 7, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(m_RegionFormatButton, 8, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 5, 5, QSizePolicy::Expanding, QSizePolicy::Expanding),
            9, Qt::AlignCenter);
}

void DateTimeWidget::showTimeZoneDialog()
{
    /* m_Dlg = new TimeZoneDialog();
    this->setEnabled(false);
    m_Dlg->exec();
    this->setEnabled(true);
    m_Dlg->deleteLater();
    m_Dlg = 0;
    updateTimeZoneText();*/
    emit changeWidget(DcpDateTime::TimeZone);
}

void DateTimeWidget::updateTimeText()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("h:mm A");
    m_TimeButton->setText1(DcpDateTime::CurrentTimeButtonText);
    m_TimeButton->setText2(text);
}

void DateTimeWidget::updateDateText()
{
    QDateTime date = QDateTime::currentDateTime();
    QString text = date.toString("dddd, dd MMMM yyyy");
    m_DateButton->setText1(DcpDateTime::DateButtonText);
    m_DateButton->setText2(text);
}

void DateTimeWidget::updateTimeZoneText()
{
    QString timezone = DcpTimeZoneConf::instance()->defaultTimeZone().gmt() + " " +
                       DcpTimeZoneConf::instance()->defaultTimeZone().city();
    m_TimeZoneButton->setText(DcpDateTime::CurrentTimeZoneText, timezone);
}

