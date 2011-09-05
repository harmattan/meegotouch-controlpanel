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

#include "dcpqmlwidget.h"

#include <MLabel>
#include <dcpdebug.h>
#include <QGraphicsLinearLayout>
#include <QDeclarativeError>
#include <QDeclarativeEngine>
#include <QDeclarativeComponent>

DcpQmlWidget::DcpQmlWidget(const QString& qmlPath)
{
    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout(
                                      Qt::Vertical, this);
    setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);

    // create the qml widget:
    QDeclarativeEngine *engine = new QDeclarativeEngine (this);
    QDeclarativeComponent component(engine, QUrl::fromLocalFile(qmlPath));
    QGraphicsObject *object =
        qobject_cast<QGraphicsObject *>(component.create());
    if (object) {
        // all fine, make it visible
        object->setParentItem (this);
        setPreferredSize (object->boundingRect().size());
    } else {
        // error happened
        createErrorLabel (QString("Error loading %1").arg(qmlPath));
        foreach (QDeclarativeError error, component.errors()) {
            createErrorLabel (error.toString());
        }
    }

    enableAutoTitle();
}

void DcpQmlWidget::createErrorLabel(const QString& text)
{
    MLabel* label;

    label = new MLabel(this);
    label->setText(text);
    label->setWrapMode (QTextOption::WrapAtWordBoundaryOrAnywhere);
    label->setWordWrap (true);
    label->setStyleName ("CommonBodyTextInverted");
    ((QGraphicsLinearLayout*)(layout()))->addItem(label);

    DCP_WARNING(qPrintable(text));
}

void DcpQmlWidget::requestPage (int id)
{
    emit changeWidget (id);
}

