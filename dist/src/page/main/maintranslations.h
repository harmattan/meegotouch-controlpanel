#ifndef MAINTRANSLATIONS_H
#define MAINTRANSLATIONS_H
#include <DuiLocale>
namespace Dcp {
static const QString componentTexts[] = {
    trid("dcp_title_personalization","Personalization"), /* <- title */
    trid("dcp_desc_personalization","<p>Personalize the device with e.g. "
                            "<font color=#e48415>profile, themes, fonts, "
                            "home screen, language etc.</font></p>"),
    trid("dcp_title_connectivity", "Connectivity"), /* <- title */
    trid("dcp_desc_connectivity","<p>Adjust connections of e.g. "
                            "<font color=#e48415>"
                            "Internet connection, Bluetooth, GPS etc.</font></p>"),
    trid("dcp_title_display", "Display"), /* <- title */
    trid("dcp_desc_display","<p>Adjust display appearance with e.g. "
                            "<font color=#e48415>Light "
                            "sensor, brightness etc.</font></p>"),
    trid("dcp_title_sound", "Sound"), /* <- title */
    trid("dcp_desc_sound","<p>Adjust tones for e.g. "
                            "<font color=#e48415>"
                            "Message alert, email "
                            "alert etc.</font></p>"),
    trid("dcp_title_call", "Call"), /* <- title */
    trid("dcp_desc_call","<p>Adjust settings with e.g. "
                            "<font color=#e48415>"
                            "call waiting, automatic redial etc.</font></p>"),
    trid("dcp_title_datetime", "Date & Time"), /* <- title */
    trid("dcp_desc_datetime","<p>Adjust Date & Time with e.g. "
                            "<font color=#e48415>"
                            "time format and timezone.</font></p>"),
    trid("dcp_title_security", "Security"), /* <- title */
    trid("dcp_desc_security","<p>Adjust phone security settings with e.g. "
                            "<font color=#e48415>passcode, privacy lock"
                            " etc.</font></p>"),
    trid("dcp_title_device", "Device system"), /* <- title */
    trid("dcp_desc_device","<p>View <font color=#e48415>"
                            "memory information</font> and "
                            "<font color=#e48415>backup / restore "
                            "data.</font></p>"),
    trid("dcp_title_account", "Account"), /* <- title */
    trid("dcp_desc_account","<p>Create your own service accounts in e.g. "
                            "<font color=#e48415>Ovi, Google, Yahooo "
                            "etc. </font>and adjust settings for "
                            "existing accounts,</p>"),
    trid("dcp_title_application", "Application"), /* <- title */
    trid("dcp_desc_application","<p>Adjust settings for each application e.g. "
                            "<font color=#e48415>Browser, Messaging, "
                            "Calendar etc.</font></p>"),
    QString()
	};
    
   const QString resetSettingsTitle = trid("dcp_title_reset_settings", "Reset settings");
   const QString resetSettingsDescription = trid("dcp_desc_reset_settings",
                                     "Reset network settings; Delete all media "
                                     "and data or reset all settings without "
                                     "deleting all media and data.");
   
   const QString settingsTitle = trid("dcp_title_settings", "Settings");
   
};
#endif // MAINTRANSLATIONS_H

