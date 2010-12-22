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
#include "dcpdebug.h"

#include <DcpAppletDb>
#include <DcpAppletMetadata>
#include <DcpAppletObject>
#include <DcpRetranslator>

#include <QtDebug>
#include <MPannableViewport>
#include <QGraphicsLinearLayout>


DcpAppletCategoryPage::DcpAppletCategoryPage (
        const Category *categoryInfo) :
    DcpPage (),
    m_CategoryInfo (categoryInfo),
    m_Category(0)
{
}

DcpAppletCategoryPage::~DcpAppletCategoryPage ()
{
}

void
DcpAppletCategoryPage::createCategories ()
{
    QGraphicsLinearLayout *layout = mainLayout ();
    dcp_failfunc_unless(layout);

    DcpMainCategory *otherCategories = new DcpMainCategory();
    QList<const Category*> categoryList;
    if (m_CategoryInfo) {
        categoryList = m_CategoryInfo->children();
    }

    foreach (const Category *info, categoryList) {
        DcpSingleComponent *button;

        button = new DcpSingleComponent(otherCategories, info->titleId(),
                                        info->iconId(), info->subtitleId());
        button->setSubPage(PageHandle(PageHandle::APPLETCATEGORY, info->name()));
        otherCategories->appendWidget(button);
    }

    layout->addItem(otherCategories);
}

void
DcpAppletCategoryPage::createContent ()
{
    DcpPage::createContent ();

    // create the categories:
    createCategories();

    // create the applet list:
    m_Category = new DcpAppletButtons(m_CategoryInfo);
    mainLayout()->addItem (m_Category);

#ifdef PROGRESS_INDICATOR
    // show progress indicator while loading the applets:
    connect (m_Category, SIGNAL (loadingFinished()),
             this, SLOT (onLoadingFinished()));
    setProgressIndicatorVisible (true);
#endif

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
DcpAppletCategoryPage::reload ()
{
    DCP_DEBUG ("");

    if (m_LoadedAppletCategory != appletCategory()) {
        m_Category->setCategoryInfo (m_CategoryInfo);
        retranslateUi();
    }

    // move the page to the top:
    pannableViewport()->setPosition (QPointF(0,0));

    DcpPage::reload();
}

void DcpAppletCategoryPage::back ()
{
    DcpPage::back();
}

void
DcpAppletCategoryPage::retranslateUi()
{
    // briefwidgets take care of themselves, so we only update title here
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


