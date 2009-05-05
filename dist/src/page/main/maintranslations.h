#ifndef MAINTRANSLATIONS_H
#define MAINTRANSLATIONS_H
#include <DuiLocale>

typedef struct _DcpCategoryInfo DcpCategoryInfo;
#include "pages.h"

struct _DcpCategoryInfo
{
    QString title;
    QString description;
    QString appletCategory;
    Pages::Id subPageId;
};

namespace DcpMain {
static const DcpCategoryInfo CategoryInfos[] = {
    {
        trid("qtn_sett_main_seeing", "Seeing & Touching"),
        trid("qtn_sett_main_seeing_info",
             "Adjust settings for e.g. <font color=#e48415>"
             "Wallpaper, Theme, Brightness, Touch feedback, etc."
            ),
        "Seeing & Touching",
        Pages::SEEINGTOUCHING
    },
    {
        trid("qtn_sett_main_connectivity", "Connectivity"),
        trid("qtn_sett_main_connectivity_info",
             "Adjust connections of e.g. "
             "<font color=#e48415>"
             "Internet connection, Bluetooth, GPS etc.</font>"
            ),
        "Connectivity",
        Pages::CONNECTIVITY
    },
    {
        trid("qtn_sett_main_sound", "Sound"),
        trid("qtn_sett_main_sound_info",
             "Adjust settings for e.g. "
             "<font color=#e48415>"
             "Ringtone, profile, volume control, system sound"
             " etc.</font>"
            ),
        "Sound",
        Pages::SOUND
    },
    {
        trid("qtn_sett_main_regional", "Regional settings"),
        trid("qtn_sett_main_regional_info",
             "Adjust Language & Time setting with e.g. "
             "<font color=#e48415>region format and timezone, etc.</font>"
            ),
        "RegionalSettings",
        Pages::REGIONALSETTING
    },
    {
        trid("qtn_sett_main_account", "Service accounts"),
        trid("qtn_sett_main_account_info",
             "Create your own service accounts in e.g. "
             "<font color=#e48415>Ovi, Google, Yahooo "
             "etc. </font>and adjust settings for "
             "existing accounts,"
            ),
        "Account",
        Pages::ACCOUNTS
    },
    {
        trid("qtn_sett_main_device", "Device system"),
        trid("qtn_sett_main_device_info",
             "Adjust system settings with e.g. <font color=#e48415>"
             "Battery, Call & SIM, passcode, Sync, </font> and "
             "<font color=#e48415>Backup / restore "
             "</font>"
            ),
        "System",
        Pages::DEVICESYSTEM
    },
    {
        trid("qtn_sett_application", "Application"),
        trid("qtn_sett_application_info",
             "Adjust settings for each application e.g. "
             "<font color=#e48415>Browser, Messaging, "
             "Calendar etc.</font>"
            ),
        "Application",
        Pages::APPLICATION
    },
    {
        trid("qtn_sett_resetsettings", "Reset settings"),
        trid("qtn_sett_resetsettings_info",
             "Delete all media "
             "and data or reset all settings without "
             "deleting media and data."
            ),
        "Reset settings",
        Pages::RESETSETTINGS
    },
    {"", "", "", Pages::NOPAGE}
	};
   
   const QString settingsTitle = trid("qtn_sett_title", "Settings");
   const QString mostRecentUsedTitle = trid ("qtn_sett_main_most", "Most recent used");
   const QString quitMenuItemText = trid("qtn_quit_main_text", "Exit");
};
#endif // MAINTRANSLATIONS_H
