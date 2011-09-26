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
#include "categoryutils.h"

#include "pages.h"
#include "dcpappletmanager.h"
#include <DcpAppletMetadata>
#include <DcpApplet>
#include <DcpContentButton>
#include <DcpContentItem>
#include <DcpWidgetTypes>

#include "dcptranslationmanager.h"

#include <MList>
#include <MListItem>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QVariant>
#include <MSeparator>
#include <MHelpButton>
#include <MLabel>
#include <QGraphicsLinearLayout>
#include <MStylableWidget>

DcpAppletButtons::DcpAppletButtons (
        const Category *categoryInfo,
        QGraphicsWidget        *parent,
        DcpPage        *ownerPage)
: DcpMainCategory (parent),
    m_CategoryInfo (categoryInfo),
    m_List (new MList(this)),
    m_Page (ownerPage),
    m_SubHeader (0),
    m_HasButton (false)
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
DcpAppletButtons::retranslateUi()
{
    QString subHeaderText = m_CategoryInfo ? m_CategoryInfo->subHeaderText()
                            : QString();
    if (m_SubHeader) {
        m_SubHeader->setText (subHeaderText);
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
        metadatas = CategoryUtils::metadataList (m_CategoryInfo);
    }

    // ensure that all needed catalogs are loaded for the applets before
    DcpTranslationManager::instance()->ensureTranslationsAreLoaded(metadatas);

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
    QStringList mainApplets = m_CategoryInfo->mainApplets();
    foreach (DcpAppletMetadata* metadata, metadatas) {
        addComponent (metadata, model, mainApplets);
    }

    // spacer for the buttons if any
    if (m_HasButton) {
        insertSpacer (getItemCount()-1);
    }

    QString subHeaderText = m_CategoryInfo->subHeaderText();

    // separator for the main applets
    // if we do not have a subheader
    if (!mainApplets.isEmpty() && subHeaderText.isEmpty()) {
        MSeparator* sep = new MSeparator();
        sep->setStyleName ("CommonItemDividerInverted");
        mLayout()->insertItem (getItemCount()-1, sep);
    }

    // subheader with separator if we have
    if (!subHeaderText.isEmpty() && !mainApplets.isEmpty() && !m_SubHeader) {
        MStylableWidget* row = new MStylableWidget();
        row->setStyleName ("CommonGroupHeaderPanelInverted");

        QGraphicsLinearLayout *lout =
            new QGraphicsLinearLayout(Qt::Horizontal, row);
        lout->setContentsMargins(0, 0, 0, 0);
        lout->setSpacing(0);

        MSeparator *sep = new MSeparator();
        sep->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sep->setContentsMargins(0, 0, 0, 0);
        sep->setStyleName("CommonGroupHeaderDividerInverted");

        m_SubHeader = new MLabel (subHeaderText);
        m_SubHeader->setStyleName ("CommonGroupHeaderInverted");
        lout->addItem(sep);
        lout->setAlignment (sep, Qt::AlignVCenter);
        lout->addItem(m_SubHeader);

        mLayout()->insertItem (getItemCount()-1, lout);
    }

    // subheader without separator
    if (!subHeaderText.isEmpty() && mainApplets.isEmpty() && !m_SubHeader) {
        m_SubHeader = new MLabel (subHeaderText);
        m_SubHeader->setStyleName ("CommonBodyTextInverted");
        mLayout()->insertItem (getItemCount()-1, m_SubHeader);
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
                                QStandardItemModel* model,
                                const QStringList& mainApplets)
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

    // main applets are the first applets of a category, visually separated
    // from the others:
    if (mainApplets.contains (name)) {
        mLayout()->insertItem (getItemCount()-1,
                               createDefault (applet, metadata));
        return;
    }

    switch (widgetId) {
        case DcpWidgetType::Button:
            if (!m_HasButton) {
                m_HasButton = true;
                insertSpacer (getItemCount()-1);
            }
            mLayout()->insertItem (getItemCount()-1,
                               createButton (applet, metadata));
            break;

        case DcpWidgetType::Special: {
            /*
             * The special type of applet brief creates its own icon,
             * please do not use it.
             */
            QGraphicsWidget* widget = createSpecial (applet);
            if (widget) {
                mLayout()->insertItem (getItemCount()-1, widget);
                mLayout()->setAlignment (widget, Qt::AlignHCenter);
            }
            }
            break;

        case DcpWidgetType::Slider:
            // unfortunately mlist does not seem to honor variable item height,
            // that is why this slider hack here:
            appendWidget (createSlider(applet, metadata));
            break;

        default: {
            // the normal items come into the list:
            QString tdriverID = genTDriverID("DcpContentItem::", metadata);

            QStandardItem* item = new QStandardItem();
            item->setData (QVariant::fromValue(metadata),
                           DcpContentItemCellCreator::MetadataRole);
            item->setData (QVariant::fromValue(applet),
                           DcpContentItemCellCreator::AppletRole);
            item->setData (tdriverID, DcpContentItemCellCreator::TDriverRole);
            model->appendRow(item);
                 }
            break;
    };
}

QGraphicsWidget* DcpAppletButtons::createSlider (DcpAppletObject* applet,
                                                 DcpAppletMetadata* metadata)
{
    DcpContentItem *slider = new DcpContentItem (applet);
    if (!applet) slider->setMetadata (metadata);
    slider->setTDriverID (genTDriverID("DcpContentItem::", metadata));
    return slider;
}

QString DcpAppletButtons::genTDriverID (const char* prefix,
                                        DcpAppletMetadata* metadata)
{
    return prefix + m_CategoryInfo->titleId() + "::" +
           metadata->category() + "::" + metadata->name();
}

QGraphicsWidget* DcpAppletButtons::createSpecial (DcpAppletObject* applet)
{
    if (!applet || !applet->applet()) {
        qWarning ("Warning: no applet for special type of briefview, skipped");
        return 0;
    }

    int widgetId = applet->getMainWidgetId();
    // we can specify the page here if we need support for menu items, progress indicator etc
    DcpAppletWidget* widget =
        DcpAppletPage::constructAppletWidget (applet, m_Page, widgetId);
    if (!widget) {
        qWarning ("Warning: special type of briefview did not supply an icon, skipped");
        return 0;
    }
    widget->setParent (this);
    return widget->graphicsWidget();
}

QGraphicsWidget* DcpAppletButtons::createButton (DcpAppletObject* applet,
                                                 DcpAppletMetadata* metadata)
{
    DcpContentButton *button = new DcpContentButton (applet);
    if (!applet) {
        button->setMetadata (metadata);
    }

    button->setTDriverID (genTDriverID("DcpContentButton::", metadata));
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
    return c;
}

QGraphicsWidget* DcpAppletButtons::createDefault (DcpAppletObject* applet,
        DcpAppletMetadata* metadata)
{
    DcpContentItem* cell = new DcpContentItem();
    cell->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Fixed);

    if (applet) {
        cell->setApplet (applet);
    } else {
        cell->setMetadata (metadata);
    }

    cell->setTDriverID (genTDriverID("DcpContentItem::", metadata));
    return cell;
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

