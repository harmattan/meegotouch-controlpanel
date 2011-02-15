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
    m_Value(50)
{
    qDebug() << "slider applet got loaded" << m_Value;

#if 0
    // this makes the slider increase in every 2nd sec
    startTimer (2000);
#endif
}

int SkeletonBrief::widgetTypeID() const
{
    return DcpWidgetType::Slider;
}

QVariant SkeletonBrief::value() const
{
    return m_Value;
}

void SkeletonBrief::setValue(const QVariant& value)
{
    m_Value = value.toInt();
    qDebug() << "slider applet: new value is" << m_Value;
}

void SkeletonBrief::timerEvent ( QTimerEvent * )
{
    // increase the value and notify controlpanel that it changed:
    m_Value++;
    emit valuesChanged ();
}

