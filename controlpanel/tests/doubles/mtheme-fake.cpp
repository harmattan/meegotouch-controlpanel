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

#include <MTheme>
#include "mtheme-fake.h"

static MTheme* inst = 0;
static QSet<QString> loadedThemes;

MTheme::MTheme(const QString &, const QString &, ThemeService ): d_ptr(0)
{
}


MTheme * MTheme::instance()
{
    if (!inst) inst = new MTheme ("x");
    return inst;
}

bool MTheme::loadCSS(const QString &filename, InsertMode)
{
    loadedThemes.insert (filename);
    return true;
}

QString MTheme::currentTheme ()
{
    return "x";
}

QSet<QString>& mtheme_loadedThemes()
{
    return loadedThemes;
}

