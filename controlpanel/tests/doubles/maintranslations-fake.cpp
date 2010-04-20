/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include "maintranslations.h"

const DcpCategoryInfo
DcpMain::CategoryInfos[] =
{
    {
        "qtn-fake",
        "fake-category",
        PageHandle::LOOKANDFEEL,
        NULL
    },
    {
        "qtn-fake-2",
        "fake-category-2",
        PageHandle::LOOKANDFEEL,
        NULL
    },
    {
        // The last element must have the .titleId == 0
        0, 0, PageHandle::NOPAGE, NULL
    }
};

const DcpCategoryInfo DcpMain::mostUsedCategory =
{
    "qtn_sett_main_most",
    "mostUsed-category",
    PageHandle::NOPAGE,
    NULL
};


const char* DcpMain::settingsTitleId = "qtn_sett_main_title";
const char* DcpMain::otherCategoriesTitleId = "qtn_sett_main_other";
const char* DcpMain::quitMenuItemTextId = "qtn_comm_exit";

const DcpCategoryInfo *
dcp_find_category_info (
        PageHandle::PageTypeId,
        const DcpCategoryInfo*)
{
    return NULL;
}

const DcpCategoryInfo *
dcp_find_category_info (
        const QString&,
        const DcpCategoryInfo*)
{
    return NULL;
}

bool
dcp_category_name_enlisted (
        const QString&)
{
    return true;
}
