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

#ifndef DCPCATEGORIES_H
#define DCPCATEGORIES_H

#include <QList>
#include <QHash>
#include <QString>
class Category;

class DcpCategories
{
public:
    static DcpCategories* instance();
    static void destroy();
    ~DcpCategories();

    Category* categoryById (const QString& id) const;
    QList<const Category*> categoryChildren (const QString& id) const;

    static bool hasCategory (const QString& id);

    Category* mainPageCategory () const {
        return categoryById (mainPageCategoryName());
    }
    static QString mainPageCategoryName () { return "MainPage"; }

private:
    DcpCategories();
    static DcpCategories* sm_Instance;
    void add (Category* category);

    QList<Category*> m_Categories;
    QHash<QString, Category*> m_CategoryById;
};

#endif // DCPCATEGORIES_H

