#include "dcpbriefcomponent.h"

#include <DcpBriefWidget>
#include <QGraphicsLinearLayout>
#include <DcpAppletMetadata>

DcpBriefComponent::DcpBriefComponent(
		DcpAppletMetadata* metadata,
		DcpCategory *category,
		const QString& logicalId)
    : DcpComponent (category,"", 0, logicalId),
      m_BriefWidget (new DcpBriefWidget(metadata, this))
{
    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout(this);
    layout->addItem(m_BriefWidget);

    setMattiID ("DcpBriefComponent::" + logicalId + "::" + 
		    metadata->category() + "::" + metadata->name());

    connect (m_BriefWidget, SIGNAL(clicked()), this, SLOT(switchToSubPage()));
    connect (metadata, SIGNAL (activateApplet()), 
		    this, SLOT(switchToSubPage()));
}

DcpBriefComponent::~DcpBriefComponent()
{
}

void DcpBriefComponent::setMetadata(DcpAppletMetadata* metadata)
{
    m_BriefWidget->setMetadata(metadata);
}

QString DcpBriefComponent::mattiID()
{
    return m_mattiID;
}

void DcpBriefComponent::setMattiID(const QString &mattiID)
{
    m_mattiID=mattiID;
}

