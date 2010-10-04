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

#include "dcpdebug.h"

#include "pages.h"

PageHandle::PageHandle (
        PageTypeId      pageType, 
        const QString  &name,
        int             widgetId,
        bool            isStandalone):  
    id (pageType),
    param (name),
    widgetId (widgetId),
    isStandalone (isStandalone)
{
}


QString
PageHandle::getStringVariant () const
{
    const char *typeName = "Unknown";

    switch (id) {
        case NOPAGE:
            typeName = "NOPAGE";
            break;

        case MAIN:
            typeName = "MAIN";
            break;

        case CATEGORY_PAGEID_START:
            typeName = "CATEGORY_PAGEID_START";
            break;

        case LOOKANDFEEL:
            typeName = "LOOKANDFEEL";
            break;

        case CONNECTIVITY:
            typeName = "CONNECTIVITY";
            break;
        case REGIONALSETTING:
            typeName = "REGIONALSETTING";
            break;
        case DEVICESYSTEM:
            typeName = "DEVICESYSTEM";
            break;

        case UTILITIES:
            typeName = "UTILITIES";
            break;

        case ServiceAccounts:
            typeName = "ServiceAccounts";
            break;

        case Applications:
            typeName = "Applications";
            break;

        case CATEGORY_PAGEID_END:
            typeName = "CATEGORY_PAGEID_END";
            break;

        case APPLET:
            typeName = "APPLET";
            break;

        case APPLETCATEGORY:
	    typeName = "APPLETCATEGORY";
	    break;

        case PAGEID_COUNT:
            typeName = "PAGEID_COUNT";
            break;
    }

    return QString (typeName) + "://" 
        + param + "/" 
        + QString::number (widgetId);
}


bool PageHandle::operator== (const PageHandle& page) const
{
    return page.id == id && page.param == param &&
           page.widgetId == widgetId;
}

