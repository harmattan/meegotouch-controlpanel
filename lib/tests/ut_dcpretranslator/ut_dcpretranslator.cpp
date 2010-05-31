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
#include <dcpappletmetadata.h>
#include <filedatas.h>
#include <MLocale>

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
    desktopTestFile =  "test.desktop";
    desktopBadTestFile = "testBad.desktop";

    fileDatas[desktopTestFile]["Name"] = "Browser";
    fileDatas[desktopTestFile]["Desktop Entry/Type"] = "DUIApplet";
    fileDatas[desktopTestFile]["Desktop Entry/Icon"] = "";
    fileDatas[desktopTestFile]["Desktop Entry/Exec"] = "";
    fileDatas[desktopTestFile]["Desktop Entry/X-logical-id"] = "qtn_sett_main_browser";
    fileDatas[desktopTestFile]["Desktop Entry/X-translation-catalog"] = "duisettings";
    fileDatas[desktopTestFile]["DUI/X-DUIApplet-Applet"] = "testapplet.so";
    fileDatas[desktopTestFile]["DUI/X-DUIApplet/ImageLandscape"] = "Widget_landscape_weather.png";
    fileDatas[desktopTestFile]["DUI/X-DUIApplet-ImagePortrait"] = "Widget_portrait_weather.png";
    fileDatas[desktopTestFile]["DUI/X-DUIApplet-ApplicationCommand"] = "./test";
    fileDatas[desktopTestFile]["DUI/X-DUIApplet-Dslfile"] = "dslfile";
    fileDatas[desktopTestFile]["DCP/Category"] = "Application";
    fileDatas[desktopTestFile]["DCP/Order"] = "1";
    fileDatas[desktopTestFile]["DCP/WidgetType"] = "DcpLabel2";
    fileDatas[desktopTestFile]["DCP/Text2"] = "firefox";
    fileDatas[desktopTestFile]["DCP/Align"] = "RIGHT";
    fileDatas[desktopTestFile]["DCP/Image"] = "test.png";
    fileDatas[desktopTestFile]["DCP/Part"] = "RobiJonMegKutyaraDer";
    fileDatas[desktopTestFile]["DCP/Parent"] = "RobiJonMegKutyaraDer_II";
    fileDatas[desktopTestFile]["isValid"] = "y";
    fileDatas[desktopBadTestFile]["Desktop Entry/Name"] = "Browser";
    fileDatas[desktopBadTestFile]["Desktop Entry/Type"] = "DUIApplet";
    fileDatas[desktopBadTestFile]["Desktop Entry/Icon"] = "";
    fileDatas[desktopBadTestFile]["Desktop Entry/Exec"] = "";
    fileDatas[desktopBadTestFile]["Desktop Entry/X-logical-id"] = "qtn_sett_main_browser";
    fileDatas[desktopBadTestFile]["Desktop Entry/X-translation-catalog"] = "";
    fileDatas[desktopBadTestFile]["DUI/X-DUIApplet-Applet"] = "libexampleapplet.so";
    fileDatas[desktopBadTestFile]["DUI/X-DUIApplet/ImageLandscape"] = "Widget_landscape_weather.png";
    fileDatas[desktopBadTestFile]["DUI/X-DUIApplet-ImagePortrait"] = "Widget_portrait_weather.png";
    fileDatas[desktopBadTestFile]["DCP/Category"] = "Application";
    fileDatas[desktopBadTestFile]["DCP/Order"] = "1";
    fileDatas[desktopBadTestFile]["DCP/WidgetType"] = "DcpLabel2";
    fileDatas[desktopBadTestFile]["DCP/Text2"] = "firefox";
    fileDatas[desktopBadTestFile]["isValid"] = "n";
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
    m_subject->setMainCatalogName("duisettings");
    QCOMPARE(m_subject->priv->binaryName, QString("duisettings"));
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
    m_subject->retranslate();
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpRetranslator::testLoadAppletTranslationOK()
{
    MLocale locale;
    DcpAppletMetadata *metadata = new DcpAppletMetadata(desktopTestFile);
    QVERIFY(!m_subject->priv->loadedTranslations.contains("duisettings"));
    QVERIFY(m_subject->loadAppletTranslation(locale, metadata));
    QVERIFY(m_subject->priv->loadedTranslations.contains("duisettings"));
    m_subject->priv->loadedTranslations.remove("duisettings");
}

void Ut_DcpRetranslator::testLoadAppletTranslationNOK()
{
    MLocale locale;
    DcpAppletMetadata *metadata = new DcpAppletMetadata(desktopBadTestFile);
    QVERIFY(!m_subject->priv->loadedTranslations.contains("duisettings"));
    QVERIFY(!m_subject->loadAppletTranslation(locale, metadata));
    QVERIFY(!m_subject->priv->loadedTranslations.contains("duisettings"));
}

QTEST_APPLESS_MAIN(Ut_DcpRetranslator)
