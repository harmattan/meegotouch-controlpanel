#include <DcpWidgetTypes>
#include "buttonbrief.h"
ButtonBrief::ButtonBrief():
    m_ToggleState(true)
{
}

QString ButtonBrief::valueText() const
{
    QString value = m_ToggleState ? "On" : "Off";
    return value;
}

QString ButtonBrief::titleText() const
{
    return "Button-like applet";
}

bool ButtonBrief::toggle() const
{
    return m_ToggleState;
}

void ButtonBrief::setToggle (bool toggle)
{
    m_ToggleState = toggle;
    emit valuesChanged();
}

int ButtonBrief::widgetTypeID() const
{
    return DcpWidgetType::Button;
}

