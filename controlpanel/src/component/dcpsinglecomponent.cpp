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
#include "pagefactory.h"
#include "dcpsinglecomponent.h"
#include "pages.h"

#include "dcpdebug.h"
#include <MImageWidget>


DcpSingleComponent::DcpSingleComponent (
        QGraphicsWidget     *parent,
        const QString       &logicalId,
        const QString       &title,
        const QString       &imageId,
        const QString       &subTitle)
: MBasicListItem(subTitle.isEmpty() ? MBasicListItem::IconWithTitle:
                 MBasicListItem::IconWithTitleAndSubtitle, parent)
{
    setTitle(title);
    imageWidget()->setImage (imageId);
    setSubtitle(subTitle);

    connect(this, SIGNAL (clicked()),
            this, SLOT (activate()));

    m_MattiID = "DcpSingleComponent::" + logicalId;
}

DcpSingleComponent::~DcpSingleComponent()
{
}

void
DcpSingleComponent::activate ()
{
    PageFactory *pageFactory = PageFactory::instance();
    pageFactory->changePage (subPage());
}

