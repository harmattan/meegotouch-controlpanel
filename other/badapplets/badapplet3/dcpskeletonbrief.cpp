#include <DcpWidgetTypes>
#include "dcpskeletonbrief.h"
#include <QtDebug>

SkeletonBrief::SkeletonBrief():
    m_ToggleState(true)
{
}

bool SkeletonBrief::toggle() const
{
    return false;
}

void SkeletonBrief::setToggle (bool toggle)
{
    m_ToggleState = toggle;
}

int SkeletonBrief::widgetTypeID() const
{
    return DCPLABELBUTTON;
}

