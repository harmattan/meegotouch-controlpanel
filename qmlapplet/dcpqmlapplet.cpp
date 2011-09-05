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
#include "dcpqmlwidget.h"
#include "dcpqmlbrief.h"
#include "dcpqmlcontacter.h"

#include <QDebug>
#include <dcpdebug.h>
#include <MAction>
#include <QtDeclarative>


Q_EXPORT_PLUGIN2(qml, DcpQmlApplet)

DcpQmlApplet* DcpQmlApplet::sm_Applet = 0;

DcpQmlApplet::DcpQmlApplet ()
{
    sm_Applet = this;
}

void DcpQmlApplet::init()
{
    qmlRegisterType<DcpQmlContacter> (
            "com.nokia.controlpanel", 0, 1, "Dcp"
    );
}

DcpWidget* DcpQmlApplet::constructWidget(int widgetId)
{
    if (widgetId >= 0 && widgetId < m_QmlPaths.count()) {
        m_CurrentWidget = new DcpQmlWidget(m_QmlPaths.at(widgetId));
    } else {
        qWarning("declarative applet was called with non valid widgetid: %d",
                 widgetId);
        m_CurrentWidget = 0;
    }
    return m_CurrentWidget;
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

void DcpQmlApplet::requestPage (const QString& qmlPath)
{
    dcp_failfunc_unless (m_CurrentWidget);
    int id = partID (qmlPath);
    m_CurrentWidget->requestPage (id);
}

DcpQmlApplet* DcpQmlApplet::instance()
{
    return sm_Applet;
}

