#include "timeview.h"
#include "dcpdatetime.h"
#include "datetimetranslation.h"
#include "dcpspaceritem.h"

#include <duilayout.h>
#include <duilinearlayoutpolicy.h>
#include <DuiWidget>
#include <duiscenemanager.h>
#include <duicontainer.h>

TimeView::TimeView(QGraphicsWidget *parent)
           :DcpWidget(parent)
{
    setReferer(DcpDateTime::Main);
    initWidget();
}

TimeView::~TimeView()
{
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
    DuiLayout *widgetLayout = new DuiLayout(centralWidget);
    widgetLayout->setAnimator(0);
    widgetLayout->setContentsMargins(0.0, 0.0, 0.0, 0.0);
    DuiLinearLayoutPolicy *widgetLayoutPolicy = 
        new DuiLinearLayoutPolicy(widgetLayout, Qt::Vertical);
    widgetLayoutPolicy->setSpacing(10);
    widgetLayout->setPolicy(widgetLayoutPolicy);
    centralWidget->setLayout(widgetLayout);

    // add items to widgetLayoutPolicy
    widgetLayoutPolicy->addItemAtPosition(
            new DcpSpacerItem(this, 
                DuiSceneManager::instance()->visibleSceneRect().width() - 35, 
                5, QSizePolicy::Fixed, QSizePolicy::Expanding), 0, Qt::AlignCenter);

    // setCentralWidget
    m_Container->setCentralWidget(centralWidget);

    // add items to mainLayoutPolicy
    mainLayoutPolicy->addItemAtPosition(m_Container, 0, Qt::AlignCenter);
}

