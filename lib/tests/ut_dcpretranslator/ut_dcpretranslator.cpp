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

#include <dcpretranslator.h>
#include <dcpretranslator_p.h>


#include "ut_dcpretranslator.h"

void Ut_DcpRetranslator::init()
{
    m_subject = DcpRetranslator::instance();
}

void Ut_DcpRetranslator::cleanup()
{
}

void Ut_DcpRetranslator::initTestCase()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpRetranslator::cleanupTestCase()
{
}

void Ut_DcpRetranslator::testInstance()
{
    QVERIFY(m_subject);
    QCOMPARE((void*)m_subject, (void*)DcpRetranslator::instance());
    QVERIFY(!DcpRetranslatorPriv::compatibleMode);
    QCOMPARE((void*)m_subject, (void*)m_subject->priv->instance);
}

void Ut_DcpRetranslator::testMainCatalogName()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpRetranslator::testEnsureTranslationsAreLoaded()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpRetranslator::testEnsureTranslationLoaded()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpRetranslator::testRetrenslate()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpRetranslator::testLoadAppletTranslation()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}


QTEST_APPLESS_MAIN(Ut_DcpRetranslator)
