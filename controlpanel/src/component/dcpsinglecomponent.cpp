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
#include "category.h"

#include <QtGui/QGraphicsGridLayout>

#include <MImageWidget>
#include <MLabel>
#include <MImageWidget>


DcpSingleComponent::DcpSingleComponent (
        QGraphicsWidget     *parent,
        const Category      *category )
: MBasicListItem(category->subtitleId().isEmpty() ? MBasicListItem::IconWithTitle:
                 MBasicListItem::IconWithTitleAndSubtitle, parent),
                 m_TDriverID ("DcpSingleComponent::" + category->titleId()),
                 m_Category (category)
{
    setObjectName (QString());
    setStyleName("CommonPanelInverted");

    connect(this, SIGNAL (clicked()), this, SLOT (activate()));
    retranslateUi ();
}

DcpSingleComponent::~DcpSingleComponent()
{
}

void DcpSingleComponent::retranslateUi()
{
    dcp_failfunc_unless (m_Category);

    setTitle (m_Category->title());
    QString subtitle = m_Category->subtitle();
    if (!subtitle.isEmpty()) {
        setSubtitle (subtitle);
    }
}

QGraphicsLayout *DcpSingleComponent::createLayout()
{
    QGraphicsGridLayout *layout = new QGraphicsGridLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    bool hasTwoLabels = !subtitleLabelWidget()->text().isEmpty();
    int maxRowCount = hasTwoLabels ? 3 : 1;

    QString imageId = m_Category->iconId();
    bool hasImage = !imageId.isEmpty();
    if (hasImage) {
        imageWidget()->setStyleName("CommonMainIcon");
        imageWidget()->setImage (imageId);
        layout->addItem(imageWidget(), 0, 0, maxRowCount, 1);
        layout->setAlignment(imageWidget(), Qt::AlignVCenter | Qt::AlignLeft);
    }

    titleLabelWidget()->setStyleName("CommonTitleInverted");
    layout->addItem(titleLabelWidget(), 0, 1);

    if (hasTwoLabels) {
        layout->setAlignment(titleLabelWidget(), Qt::AlignTop | Qt::AlignLeft);
        subtitleLabelWidget()->setStyleName("CommonSubTitleInverted");
        layout->addItem(subtitleLabelWidget(), 1, 1);

        layout->addItem(new QGraphicsWidget(), 2, 1);
    }

    MImageWidget *drillImage =
        new MImageWidget("icon-m-common-drilldown-arrow-inverse", this);
    drillImage->setStyleName("CommonDrillDownIcon");
    layout->addItem(drillImage, 0, 2, maxRowCount, 1);
    layout->setAlignment(drillImage, Qt::AlignVCenter | Qt::AlignRight);

    return layout;
}

void
DcpSingleComponent::activate ()
{
    PageFactory *pageFactory = PageFactory::instance();
    pageFactory->changePage (subPage());
}

