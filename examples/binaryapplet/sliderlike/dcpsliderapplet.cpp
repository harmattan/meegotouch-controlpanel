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

#include <QDebug>
#include <MAction>
#include <MLibrary>

#include "dcpsliderapplet.h"
#include "dcpsliderbrief.h"

M_LIBRARY
Q_EXPORT_PLUGIN2(dcpskelsliderapplet, SliderExampleApplet)


QVector<MAction*> SliderExampleApplet::viewMenuItems()
{
    QVector<MAction*> vector;
    return vector;
}

DcpBrief* SliderExampleApplet::constructBrief(int)
{
    return new SliderExampleBrief();
}

