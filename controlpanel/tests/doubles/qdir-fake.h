/***************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef QDIR_FAKE_H__
#define QDIR_FAKE_H__

#include <QStringList>

class QDirFake 
{
    public:
        static void createFakeDir(const QString &dir, 
                                  const QStringList &content);
        static void removeFakeDir(const QString &dir);
};
#endif
