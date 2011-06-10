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

/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpstylablewidget.h"
#include "dcpstylablewidget_p.h"



DcpStylableWidgetPrivate::DcpStylableWidgetPrivate ():
    m_WidgetId (-1),
    isProgressIndicatorVisible (false)
{
}


DcpStylableWidget::DcpStylableWidget (QGraphicsWidget *parent) 
    : MStylableWidget (parent), 
      d_ptr (0)
{
}

DcpStylableWidget::~DcpStylableWidget ()
{
}


static int curWID = 1;
int 
DcpStylableWidget::getWidgetId ()
{
    return curWID;
}

bool 
DcpStylableWidget::setWidgetId (
        int widgetId)
{
    curWID = widgetId;
    return true;
}

void
DcpStylableWidget::setReferer (int widgetId)
{
    Q_UNUSED (widgetId);
}

bool 
DcpStylableWidget::back ()
{
    return false;
}

bool 
DcpStylableWidget::pagePans () const 
{
    return true; 
}

QString
DcpStylableWidget::title() const
{
    return QString();
}

static bool curPIV = true;
void DcpStylableWidget::setProgressIndicatorVisible(bool PIV)
{
    curPIV = PIV;
}

bool DcpStylableWidget::isProgressIndicatorVisible() const
{
    return curPIV;
}


