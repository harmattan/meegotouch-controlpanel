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
#include "dcpwidget.h"
#include "dcpwidget_p.h"



DcpWidgetPrivate::DcpWidgetPrivate ():
    m_WidgetId (-1),
    isProgressIndicatorVisible (false)
{
}


DcpWidget::DcpWidget (QGraphicsWidget *parent) 
    : MWidget (parent), 
      d_ptr (0)
{
}

DcpWidget::~DcpWidget ()
{
}

static int curWID = 1;
int 
DcpWidget::getWidgetId ()
{
    return curWID;
}

bool 
DcpWidget::setWidgetId (
        int widgetId)
{
    curWID = widgetId;
    return true;
}

void
DcpWidget::setReferer (int widgetId)
{
    Q_UNUSED (widgetId);
}

bool 
DcpWidget::back ()
{
    return false;
}

bool 
DcpWidget::pagePans () const 
{
    return true; 
}

QString
DcpWidget::title() const
{
    return QString();
}

static bool curPIV = true;
void DcpWidget::setProgressIndicatorVisible(bool PIV)
{
    curPIV = PIV;
}

bool DcpWidget::isProgressIndicatorVisible() const
{
    return curPIV;
}


