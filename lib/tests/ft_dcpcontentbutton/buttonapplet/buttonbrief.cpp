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
#include "buttonbrief.h"
ButtonBrief::ButtonBrief():
    m_ToggleState(true)
{
}

QString ButtonBrief::valueText() const
{
    QString value = m_ToggleState ? "On" : "Off";
    return value;
}

QString ButtonBrief::titleText() const
{
    return "Button-like applet";
}

bool ButtonBrief::toggle() const
{
    return m_ToggleState;
}

void ButtonBrief::setToggle (bool toggle)
{
    m_ToggleState = toggle;
    emit valuesChanged();
}

int ButtonBrief::widgetTypeID() const
{
    return DcpWidgetType::Button;
}

