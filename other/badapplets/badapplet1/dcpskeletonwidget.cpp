#include <DuiLayout>
#include <DuiLinearLayoutPolicy>
#include <DuiLabel>
#include "dcpskeletonwidget.h"
#include "translations.h"
#include "dcpskeleton.h"

const int widgetWidth = 100;

SkeletonWidget::SkeletonWidget(QGraphicsWidget *parent)
	    :DcpWidget(parent)
{
    setReferer(DcpSkeleton::NoReferer);
    initWidget();
}

SkeletonWidget::~SkeletonWidget()
{
}


void SkeletonWidget::initWidget()
{
    DuiLayout *mainLayout = new DuiLayout(this);
    mainLayout->setAnimator(0);
    DuiLinearLayoutPolicy *mainLayoutPolicy = 
            new DuiLinearLayoutPolicy(mainLayout, Qt::Horizontal);
    mainLayout->setPolicy(mainLayoutPolicy);
	
    m_aboutLabel = new DuiLabel(DcpSkeleton::About, this);
    m_aboutLabel->setObjectName("LabelAbout");
	
    mainLayoutPolicy->addItem(m_aboutLabel, Qt::AlignLeft);
    setLayout(mainLayout);

    qDebug("Bad applet 1 aborted when creating the widget");
    abort();
}

