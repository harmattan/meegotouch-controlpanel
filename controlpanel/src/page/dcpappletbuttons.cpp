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
#include "maintranslations.h"
#include "dcpdebug.h"

#include <Pages>
#include <DcpAppletDb>
#include <DcpAppletMetadata>
#include <DcpAppletObject>
#include <DcpApplet>
#include <DcpWidgetTypes>
#include <DcpContentButton>
#include <DcpContentItem>

#include <MSceneManager>
// #include <MGridLayoutPolicy>
// #include <MLinearLayoutPolicy>
#include <DcpRetranslator>
#include <QGraphicsLayout>


DcpAppletButtons::DcpAppletButtons (
        const DcpCategoryInfo  *categoryInfo,
        const QString          &title,
        QGraphicsWidget        *parent)
: DcpMainCategory (title, parent, categoryInfo->titleId),
    m_CategoryInfo (categoryInfo)
{
    setCreateSeparators (false);
    setMaxColumns (1);
    createContents ();
    setMattiID (
            QString ("DcpAppletButtons::") + 
            categoryInfo->titleId + "::" + 
            categoryInfo->appletCategory);
}


DcpAppletButtons::~DcpAppletButtons()
{
    markAllInactive();
}

// marks all the appletmetadatas inactive, so they know they are "released"
void
DcpAppletButtons::markAllInactive()
{
    for(int i=0; i<layout()->count(); i++) {
        QGraphicsItem* item = layout()->itemAt(i)->graphicsItem();
        if (!item || !item->isWidget()) continue;
        QGraphicsWidget* widget = (QGraphicsWidget*) item;
        DcpContentItem* briefWidget = qobject_cast<DcpContentItem*>(widget);
        if (!briefWidget) continue;
        briefWidget->applet()->metadata()->markInactive();
    }
}


void
DcpAppletButtons::createContents ()
{
    DCP_DEBUG ("");
    /*
     * Getting the list of applet variants (metadata objects) that will go into
     * this widget.
     */
    DcpAppletMetadataList metadatas;
    if (m_CategoryInfo == &DcpMain::mostUsedCategory) {
        metadatas = DcpAppletDb::instance()->listMostUsed ();
    } else {
        bool        withUncategorized;
        const char *names[3];

        withUncategorized =
            m_CategoryInfo->subPageId == PageHandle::Applications;

        names[0] = m_CategoryInfo->titleId;
        names[1] = m_CategoryInfo->appletCategory;
        names[2] = 0;

        metadatas = DcpAppletDb::instance()->listByCategory (names, 2,
                    withUncategorized ? DcpMain::isCategoryNameEnlisted : NULL);
    }

    // ensure that all needed catalogs are loaded for the applets before construction
    DcpRetranslator::instance()->ensureTranslationsAreLoaded(metadatas);

    // adds the briefwidgets
    foreach (DcpAppletMetadata* item, metadatas) {
        addComponent (item);
    }
}

DcpAppletMetadata*
DcpAppletButtons::appletMetadata (int pos)
{
    QGraphicsWidget* widget = widgetAt(pos);
    if (!widget) return 0;
    DcpContentItem* contentItem = qobject_cast<DcpContentItem*>(widget);
    if (!contentItem) return 0;
    DcpAppletObject* applet = contentItem->applet();
    if (!applet) return 0;
    return applet->metadata();
}

void
DcpAppletButtons::addComponent (DcpAppletMetadata *metadata)
{
    metadata->markActive();

    // FIXME: we can avoid this additional lookup i guess
    QGraphicsWidget *briefWidget;
    DcpAppletObject* applet = DcpAppletDb::instance ()->applet (metadata->name());
    int widgetId = metadata->widgetTypeID();
    if (widgetId == DcpWidgetType::Button) {
            DcpContentButton *button = new DcpContentButton (applet, this);
            button->setObjectName ("DcpContentButton");
            button->setMattiID ("DcpContentButton::" + logicalId() + "::" +
                             metadata->category() + "::" + metadata->name());
            briefWidget = button;
        }
        else {   
            DcpContentItem *item = new DcpContentItem (applet, this);
            item->setObjectName ("DcpContentItem");
            item->setMattiID ("DcpContentItem::" + logicalId() + "::" +
                             metadata->category() + "::" + metadata->name());

            briefWidget = item;
    }
    briefWidget->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Fixed);
    appendWidget (briefWidget);
}


bool
DcpAppletButtons::reload ()
{
//    FIXME, maybe we could make it more optimal with reusing the existing
//    widgets (at most one additional widget is coming, at most one is to be
//    removed)
//

    markAllInactive();
    deleteItems ();
    createContents ();
    return true;
}

void
DcpAppletButtons::setCategoryInfo (const DcpCategoryInfo  *categoryInfo)
{
    if (m_CategoryInfo != categoryInfo) {
        m_CategoryInfo = categoryInfo;
        reload ();
    }
}

