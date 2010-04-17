/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#ifndef DCPSINGLECOMPONENT_FAKE_H
#define DCPSINGLECOMPONENT_FAKE_H
#include "dcpsinglecomponent.h"


DcpSingleComponent::DcpSingleComponent (
        DcpComponent        *category,
        const QString       &logicalId,
        const QString       &title,
        const QString       &subTitle)
: DcpComponent (category, "", 0, logicalId)
{

    Q_UNUSED(category);
    Q_UNUSED(logicalId);
    Q_UNUSED(title);
    Q_UNUSED(subTitle);
}

DcpSingleComponent::~DcpSingleComponent()
{
}

void
DcpSingleComponent::activate ()
{
}

void
DcpSingleComponent::setTitle (const QString& title)
{
    Q_UNUSED(title);
}

QString
DcpSingleComponent::title() const
{
    return "";
}


void
DcpSingleComponent::setSubtitle (const QString& subTitle)
{
    Q_UNUSED(subTitle);
}
#endif
