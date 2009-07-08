#include "dcpbriefcomponent.h"

#include "dcpbriefwidget.h"
#include <QGraphicsLinearLayout>

DcpBriefComponent::DcpBriefComponent(DcpAppletMetadata* metadata,
                                     DcpCategory *category)
    : DcpComponent(category),
      m_BriefWidget(new DcpBriefWidget(metadata, this))
{
    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addItem(m_BriefWidget);

    connect (m_BriefWidget, SIGNAL(clicked()), this, SLOT(switchToSubPage()));
}


void DcpBriefComponent::setMetadata(DcpAppletMetadata* metadata)
{
    m_BriefWidget->setMetadata(metadata);
}

