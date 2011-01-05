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

#ifndef MEMORYCATEGORY_H
#define MEMORYCATEGORY_H

#include "category.h"

#include <QHash>

class MemoryCategory: public Category
{
public:
    MemoryCategory (const QString& name,
                    const QString& titleId = QString(),
                    const QString& parentId = QString(),
                    const QString& subtitleId = QString(),
                    const QString& subtitle = QString(),
                    const QString& iconId = QString(),
                    int order = 0,
                    const QStringList& compatibilityIds = QStringList());

protected:
    virtual QString value (int key) const;

private:
    QHash<int, QString> data;
};


#endif // MEMORYCATEGORY_H

