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

#ifndef PAGES_H
#define PAGES_H

#include <QString>

/*!
 * \brief A symbolic representation of a page.
 * The PageHandle is a purely symbolic representation of a page in the control
 * panel. It does not contain any binary information like widget pointers or
 * plugin objects, but only a string and numeric identification for a specific
 * page of a specific plugin.
 */
class PageHandle {

public:
    typedef enum {
        NOPAGE = -1,
        MAIN,
        CATEGORY_PAGEID_START,  // ---
        CONNECTIVITY,
        PHONE,
        Applications,
        NOTIFICATIONS,
        PERSONALIZE,
        BATTERY,
        SECURITY,
        REGIONALSETTING,
        LANGUAGEKEYBOARD,
        ACCESSORIES,
        BACKUP,
        ABOUT,
        CATEGORY_PAGEID_END,    // ---
        APPLET,
        APPLETCATEGORY,
        PAGEID_COUNT
    } PageTypeId;

    PageHandle (PageTypeId  pageType = NOPAGE, 
                const QString &name = "", 
                int widgetId = -1,
                bool isStandalone = false);
    bool operator== (const PageHandle& page) const;

    QString getStringVariant () const;

    PageTypeId  id;
    QString     param;
    int         widgetId;
    bool isStandalone;
};

#endif

