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

#include "dcpappletwidget.h"

#include "dcpwidget.h"
#include "dcpstylablewidget.h"

#define CONNECT_SIG(widget, signature) \
            connect (widget, SIGNAL(signature), this, SIGNAL(signature))
#define CALL(function) \
            if (m_Widget) { m_Widget->function; } else m_StylableWidget->function
#define RETURN(function) \
            return m_Widget ? m_Widget->function : m_StylableWidget->function

#define CONNECT_WIDGET(widget) \
    if (widget) { \
        CONNECT_SIG (widget, changeWidget (int)); \
        CONNECT_SIG (widget, activatePluginByName (QString)); \
        CONNECT_SIG (widget, closePage ()); \
        CONNECT_SIG (widget, inProgress (bool)); \
    }


DcpAppletWidget::DcpAppletWidget(DcpWidget* widget, QObject* parent):
    QObject (parent),
    m_Widget (widget),
    m_StylableWidget (0)
{
    CONNECT_WIDGET (widget)
}

DcpAppletWidget::DcpAppletWidget(DcpStylableWidget* widget, QObject* parent):
    QObject (parent),
    m_Widget (0),
    m_StylableWidget (widget)
{
    CONNECT_WIDGET (widget)
}

DcpAppletWidget::~DcpAppletWidget()
{
    /*
     * We should not delete these, since they will be removed by the layout
    delete m_Widget;
    delete m_StylableWidget;
     */
}


void DcpAppletWidget::setReferer(int widgetId)
{
    CALL (setReferer(widgetId));
}


bool DcpAppletWidget::back()
{
    RETURN (back());
}


bool DcpAppletWidget::pagePans() const
{
    RETURN (pagePans());
}


int DcpAppletWidget::getWidgetId()
{
    RETURN (getWidgetId());
}


bool DcpAppletWidget::setWidgetId(int widgetId)
{
    RETURN (setWidgetId(widgetId));
}


QString DcpAppletWidget::title() const
{
    RETURN (title());
}


bool DcpAppletWidget::isProgressIndicatorVisible() const
{
    RETURN (isProgressIndicatorVisible());
}


void DcpAppletWidget::setProgressIndicatorVisible(bool visible)
{
    CALL (setProgressIndicatorVisible (visible));
}

QGraphicsWidget* DcpAppletWidget::graphicsWidget () const
{
    return m_Widget ? (QGraphicsWidget*)m_Widget : (QGraphicsWidget*)m_StylableWidget;
}

