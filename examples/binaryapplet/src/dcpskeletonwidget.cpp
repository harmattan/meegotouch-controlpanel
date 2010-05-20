#include "dcpskeletonwidget.h"
#include "dcpskeleton.h"
#include <mlayout.h>
#include <mlinearlayoutpolicy.h>
#include <mlabel.h>

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
	
    //% "This is a skeleton applet, a minimal binaryapplet for controlpanel"
	m_aboutLabel = new MLabel(qtTrId("dcp_skel_appl_label"), this);
	m_aboutLabel->setObjectName("LabelAbout");
	
	mainLayoutPolicy->addItem(m_aboutLabel, Qt::AlignLeft);
    setLayout(mainLayout);
}

