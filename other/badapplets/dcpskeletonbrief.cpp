#include <DcpWidgetTypes>
#include "dcpskeletonbrief.h"
#include <QtDebug>

SkeletonBrief::SkeletonBrief():
    m_ToggleState(true)
{
}

QString SkeletonBrief::valueText() const
{
    return "value text";
}

bool SkeletonBrief::toggle() const
{
    return m_ToggleState;
}

void SkeletonBrief::setToggle (bool toggle)
{
    m_ToggleState = toggle;
    qDebug() << "Skeleton brief got toggle state:" << toggle;
}

int SkeletonBrief::widgetTypeID() const
{
    return DCPLABELBUTTON;
}


