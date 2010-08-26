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

/*
 * The applet categories that will be shown in the main window of the control
 * panel.
 */
const DcpCategoryInfo 
DcpMain::CategoryInfos[] = 
{
    {
        //% "Look & Feel"
        QT_TRID_NOOP ("qtn_sett_main_look"),
        "Look & Feel",
        PageHandle::LOOKANDFEEL,
        NULL
    },
    {
        //% "Connectivity"
        QT_TRID_NOOP ("qtn_sett_main_connectivity"),
        "Connectivity",
        PageHandle::CONNECTIVITY,
        NULL
    },
    {
        //% "Time & Language"
        QT_TRID_NOOP ("qtn_sett_main_region"),
        "Regional settings",
        PageHandle::REGIONALSETTING,
        NULL
    },
    {
        //% "Device system"
        QT_TRID_NOOP ("qtn_sett_main_data"),
        "Device system",
        PageHandle::DEVICESYSTEM,
        NULL
    },
    {
        //% "Utilities"
        QT_TRID_NOOP ("qtn_sett_main_utilities"),
        "Utilities",
        PageHandle::UTILITIES,
        NULL
    },
    {
        //% "Accounts"
        QT_TRID_NOOP ("qtn_comm_command_accounts"),
        "qtn_sett_main_account", // this is for backward compatibility only
        PageHandle::ServiceAccounts,
        NULL
    },
    {
        //% "Application settings"
        QT_TRID_NOOP ("qtn_sett_main_application"),
        "Applications",
        PageHandle::Applications,
        NULL
    },
    {
        // The last element must have the .titleId == 0
        0, 0, PageHandle::NOPAGE, NULL
    }
};

const DcpCategoryInfo DcpMain::mostUsedCategory =
{
    //% "Recently used"
    QT_TRID_NOOP("qtn_sett_main_most"),
    "MostUsed",
    PageHandle::NOPAGE,
    NULL
};


//% "Settings"
const char* DcpMain::settingsTitleId = QT_TRID_NOOP("qtn_sett_main_title");

//% "All settings"
const char* DcpMain::otherCategoriesTitleId = QT_TRID_NOOP("qtn_sett_main_other");
//% "Exit"
const char* DcpMain::quitMenuItemTextId = QT_TRID_NOOP("qtn_comm_exit");

/*!
 * Will find a DcpCategoryInfo by the page type id. Uses recirsive search to
 * find sub-categories.
 */
const DcpCategoryInfo *
DcpMain::findCategoryInfo (
        PageHandle::PageTypeId   id,
        const DcpCategoryInfo   *info)
{
    /*
     * The default place to find infos.
     */
    if (info == 0) {
        info = DcpMain::CategoryInfos;
    }

    for (int n = 0; ; ++n) {
        /*
         * The end of the array.
         */
        if (info[n].titleId == 0) {
            return 0;
        }

        /*
         * If found it.
         */
        if (info[n].subPageId == id)
            return &info[n];

        /*
         * If we have a chance to search recursively.
         */
        if (info[n].staticElements != 0) {
            const DcpCategoryInfo *retval;

            retval = findCategoryInfo (id, info[n].staticElements);
            if (retval)
                return retval;
        }
    }

    return 0;
}

/*!
 * Will find the category info by name checking both the localized version and 
 * the logical id.
 */
const DcpCategoryInfo *
DcpMain::findCategoryInfo (
        const QString           &name,
        const DcpCategoryInfo   *info)
{
    /*
     * The default place to find infos.
     */
    if (info == NULL) {
        info = DcpMain::CategoryInfos;
    }

    for (int n = 0; ; ++n) {
        /*
         * The end of the array.
         */
        if (info[n].titleId == 0)
            return 0;

        /*
         * If found it.
         */
        if (!name.compare (info[n].titleId, Qt::CaseInsensitive) ||
                !name.compare (info[n].appletCategory, Qt::CaseInsensitive)) 
            return &info[n];

        /*
         * If we have a chance to search recursively.
         */
        if (info[n].staticElements != NULL) {
            const DcpCategoryInfo *retval;

            retval = findCategoryInfo (name, info[n].staticElements);
            if (retval)
                return retval;
        }
    }

    return NULL;
}

/*!
 * \brief Check if the category name is 'recognized' by the duicontrolpanel.
 * 
 * This function is used to decide if a given category name is a supported
 * 'official' category name of the control panel. If an applet has a category
 * name that is not supported as offical the applet will appear in the
 * 'applications' category that is shown as a sub-page.
 */
bool
DcpMain::isCategoryNameEnlisted (
        const QString           &name)
{
    bool retval;

    /*
     * If the category name can be found in this inline database it is official.
     */
    retval = findCategoryInfo (name) != 0;
    if (retval)
        return retval;

    /*
     * Checking additional category names. FIXME: Should be more robust not to
     * mention the localization; I don't know what is the logical string for
     * 'Startup'.
     */
    if (name == "Startup")
        return true;

    return false;
}
