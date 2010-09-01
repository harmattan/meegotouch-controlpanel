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
#include "dcpmaincategory.h"

#include "dcpdebug.h"

DcpMainCategory::DcpMainCategory (
        QGraphicsWidget *parent,
        const QString& logicalId)
: DcpComponent (0, "", parent, logicalId)
{
    QGraphicsLinearLayout* layout =
        new QGraphicsLinearLayout(Qt::Vertical, this);

    // main category is an invisible "pure logical" widget, thats why we
    // need no margins here
    layout->setContentsMargins (0,0,0,0);
    layout->setSpacing (0);
}


void
DcpMainCategory::deleteItems ()
{
    QGraphicsLinearLayout* layout = mLayout();
    if (!layout) return;

    // delete all items in all policies:

    for (int i = layout->count() - 1; i >= 0; i--){
        QGraphicsWidget* widget = (QGraphicsWidget*)
                                  (layout->itemAt(i)->graphicsItem());
        Q_ASSERT (widget);
        layout->removeItem (widget);
        widget->deleteLater ();
    }
}


QGraphicsWidget*
DcpMainCategory::widgetAt (int i)
{
    QGraphicsLinearLayout* layout = mLayout();
    if (i>=layout->count()) return 0;
    QGraphicsLayoutItem* item = layout->itemAt(i);
    if (! item) return 0;
    return (QGraphicsWidget*)(item->graphicsItem());
}



