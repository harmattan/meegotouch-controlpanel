#include "datetimewidget.h"
#include "dcpdatetime.h"
#include "dcpspaceritem.h"
#include "dcpbutton2.h"
#include "updatebutton.h"
#include "datetimetranslation.h"
#include "dcptimezoneconf.h"
#include "dcptimezonedata.h"

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

static const QString separatorObjectName = "DcpSmallSeparator";

DateTimeWidget::DateTimeWidget(QGraphicsWidget *parent)
	    :DcpWidget(parent)
{
    setReferer(DcpDateTime::NoReferer);
    initWidget();
}

DateTimeWidget::~DateTimeWidget()
{
}

bool DateTimeWidget::back()
{
    return DcpWidget::back();
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
    mainLayoutPolicy->setSpacing(1);

    // m_DateTimeLayout
    m_DateTimeLayout = new DuiLayout(0);
    m_DateTimeLayout->setAnimator(0);
    m_DateTimeLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);

    // m_DateTimeHLayoutPolicy
    m_DateTimeHLayoutPolicy =
            new DuiLinearLayoutPolicy(m_DateTimeLayout, Qt::Horizontal);
    m_DateTimeHLayoutPolicy->setSpacing(3);

    // m_DateTimeVLayoutPolicy
    m_DateTimeVLayoutPolicy = 
            new DuiLinearLayoutPolicy(m_DateTimeLayout, Qt::Vertical);
    m_DateTimeVLayoutPolicy->setSpacing(3);
    
    m_DateTimeLayout->setPolicy(m_DateTimeHLayoutPolicy);

    // m_DateButton
    m_DateButton = new DcpButton2(this);
    this->updateDateText();
    connect(m_DateButton, SIGNAL(clicked()), this, SLOT(showDateView()));

    // m_TimeButton
    m_TimeButton = new DcpButton2(this);
    this->updateTimeText();
    connect(m_TimeButton, SIGNAL(clicked()), this, SLOT(showTimeView()));

    // separator lines
    DuiSeparator* separator1 = new DuiSeparator(this);
    separator1->setObjectName(separatorObjectName);
    DuiSeparator* separator2 = new DuiSeparator(this);
    separator2->setObjectName(separatorObjectName);
    DuiSeparator* separator3 = new DuiSeparator(this);
    separator3->setObjectName(separatorObjectName);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimeText()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateDateText()));
    timer->start(0);

    // m_TimeZoneButton
    m_TimeZoneButton = new DcpButton2(this);
    connect(m_TimeZoneButton, SIGNAL(clicked()), this, SLOT(showTimeZoneView()));
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

    // Add items to m_DateTimeHLayoutPolicy
    m_DateTimeHLayoutPolicy->addItemAtPosition(m_DateButton, 0, Qt::AlignLeft | Qt::AlignVCenter);
    m_DateTimeHLayoutPolicy->addItemAtPosition(m_TimeButton, 1, Qt::AlignRight | Qt::AlignVCenter);

    // Add items to m_DateTimeVLayoutPlicy
    m_DateTimeVLayoutPolicy->addItemAtPosition(m_DateButton, 0, Qt::AlignCenter);
    m_DateTimeVLayoutPolicy->addItemAtPosition(new DuiSeparator(this), 1, Qt::AlignCenter);
    m_DateTimeVLayoutPolicy->addItemAtPosition(m_TimeButton, 2, Qt::AlignCenter);
    
    // Add items to mainLayoutPolicy
    mainLayoutPolicy->addItemAtPosition(m_AutomaticUpdateButton, 0, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(separator1, 1);
    mainLayoutPolicy->addItemAtPosition(m_DateTimeLayout, 2, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(separator2, 3);
    mainLayoutPolicy->addItemAtPosition(m_TimeZoneButton, 4, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(separator3, 5);
    mainLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 5, 10, QSizePolicy::Expanding, QSizePolicy::Fixed),
            6, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(simpleLabel, 7, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(m_RegionFormatButton, 8, Qt::AlignCenter);
    mainLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 5, 5, QSizePolicy::Expanding, QSizePolicy::Expanding),
            9, Qt::AlignCenter);
    
    // orientation change
    connect(DuiSceneManager::instance(), SIGNAL(orientationChanged(const Dui::Orientation &)),
            this, SLOT(orientationChanged()));
    orientationChanged();
}


void DateTimeWidget::orientationChanged()
{
    if (DuiSceneManager::instance() == 0)
        return;

    switch (DuiSceneManager::instance()->orientation()) {
        case Dui::Landscape:
            m_DateTimeLayout->setPolicy(m_DateTimeHLayoutPolicy);
            break;
        case Dui::Portrait:
            m_DateTimeLayout->setPolicy(m_DateTimeVLayoutPolicy);
            break;
        default:
            break;
    }
}


void DateTimeWidget::showTimeZoneView()
{
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

void DateTimeWidget::showDateView()
{
    emit changeWidget(DcpDateTime::Date);
}

void DateTimeWidget::showTimeView()
{
    emit changeWidget(DcpDateTime::Time);
}

