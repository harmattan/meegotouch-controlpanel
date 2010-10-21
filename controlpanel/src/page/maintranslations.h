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

#ifndef MAINTRANSLATIONS_H
#define MAINTRANSLATIONS_H

#include "pages.h"
#include <QtGlobal>

/*!
 * A structure that describes an applet category that should appear inside the
 * control panel.
 * titleId: The logical id of the UI text that will be shown as a category
 *   title at the top line of the category rectangle or as a title of the
 *   category page.
 * appletCategory: The category name that will be used as a filter to find the
 *   applet variants to be shown inside the category or category page.
 * subPageId: The page type that represents this category. Whan the page with
 *   this type id will be created this category structure should be used. 
 * staticEelements: An array pointer to the category infos that should be added
 *   to the category. 
 */
struct DcpCategoryInfo
{
    const char               *titleId;
    const char               *subtitleId;
    const char               *appletCategory;
    PageHandle::PageTypeId    subPageId;
    const char               *iconId;
    const DcpCategoryInfo    *staticElements;
};

namespace DcpMain {
   extern const DcpCategoryInfo CategoryInfos[];
   extern const char *settingsTitleId;
   extern const DcpCategoryInfo mostUsedCategory;
   extern const char *otherCategoriesTitleId;
   extern const char *quitMenuItemTextId;

   const DcpCategoryInfo *
   findCategoryInfo (PageHandle::PageTypeId   id,
                    const DcpCategoryInfo   *info = 0);
   const DcpCategoryInfo *
   findCategoryInfo (
        const QString           &name,
        const DcpCategoryInfo   *info = 0);

   bool
   isCategoryNameEnlisted (const QString &name);
}
#endif


