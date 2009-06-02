#include "dcpbriefcomponent.h"

#include "dcpbriefwidget.h"
#include <DuiLayout>
#include <DuiLinearLayoutPolicy>

DcpBriefComponent::DcpBriefComponent(DcpAppletMetadata* metadata,
                                     DcpCategory *category)
    : DcpComponent(category),
      m_BriefWidget(new DcpBriefWidget(metadata, this))
{
	DuiLayout* layout = new DuiLayout(this);
    layout->setAnimator(0);
    layout->setContentsMargins(0,0,0,0);
    DuiLinearLayoutPolicy* policy = new DuiLinearLayoutPolicy (layout,
                                                               Qt::Vertical);
    policy->addItemAtPosition(m_BriefWidget,0);
    this->setLayout(layout);

    connect (m_BriefWidget, SIGNAL(clicked()), this, SLOT(switchToSubPage()));
}


void DcpBriefComponent::setMetadata(DcpAppletMetadata* metadata)
{
    m_BriefWidget->setMetadata(metadata);
}

