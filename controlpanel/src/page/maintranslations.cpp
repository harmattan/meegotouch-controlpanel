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
        //% "Connections"
        QT_TRID_NOOP ("qtn_sett_main_connections"),
        //% "Internet, Bluetooth, Network"
        QT_TRID_NOOP ("qtn_sett_main_connections_label2"),
        "Connections",
        PageHandle::CONNECTIVITY,
        "icon-m-common-wlan",
        0
    },
    {
        //% "Phone"
        QT_TRID_NOOP ("qtn_sett_main_phone"),
        //% "Call, SIM card"
        QT_TRID_NOOP ("qtn_sett_main_phone_label2"),
        "Phone",
        PageHandle::PHONE,
        "icon-m-content-call",
        0
    },
    {
        //% "Applications"
        QT_TRID_NOOP ("qtn_sett_main_applications"),
        //% "Installations, Application settings"
        QT_TRID_NOOP ("qtn_sett_main_applictions_label2"),
        "Applications",
        PageHandle::Applications,
        "icon-m-settings-applications",
        0
    },
    {
        //% "Notifications"
        QT_TRID_NOOP ("qtn_sett_main_notifications"),
        //% "Home screen feed, Alerts"
        QT_TRID_NOOP ("qtn_sett_main_notifications_label2"),
        "Notifications",
        PageHandle::NOTIFICATIONS,
        "icon-m-common-notification",
        0
    },
    {
        //% "Personalize"
        QT_TRID_NOOP ("qtn_sett_main_personalize"),
        //% "Wallpaper, Theme, Sounds"
        QT_TRID_NOOP ("qtn_sett_main_presonalize_label2"),
        "Personalize",
        PageHandle::PERSONALIZE,
        "icon-m-settings-personalize",
        0
    },
    {
        //% "Battery"
        QT_TRID_NOOP ("qtn_sett_main_battery"),
        //% "Display, battery"
        QT_TRID_NOOP ("qtn_sett_main_battery__label2"),
        "Battery",
        PageHandle::BATTERY,
        "icon-m-energy-management-battery-verylow",
//        "icon-m-energy-management-battery-low",
        0
    },
    {
        //% "Security"
        QT_TRID_NOOP ("qtn_sett_main_security"),
        //% "Lock code, Passwords & Certificates"
        QT_TRID_NOOP ("qtn_sett_main_security_label2"),
        "Security",
        PageHandle::SECURITY,
        "icon-m-settings-personalize",
        0
    },
    {
        //% "Time & Date"
        QT_TRID_NOOP ("qtn_sett_main_timedate"),
        //% "Time, Date, Region"
        QT_TRID_NOOP ("qtn_sett_main_clock_label2"),
        "Time & Date",
        PageHandle::REGIONALSETTING,
        "icon-m-common-clock",
        0
    },
    {
        //% "Language & Keyboard"
        QT_TRID_NOOP ("qtn_sett_main_language"),
        //% "Language, Text input"
        QT_TRID_NOOP ("qtn_sett_main_language_label2"),
        "Language & Keyboard",
        PageHandle::LANGUAGEKEYBOARD,
        "icon-m-common-keyboard",
        0
    },
    {
        //% "Accessories"
        QT_TRID_NOOP ("qtn_sett_main_accessories"),
        //% "USB, TV-out, Tele coil"
        QT_TRID_NOOP ("qtn_sett_main_accessories_label2"),
        "Accessories",
        PageHandle::ACCESSORIES,
        "icon-m-settings-accessories",
        0
    },
    {
        //% "Sync & Backup"
        QT_TRID_NOOP ("qtn_sett_main_backup"),
        //% "Device synchronization, Backup"
        QT_TRID_NOOP ("qtn_sett_main_backup_sub"),
        "Sync & Backup",
        PageHandle::BACKUP,
        "icon-m-common-device-root",
        0
    },
    {
        //% "About my device"
        QT_TRID_NOOP ("qtn_sett_main_aboutmy"),
        //% "Warranty, About product"
        QT_TRID_NOOP ("qtn_sett_main_aboutmy_label2"),
        "About my device",
        PageHandle::ABOUT,
        "icon-m-content-description",
        0
    },
    {
        // The last element must have the .titleId == 0
        0, 0, 0, PageHandle::NOPAGE, 0, 0
    }
};

const DcpCategoryInfo DcpMain::mostUsedCategory =
{
    //% "Recently used"
    QT_TRID_NOOP("qtn_sett_main_most"),
    QT_TRID_NOOP("qtn_sett_main_most"),
    "MostUsed",
    PageHandle::NOPAGE,
    0,
    0
};

// logical category for the mainpage
const DcpCategoryInfo DcpMain::mainPageCategory =
{
    "MainPage",
    "MainPage",
    "MainPage",
    PageHandle::NOPAGE,
    0,
    0
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
    if (name == mainPageCategory.titleId) {
        return &mainPageCategory;
    }

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
        if (info[n].staticElements != 0) {
            const DcpCategoryInfo *retval;

            retval = findCategoryInfo (name, info[n].staticElements);
            if (retval)
                return retval;
        }
    }

    return 0;
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
