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

#include "dcpsinglecomponent.h"


DcpSingleComponent::DcpSingleComponent (
        QGraphicsWidget     *category,
        const QString       &logicalId,
        const QString       &title,
        const QString       &iconId,
        const QString       &subTitle)
: MBasicListItem (MBasicListItem::TitleWithSubtitle)
{
    Q_UNUSED(category);
    Q_UNUSED(logicalId);
    Q_UNUSED(title);
    Q_UNUSED(iconId);
    Q_UNUSED(subTitle);
}

DcpSingleComponent::~DcpSingleComponent()
{
}

void
DcpSingleComponent::activate ()
{
}

QGraphicsLayout *DcpSingleComponent::createLayout()
{
    return 0;
}

