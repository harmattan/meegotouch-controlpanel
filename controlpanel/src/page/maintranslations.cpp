/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include "maintranslations.h"

static const DcpCategoryInfo
AccountsAndApplicationsElements[] = 
{
    {
        //% "Service accounts"
        QT_TRID_NOOP ("qtn_sett_main_account"),
        "Service accounts",
        PageHandle::ServiceAccounts,
        NULL
    },
    {
        //% "Applications"
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
        //% "Language & Region"
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
        //% "Accounts & Applications"
        QT_TRID_NOOP ("qtn_sett_main_combined"),
        "Accounts & Applications",
        PageHandle::ACCOUNTSANDAPPLICATIONS,
        AccountsAndApplicationsElements
    },
    {
        // The last element must have the .titleId == 0
        0, 0, PageHandle::NOPAGE, NULL
    }
};


//% "Settings"
const char* DcpMain::settingsTitleId = QT_TRID_NOOP("qtn_sett_main_title");

//% "Most recently used"
const char* DcpMain::mostRecentUsedTitleId = QT_TRID_NOOP("qtn_sett_main_most");

//% "Exit"
const char* DcpMain::quitMenuItemTextId = QT_TRID_NOOP("qtn_comm_exit");

/*!
 * Will find a DcpCategoryInfo by the page type id. Uses recirsive search to
 * find sub-categories.
 */
const DcpCategoryInfo *
dcp_find_category_info (
        PageHandle::PageTypeId   id,
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
        if (info[n].staticElements != NULL) {
            const DcpCategoryInfo *retval;

            retval = dcp_find_category_info (id, info[n].staticElements);
            if (retval)
                return retval;
        }
    }

    return NULL;
}

/*!
 * Will find the category info by name checking both the localized version and 
 * the logical id.
 */
const DcpCategoryInfo *
dcp_find_category_info (
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

            retval = dcp_find_category_info (name, info[n].staticElements);
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
dcp_category_name_enlisted (
        const QString           &name)
{
    bool retval;

    /*
     * If the category name can be found in this inline database it is official.
     */
    retval = dcp_find_category_info (name) != NULL;
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
