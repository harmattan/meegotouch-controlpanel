#include <DcpWidgetTypes>
#include "dcpskeletonbrief.h"
#include <QtDebug>

SkeletonBrief::SkeletonBrief():
    m_ToggleState(true),
    m_Value(0)
{
    startTimer(20000);
}

QString SkeletonBrief::valueText() const
{
    return "value text " + QString::number(m_Value);
}

QString SkeletonBrief::titleText() const
{
    return "title text " + QString::number(m_Value);
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

void SkeletonBrief::timerEvent(QTimerEvent*)
{
    ++m_Value;
    emit valuesChanged();
}

