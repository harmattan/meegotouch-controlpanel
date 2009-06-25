#include "dateview.h"
#include "dcpdatetime.h"
#include "datetimetranslation.h"
#include "dcpspaceritem.h"

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <DuiWidget>
#include <duicontainer.h>
#include <duilabel.h>
#include <duiscenemanager.h>

DateView::DateView(QGraphicsWidget *parent)
           :DcpWidget(parent)
{
    setReferer(DcpDateTime::Main);
    initWidget();
}

DateView::~DateView()
{
}

void DateView::initWidget()
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

    m_Container = new DuiContainer(DcpDateTime::DateDialogTitle, this);
    
    // centralWidget
    DuiWidget *centralWidget = new DuiWidget(0);
    
    // widgetLayout
    DuiLayout *widgetLayout = new DuiLayout(centralWidget);
    widgetLayout->setAnimator(0);
    widgetLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    DuiLinearLayoutPolicy *widgetLayoutPolicy = 
        new DuiLinearLayoutPolicy(widgetLayout, Qt::Vertical);
    widgetLayoutPolicy->setSpacing(10);
    widgetLayout->setPolicy(widgetLayoutPolicy);
    centralWidget->setLayout(widgetLayout);

    // labelLayout
    DuiLayout *labelLayout = new DuiLayout(0);
    labelLayout->setAnimator(0);
    labelLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    DuiLinearLayoutPolicy *labelLayoutPolicy = 
        new DuiLinearLayoutPolicy(labelLayout, Qt::Horizontal);
    labelLayoutPolicy->setSpacing(10);
    labelLayout->setPolicy(labelLayoutPolicy);

    // labelVLayout
    DuiLayout *labelVLayout = new DuiLayout(0);
    labelVLayout->setAnimator(0);
    labelVLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    DuiLinearLayoutPolicy *labelVLayoutPolicy = 
        new DuiLinearLayoutPolicy(labelVLayout, Qt::Vertical);
    labelVLayoutPolicy->setSpacing(10);
    labelVLayout->setPolicy(labelVLayoutPolicy);

    // m_DateLabel
    m_DateLabel = new DuiLabel("Jun 25", this);
    m_DateLabel->setObjectName("DateViewLabel");
    m_DateLabel->setAlignment(Qt::AlignCenter);

    // m_WeekLabel
    m_WeekLabel = new DuiLabel("Week 26", this);
    m_WeekLabel->setObjectName("WeekViewLabel");
    m_WeekLabel->setAlignment(Qt::AlignCenter);

    // add items to labelVLayoutPolicy
    labelVLayoutPolicy->addItemAtPosition(m_DateLabel, 0, Qt::AlignCenter);
    labelVLayoutPolicy->addItemAtPosition(m_WeekLabel, 1, Qt::AlignCenter);

    // add items to labelLayoutPolicy
    labelLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 5, 5, QSizePolicy::Expanding, QSizePolicy::Fixed),
            0, Qt::AlignLeft | Qt::AlignVCenter);
    labelLayoutPolicy->addItemAtPosition(labelVLayout, 1, Qt::AlignCenter);
    labelLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 5, 5, QSizePolicy::Expanding ,QSizePolicy::Fixed),
            2, Qt::AlignRight | Qt::AlignVCenter);
    
    // add items to widgetLayoutPolicy
    widgetLayoutPolicy->addItemAtPosition(labelLayout, 0, Qt::AlignCenter);
    widgetLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 
                DuiSceneManager::instance()->visibleSceneRect().width() - 35, 
                5, QSizePolicy::Fixed, QSizePolicy::Expanding), 1, Qt::AlignCenter);

    // setCentralWidget
    m_Container->setCentralWidget(centralWidget);

    // add items to mainLayoutPolicy
    mainLayoutPolicy->addItemAtPosition(m_Container, 0, Qt::AlignCenter);
}

