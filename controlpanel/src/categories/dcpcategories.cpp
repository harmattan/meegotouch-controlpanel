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
#include "filecategory.h"

#include <QDir>

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
    // add the main category:
    add (new MemoryCategory (mainPageCategoryName(), // <- name
                             "qtn_sett_main_title"   // <- translation id
                            ));

    // load the available categories:
    QDir dir (DCP_CATEGORY_DIR);
    QStringList nameFilters(QString("*.cpcategory"));
    foreach (QString fileName,
             dir.entryList (nameFilters, QDir::Readable | QDir::Files))
    {
        Category* category = new FileCategory (DCP_CATEGORY_DIR "/" + fileName);

        if (category->isValid()) {
            add (category);
        } else {
            qWarning ("Non valid category: %s", qPrintable(fileName));
            delete category;
        }
    }

    buildParentChildRelations();
}

// build the parent - child relationships:
void DcpCategories::buildParentChildRelations ()
{
    foreach (const Category* category, m_Categories) {
        QString parentId = category->parentId();
        if (parentId.isEmpty()) continue;
        Category* parent = categoryById (parentId);
        if (parent) {
            parent->addChild (category);
        } else if (!parentId.isEmpty()) {
            qWarning ("Warning: could not find the parent (%s) for the category %s",
                      qPrintable (category->parentId()),
                      qPrintable (category->name()));
        }
    }
}

/*!
 * Little helper for the constructor,
 * do not use it to add more categories later
 */
void DcpCategories::add (Category* category)
{
    m_Categories.append (category);

    // hash by their ids:
    foreach (QString id, category->referenceIds()) {
        if (!id.isEmpty()) {
            m_CategoryById.insert (id, category);
        }
    }
}

bool DcpCategories::hasCategory (const QString& id)
{
    return instance()->categoryById(id) != 0;
}

