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
#include "dcpqmlcontacter.h"

#include <MLabel>
#include <dcpdebug.h>
#include <QGraphicsLinearLayout>
#include <QDeclarativeError>
#include <QDeclarativeEngine>
#include <QDeclarativeComponent>
#include <QDeclarativeContext>
#include <QDeclarativeExpression>
#include <QDeclarativeItem>
#include <MApplicationPage>
#include <QGraphicsSceneResizeEvent>
#include <MApplicationWindow>
#include <MApplication>
#include <QTimer>
#include <QFileInfo>

DcpQmlWidget::DcpQmlWidget(const QString& qmlPath):
    m_Path (qmlPath),
    m_Object (0),
    m_HandlesItsOwnWindow (false)
{
    // for the error labels:
    new QGraphicsLinearLayout(Qt::Vertical, this);

    // get as much space as possible:
    setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);

    QTimer::singleShot (0, this, SLOT(create()));
}

DcpQmlWidget::~DcpQmlWidget()
{
    MApplicationWindow* win = MApplication::activeApplicationWindow();
    if (win) {
        // restore the hidden statusbar etc.
        win->showNormal();
    }
}

void DcpQmlWidget::create()
{
    // create has already run?
    if (m_Object) return;

    QString baseDir = QFileInfo(m_Path).absolutePath();

    // create the qml widget:
    QDeclarativeEngine *engine = new QDeclarativeEngine (this);
    engine->addImportPath (baseDir);

    QDeclarativeComponent component(engine, QUrl::fromLocalFile(m_Path));

    m_Object =
        qobject_cast<QGraphicsObject *>(component.create());
    if (m_Object) {
        // register the contacter object which enables notifications
        // between the qml and control panel
        engine->rootContext()->setContextProperty("dcp", new DcpQmlContacter);
        qmlRegisterUncreatableType<DcpQmlContacter>("com.nokia.controlpanel", 0, 1,
                "Dcp", "Please just use \"dcp\" object directly.");

        // TODO XXX this is somehow not working
        QDeclarativeExpression (engine->rootContext(), m_Object,
                    "theme.inverted = true").evaluate();

        // all fine
        m_HandlesItsOwnWindow =
            QString(m_Object->metaObject()->className()).startsWith ("PageStackWindow_");

        if (handlesItsOwnWindow()) {
            // the root object is a PageStackWindow, we let it handle everything
            hideAllControls();
            QDeclarativeExpression (engine->rootContext(), m_Object,
                    "screen.allowedOrientations = Screen.Portrait").evaluate();
            m_Object->setRotation (90);

            QTimer::singleShot (0, this, SLOT(adjustObjectSize()));
        } else {
            // the root object is not a PageStackWindow, we handle it as a widget
            m_Object->setParentItem (this);
            setPreferredSize (m_Object->boundingRect().size());
            enableAutoTitle();
        }
        connect (engine, SIGNAL(quit()), this, SIGNAL(closePage()));

    } else {
        // error happened
        createErrorLabel (QString("Error loading %1").arg(m_Path));
        foreach (QDeclarativeError error, component.errors()) {
            createErrorLabel (error.toString());
        }
    }
}


void DcpQmlWidget::adjustObjectSize()
{
    QDeclarativeItem* item = qobject_cast<QDeclarativeItem*>(m_Object);
    if (!item) return;
    item->setSize (size());
    if (!m_Object->parentItem()) {
        m_Object->setParentItem (this);
    }
}

/*
 * Returns the page the widget is in case it is on a page,
 * otherwise returns 0.
 */
MApplicationPage* DcpQmlWidget::page ()
{
    QGraphicsWidget* item = this;
    MApplicationPage* page = 0;
    do {
        page = qobject_cast<MApplicationPage*>(item);
        item = item->parentWidget();
    } while (!page && item);
    return page;
}

void DcpQmlWidget::hideAllControls()
{
    // hide everything on the page (qml displays its window totally)
    MApplicationPage* page = this->page();
    dcp_failfunc_unless (page);

    page->setComponentsDisplayMode (MApplicationPage::AllComponents,
                                    MApplicationPageModel::Hide);
    page->setPannable (false);

    MApplicationWindow* win = MApplication::activeApplicationWindow();
    if (win) {
        // hide everything:
        win->showFullScreen();
    }
}

void DcpQmlWidget::resizeEvent ( QGraphicsSceneResizeEvent * )
{
    // handle the size of the main m_Object (it is not a widget, so could
    // not put it into a layout)
    adjustObjectSize ();
}

void DcpQmlWidget::polishEvent ()
{
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

