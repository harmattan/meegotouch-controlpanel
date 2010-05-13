/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel.
**
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#ifndef FT_MKFTCLASSNAME_H
#define FT_MKFTCLASSNAME_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/MkFtClassName class declaration
#include "mkftclassname.h"

Q_DECLARE_METATYPE(MkFtClassName*);

class Ft_MkFtClassName : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();

    MKFTCLASSMEMBERS

private:
    MkFtClassName* m_subject;
};

#endif
