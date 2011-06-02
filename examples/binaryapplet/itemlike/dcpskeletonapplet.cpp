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

#include <MAction>
#include <MLibrary>

#include <DcpStylableWidget>
#include "dcpskeletonapplet.h"
#include "dcpskeletonwidget.h"
#include "dcpskeleton.h"
#include "dcpskeletonbrief.h"

M_LIBRARY
Q_EXPORT_PLUGIN2(skeletonapplet, SkeletonApplet)

void SkeletonApplet::init()
{
    /* Do not do this, as this wont support switching themes and will cause
     * performance problems when loading the category pages.
     * See the documentation package for details.
     *
    MTheme::loadCSS("/usr/share/themes/base/meegotouch/"
                    "libdcpskeletonapplet/style/libdcpskeletonapplet.css");
     */
};

DcpStylableWidget* SkeletonApplet::constructStylableWidget(int widgetId)
{
	switch (widgetId)
    {
        case DcpSkeleton::Main:
                    return pageMain();
                    break;
        // more cases here if applet has more pages
        default:
                    qDebug("Page Unknown");
                    return 0;
                    break;
    };
}

DcpStylableWidget* SkeletonApplet::pageMain()
{
	return new SkeletonWidget();
}



QString SkeletonApplet::title() const
{
    //% "Skeleton applet"
    return qtTrId("dcp_skel_appl_titl");
}

QVector<MAction*> SkeletonApplet::viewMenuItems()
{
    QVector<MAction*> vector(3);

    //% "Example action"
    vector[0] = new MAction(qtTrId("dcp_skel_appl_action"), this);
    vector[0]->setLocation(MAction::ApplicationMenuLocation);

    vector[1] = new MAction(this);
    vector[1]->setIconID ("icon-m-input-reset");
    vector[1]->setLocation(MAction::ToolBarLocation);

    vector[2] = new MAction(this);
    vector[2]->setIconID ("icon-m-input-add");
    vector[2]->setLocation(MAction::ToolBarLocation);

    return vector;
}

DcpBrief* SkeletonApplet::constructBrief(int)
{
    return new SkeletonBrief();
}

