#ifndef LANGUAGETRANSLATION_H
#define LANGUAGETRANSLATION_H

#include <DuiLocale>

namespace DcpLanguage {
    const QString AppletTitle = trid("qtn_lang_title", "Language");
    const QString DisplayButtonTitle = trid("qtn_lang_display", "Display language");
    const QString KeyboardButtonTitle = trid("qtn_lang_keyboard", "Keyboard languages");
    const QString RegionButtonTitle = trid("qtn_lang_region_format", "Region format");
    const QString SetLanguageText = trid("qtn_lang_info_text",
                    "To set language display format, go to");
    const QString OviFeeds = trid("ovi_feeds", "Ovi feeds");
    const QString RecentDisplayText = trid("recent_display_text",
                    "Recent released display languages");
    const QString RecentKeyboardText = trid("recent_keyboard_text",
                    "Recent released keyboard languages");
    const QString SelectDisplayText = trid("qtn_lang_select_display",
                    "Select display language");
    const QString SelectKeyboardText = trid("qt_lang_select_keyboard",
                    "Select keyboard languages");
    const QString InDeviceText = trid("in_device_text",
                    "Pre-installed languages");
    const QString DownloadedText = trid("donwloaded_text",
                    "Downloaded language");
    const QString InstalledText = trid("installed_text",
                    "Installed language");
    const QString RemoveButtonText = trid ("remove_button_text",
                    "Remove");
    const QString RestoreQueryLabelText = trid("qtn_lang_resotre_query",
            "You have not selected any keyboard language,<br> would you like" 
            " to restore the previous selection?");
    const QString RestorePreviousText = trid("qtn_lang_restore_query", 
                    "Restore previous");
    const QString SelectNewText = trid("qtn_lang_select",
            "Select new");
};
#endif // LANGUAGETRANSLATION_H
