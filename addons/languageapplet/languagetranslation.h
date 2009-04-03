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
};
#endif // LANGUAGETRANSLATION_H
