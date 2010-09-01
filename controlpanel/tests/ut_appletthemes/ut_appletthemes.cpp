/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel.
**
**
** This program is free software
{

}

 you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#include <QObject>
#include <QGraphicsSceneMouseEvent>

#include <appletthemes.h>
#include "ut_appletthemes.h"

#include "qfileinfo-fake.h"
#include "mtheme-fake.h"

#define THEME_DIR "/usr/share/themes/base/meegotouch/duicontrolpanel/style/"


void Ut_AppletThemes::init()
{

}


void Ut_AppletThemes::cleanup()
{

}


void Ut_AppletThemes::initTestCase()
{

}


void Ut_AppletThemes::cleanupTestCase()
{

}


void Ut_AppletThemes::testConstructDestruct()
{
    // check that an instance gets created:
    QVERIFY (AppletThemes::instance());
    QCOMPARE (AppletThemes::instance(), AppletThemes::sm_Instance);

    // deletion unmarks the instance:
    delete AppletThemes::instance();
    QVERIFY (! AppletThemes::sm_Instance);

    // again creating the instance is possible:
    QVERIFY (AppletThemes::instance());
}


void Ut_AppletThemes::testEnsureCssLoaded()
{
    AppletThemes* themes = AppletThemes::instance();

    // start with empty list:
    themes->m_LoadedThemes.clear();

    // trying with nonexistant css file (theme does not get loaded for real):
    themes->ensureCssLoaded ("libexample.so.0.1");
    QCOMPARE(themes->m_LoadedThemes.count(), 1);
    QVERIFY (themes->m_LoadedThemes.contains ("libexample.so.0.1")); // checked, but
    QVERIFY (!mtheme_loadedThemes().contains (THEME_DIR "example.css")); // not loaded!

    // trying with various lib names (theme gets loaded for real)
    qfileinfo_setExists (THEME_DIR "example1.css");
    themes->ensureCssLoaded ("libexample1.so.0.1");
    QCOMPARE (themes->m_LoadedThemes.count(), 2);
    QVERIFY (themes->m_LoadedThemes.contains ("libexample1.so.0.1"));
    QVERIFY (mtheme_loadedThemes().contains (THEME_DIR "example1.css"));

    qfileinfo_setExists (THEME_DIR "example2.css");
    themes->ensureCssLoaded ("libexample2.so.0");
    QCOMPARE (themes->m_LoadedThemes.count(), 3);
    QVERIFY (themes->m_LoadedThemes.contains ("libexample2.so.0"));
    QVERIFY (mtheme_loadedThemes().contains (THEME_DIR "example2.css"));

    qfileinfo_setExists (THEME_DIR "example3.css");
    themes->ensureCssLoaded ("libexample3.so");
    QCOMPARE (themes->m_LoadedThemes.count(), 4);
    QVERIFY (themes->m_LoadedThemes.contains ("libexample3.so"));
    QVERIFY (mtheme_loadedThemes().contains (THEME_DIR "example3.css"));

    // calling with the same lib name (.css does not get loaded again)
    mtheme_loadedThemes().remove (THEME_DIR "example3.css");
    themes->ensureCssLoaded ("libexample3.so");
    QVERIFY (!mtheme_loadedThemes().contains (THEME_DIR "example3.css"));
}


void Ut_AppletThemes::testOnThemeIsChanging()
{
    // we have an instance with nonempty loaded css:
    AppletThemes::instance()->m_LoadedThemes.insert ("xxx");;

    AppletThemes::instance()->onThemeIsChanging();

    // the set becomes empty:
    QVERIFY (AppletThemes::instance()->m_LoadedThemes.isEmpty());
}



QTEST_APPLESS_MAIN(Ut_AppletThemes)

