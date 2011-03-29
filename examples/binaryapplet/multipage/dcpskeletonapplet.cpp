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

#include <DcpStylableWidget>
#include "dcpskeletonapplet.h"
#include "dcpskeletonwidget.h"

M_LIBRARY
Q_EXPORT_PLUGIN2(skeletonapplet, SkeletonApplet)

void SkeletonApplet::init()
{
};

DcpStylableWidget* SkeletonApplet::constructStylableWidget(int widgetId)
{
	return new SkeletonWidget(widgetId);
}

QString SkeletonApplet::title() const
{
    return QString();
}

QVector<MAction*> SkeletonApplet::viewMenuItems()
{
    QVector<MAction*> vector;
    /*
    vector[0] = new MAction("Start language applet", this);
    vector[0]->setLocation(MAction::ApplicationMenuLocation);
     */
    return vector;
}

