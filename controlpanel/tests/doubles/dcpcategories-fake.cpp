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

#include "dcpcategories.h"
#include "memorycategory.h"

DcpCategories* DcpCategories::sm_Instance = 0;

DcpCategories* DcpCategories::instance()
{
    if (!sm_Instance) {
        sm_Instance = new DcpCategories();
    }
    return sm_Instance;
}


void DcpCategories::destroy()
{
    delete sm_Instance;
}


DcpCategories::~DcpCategories()
{
    // unmarks the instance:
    sm_Instance = 0;

    // free up
    qDeleteAll (m_Categories);
}


Category* DcpCategories::categoryById(const QString& id) const
{
    return m_CategoryById.value (id);
}


QList<const Category*> DcpCategories::categoryChildren(const QString& id) const
{
    const Category* category = categoryById (id);
    return category ? category->children () : QList<const Category*>();
}


DcpCategories::DcpCategories()
{
    add (new MemoryCategory (
                      "FAKE-CATEGORY",
                      "fake-category",
                      "MainPage",
                      "qtn_subtitle",
                      "Value line",
                      "icon"));

    add (new MemoryCategory (
                      "ZERO",
                      "",
                      "",
                      "MainPage",
                      "",
                      ""));

    add (new MemoryCategory (
                      "MainPage",
                      "qtn_sett_main_title",
                      "",
                      "",
                      "",
                      ""));
}

void DcpCategories::add (Category* category)
{
    m_Categories.append (category);

    // hash by their ids:
    foreach (QString id, category->referenceIds()) {
        m_CategoryById.insert (id, category);
    }
}

bool DcpCategories::hasCategory (const QString& id)
{
    return instance()->categoryById(id) != 0;
}

