#ifndef LANGUAGETRANSLATION_H
#define LANGUAGETRANSLATION_H

#include <DuiLocale>

namespace DcpLanguage {
    const QString AppletTitle = trid("applet_title", "Language");
    const QString DisplayButtonTitle = trid("display_button_title", "Display language");
    const QString KeyboardButtonTitle = trid("keyboard_button_title", "Keyboard languages");
    const QString RegionButtonTitle = trid("region_button_title", "Region format");
    const QString SetLanguageText = trid("set_language_text",
                    "To set language display format, go to");
    const QString OviFeeds = trid("ovi_feeds", "Ovi feeds");
    const QString RecentDisplayText = trid("recent_display_text",
                    "Recent released display languages");
    const QString RecentKeyboardText = trid("recent_keyboard_text",
                    "Recent released keyboard languages");
    const QString SelectDisplayText = trid("select_display_text",
                    "Select display language");
    const QString SelectKeyboardText = trid("select_keyboard_text",
                    "Select keyboard languages");
    const QString InDeviceText = trid("in_device_text",
                    "Pre-installed languages");
    const QString DownloadedText = trid("donwloaded_text",
                    "Downloaded language");
    const QString InstalledText = trid("installed_text",
                    "Installed language");
    const QString RemoveButtonText = trid ("remove_button_text",
                    "Remove");
    const QString RemoveLanguage = trid("remove_language_text", 
                    "Keep Last?");
};
#endif // LANGUAGETRANSLATION_H
