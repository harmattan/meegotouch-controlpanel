/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include "dcpbriefcomponent.h"

#include "dcpcontentitem.h"
#include "dcpappletmetadata.h"
#include "dcpappletobject.h"
//#include "dcpwidgettypes.h"
#include "pages.h"

#include <QGraphicsLinearLayout>


#include "dcpdebug.h"


DcpBriefComponent::DcpBriefComponent (
        DcpAppletObject   *applet,
        DcpComponent        *category,
        const QString       &logicalId)
: DcpComponent (category, "", 0, logicalId)
{
    applet->metadata()->markActive();
    m_BriefWidget = new DcpContentItem (applet, this);
    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout (this);
    layout->addItem (m_BriefWidget);

    setMattiID ("DcpBriefComponent::" + logicalId + "::" + 
            applet->metadata()->category() + "::" + applet->metadata()->name());
}


DcpBriefComponent::~DcpBriefComponent()
{
    m_BriefWidget->applet()->metadata()->markInactive();
}


void
DcpBriefComponent::setApplet(
        DcpAppletObject* applet)
{
    m_BriefWidget->setApplet(applet);
}


