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

#include "dcpappletpage.h"

DcpAppletPage::DcpAppletPage (DcpAppletObject *applet, int widgetId) :
    DcpPage(),
    m_Applet (applet),
    m_WidgetId (widgetId),
    m_MainWidget (0),
    m_MissingLabel (0)
{
}


DcpAppletPage::~DcpAppletPage ()
{
}

void
DcpAppletPage::createContent ()
{
}

bool 
DcpAppletPage::hasWidget () const
{
    return true;
}

bool 
DcpAppletPage::hasError ()
{
    return false;
}

int 
DcpAppletPage::widgetId ()
{
    return m_WidgetId;
}

DcpAppletObject*
DcpAppletPage::applet()
{
    return m_Applet;
}


void
DcpAppletPage::load ()
{
}

void
DcpAppletPage::retranslateUi()
{
}

DcpAppletWidget*
DcpAppletPage::constructAppletWidget(DcpAppletObject*, DcpPage*, int)
{
    return 0;
}

bool
DcpAppletPage::preventQuit()
{
    return false;
}

