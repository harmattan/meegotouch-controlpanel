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

#include <DcpStylableWidget>
#include "dcpsheetapplet.h"

#include <MAction>
#include <MLibrary>
#include <MLabel>
#include <MSheet>
#include <MBasicSheetHeader>

M_LIBRARY
Q_EXPORT_PLUGIN2(sheetapplet, SheetApplet)

void SheetApplet::init()
{
};

DcpStylableWidget* SheetApplet::constructStylableWidget(int widgetId)
{
    Q_UNUSED (widgetId);

    MSheet* sheet = new MSheet();
    MBasicSheetHeader* header = new MBasicSheetHeader();
    header->setPositiveAction (new MAction("Ok", header));
    header->setNegativeAction (new MAction("Cancel", header));
    connect(header->positiveAction(), SIGNAL(triggered()), sheet, SLOT(dismiss()));
    connect(header->negativeAction(), SIGNAL(triggered()), sheet, SLOT(dismiss()));
    sheet->setHeaderWidget (header);
    sheet->setCentralWidget (new MLabel ("This is a sheet"));

    // this way the sheet will use its own window:
    sheet->appearSystemwide (MSceneWindow::DestroyWhenDone);
    return 0;
}

QString SheetApplet::title() const
{
    return QString();
}

QVector<MAction*> SheetApplet::viewMenuItems()
{
    return QVector<MAction*>();
}

