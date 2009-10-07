#include "timeview.h"
#include "dcpdatetime.h"
#include "datetimetranslation.h"
#include "dcpspaceritem.h"

#include "dcptime.h"

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <DuiWidget>
#include <duiscenemanager.h>
#include <duicontainer.h>
#include <QGraphicsLinearLayout>

#include <clock/settingalarm.h>


TimeView::TimeView(QGraphicsWidget *parent)
           :DcpWidget(parent)
{
    setReferer(DcpDateTime::Main);
    dcpTime = new DcpTime(this);
    initWidget();
}

bool TimeView::back()
{
    //qDebug() << m_TimePicker->hours() << ":" <<m_TimePicker->minutes() ;

    dcpTime->setTime(m_TimePicker->hours(), m_TimePicker->minutes());

    return DcpWidget::back();
}

void TimeView::initWidget()
{
    // mainLayout
    DuiLayout *mainLayout = new DuiLayout(this);
    mainLayout->setAnimator(0);
    mainLayout->setContentsMargins(0.0, 12.0, 0.0, 12.0);
    DuiLinearLayoutPolicy *mainLayoutPolicy = new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayoutPolicy->setSpacing(10);
    mainLayout->setPolicy(mainLayoutPolicy);
    this->setLayout(mainLayout);

    m_Container = new DuiContainer(DcpDateTime::TimeDialogTitle, this);
    
    // centralWidget
    DuiWidget *centralWidget = new DuiWidget(0);
    
    // widgetLayout
    QGraphicsLinearLayout *widgetLayout = new QGraphicsLinearLayout(Qt::Horizontal, centralWidget);
    widgetLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    widgetLayout->setSpacing(2);

    // analogClock
    m_TimePicker = new SettingAlarm();
    m_TimePicker->setMinimumSize(QSize(400, 400));
    m_TimePicker->setMaximumSize(QSize(400, 400));
    timeOrDateChanged();

	widgetLayout->addItem(new DcpSpacerItem(centralWidget, 10, 10, QSizePolicy::Expanding, QSizePolicy::Preferred));
    widgetLayout->addItem(m_TimePicker);
    widgetLayout->setAlignment(m_TimePicker, Qt::AlignCenter);
	widgetLayout->addItem(new DcpSpacerItem(centralWidget, 10, 10, QSizePolicy::Expanding, QSizePolicy::Preferred));

    // setCentralWidget
    m_Container->setCentralWidget(centralWidget);

    // add items to mainLayoutPolicy
    mainLayoutPolicy->addItem(m_Container, Qt::AlignCenter);

    connect(dcpTime, SIGNAL(timeOrDateChanged()), this, SLOT(timeOrDateChanged()));
}

void TimeView::timeOrDateChanged()
{
    int hour, min;
    dcpTime->getTime(hour, min);
    m_TimePicker->setHours(hour);
    m_TimePicker->setMinutes(min);
}

