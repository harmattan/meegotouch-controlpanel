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

SliderExampleBrief::SliderExampleBrief():
    m_Value(50)
{
    qDebug() << "slider applet got loaded" << m_Value;

#if 0
    // this makes the slider changing in every sec
    startTimer (1000);
#endif
}

int SliderExampleBrief::widgetTypeID() const
{
    return DcpWidgetType::Slider;
}

QString SliderExampleBrief::valueText() const
{
    return (m_Value / 4) % 2 ?
        // Here we return no description about why the slider is disabled,
        // which will result in a disabled slider showing no value
        QString()

        // Here we return description about why the slider is disabled,
        // this will result in the message in place of the slider:
        : "Slider is disabled";
}

QVariant SliderExampleBrief::value() const
{
    return m_Value % 2 ? m_Value : QVariant();
}

void SliderExampleBrief::setValue(const QVariant& value)
{
    m_Value = value.toInt();
    qDebug() << "slider applet: new value is" << m_Value;
}

void SliderExampleBrief::timerEvent ( QTimerEvent * )
{
    // increase the value and notify controlpanel that it changed:
    m_Value++;
    emit valuesChanged ();
}

