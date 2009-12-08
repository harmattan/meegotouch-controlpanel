#ifndef DCPWIDGETTYPES_H
#define DCPWIDGETTYPES_H
#include <QString>

static const QString  WIDGETNAME[] = {
    "DcpLabel",
    "DcpLabel2",
    "DcpLabelButton",
    "DcpLabel2Button",
    "DcpLabel2Image",
    "DcpLabel2Toggle",
};

enum WIDGETTYPEID {
    DCPLABEL = 0,           //"DcpLabel"
    DCPLABEL2,          //"DcpLabel2"
    DCPLABELBUTTON,     //"DcpLabelButton"
    DCPLABEL2BUTTON,    //"DcpLabel2Button"
    DCPLABEL2IMAGE,     //"DcpLabel2Image"
    DCPLABEL2TOGGLE,    //"DcpLabel2Toggle"
    WIDGETN
};

#endif // DCPWIDGETTYPES_H
