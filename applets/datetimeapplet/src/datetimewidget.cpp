#include "datetimewidget.h"
#include "dcpdatetime.h"
#include <DcpSpacerItem>
#include <DcpButton2>
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
    timer->start(1000);

    // m_TimeZoneButton
    m_TimeZoneButton = new DcpButton2(this);
    connect(m_TimeZoneButton, SIGNAL(clicked()), this, SLOT(showTimeZoneView()));
    updateTimeZoneText();

    // m_AutomaticUpdateButton
    m_AutomaticUpdateButton = new UpdateButton(this);

    // m_SimpleLabel
    m_SimpleLabel = new DuiLabel(this);
    m_SimpleLabel->setObjectName("SimpleLabel");
    m_SimpleLabel->setAlignment(Qt::AlignCenter);

    // regionFormatButton
    m_RegionFormatButton = new DuiButton(this);
    m_RegionFormatButton->setObjectName("RegionFormatButton");

    // Add items to m_DateTimeHLayoutPolicy
    m_DateTimeHLayoutPolicy->addItem(m_DateButton, Qt::AlignLeft | Qt::AlignVCenter);
    m_DateTimeHLayoutPolicy->addItem(m_TimeButton, Qt::AlignRight | Qt::AlignVCenter);

    // Add items to m_DateTimeVLayoutPlicy
    m_DateTimeVLayoutPolicy->addItem(m_DateButton, Qt::AlignCenter);
    DuiSeparator* separator4 = new DuiSeparator(this);
    separator4->setObjectName(separatorObjectName);
    m_DateTimeVLayoutPolicy->addItem(separator4);
    m_DateTimeVLayoutPolicy->addItem(m_TimeButton, Qt::AlignCenter);

    // Add items to mainLayoutPolicy
    mainLayoutPolicy->addItem(m_AutomaticUpdateButton, Qt::AlignCenter);
    mainLayoutPolicy->addItem(separator1);
    mainLayoutPolicy->addItem(m_DateTimeLayout, Qt::AlignCenter);
    mainLayoutPolicy->addItem(separator2);
    mainLayoutPolicy->addItem(m_TimeZoneButton, Qt::AlignCenter);
    mainLayoutPolicy->addItem(separator3);
    mainLayoutPolicy->addItem(
            new DcpSpacerItem(this, 5, 10, QSizePolicy::Expanding, QSizePolicy::Fixed),
            Qt::AlignCenter);
    mainLayoutPolicy->addItem(m_SimpleLabel, Qt::AlignCenter);
    mainLayoutPolicy->addItem(m_RegionFormatButton, Qt::AlignCenter);
    mainLayoutPolicy->addItem(
            new DcpSpacerItem(this, 5, 5, QSizePolicy::Expanding, QSizePolicy::Expanding),
            Qt::AlignCenter);

    // orientation change
    connect(DuiSceneManager::instance(), SIGNAL(orientationChanged(const Dui::Orientation &)),
            this, SLOT(orientationChanged()));
    orientationChanged();

    // "on the fly" language change
    connect (qApp, SIGNAL(localeSettingsChanged()),
             this, SLOT(onLocaleChanged()));
    onLocaleChanged();
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

void DateTimeWidget::onLocaleChanged()
{
    m_SimpleLabel->setText(trid(DcpDateTime::setDateTimeTextId,
                                DcpDateTime::setDateTimeTextDefault));
    m_RegionFormatButton->setText(trid(DcpDateTime::regionButtonTextId,
                                       DcpDateTime::regionButtonTextDefault));
    m_AutomaticUpdateButton->setText(trid(DcpDateTime::automaticUpdateTextId,
                                 DcpDateTime::automaticUpdateTextDefault));
    updateTimeText();
    updateDateText();
    updateTimeZoneText();
}

void DateTimeWidget::updateTimeText()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("h:mm A");
    m_TimeButton->setText1(trid(DcpDateTime::currentTimeButtonTextId,
                                DcpDateTime::currentTimeButtonTextDefault));
    m_TimeButton->setText2(text);
}

void DateTimeWidget::updateDateText()
{
    QDateTime date = QDateTime::currentDateTime();
    QString text = date.toString("dddd, dd MMMM yyyy");
    m_DateButton->setText1(trid(DcpDateTime::dateButtonTextId,
                                DcpDateTime::dateButtonTextDefault));
    m_DateButton->setText2(text);
}

void DateTimeWidget::updateTimeZoneText()
{
    QString timezone = DcpTimeZoneConf::instance()->defaultTimeZone().gmt() + " " +
                       DcpTimeZoneConf::instance()->defaultTimeZone().city();
    m_TimeZoneButton->setText(trid(DcpDateTime::currentTimeZoneTextId,
                                   DcpDateTime::currentTimeZoneTextDefault)
                              , timezone);
}

void DateTimeWidget::showDateView()
{
    emit changeWidget(DcpDateTime::Date);
}

void DateTimeWidget::showTimeView()
{
    emit changeWidget(DcpDateTime::Time);
}

