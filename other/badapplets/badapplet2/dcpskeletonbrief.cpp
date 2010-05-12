#include <DcpWidgetTypes>
#include "dcpskeletonbrief.h"
#include <QtDebug>

SkeletonBrief::SkeletonBrief():
    m_ToggleState(true)
{
    startTimer(5000);
}

QString SkeletonBrief::valueText() const
{
    static int nothing = 0;
    abort();
    nothing++;
    return "value text " + QString::number(nothing);
}

bool SkeletonBrief::toggle() const
{
    qDebug() << "Bad applet2 aborted from toggle() call";
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

