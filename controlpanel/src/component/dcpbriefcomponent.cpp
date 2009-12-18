/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include "dcpbriefcomponent.h"
#include "dcpappletmetadata.h"
#include "dcpbriefwidget.h"
#include "pages.h"

#include <QGraphicsLinearLayout>


#define DEBUG
#include "../../../lib/src/dcpdebug.h"

DcpBriefComponent::DcpBriefComponent (
		DcpAppletMetadata   *metadata,
		DcpCategory         *category,
		const QString       &logicalId)
: DcpComponent (category,"", 0, logicalId),
    m_BriefWidget (new DcpBriefWidget (metadata, this))
{
    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout (this);
    layout->addItem (m_BriefWidget);

    setMattiID ("DcpBriefComponent::" + logicalId + "::" + 
		    metadata->category() + "::" + metadata->name());
}

DcpBriefComponent::~DcpBriefComponent()
{
}


void 
DcpBriefComponent::setMetadata (
        DcpAppletMetadata* metadata)
{
    m_BriefWidget->setMetadata(metadata);
}

QString DcpBriefComponent::mattiID()
{
    return m_mattiID;
}

void 
DcpBriefComponent::setMattiID (
        const QString &mattiID)
{
    m_mattiID = mattiID;
}

