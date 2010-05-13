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

#include <MTheme>
#include <QtDebug>
#include <DcpWidget>
#include <DcpBrief>
#include "testapplet.h"
#include "testappletwidget.h"

Q_EXPORT_PLUGIN2(testapplet, TestApplet)

TestApplet::~TestApplet()
{
    qDebug() << "TestApplet destructor";
}

void TestApplet::init()
{
    qDebug() << "TestApplet init";
    MTheme::loadCSS(DATADIR "/testapplet.css");
}

DcpWidget *TestApplet::constructWidget(int widgetId)
{
    return new TestAppletWidget();
}

QString TestApplet::title() const
{
    return "Test title 1";
}

QVector<MAction*> TestApplet::viewMenuItems()
{
    return QVector<MAction*>();
}

DcpBrief *TestApplet::constructBrief(int)
{
    return new DcpBrief();
}
