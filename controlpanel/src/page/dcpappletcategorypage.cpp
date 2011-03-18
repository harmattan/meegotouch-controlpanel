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

#include "dcpappletcategorypage.h"
#include "dcpsinglecomponent.h"
#include "dcpappletbuttons.h"
#include "dcpmaincategory.h"
#include "category.h"
#include "pages.h"
#include "dcpmostused.h"
#include "dcpdebug.h"

#include <DcpAppletDb>
#include <DcpAppletMetadata>
#include <DcpAppletObject>
#include <DcpRetranslator>

#include <QtDebug>
#include <QGraphicsLinearLayout>


DcpAppletCategoryPage::DcpAppletCategoryPage (
        const Category *categoryInfo) :
    DcpPage (),
    m_CategoryInfo (categoryInfo),
    m_Category (0),
    m_MostUsed (0)
{
}

DcpAppletCategoryPage::~DcpAppletCategoryPage ()
{
}

QGraphicsWidget*
DcpAppletCategoryPage::createCategories ()
{
    DcpMainCategory *otherCategories = new DcpMainCategory();
    QList<const Category*> categoryList;
    if (m_CategoryInfo) categoryList = m_CategoryInfo->children();
    if (categoryList.isEmpty()) {
        return otherCategories;
    }

    if (m_CategoryInfo->componentOrder() == Category::AppletsFirst) {
        otherCategories->appendSeparator();
    }

    foreach (const Category *info, categoryList) {
        DcpRetranslator::instance()->ensureTranslationsAreLoaded (
                info->translationCategories());
        DcpSingleComponent *button =
            new DcpSingleComponent(otherCategories, info);
        button->setSubPage(
                PageHandle(PageHandle::APPLETCATEGORY, info->name()));
        otherCategories->appendWidget(button);
    }

    if (m_CategoryInfo->componentOrder() == Category::CategoriesFirst) {
        otherCategories->appendSeparator();
    }

    return otherCategories;
}

void
DcpAppletCategoryPage::mostUsedAppears ()
{
    dcp_failfunc_unless (m_MostUsed);
    QGraphicsLinearLayout* layout = mainLayout();
    dcp_failfunc_unless (layout);
    layout->insertItem (1, m_MostUsed);
    m_MostUsed->show();
}

/*
 * Helper function which adds the "categories" and the "applets"
 * in the correct order to the layout
 */
void
DcpAppletCategoryPage::addCategoryToLayoutOrdered (
        QGraphicsLinearLayout* layout,
        QGraphicsWidget* category,
        QGraphicsWidget* appletBriefs)
{
    if (m_CategoryInfo->componentOrder() == Category::CategoriesFirst) {
        layout->addItem (category);
        layout->addItem (appletBriefs);
    } else {
        layout->addItem (appletBriefs);
        layout->addItem (category);
    }
}

void
DcpAppletCategoryPage::createContent ()
{
    DcpPage::createContent ();

    // Most Used Items:
    bool hasMostUsed = m_CategoryInfo->hasMostUsed();
    if (hasMostUsed) {
        m_MostUsed = new DcpMostUsed(this);
        m_MostUsed->hide ();
        connect (m_MostUsed, SIGNAL (itemsBecameAvailable()),
                 this, SLOT (mostUsedAppears()));
        if (m_MostUsed->itemsAvailable()) {
            mostUsedAppears();
        }
        connect (this, SIGNAL (appearing()), m_MostUsed, SLOT(refresh()));
    }

    // create the categories:
    QGraphicsWidget* categoryWidget = createCategories();

    // create the applet list:
    m_Category = new DcpAppletButtons(m_CategoryInfo);

    // add them to the layout:
    if (hasMostUsed) {
        // box around them:
        MContainer* container = new MContainer();
        container->setStyleName ("CommonContainerInverted");
        // TODO no retranslateUi is implemented for this -V
        //% "All settings"
        container->setTitle (qtTrId("qtn_sett_main_other"));
        mainLayout()->addItem(container);

        // put them in the box:
        QGraphicsLinearLayout* clayout =
            new QGraphicsLinearLayout (Qt::Vertical,
                                       container->centralWidget());
        addCategoryToLayoutOrdered (clayout, categoryWidget, m_Category);

    } else {
        // just add them to the layout without box:
        addCategoryToLayoutOrdered (mainLayout(), categoryWidget, m_Category);
    }

#ifdef PROGRESS_INDICATOR
    // show progress indicator while loading the applets:
    connect (m_Category, SIGNAL (loadingFinished()),
             this, SLOT (onLoadingFinished()));
    setProgressIndicatorVisible (true);
#endif
    mainLayout()->addStretch();

    retranslateUi();
}

const QString 
DcpAppletCategoryPage::appletCategory() const 
{
    return m_CategoryInfo->name();
}

void
DcpAppletCategoryPage::setCategoryInfo (
        const Category *categoryInfo)
{
    m_CategoryInfo = categoryInfo;
}

/*! \brief Returns the count of applets present in the active category.
 *
 * Note that it is not very cheap, because it forces the items (widgets) to be
 * loaded. So only use it in case you want to load the items anyway
 */
int
DcpAppletCategoryPage::appletCount()
{
    // this forces loading the items
    if (!isContentCreated()) {
        createContent();
    } else if (m_LoadedAppletCategory != appletCategory()) {
        m_Category->setCategoryInfo (m_CategoryInfo);
    }

    return m_Category->metadataCount();
}

/*! \brief Returns the metadata at the specified position.
 *
 * Note, the same applies as for appletCount().
 */
DcpAppletMetadata*
DcpAppletCategoryPage::appletMetadata(int i)
{
    if (i < appletCount()) {
        return m_Category->appletMetadata(i);
    } else {
        return 0;
    }
}

void
DcpAppletCategoryPage::retranslateUi()
{
    // briefwidgets take care of themselves, so we only update titles here
    setTitle(m_CategoryInfo ? m_CategoryInfo->title() : QString());
    if (isContentCreated()) {
        setTitleLabel ();
    }
}


void
DcpAppletCategoryPage::onLoadingFinished ()
{
#ifdef PROGRESS_INDICATOR
    setProgressIndicatorVisible (false);
#endif
}


