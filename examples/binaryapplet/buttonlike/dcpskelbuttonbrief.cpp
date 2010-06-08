#include <DcpWidgetTypes>
#include "dcpskelbuttonbrief.h"
#include <QDebug>
SkelButtonBrief::SkelButtonBrief():
    m_ToggleState(true)
{
}

QString SkelButtonBrief::valueText() const
{
    QString value = m_ToggleState ? "On" : "Off";
    qDebug() << value;
    return "value is " + value;
}

QString SkelButtonBrief::titleText() const
{
    return "Button-like applet";
}

bool SkelButtonBrief::toggle() const
{
    return m_ToggleState;
}

void SkelButtonBrief::setToggle (bool toggle)
{
    m_ToggleState = toggle;
    emit valuesChanged();
}

int SkelButtonBrief::widgetTypeID() const
{
    return DcpWidgetType::Button;
}

