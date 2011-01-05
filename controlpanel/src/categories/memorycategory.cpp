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

#include "memorycategory.h"


MemoryCategory::MemoryCategory(const QString& name,
                               const QString& titleId,
                               const QString& parentId,
                               const QString& subtitleId,
                               const QString& subtitle,
                               const QString& iconId,
                               int order,
                               const QStringList& compatibilityIds)
{
    data.insert (ParentId, parentId);
    data.insert (NameId, name);
    data.insert (NameLogicalId, titleId);
    data.insert (ValueId, subtitle);
    data.insert (ValueLogicalId, subtitleId);
    data.insert (IconId, iconId);
    data.insert (AliasesId, compatibilityIds.join(QChar(',')));
    data.insert (OrderId, QString::number (order));
}

QString MemoryCategory::value(int key) const
{
    return data.value (key);
}

