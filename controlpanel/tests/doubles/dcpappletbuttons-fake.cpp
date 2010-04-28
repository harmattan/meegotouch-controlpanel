/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpappletbuttons.h"

DcpAppletButtons::DcpAppletButtons (
        const DcpCategoryInfo  *categoryInfo,
        const QString          &title,
        QGraphicsWidget        *parent)
: DcpMainCategory (title, parent, categoryInfo->titleId),
    m_CategoryInfo (categoryInfo)
{
}

DcpAppletButtons::~DcpAppletButtons ()
{
}

void
DcpAppletButtons::createContents ()
{
}

void
DcpAppletButtons::addComponent (
        DcpAppletMetadata *metadata)
{
    Q_UNUSED(metadata);
}


bool
DcpAppletButtons::reload ()
{
    return true;
}


