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
#include "dcpcategorycomponent.h"
#include "dcpappletbuttons.h"

#include <MContainer>
#include <QGraphicsLinearLayout>

#include "dcpdebug.h"

/*!
 * Constructor that uses DcpCategoryInfo to create a DcpCategoryComponent.
 */
DcpCategoryComponent::DcpCategoryComponent (
            DcpComponent            *category, 
            const DcpCategoryInfo  *categoryInfo,
            QGraphicsWidget        *parent)
: DcpComponent (category, categoryInfo->appletCategory, parent, 
                categoryInfo->titleId),
    m_AppletButtons(0),
    m_CategoryInfo (categoryInfo)
{
    createContents ();
    setMattiID (QString("DcpCategoryComponent::") + categoryInfo->titleId);

    // this component is a convenience one and should not be visible for the user
    // at all, thus disabling margins.
    setContentsMargins(0,0,0,0);
    layout()->setContentsMargins(0,0,0,0);
    retranslateUi();
}


DcpCategoryComponent::~DcpCategoryComponent()
{
}


void
DcpCategoryComponent::setTitle (
        const QString &title)
{
    m_AppletButtons->setTitle (title);
    m_Container->setTitle (title);
    DcpComponent::setTitle (title);
}

void
DcpCategoryComponent::retranslateUi()
{
    if (m_CategoryInfo) {
        setTitle (qtTrId (m_CategoryInfo->titleId));
    } else {
        setTitle (qtTrId (DCP_STR(m_LogicalId)));
    }
}

void
DcpCategoryComponent::createContents ()
{
    QGraphicsLinearLayout *layout;

    DCP_DEBUG ("");
    m_Container = new MContainer (this);
    m_Container->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout = new QGraphicsLinearLayout (Qt::Vertical, this);
    layout->addItem (m_Container);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    m_AppletButtons = new DcpAppletButtons (m_CategoryInfo, title());

    m_Container->setCentralWidget (m_AppletButtons);
}

bool 
DcpCategoryComponent::reload ()
{
    DCP_DEBUG ("WARNING: RELOADING");
    return m_AppletButtons->reload();
}

// ! Can be misleading, because it returns the count of the items already loaded
int
DcpCategoryComponent::getItemCount ()
{
    return m_AppletButtons ? m_AppletButtons->getItemCount () : 0;
}

