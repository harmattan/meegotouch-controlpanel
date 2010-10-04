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
#include <QByteArray>

#include <DcpApplet>
#include <DcpWidgetTypes>

#include <DcpAppletMetadata>

#include "ft_dcpappletmetadata.h"
#include <MGConfItem>

void Ft_DcpAppletMetadata::initTestCase()
{
    static int c = 0;
    static QByteArray arg("dummyarg");
    char *argp = arg.data();
    qap = new QCoreApplication(c, &argp);
    QString desktopDir(qApp->applicationDirPath() + 
                       "/ft_dcpappletmetadata-data/desktops/");
    desktopTestFile =  desktopDir + "test.desktop";
    desktopBadTestFile = desktopDir + "testBad.desktop";

    appletDir = "so.applet/";
    appletSo = "testapplet.so";
}

void Ft_DcpAppletMetadata::cleanupTestCase()
{
    delete qap;
}

void Ft_DcpAppletMetadata::init()
{
    QVERIFY(m_subject = new DcpAppletMetadata(desktopTestFile));
}

void Ft_DcpAppletMetadata::cleanup()
{
    if (m_subject) {
       delete m_subject;
       m_subject = 0;
    }
}

void Ft_DcpAppletMetadata::testCreateAndDestroy()
{
    if (QTest::currentTestFailed()) return;
}

void Ft_DcpAppletMetadata::testIsValid()
{
    if (QTest::currentTestFailed()) return;

    QVERIFY(m_subject->isValid());
    delete m_subject;
    m_subject = 0;

    QWARN("\n\t----Expected QWARN: Multiple definitions of group 'M'----");
    QVERIFY((m_subject = new DcpAppletMetadata(desktopBadTestFile)));
    QVERIFY(!m_subject->isValid());
}

void Ft_DcpAppletMetadata::testIsModified()
{
    if (QTest::currentTestFailed()) return;

    QVERIFY((m_subject = new DcpAppletMetadata(desktopTestFile)));

    QVERIFY(!m_subject->isModified());
#if 0
    FIXME

    // touch the desktop file:
    QFile file(desktopTestFile);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    file.close();

    QVERIFY(m_subject->isModified());
#endif
}

void Ft_DcpAppletMetadata::testName()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->name(), QString("Browser"));
}
void Ft_DcpAppletMetadata::testFileName()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->fileName(), desktopTestFile);
}

void Ft_DcpAppletMetadata::testCategory()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->category(), QString("Application"));
}

void Ft_DcpAppletMetadata::testBinary()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->binary(), QString("testapplet.so"));
}

void Ft_DcpAppletMetadata::testFullBinary()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->fullBinary(), appletDir + appletSo);
}

void Ft_DcpAppletMetadata::testWidgetTypeID()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->widgetTypeID(), static_cast<int>(DcpWidgetType::Label));
}  

void Ft_DcpAppletMetadata::testAlign()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->align(), Qt::AlignRight);

}

void Ft_DcpAppletMetadata::testToggle()
{
    if (QTest::currentTestFailed()) return;
    QSKIP("!!!! UnableToLoadAnyApplet bug under fixxing by Lgal !!!!",
            SkipSingle);

}


void Ft_DcpAppletMetadata::testImageName()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->imageName(), QString("test.png"));
}

void Ft_DcpAppletMetadata::testOrder()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->order(), 1);
}

#ifdef MOSTUSED
void Ft_DcpAppletMetadata::testUsage()
{

    if (QTest::currentTestFailed()) return;

    qWarning() <<"\n@@" <<m_subject->usage() <<"@@\n";
    QSKIP("!!!! RelativePath bug under fixxing by Retsoft !!!!", SkipSingle);
}
#endif

void Ft_DcpAppletMetadata::testPart()
{
    if (QTest::currentTestFailed()) return;

    QCOMPARE(m_subject->part(), QString("RobiJonMegKutyaraDer"));
}


QTEST_APPLESS_MAIN(Ft_DcpAppletMetadata)
