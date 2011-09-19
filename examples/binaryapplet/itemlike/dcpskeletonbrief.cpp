/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel.
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#include <DcpWidgetTypes>
#include "dcpskeletonbrief.h"
#include <QtDebug>

SkeletonBrief::SkeletonBrief():
    m_ToggleState(true),
    m_Value(0)
{
    startTimer(1000);
}

QString SkeletonBrief::valueText() const
{
    /* Here we can return a custom value line if needed.
     * In case we do not do that, the static one from the .desktop file will be
     * used. */
#if 1
    return "value text " + QString::number(m_Value);
#else
    return QString();
#endif
}

QString SkeletonBrief::titleText() const
{
    return "title text " + QString::number(m_Value);
}

/* The plugin can specify that it has a toggle like this:
 */
int SkeletonBrief::widgetTypeID() const
{
    return DcpWidgetType::Toggle;
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

void SkeletonBrief::timerEvent(QTimerEvent*)
{
    ++m_Value;
    if (m_Value % 5 == 0) {
        m_ToggleState = !m_ToggleState;
    }
    emit valuesChanged();
}

QString SkeletonBrief::helpId () const
{
    return "test.cfg";
}

