/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#ifndef DCPBRIEFCOMPONENT_FAKE_H
#define DCBRIEFCOMPONENT_FAKE_H
#include "dcpbriefcomponent.h"
#include "dcpappletmetadata-fake.h"
#include "dcpappletobject-fake.h"

DcpBriefComponent::DcpBriefComponent (
        DcpAppletObject   *applet,
        DcpComponent        *category,
        const QString       &logicalId)
: DcpComponent (category, "", 0, logicalId)
{
    Q_UNUSED(applet);
    Q_UNUSED(category);
    Q_UNUSED(logicalId);
}


DcpBriefComponent::~DcpBriefComponent()
{
}


void 
DcpBriefComponent::setApplet(
        DcpAppletObject* applet)
{
    Q_UNUSED(applet);
}

void
DcpBriefComponent::activate ()
{
}
#endif // DCPBRIEFCOMPONENT_FAKE_H
