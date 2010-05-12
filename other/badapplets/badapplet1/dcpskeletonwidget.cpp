#include <MLayout>
#include <MLinearLayoutPolicy>
#include <MLabel>
#include "dcpskeletonwidget.h"
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
    MLayout *mainLayout = new MLayout(this);
    mainLayout->setAnimation(0);
    MLinearLayoutPolicy *mainLayoutPolicy = 
            new MLinearLayoutPolicy(mainLayout, Qt::Horizontal);
    mainLayout->setPolicy(mainLayoutPolicy);
	
    m_aboutLabel = new MLabel("About", this);
    m_aboutLabel->setObjectName("LabelAbout");
	
    mainLayoutPolicy->addItem(m_aboutLabel, Qt::AlignLeft);
    setLayout(mainLayout);

    qDebug("Bad applet 1 aborted when creating the widget");
    abort();
}

