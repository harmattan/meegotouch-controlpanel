/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include "dcpbriefcomponent.h"

#include <DcpBriefWidget>
#include <QGraphicsLinearLayout>
#include <DcpAppletMetadata>

#include "pages.h"

#define DEBUG
#include "../../../lib/src/dcpdebug.h"

DcpBriefComponent::DcpBriefComponent (
		DcpAppletMetadata   *metadata,
		DcpCategory         *category,
		const QString       &logicalId)
: DcpComponent (category,"", 0, logicalId),
    m_BriefWidget (new DcpBriefWidget(metadata, this))
{
    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout(this);
    layout->addItem(m_BriefWidget);

    setMattiID ("DcpBriefComponent::" + logicalId + "::" + 
		    metadata->category() + "::" + metadata->name());

    /*
     * Here is how we activate an applet. When the user clicks on the widget we
     * send a signal to the metadata, then the metadata will do what it needs to
     * do in order to appear on the screen.
     */
    connect (m_BriefWidget, SIGNAL (clicked()),
        metadata, SIGNAL (activate ()));
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

void DcpBriefComponent::setMattiID(const QString &mattiID)
{
    m_mattiID = mattiID;
}

