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

#include "dcpdeclapplet.h"
#include <QDebug>
#include <MAction>
#include "dcpdeclwidget.h"
#include "dcpdeclbrief.h"

Q_EXPORT_PLUGIN2(declarative, DcpDeclApplet)

void DcpDeclApplet::init()
{
}

DcpWidget* DcpDeclApplet::constructWidget(int widgetId)
{
    if (widgetId >= 0 && widgetId < m_XmlPaths.count()) {
        return new DcpDeclWidget(m_XmlPaths.at(widgetId));
    } else {
        qWarning("declarative applet was called with non valid widgetid: %d",
                 widgetId);
        return 0;
    }
}


QString DcpDeclApplet::title() const
{
    return QString(); // TODO
}

QVector<MAction*> DcpDeclApplet::viewMenuItems()
{
    QVector<MAction*> vector;
    return vector;
}

DcpBrief* DcpDeclApplet::constructBrief(int)
{
    return 0;
}

int DcpDeclApplet::partID(const QString& partStr)
{
    int id = m_XmlPaths.indexOf(partStr);
    if (id < 0){
        id = m_XmlPaths.count();
        m_XmlPaths.append(partStr);
    }
    return id;
}

