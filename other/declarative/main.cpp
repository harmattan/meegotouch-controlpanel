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

#include <DuiApplication>
#include <DuiApplicationWindow>
#include <DuiApplicationPage>
#include <DuiLabel>
#include <QGraphicsLinearLayout>

#include <QFile>
#include <DuiDeclarativeSettingsParser>
#include <DuiDeclarativeSettingsBinary>
#include <DuiDeclarativeSettings>
#include <DuiDeclarativeSettingsFactory>
#include <DuiGConfDataStore>

int main(int argc, char** argv)
{
    Q_ASSERT (argc > 1);
    
    DuiApplication app(argc, argv);
    DuiApplicationWindow win;
    DuiApplicationPage page;
    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout(
            Qt::Vertical, page.centralWidget());
    layout->addItem(new DuiLabel("TEST"));


    /* -- */
    QFile file(argv[1]);
    Q_ASSERT(file.open(QIODevice::ReadOnly));
    
    DuiDeclarativeSettingsParser parser;
    if (!parser.readFrom(file)) {
        qDebug("Parser error");
        return 1;
    }
    DuiDeclarativeSettingsBinary* binary = parser.createSettingsBinary();
    Q_ASSERT(binary);
    DuiGConfDataStore* datastore = new DuiGConfDataStore();
    foreach (QString key, binary->keys()) {
        datastore->addGConfKey(key, key);
    }
    DuiDeclarativeSettings* widget = 
        DuiDeclarativeSettingsFactory::createWidget(*binary, datastore);
    Q_ASSERT(widget);
    layout->addItem(widget);
    /* -- */

    page.appearNow();
    win.show();
    return app.exec();
}

