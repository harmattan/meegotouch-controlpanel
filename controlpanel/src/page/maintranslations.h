/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#ifndef MAINTRANSLATIONS_H
#define MAINTRANSLATIONS_H

typedef struct _DcpCategoryInfo DcpCategoryInfo;
#include <Pages>
#include <DuiLocale>

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
struct _DcpCategoryInfo
{
    const char               *titleId;
    const char               *appletCategory;
    PageHandle::PageTypeId    subPageId;
    const DcpCategoryInfo    *staticElements;
};

namespace DcpMain {
   extern const DcpCategoryInfo CategoryInfos[];
   extern const char *settingsTitleId;
   extern const char *mostRecentUsedTitleId;
   extern const char *quitMenuItemTextId;
};

#endif


