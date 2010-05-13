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

#include <QObject>
#include <QGraphicsSceneMouseEvent>

mkftclassinclude
mkftclassinclude_p

#include "ft_mkftclassname.h"

void Ft_MkFtClassName::init()
{
    m_subject = new MkFtClassName();
}

void Ft_MkFtClassName::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ft_MkFtClassName::initTestCase()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ft_MkFtClassName::cleanupTestCase()
{
}

QTEST_MAIN(Ft_MkFtClassName)
