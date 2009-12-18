/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#ifndef MAINTRANSLATIONS_H
#define MAINTRANSLATIONS_H

typedef struct _DcpCategoryInfo DcpCategoryInfo;
#include <Pages>
#include <DuiLocale>

struct _DcpCategoryInfo
{
    const char* titleId;
    const char* appletCategory;
    PageHandle::PageTypeId subPageId;
};

namespace DcpMain {
   extern const DcpCategoryInfo CategoryInfos[];
   extern const char* settingsTitleId;
   extern const char* mostRecentUsedTitleId;
   extern const char* quitMenuItemTextId;
};

#endif // MAINTRANSLATIONS_H


