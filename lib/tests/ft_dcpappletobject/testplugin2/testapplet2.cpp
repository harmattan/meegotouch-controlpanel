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
#include "testapplet2.h"
#include "testappletwidget2.h"

Q_EXPORT_PLUGIN2(testapplet2, TestApplet2)

TestApplet2::~TestApplet2()
{
    qDebug() << "TestApplet2 destructor";
}

void TestApplet2::init()
{
    qDebug() << "TestApplet2 init";
    MTheme::loadCSS(DATADIR "/testapplet2.css");
}

DcpWidget *TestApplet2::constructWidget(int widgetId)
{
    return new TestAppletWidget2();
}

QString TestApplet2::title() const
{
    return "Test title 2";
}

QVector<MAction*> TestApplet2::viewMenuItems()
{
    return QVector<MAction*>();
}

DcpBrief *TestApplet2::constructBrief(int)
{
    return new DcpBrief();
}
