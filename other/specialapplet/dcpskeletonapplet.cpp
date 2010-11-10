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
#include "dcpskeletonapplet.h"
#include "dcpskeletonwidget.h"
#include "specialicon.h"
#include "dcpskeleton.h"

Q_EXPORT_PLUGIN2(skeletonapplet, SkeletonApplet)

void SkeletonApplet::init()
{
};

DcpWidget* SkeletonApplet::constructWidget(int widgetId)
{
	switch (widgetId)
    {
        case DcpSkeleton::Icon:
                    return new SpecialIcon();
                    break;
        case DcpSkeleton::Main:
                    return pageMain();
                    break;
        // more cases here if applet has more pages
        default:
                    qDebug() << "Page Unknown";
                    return 0;
                    break;
    };
}

DcpWidget* SkeletonApplet::pageMain()
{
    return new SkeletonWidget();
}

