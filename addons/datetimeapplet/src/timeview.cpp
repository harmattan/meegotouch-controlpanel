#include "timeview.h"
#include "dcpdatetime.h"
#include "datetimetranslation.h"
#include "dcpspaceritem.h"
#include "analogclock.h"

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <DuiWidget>
#include <duiscenemanager.h>
#include <duicontainer.h>
#include <QGraphicsLinearLayout>


TimeView::TimeView(QGraphicsWidget *parent)
           :DcpWidget(parent)
{
    setReferer(DcpDateTime::Main);
    initWidget();
}

TimeView::~TimeView()
{
	delete m_TimePicker;
	m_TimePicker = NULL;
}

void TimeView::initWidget()
{
    // mainLayout
    DuiLayout *mainLayout = new DuiLayout(this);
    mainLayout->setAnimator(0);
    mainLayout->setContentsMargins(0.0, 12.0, 0.0, 12.0);
    DuiLinearLayoutPolicy *mainLayoutPolicy =
        new DuiLinearLayoutPolicy(mainLayout, Qt::Vertical);
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
/*    AnalogClock *analogClock = new AnalogClock(centralWidget);
    analogClock->setMinimumSize(QSize(300, 300));
    analogClock->setMaximumSize(QSize(300, 300));

	widgetLayout->addItem(new DcpSpacerItem(centralWidget, 10, 10, QSizePolicy::Expanding, QSizePolicy::Preferred));
    widgetLayout->addItem(analogClock);
    widgetLayout->setAlignment(analogClock, Qt::AlignCenter);
    widgetLayout->addItem(new DcpSpacerItem(centralWidget, 10, 10, QSizePolicy::Expanding, QSizePolicy::Preferred));
*/

	m_TimePicker = new SettingAlarm;
    //AnalogClock *analogClock = new AnalogClock(centralWidget);
    m_TimePicker->setMinimumSize(QSize(400, 400));
    m_TimePicker->setMaximumSize(QSize(400, 400));

	widgetLayout->addItem(new DcpSpacerItem(centralWidget, 10, 10, QSizePolicy::Expanding, QSizePolicy::Preferred));
    widgetLayout->addItem(m_TimePicker);
    widgetLayout->setAlignment(m_TimePicker, Qt::AlignCenter);
    widgetLayout->addItem(new DcpSpacerItem(centralWidget, 10, 10, QSizePolicy::Expanding, QSizePolicy::Preferred));


    // setCentralWidget
    m_Container->setCentralWidget(centralWidget);

    // add items to mainLayoutPolicy
    mainLayoutPolicy->addItemAtPosition(m_Container, 0, Qt::AlignCenter);

    // orientation change
    connect(DuiSceneManager::instance(), SIGNAL(orientationChanged(const Dui::Orientation &)),
            this, SLOT(orientationChnaged()));
    orientationChanged();
}

void TimeView::orientationChanged()
{
    DuiSceneManager *manager = DuiSceneManager::instance();
    if (manager == 0)
        return;
}

