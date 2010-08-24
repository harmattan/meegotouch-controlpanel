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
    m_CategoryInfo (categoryInfo),
    m_AppletLoaderPos (0)
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
    for(int i=0; i<getItemCount(); i++) {
        DcpAppletMetadata* metadata = this->appletMetadata(i);
        if (metadata) {
            metadata->markInactive();
        }
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

void
DcpAppletButtons::startLoading()
{
    m_AppletLoaderPos = 0;
    m_AppletLoaderTimer = startTimer (0);
}

void
DcpAppletButtons::timerEvent(QTimerEvent *event)
{
    if (m_AppletLoaderTimer == event->timerId()) {

        // stop if loading finished:
        if (m_AppletLoaderPos >= getItemCount()) {
            killTimer (m_AppletLoaderTimer);
            emit loadingFinished();
            return;
        }

        // load the next applet:
        loadApplet (widgetAt (m_AppletLoaderPos));
        m_AppletLoaderPos++;
    }
}

DcpAppletMetadata*
DcpAppletButtons::appletMetadata (int pos)
{
    QGraphicsWidget* widget = widgetAt(pos);
    if (!widget) return 0;

    DcpContentItem* contentItem = qobject_cast<DcpContentItem*>(widget);
    if (contentItem) return contentItem->metadata();

    DcpContentButton* contentWidget = qobject_cast<DcpContentButton*>(widget);
    if (contentWidget) return contentWidget->metadata();

    return 0;
}

void DcpAppletButtons::loadApplet (QGraphicsObject* item)
{
    if (qobject_cast<DcpContentButton*> (item)) {
        qobject_cast<DcpContentButton*>(item)->loadApplet ();
    } else {
        qobject_cast<DcpContentItem*>(item)->loadApplet ();
    }
}

void
DcpAppletButtons::addComponent (DcpAppletMetadata *metadata)
{
    metadata->markActive();

    QGraphicsWidget *briefWidget;
    int widgetId = metadata->widgetTypeID();
    if (widgetId == DcpWidgetType::Button) {
            DcpContentButton *button = new DcpContentButton (0, this);
            button->setObjectName ("DcpContentButton");
            button->setMetadata (metadata);
            button->setMattiID ("DcpContentButton::" + logicalId() + "::" +
                             metadata->category() + "::" + metadata->name());
            briefWidget = button;
    } else {
            DcpContentItem *item = new DcpContentItem (0, this);
            item->setObjectName ("DcpContentItem");
            item->setMetadata (metadata);
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

