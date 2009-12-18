/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include "maintranslations.h"

const DcpCategoryInfo 
DcpMain::CategoryInfos[] = 
{
    {
        //% "Look & Feel"
	    QT_TRID_NOOP ("qtn_sett_main_look"),
    	"Look & Feel",
    	PageHandle::LOOKANDFEEL
    },
    {
        //% "Sounds"
        QT_TRID_NOOP ("qtn_sett_main_sound"),
        "Sound",
        PageHandle::SOUND
    },
    {
        //% "Connectivity"
        QT_TRID_NOOP ("qtn_sett_main_connectivity"),
        "Connectivity",
        PageHandle::CONNECTIVITY
    },
    {
        //% "Regional settings"
        QT_TRID_NOOP ("qtn_sett_main_region"),
        "Regional settings",
        PageHandle::REGIONALSETTING
    },
    {
        //% "Device utilities"
        QT_TRID_NOOP ("qtn_sett_main_device"),
        "Device utilities",
        PageHandle::DEVICEUTILITIES
    },
    {
        //% "Device system"
        QT_TRID_NOOP ("qtn_sett_main_data"),
        "Device system",
        PageHandle::DEVICESYSTEM
    },
    {
        //% "Accounts & Applications"
        QT_TRID_NOOP ("qtn_sett_main_combined"),
        "Accounts & Applications",
        PageHandle::ACCOUNTSANDAPPLICATIONS
    },
    {
        // The last element must have the .titleId == 0
	    0, 0, PageHandle::NOPAGE 
    }
};


//% "Settings"
const char* DcpMain::settingsTitleId = QT_TRID_NOOP("qtn_sett_main_title");

//% "Most recently used"
const char* DcpMain::mostRecentUsedTitleId = QT_TRID_NOOP("qtn_sett_main_most");

//% "Exit"
const char* DcpMain::quitMenuItemTextId = QT_TRID_NOOP("qtn_comm_exit");
