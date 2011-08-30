/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel.
**
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#include "dcpqmlapplet.h"
#include <QDebug>
#include <MAction>
#include "dcpqmlwidget.h"
#include "dcpqmlbrief.h"

Q_EXPORT_PLUGIN2(declarative, DcpQmlApplet)

void DcpQmlApplet::init()
{
}

DcpWidget* DcpQmlApplet::constructWidget(int widgetId)
{
    if (widgetId >= 0 && widgetId < m_QmlPaths.count()) {
        return new DcpQmlWidget(m_QmlPaths.at(widgetId));
    } else {
        qWarning("declarative applet was called with non valid widgetid: %d",
                 widgetId);
        return 0;
    }
}


QString DcpQmlApplet::title() const
{
    return QString(); // TODO
}

QVector<MAction*> DcpQmlApplet::viewMenuItems()
{
    QVector<MAction*> vector;
    return vector;
}

DcpBrief* DcpQmlApplet::constructBrief(int)
{
    return 0;
}

int DcpQmlApplet::partID(const QString& partStr)
{
    int id = m_QmlPaths.indexOf(partStr);
    if (id < 0){
        id = m_QmlPaths.count();
        m_QmlPaths.append(partStr);
    }
    return id;
}

