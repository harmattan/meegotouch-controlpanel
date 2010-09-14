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

#include <QtGui>
#include <QDebug>
#include <MAction>
#include <MTheme>
#include <DcpWidget>
#include "dcpskelbuttonapplet.h"
#include "dcpskelbutton.h"
#include "dcpskelbuttonbrief.h"

Q_EXPORT_PLUGIN2(skelbuttonapplet, SkelButtonApplet)

void SkelButtonApplet::init()
{
};

DcpWidget* SkelButtonApplet::constructWidget(int widgetId)
{
    // No views for button-like applets by default
    Q_UNUSED(widgetId);
    return 0;
}

QString SkelButtonApplet::title() const
{
    //% "SkelButton applet"
    return qtTrId("dcp_skel_appl_titl");
}

QVector<MAction*> SkelButtonApplet::viewMenuItems()
{
    QVector<MAction*> vector(1);
    //% "Example action"
    vector[0] = new MAction(qtTrId("dcp_skel_appl_action"), this);
    vector[0]->setLocation(MAction::ApplicationMenuLocation);
    return vector;
}

DcpBrief* SkelButtonApplet::constructBrief(int)
{
    return new SkelButtonBrief();
}

