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
#include "dcpskelbuttonbrief.h"
#include <QDebug>
SkelButtonBrief::SkelButtonBrief():
    m_ToggleState(true)
{
}

QString SkelButtonBrief::titleText() const
{
    QString value = m_ToggleState ? "On" : "Off";
    qDebug() << value;
    return "value is " + value;
}

QString SkelButtonBrief::valueText() const
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

