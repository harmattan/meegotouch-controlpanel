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
#include "dcpcontentitemcellcreator.h"

#include <Pages>
#include <DcpAppletDb>
#include <DcpAppletMetadata>
#include <DcpAppletObject>
#include <DcpApplet>
#include <DcpContentButton>
#include <DcpWidgetTypes>

#include <DcpRetranslator>

#include <MList>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QVariant>

DcpAppletButtons::DcpAppletButtons (
        const DcpCategoryInfo  *categoryInfo,
        QGraphicsWidget        *parent)
: DcpMainCategory (parent),
    m_CategoryInfo (categoryInfo),
    m_AppletLoaderPos (0),
    m_List (new MList(this))
{
    DcpContentItemCellCreator* cellCreator = new DcpContentItemCellCreator();
    m_List->setCellCreator(cellCreator);
    appendWidget (m_List);

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
    for(int i=0; i<metadataCount(); i++) {
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
#ifdef MOSTUSED
    if (m_CategoryInfo == &DcpMain::mostUsedCategory) {
        metadatas = DcpAppletDb::instance()->listMostUsed ();
    } else 
#endif
    {
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


    // ensure that all needed catalogs are loaded for the applets before
    DcpRetranslator::instance()->ensureTranslationsAreLoaded(metadatas);

    // add the elements:
    QStandardItemModel* model = new QStandardItemModel(m_List);
    foreach (DcpAppletMetadata* metadata, metadatas) {
        addComponent (metadata, model);
    }

    QAbstractItemModel* prevModel = m_List->itemModel();
    m_List->setItemModel (model);
    delete prevModel;
}

void
DcpAppletButtons::startLoading()
{
    m_AppletLoaderPos = 0;

    if (metadataCount() > 0) {
        m_AppletLoaderTimer = startTimer (0);
    } else {
        emit loadingFinished();
    }
}

bool
DcpAppletButtons::loadingStepNext()
{
    // stop if loading finished:
    if (m_AppletLoaderPos >= metadataCount()-1) {
        killTimer (m_AppletLoaderTimer);
        emit loadingFinished();
        return false;
    }
    m_AppletLoaderPos++;
    return true;
}

/*
 * loads the applet of the widget in the specified row
 * returns true if the loading was necessery, otherwise
 *         false (the applet was already loaded)
 */
bool DcpAppletButtons::loadApplet (int row)
{
    DcpAppletMetadata* metadata = appletMetadata (row);
    DcpAppletDb* db = DcpAppletDb::instance();
    QString appletId = metadata->name();

    // if an applet is already loaded, we have to do nothing:
    if (db->isAppletLoaded(appletId)) return false;

    DcpAppletObject* applet = db->applet (appletId);
    if (applet->isAppletLoaded()) {
        QStandardItemModel* model =
            qobject_cast<QStandardItemModel*>(m_List->itemModel());
        Q_ASSERT (model);
        QStandardItem* item = model->item (row);
        item->setData (QVariant::fromValue(applet),
                       DcpContentItemCellCreator::AppletRole);
    } else {
        // if no applet got loaded, we did nothing:
        return false;
    }

    return true;
}



void
DcpAppletButtons::timerEvent(QTimerEvent *event)
{
    if (m_AppletLoaderTimer == event->timerId()) {
        // this loads the next applet (which is not loaded), exactly one in
        // every event
        bool wasLoadingNecessary;
        bool hasMoreItems;
        do {
            wasLoadingNecessary = loadApplet (m_AppletLoaderPos);
            hasMoreItems = loadingStepNext ();
            // end loop if an applet was loaded, or if there is no more items:
        } while (!wasLoadingNecessary && hasMoreItems);
    }
}

int
DcpAppletButtons::metadataCount () const
{
    QStandardItemModel* model =
        qobject_cast<QStandardItemModel*>(m_List->itemModel());
    if (!model) return 0;
    return model->rowCount();
}

DcpAppletMetadata*
DcpAppletButtons::appletMetadata (int pos)
{
    QStandardItemModel* model =
        qobject_cast<QStandardItemModel*>(m_List->itemModel());
    if (!model) return 0;

    Q_ASSERT (pos < model->rowCount());
    Q_ASSERT (pos >= 0);

    return model->item (pos)->data().value<DcpAppletMetadata*>();
}


void
DcpAppletButtons::addComponent (DcpAppletMetadata *metadata,
                                QStandardItemModel* model)
{
    metadata->markActive();

    int widgetId = metadata->widgetTypeID();

    // if the applet is already loaded, we skip the two step, and
    // set the applet directly instead of its metadata only
    DcpAppletObject* applet = 0;
    DcpAppletDb* db = DcpAppletDb::instance();
    QString name = metadata->name();
    if (db->isAppletLoaded (name)) {
        applet = db->applet (name);
    }

    QString mattiPostfix = QString(m_CategoryInfo->titleId) +
                           "::" + metadata->category() + "::" + name;

    if (widgetId == DcpWidgetType::Button) {
        DcpContentButton *button = new DcpContentButton (applet, this);
        if (!applet) {
//            in case it is needed we can load it later also
//            button->setMetadata (metadata);
            button->setApplet (db->applet(name));
        }
        button->setMattiID ("DcpContentButton::" + mattiPostfix);
        button->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Fixed);

        // put it before the mlist:
#if 0
        mLayout()->insertItem (getItemCount()-1, button);
#else
        // FIXME: this is a workaround for 188565 -  Offline mode button is left aligned...
        // It is a layout bug in Qt, please remove this, after NB#188780 gets fixed.

        QGraphicsWidget* spacer1 = new QGraphicsWidget();
        QGraphicsWidget* spacer2 = new QGraphicsWidget();
        spacer1->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
        spacer2->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
        QGraphicsLinearLayout* wlayout = new QGraphicsLinearLayout();
        wlayout->addItem (spacer1);
        wlayout->addItem (button);
        wlayout->addItem (spacer2);
        mLayout()->insertItem (getItemCount()-1, wlayout);
#endif

    } else {
        QString mattiID = "DcpContentItem::" + mattiPostfix;

        QStandardItem* item = new QStandardItem();
        item->setData (QVariant::fromValue(metadata),
                       DcpContentItemCellCreator::MetadataRole);
        item->setData (QVariant::fromValue(applet),
                       DcpContentItemCellCreator::AppletRole);
        item->setData (mattiID, DcpContentItemCellCreator::MattiRole);
        model->appendRow(item);
    }
}


bool
DcpAppletButtons::reload ()
{
    markAllInactive();

    // delete DcpContentButtons:
    for (int i=0; i<getItemCount()-1; i++) {
        QGraphicsWidget* w = widgetAt (i);
        delete w;
    }
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

