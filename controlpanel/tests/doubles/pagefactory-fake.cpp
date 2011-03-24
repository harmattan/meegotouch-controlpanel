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

/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include "pagefactory.h"
#include "dcppage.h"

PageFactory *PageFactory::sm_Instance = 0;
static DcpPage* sCurrentPage = 0;

PageFactory::PageFactory ():
    QObject ()
{
}

PageFactory::~PageFactory ()
{
}

void
PageFactory::destroy()
{
}


PageFactory *
PageFactory::instance ()
{
    if (!sm_Instance)
        sm_Instance = new PageFactory();
    return sm_Instance;
}

DcpPage*
PageFactory::createPage (
        const PageHandle &)
{
    return 0;
}

DcpPage*
PageFactory::currentPage ()
{
    return sCurrentPage;
}

bool
PageFactory::changePage (const PageHandle &handle, bool)
{
    delete sCurrentPage;
    sCurrentPage = new DcpPage();
    sCurrentPage->setHandle (handle.id, handle.param);
    return true;
}

void
PageFactory::pageChanged (MApplicationPage *)
{
}

void
PageFactory::appletWantsToStart (int)
{
}

void
PageFactory::onAppletLoaded (DcpAppletObject *)
{
}

bool
PageFactory::changeToAppletPage (const QString& appletName)
{
    Q_UNUSED (appletName);
    return true;
}

void PageFactory::preloadAppletLauncher ()
{
}

void PageFactory::preloadBriefReceiver()
{
}

void PageFactory::mainPageFirstShown()
{
}

void PageFactory::onDisplayEntered ()
{
}

bool
PageFactory::isCurrentPage (const PageHandle &)
{
    return false;
}

MApplicationWindow* PageFactory::window ()
{
    return 0;
}

void PageFactory::newWin ()
{
}

void
PageFactory::raiseMainWindow()
{
}

bool PageFactory::eventFilter(QObject *obj, QEvent *event)
{
    return QObject::eventFilter (obj, event);
}


