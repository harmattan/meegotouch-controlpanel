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
#include <QDeclarativeItem>
#include <MApplicationPage>
#include <QGraphicsSceneResizeEvent>
#include <QDebug>

DcpQmlWidget::DcpQmlWidget(const QString& qmlPath):
    m_Object (0),
    m_HandlesItsOwnWindow (false)

DcpQmlWidget::DcpQmlWidget(const QString& qmlPath)
{
    // for the error labels:
    new QGraphicsLinearLayout(Qt::Vertical, this);

    // get as much space as possible:
    setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);

    // create the qml widget:
    QDeclarativeEngine *engine = new QDeclarativeEngine (this);
    QDeclarativeComponent component(engine, QUrl::fromLocalFile(qmlPath));
    m_Object =
        qobject_cast<QGraphicsObject *>(component.create());
    if (m_Object) {
        // all fine, make it visible
        m_Object->setParentItem (this);
        m_HandlesItsOwnWindow =
            QString(m_Object->metaObject()->className()).startsWith ("PageStackWindow_");

        if (handlesItsOwnWindow()) {
        } else {
            setPreferredSize (m_Object->boundingRect().size());
            enableAutoTitle();
        }
    } else {
        // error happened
        createErrorLabel (QString("Error loading %1").arg(qmlPath));
        foreach (QDeclarativeError error, component.errors()) {
            createErrorLabel (error.toString());
        }
    }
}

void DcpQmlWidget::resizeEvent ( QGraphicsSceneResizeEvent * event )
{
    if (!handlesItsOwnWindow()) return;

    // handle the size of the main m_Object (it is not a widget, so could
    // not put it into a layout)
    QDeclarativeItem* item = qobject_cast<QDeclarativeItem*>(m_Object);
    dcp_failfunc_unless (item);
    item->setSize (event->newSize());
}

void DcpQmlWidget::polishEvent ()
{
    if (!handlesItsOwnWindow()) return;

    // hide everything on the page (qml displays its window totally)
    QGraphicsWidget* item = this;
    MApplicationPage* page = 0;
    do {
        page = qobject_cast<MApplicationPage*>(item);
        item = item->parentWidget();
    } while (!page);
    dcp_failfunc_unless (page);

    page->setComponentsDisplayMode (MApplicationPage::AllComponents,
                                    MApplicationPageModel::Hide);
}

bool DcpQmlWidget::pagePans () const
{
    return !handlesItsOwnWindow();
}

bool DcpQmlWidget::handlesItsOwnWindow() const
{
    return m_HandlesItsOwnWindow;
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

