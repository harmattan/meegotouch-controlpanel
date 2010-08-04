#include "dcpskeletonwidget.h"
#include "dcpskeleton.h"
#include <mlayout.h>
#include <mlinearlayoutpolicy.h>
#include <mlabel.h>
#include <QTimer>

SkeletonWidget::SkeletonWidget(QGraphicsWidget *parent)
	    :DcpWidget(parent)
{
    setReferer(DcpSkeleton::NoReferer);
    initWidget();

    // this demonstrates the usage of the progress indicator:
    setProgressIndicatorVisible (true);
    QTimer::singleShot ( 3000, this, SLOT(loadingFinished()) );
}

void
SkeletonWidget::loadingFinished()
{
    setProgressIndicatorVisible (false);
}

SkeletonWidget::~SkeletonWidget()
{
    if (m_MainLayout)
        delete m_MainLayout;
    if (m_MainLayoutPolicy)
        delete m_MainLayoutPolicy;
}


void SkeletonWidget::initWidget()
{
    MLayout *m_MainLayout = new MLayout(this);
    m_MainLayout->setAnimation(0);
    MLinearLayoutPolicy *m_MainLayoutPolicy =
            new MLinearLayoutPolicy(m_MainLayout, Qt::Horizontal);
    m_MainLayout->setPolicy(m_MainLayoutPolicy);
	
    //% "This is a skeleton applet, a minimal binaryapplet for controlpanel"
	m_aboutLabel = new MLabel(qtTrId("dcp_skel_appl_label"), this);
	m_aboutLabel->setObjectName("LabelAbout");
	
	m_MainLayoutPolicy->addItem(m_aboutLabel, Qt::AlignLeft);
    setLayout(m_MainLayout);
}

