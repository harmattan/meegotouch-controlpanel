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
#include "dcpdebug.h"
#include "dcpcontentitemcellcreator.h"
#include "dcpremoteappletobject.h"
#include "dcpappletif.h"
#include "dcpappletwidget.h"
#include "dcpappletpage.h"
#include "category.h"
#include "dcpcategories.h"

#include "pages.h"
#include "dcpappletmanager.h"
#include <DcpAppletMetadata>
#include <DcpApplet>
#include <DcpContentButton>
#include <DcpWidgetTypes>

#include <DcpRetranslator>

#include <MList>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QVariant>

#include <MHelpButton>

DcpAppletButtons::DcpAppletButtons (
        const Category *categoryInfo,
        QGraphicsWidget        *parent)
: DcpMainCategory (parent),
    m_CategoryInfo (categoryInfo),
    m_List (new MList(this))
{
    DcpContentItemCellCreator* cellCreator = new DcpContentItemCellCreator();
    m_List->setCellCreator(cellCreator);
    appendWidget (m_List);

    createContents ();
}


DcpAppletButtons::~DcpAppletButtons()
{
    markAllInactive();
}

QString DcpAppletButtons::mattiID () const
{
    return m_TDriverID;
}

void DcpAppletButtons::setMattiID (const QString &mattiID)
{
    m_TDriverID = mattiID;
}

QString DcpAppletButtons::TDriverID () const
{
    return m_TDriverID;
}

void DcpAppletButtons::setTDriverID (const QString &tdriverID)
{
    m_TDriverID = tdriverID;
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
    if (!m_CategoryInfo) return;

    /*
     * Getting the list of applet variants (metadata objects) that will go into
     * this widget.
     */
    DcpAppletMetadataList metadatas;
    bool isMostUsed = m_CategoryInfo->name() == MostUsed;
    if (isMostUsed) {
        metadatas = DcpAppletManager::instance()->listMostUsed();
    } else {
        bool withUncategorized = m_CategoryInfo->containsUncategorized();
        metadatas =
            DcpAppletManager::instance()->listByCategory (
                    m_CategoryInfo->referenceIds(),
                    withUncategorized ? DcpCategories::hasCategory : NULL);
    }

    // ensure that all needed catalogs are loaded for the applets before
    DcpRetranslator::instance()->ensureTranslationsAreLoaded(metadatas);

    // sort it: (mostused is already sorted)
    if (!isMostUsed) {
        qSort (metadatas.begin(), metadatas.end(),
               m_CategoryInfo->appletSort() == Category::SortByTitle ?
               DcpAppletMetadata::titleLessThan :
               DcpAppletMetadata::orderLessThan
        );
    }

    // add the elements:
    QStandardItemModel* model = new QStandardItemModel(m_List);
    foreach (DcpAppletMetadata* metadata, metadatas) {
        addComponent (metadata, model);
    }

    QAbstractItemModel* prevModel = m_List->itemModel();
    m_List->setItemModel (model);
    delete prevModel;

    setTDriverID (
            QString ("DcpAppletButtons::") +
            m_CategoryInfo->titleId() + "::" +
            m_CategoryInfo->name());
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

    dcp_failfunc_unless (pos < model->rowCount(), 0);
    dcp_failfunc_unless (pos >= 0, 0);

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
    DcpAppletManager* mng = DcpAppletManager::instance();
    if (mng->isAppletLoaded (name) || metadata->hasInProcessBrief()) {
        applet = mng->applet (name);
    } else {
        applet = new DcpRemoteAppletObject (metadata, model);
    }

    QString tdriverPostfix = QString(m_CategoryInfo->titleId()) +
                           "::" + metadata->category() + "::" + name;

    if (widgetId == DcpWidgetType::Button) {
        DcpContentButton *button = new DcpContentButton (applet);

        button->setTDriverID ("DcpContentButton::" + tdriverPostfix);
        button->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Fixed);

        // put it before the mlist:
        QGraphicsWidget* c = new QGraphicsWidget();
        QGraphicsWidget* spacer1 = new QGraphicsWidget();
        QGraphicsWidget* spacer2 = new QGraphicsWidget();
        c->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Fixed);
        spacer1->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
        spacer2->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
        QGraphicsLinearLayout* wlayout = new QGraphicsLinearLayout(c);
        wlayout->setContentsMargins(0,0,0,0);

        QString helpId = applet ? applet->helpId():
                         metadata ? metadata->helpId():
                         QString();
        if (!helpId.isEmpty()) {
            MHelpButton* help = new MHelpButton (helpId);
            help->setViewType(MButton::iconType);
            help->setIconID ("icon-s-description-inverse");
            wlayout->addItem (help);
        }

        wlayout->addItem (spacer1);
        wlayout->addItem (button);
        wlayout->addItem (spacer2);
        mLayout()->insertItem (getItemCount()-1, c);

    /*
     * The special type of applet brief creates its own icon,
     * please do not use it.
     */
    } else if (widgetId == DcpWidgetType::Special) {
        if (!applet || !applet->applet()) {
            qWarning ("Warning: no applet for special type of briefview, skipped");
            return;
        }

        int widgetId = applet->getMainWidgetId();
        // we can specify the page here if we need support for menu items, progress indicator etc
        DcpAppletWidget* widget =
            DcpAppletPage::constructAppletWidget (applet, 0, widgetId);
        if (!widget) {
            qWarning ("Warning: special type of briefview did not supply an icon, skipped");
            return;
        }
        widget->setParent (this);
        mLayout()->insertItem (getItemCount()-1, widget->graphicsWidget());
        mLayout()->setAlignment (widget->graphicsWidget(), Qt::AlignHCenter);

    } else if (widgetId == DcpWidgetType::Slider) {
        // unfortunately mlist does not seem to honor variable item height,
        // that is why this slider hack here:
        DcpContentItem *slider = new DcpContentItem (applet);
        if (!applet) slider->setMetadata (metadata);
        QString tdriverID = "DcpContentItem::" + tdriverPostfix;
        slider->setTDriverID (tdriverID);
        appendWidget (slider);

    }else {
        QString tdriverID = "DcpContentItem::" + tdriverPostfix;

        QStandardItem* item = new QStandardItem();
        item->setData (QVariant::fromValue(metadata),
                       DcpContentItemCellCreator::MetadataRole);
        item->setData (QVariant::fromValue(applet),
                       DcpContentItemCellCreator::AppletRole);
        item->setData (tdriverID, DcpContentItemCellCreator::TDriverRole);
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
DcpAppletButtons::setCategoryInfo (const Category *categoryInfo)
{
    if (m_CategoryInfo != categoryInfo) {
        m_CategoryInfo = categoryInfo;
        reload ();
    }
}

