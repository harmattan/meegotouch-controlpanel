/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel.
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpappletbuttons.h"

DcpAppletButtons::DcpAppletButtons (
        const Category  *categoryInfo,
        QGraphicsWidget        *parent)
: DcpMainCategory (parent),
    m_CategoryInfo (categoryInfo)
{
}

void DcpAppletButtons::setCategoryInfo(const Category*)
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
        DcpAppletMetadata *metadata, QStandardItemModel*)
{
    Q_UNUSED(metadata);
}


bool
DcpAppletButtons::reload ()
{
    return true;
}

DcpAppletMetadata* DcpAppletButtons::appletMetadata(int)
{
    return 0;
}

int
DcpAppletButtons::metadataCount () const
{
    return 0;
}

QString DcpAppletButtons::mattiID() const
{
    return QString();
}

QString DcpAppletButtons::TDriverID() const
{
    return QString();
}

void DcpAppletButtons::setMattiID(QString const&)
{
}

void DcpAppletButtons::setTDriverID(QString const&)
{
}

void DcpAppletButtons::helpClicked(){}
