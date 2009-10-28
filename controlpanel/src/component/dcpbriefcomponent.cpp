#include "dcpbriefcomponent.h"

#include <DcpBriefWidget>
#include <QGraphicsLinearLayout>
#include <QDebug>
DcpBriefComponent::DcpBriefComponent(DcpAppletMetadata* metadata,
                                     DcpCategory *category,
                                     const QString& logicalId)
    : DcpComponent(category,"", 0, logicalId),
      m_BriefWidget(new DcpBriefWidget(metadata, this))
{
    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout(this);
//    layout->setContentsMargins(0,0,0,0);
    layout->addItem(m_BriefWidget);

    connect (m_BriefWidget, SIGNAL(clicked()), this, SLOT(switchToSubPage()));
    qDebug() << "@@@@@@" << this->logicalId();
}

DcpBriefComponent::~DcpBriefComponent()
{
}

void DcpBriefComponent::setMetadata(DcpAppletMetadata* metadata)
{
    m_BriefWidget->setMetadata(metadata);
}

