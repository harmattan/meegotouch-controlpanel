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
        trid("dcp_title_personalization", "Personalization"),
        trid("dcp_desc_personalization",
             "Personalize the device with e.g.<br/> "
             "<font color=#e48415>profile, themes, fonts,<br/> "
             "home screen, language etc.</font>"
            ),
        "Personalization",
        Pages::PERSONALIZATION
    },
    {
        trid("dcp_title_connectivity", "Connectivity"), 
        trid("dcp_desc_connectivity",
             "Adjust connections of e.g. "
             "<font color=#e48415>"
             "Internet connection, Bluetooth, GPS etc.</font>"
            ),
        "Connectivity",
        Pages::CONNECTIVITY
    },
    {
        trid("dcp_title_display", "Display"), 
        trid("dcp_desc_display",
             "Adjust display appearance with e.g. "
             "<font color=#e48415>Light "
             "sensor, brightness etc.</font>"
            ),
        "Display",
        Pages::DISPLAY
    },
    {
        trid("dcp_title_sound", "Sound"), 
        trid("dcp_desc_sound",
             "Adjust tones for e.g. "
             "<font color=#e48415>"
             "Message alert, email "
             "alert etc.</font>"
            ),
        "Sound",
        Pages::SOUND
    },
    {
        trid("dcp_title_call", "Call"), 
        trid("dcp_desc_call",
             "Adjust settings with e.g. "
             "<font color=#e48415>"
             "call waiting, automatic redial etc.</font>"
            ),
        "Call",
        Pages::CALL
    },
    {
        trid("dcp_title_datetime", "Date & Time"), 
        trid("dcp_desc_datetime",
             "Adjust Date & Time with e.g. "
             "<font color=#e48415>"
             "time format and timezone.</font>"
            ),
        "DateTime",
        Pages::DATETIME
    },
    {
        trid("dcp_title_security", "Security"), 
        trid("dcp_desc_security",
             "Adjust phone security settings with e.g. "
             "<font color=#e48415>passcode, privacy lock"
             " etc.</font>"
            ),
        "Security",
        Pages::SECURITY
    },
    {
        trid("dcp_title_device", "Device system"), 
        trid("dcp_desc_device",
             "View <font color=#e48415>"
             "memory information</font> and "
             "<font color=#e48415>backup / restore "
             "data.</font>"
            ),
        "System",
        Pages::MAIN
    },
    {
        trid("dcp_title_account", "Account"), 
        trid("dcp_desc_account",
             "Create your own service accounts in e.g. "
             "<font color=#e48415>Ovi, Google, Yahooo "
             "etc. </font>and adjust settings for "
             "existing accounts,"
            ),
        "Account",
        Pages::ACCOUNTS
    },
    {
        trid("dcp_title_application", "Application"), 
        trid("dcp_desc_application",
             "Adjust settings for each application e.g. "
             "<font color=#e48415>Browser, Messaging, "
             "Calendar etc.</font>"
            ),
        "Application",
        Pages::APPLET
    },
    {"", "", "", Pages::NOPAGE}
	};

   const QString resetSettingsTitle = trid("dcp_title_reset_settings", "Reset settings");
   const QString resetSettingsDescription = trid("dcp_desc_reset_settings",
                                     "Reset network settings; Delete all media "
                                     "and data or reset all settings without "
                                     "deleting all media and data.");
   
   const QString settingsTitle = trid("dcp_title_settings", "Settings");
   
};
#endif // MAINTRANSLATIONS_H

