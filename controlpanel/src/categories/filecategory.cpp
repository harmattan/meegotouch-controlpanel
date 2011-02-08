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

#include "filecategory.h"

#include <QSettings>

const char* FileCategory::keys[KeyIdMax] = {
    "Parent",
    "Name",
    "Name-logical-id",
    "Value",
    "Value-logical-id",
    "Icon",
    "Aliases",
    "Translation-catalogs",
    "Order",
    "ComponentOrder"
};

FileCategory::FileCategory(const QString& fileName):
    m_Settings (new QSettings (fileName, QSettings::IniFormat))
{
}

FileCategory::~FileCategory ()
{
    delete m_Settings;
}

inline QString FileCategory::value (int key) const
{
    return m_Settings->value (keys[key]).toString();
}

bool FileCategory::isValid() const
{
    return m_Settings && (m_Settings->status() == QSettings::NoError) &&
           Category::isValid();
}

