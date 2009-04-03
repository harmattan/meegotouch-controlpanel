#ifndef DISPLAYTRANSLATION_H
#define DISPLAYTRANSLATION_H

#include <DuiLocale>

namespace DcpDisplay {
    const QString AppletTitle = trid("applet_title", "Display");
    const QString BrightnessText = trid("brightness_text", "Brightness:");
    const QString ScreenLightsText = 
            trid("screen_lights_text", "Screen lights on:");

    const QString ChargingText = trid("charging_text",
            "While charging keep screen lights");
    const QString NoteText = trid("note_text",
            "Note! Display settings depend on the user power profile.");
};
#endif // DISPLAYTRANSLATION_H
