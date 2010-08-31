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

#include "dcpdeclwidget.h"

#include <QGraphicsLinearLayout>
#include <QFile>
#include <MSettingsLanguageParser>
#include <MSettingsLanguageBinary>
#include <MSettingsLanguageWidget>
#include <MSettingsLanguageWidgetFactory>
#include <MLabel>

#include "dynamicgconfdatastore.h"
#include <dcpdebug.h>

static const QString defaultPath = "/usr/lib/duicontrolpanel/uidescriptions/";

DcpDeclWidget::DcpDeclWidget(const QString& xmlPath)
{
    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout(
                                      Qt::Vertical, this);

    QString filePath = xmlPath.startsWith('/') ? xmlPath
                                               : defaultPath + xmlPath;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        createErrorLabel(
            QString("Cannot find applet xml file %1").arg(filePath)
            );
        return;
    }

    MSettingsLanguageParser parser;
    if (!parser.readFrom(file)) {
        createErrorLabel(QString("Error parsing the ui description %1")
                         .arg(filePath));
        return;
    }

    MSettingsLanguageBinary* binary = parser.createSettingsBinary();
    if (!binary) {
        createErrorLabel(QString("Error parsing the ui description %1")
                         .arg(filePath));
        return;
    }

    MDataStore* datastore = new DynamicGConfDataStore (this);

    MSettingsLanguageWidget* widget =
        MSettingsLanguageWidgetFactory::createWidget(*binary, datastore );
    Q_ASSERT(widget);
    layout->addItem(widget);
}

void DcpDeclWidget::createErrorLabel(const QString& text)
{
    MLabel* label = new MLabel(this);
    label->setText("Error parsing the ui description, see log");
    DCP_WARNING(qPrintable(text));
    ((QGraphicsLinearLayout*)(layout()))->addItem(label);
}

