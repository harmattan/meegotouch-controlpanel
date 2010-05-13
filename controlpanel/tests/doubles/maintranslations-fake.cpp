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
DcpMain::findCategoryInfo (
        PageHandle::PageTypeId,
        const DcpCategoryInfo*)
{
    return NULL;
}

const DcpCategoryInfo *
DcpMain::findCategoryInfo (
        const QString&,
        const DcpCategoryInfo*)
{
    return NULL;
}

bool
DcpMain::isCategoryNameEnlisted (
        const QString&)
{
    return true;
}
