#include "maintranslations.h"

#include <DuiLocale>

const DcpCategoryInfo DcpMain::CategoryInfos[] = {
    {
        trid("qtn_sett_main_seeing", "Look & Feel"),
        trid("qtn_sett_main_seeing_info",
             "Wallpaper, Theme, Touch feedback,<br>Display, LED light."
            ),
        "???????????????? Look & Feel ????????????????",
        Pages::LOOKANDFEEL
    },
    {
        trid("qtn_sett_main_connectivity", "Connectivity"),
        trid("qtn_sett_main_connectivity_info",
             "Offline mode, Internet connection,<br>"
             "Bluetooth, Positioning, Phone network."
            ),
        "Connectivity",
        Pages::CONNECTIVITY
    },
    {
        trid("qtn_sett_main_sound", "Sound"),
        trid("qtn_sett_main_sound_info",
             "Ringtone, Profile, Sound feedback,<br>"
             "Volume control."
            ),
        "Sound",
        Pages::SOUND
    },
    {
        trid("qtn_sett_main_regional", "Regional settings"),
        trid("qtn_sett_main_regional_info",
             "Date & Time, Region format, Language."
            ),
        "Regional settings",
        Pages::REGIONALSETTING
    },
    {
        trid("qtn_sett_main_account", "Service accounts"),
        trid("qtn_sett_main_account_info",
             "Ovi and other service accounts."
            ),
        "Account",
        Pages::ACCOUNTS
    },
    {
        trid("qtn_sett_main_device", "Device utilities"),
        trid("qtn_sett_main_device_info",
             "Synchronization, Backup/restore."
            ),
        "Device utilities",
        Pages::DEVICEUTILITIES
    },
    {
        trid("qtn_sett_application", "Application"),
        trid("qtn_sett_application_info",
             "Browser, Calendar, Messaging..."
            ),
        "Application",
        Pages::APPLICATION
    },
    {
        trid("qtn_sett_resetsettings", "Device system"),
        trid("qtn_sett_resetsettings_info",
             "Battery, Call & SIM, Passcode, "
             "Reset<br>settings, About."
            ),
        "Device system",
        Pages::DEVICESYSTEM
    },
    { QString(), QString(), QString(), Pages::NOPAGE }
};

const QString DcpMain::settingsTitle = trid("qtn_sett_title", "Settings");
const QString DcpMain::mostRecentUsedTitle = trid ("qtn_sett_main_most", "Most recent used");
const QString DcpMain::quitMenuItemText = trid("qtn_quit_main_text", "Exit");


