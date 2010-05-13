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

#include <QObject>
#include <QGraphicsSceneMouseEvent>

#include <dcpappletpage.h>
#include <dcpappletobject.h>

#include "ut_dcpappletpage.h"

void Ut_DcpAppletPage::init()
{
    m_subject = new DcpAppletPage(0);
}

void Ut_DcpAppletPage::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_DcpAppletPage::initTestCase()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpAppletPage::cleanupTestCase()
{
}

QTEST_APPLESS_MAIN(Ut_DcpAppletPage)
