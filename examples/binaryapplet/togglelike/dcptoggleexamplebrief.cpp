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

#include "dcptoggleexamplebrief.h"

#include <DcpWidgetTypes>
#include <QtDebug>
#include <QTimerEvent>


ToggleExampleBrief::ToggleExampleBrief():
    m_ToggleState(true),
    m_Timer(-1)
{
}

/* The plugin specifies here that it has a toggle:
 */
int ToggleExampleBrief::widgetTypeID() const
{
    return DcpWidgetType::Toggle;
}

QString ToggleExampleBrief::valueText() const
{
    if (m_Timer < 1) {
        return QString("Toggle state is %1").arg(m_ToggleState.toString());
    } else {
        return QString("Changing toggle state after %1 seconds").arg (m_Timer);
    }
}

void ToggleExampleBrief::timerEvent (QTimerEvent* event)
{
    --m_Timer;
    if (m_Timer < 1) {
        // switch the toggle's stored value:
        m_ToggleState.setValue (!m_ToggleState.toBool());

        // stop the countdown:
        killTimer (event->timerId());
    }

    // notify about that something changed (valueText() or value())
    emit valuesChanged();
}

void ToggleExampleBrief::setValue (const QVariant& value)
{
    m_ToggleState = value;

    // start the countdown:
    if (m_Timer < 1) {
        startTimer (1000);
        m_Timer = 10;
    }

    /* You do _not_ need to do this every time the value changes.
     * But here we notify controlpanel that the valueText has changed
     * (second line text of the brief):
     */
    emit valuesChanged ();
}

QVariant ToggleExampleBrief::value () const
{
    return m_ToggleState;
}

