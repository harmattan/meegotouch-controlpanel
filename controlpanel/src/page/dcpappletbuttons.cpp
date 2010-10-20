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
#include "dcpremoteappletobject.h"

#include <Pages>
#include <DcpAppletDb>
#include <DcpAppletMetadata>
#include <DcpApplet>
#include <DcpContentButton>
#include <DcpWidgetTypes>

#include <DcpRetranslator>

#include <MList>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QVariant>
#include <HelpButton>

DcpAppletButtons::DcpAppletButtons (
        const DcpCategoryInfo  *categoryInfo,
        QGraphicsWidget        *parent)
: DcpMainCategory (parent),
    m_CategoryInfo (categoryInfo),
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
    QString name = metadata->name();
    DcpAppletDb* db = DcpAppletDb::instance();
    if (db->isAppletLoaded (name) || metadata->binary().isEmpty()

        /*
         * TODO the outprocess implementation supports handling of the toggle
         * state, but currently offline applet wants to create dialog and
         * notification which requires it to be loaded. We could make an
         * api for doing so, and then we could load this kind of applet icon
         * in separate process as well
         */
        || widgetId == DcpWidgetType::Button

       ) {
        applet = db->applet (name);
    } else {
        applet = new DcpRemoteAppletObject (metadata, model);
    }

    QString mattiPostfix = QString(m_CategoryInfo->titleId) +
                           "::" + metadata->category() + "::" + name;

    if (widgetId == DcpWidgetType::Button) {
        DcpContentButton *button = new DcpContentButton (applet);

        button->setMattiID ("DcpContentButton::" + mattiPostfix);
        button->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Fixed);

        // put it before the mlist:
        QGraphicsWidget* c = new QGraphicsWidget();
        QGraphicsWidget* spacer1 = new QGraphicsWidget();
        QGraphicsWidget* spacer2 = new QGraphicsWidget();
        c->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
        spacer1->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
        spacer2->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
        QGraphicsLinearLayout* wlayout = new QGraphicsLinearLayout(c);
        wlayout->setContentsMargins(0,0,0,0);
        QString helpId = applet ? applet->helpId():
                         metadata ? metadata->helpId():
                         QString();
        if (!helpId.isEmpty()) {
            HelpButton* help = new HelpButton (helpId);
            help->setViewType(MButton::iconType);
            help->setIconID ("icon-m-content-description");
            wlayout->addItem (help);
        }
        wlayout->addItem (spacer1);
        wlayout->addItem (button);
        wlayout->addItem (spacer2);
        mLayout()->insertItem (getItemCount()-1, c);

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
    markAllInactive ();

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

