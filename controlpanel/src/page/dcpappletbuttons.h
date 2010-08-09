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

#ifndef DCPAPPLETBUTTONS_H
#define DCPAPPLETBUTTONS_H

#include <DcpMainCategory>

#include "maintranslations.h"

class DcpAppletMetadata;

class DcpAppletButtons :
    public DcpMainCategory
{
    Q_OBJECT

public:
    DcpAppletButtons (
            const DcpCategoryInfo  *categoryInfo,
            const QString          &title = "",
            QGraphicsWidget        *parent = 0);
    ~DcpAppletButtons ();

    void setCategoryInfo (const DcpCategoryInfo  *categoryInfo);

    void addComponent (
            DcpAppletMetadata *metadata);

    virtual bool reload();
    DcpAppletMetadata* appletMetadata (int pos);

protected:
    virtual void createContents();

private:
    void markAllInactive();

    const DcpCategoryInfo  *m_CategoryInfo;
    friend class Ut_DcpAppletButtons;
};

#endif

