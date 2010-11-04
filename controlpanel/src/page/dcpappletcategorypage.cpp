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
#include "dcpappletbuttons.h"
#include <QDebug>

#include <DcpAppletDb>
#include <DcpAppletMetadata>
#include <DcpAppletObject>
#include <DcpRetranslator>

#include "dcpdebug.h"

DcpAppletCategoryPage::DcpAppletCategoryPage (
        const DcpCategoryInfo  *categoryInfo) :
    DcpPage (),
    m_CategoryInfo (categoryInfo),
    m_TitleId(0),
    m_Category(0)
{
}

DcpAppletCategoryPage::~DcpAppletCategoryPage ()
{
}

void 
DcpAppletCategoryPage::createContent ()
{
    DcpPage::createContent ();

    m_Category = new DcpAppletButtons(m_CategoryInfo);
    mainLayout()->addItem (m_Category);

#ifdef PROGRESS_INDICATOR
    // show progress indicator
    connect (m_Category, SIGNAL (loadingFinished()),
             this, SLOT (onLoadingFinished()));
    setProgressIndicatorVisible (true);
#endif

    retranslateUi();
}

const QString 
DcpAppletCategoryPage::appletCategory() const 
{
    return m_CategoryInfo->appletCategory;
}

void 
DcpAppletCategoryPage::setCategoryInfo (
        const DcpCategoryInfo *categoryInfo) 
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
    }

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
    setTitle(qtTrId(m_TitleId));
    if (isContentCreated()) {
        setTitleLabel ();
    }
}

void
DcpAppletCategoryPage::setTitleId(const char* titleId)
{
    m_TitleId = titleId;
    retranslateUi();
}


void
DcpAppletCategoryPage::onLoadingFinished ()
{
#ifdef PROGRESS_INDICATOR
    setProgressIndicatorVisible (false);
#endif
}


