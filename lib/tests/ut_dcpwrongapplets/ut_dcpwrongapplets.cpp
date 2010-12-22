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

#include <dcpwrongapplets.h>
#include <dcpappletobject.h>

#include "ut_dcpwrongapplets.h"
#include "execinfo-fake.h"
#include "signal-fake.h"
#include "mgconfitem-fake.h"

// this is because we test internal functions also which are not exported:
#include "dcpwrongapplets.cpp"

// an example appletpath:
const char* exampleAppletPath = "/usr/lib/duicontrolpanel/applets/libxxx.so";

void Ut_DcpWrongApplets::init()
{
}

void Ut_DcpWrongApplets::cleanup()
{
    DcpWrongApplets::destroyInstance();
    DcpWrongApplets::sm_Disabled = false;
    emptyFakeGConf();
}

void Ut_DcpWrongApplets::initTestCase()
{
}

void Ut_DcpWrongApplets::cleanupTestCase()
{
}

void Ut_DcpWrongApplets::testBacktraceLineIsAnApplet()
{
    // a matching line:
    const char* line = "065 /manni/usr/lib/duicontrolpanel/applets/libss.so.4"
                        "(_ZN12QApplication15x11ProcessEventEP7_XEvent+0x1311)"
                        " [0xf69ec481]";
    const char* start;
    const char* end;
    bool result = backtrace_line_is_an_applet(line, &start, &end);
    QCOMPARE (result, true);
    QCOMPARE ((int)((start-line)/sizeof(char)), 10);
    QCOMPARE ((int)((end-line)/sizeof(char)), 53);

    // a non matching line:
    line = "065 /usr/lib/libQtGui.so.4(_ZN12QApplication15x"
           "11ProcessEventEP7_XEvent+0x1311) [0xf69ec481]";
    result = backtrace_line_is_an_applet(line, &start, &end);
    QCOMPARE (result, false);
    QCOMPARE (start, (char*)0);
}


void Ut_DcpWrongApplets::testMarkAppletAsBad()
{
    mark_applet_as_bad (exampleAppletPath);
    QString date = MGConfItem(keyPath + exampleAppletPath + KEY_SEPARATOR +
                              "CrashDateTime").value().toString();
    QVERIFY (!date.isEmpty());
}


void Ut_DcpWrongApplets::testSomeCrashHappened()
{
//  // -- segfault from an applet --
//  segfaultFromApplet = true;
//  bool result = some_crash_happened();

//  // it found the applet:
//  QCOMPARE (result, true);

//  // the applet was marked bad:
//  const char* path = "/usr/lib/duicontrolpanel/applets/libss.so.4";
//  QString date = MGConfItem(keyPath + path + KEY_SEPARATOR +
//                            "CrashDateTime").value().toString();
//  QVERIFY (!date.isEmpty());


//  // -- segfault from the application --
//  segfaultFromApplet = false;
//  result = some_crash_happened();

//  // it found no applet:
//  QCOMPARE (result, false);
}


    /* No luck to fake to exit() calls yet...
void Ut_DcpWrongApplets::testTerminationSignalHandler()
{
    // terminate normally:
    lastExitStatus = -1;
    termination_signal_handler (SIGTERM);
    QCOMPARE (lastExitStatus, 0);
    lastExitStatus = -1;
    termination_signal_handler (SIGINT);
    QCOMPARE (lastExitStatus, 0);

    // terminate with a crash from the application:
    lastExitStatus = -1;
    segfaultFromApplet = false;
    termination_signal_handler (SIGSEGV);
    QCOMPARE (lastExitStatus, 0);

    // terminate with an applet crash:
    lastExitStatus = -1;
    segfaultFromApplet = true;
    termination_signal_handler (SIGSEGV);
    QCOMPARE (lastExitStatus, 0);
}
     */


void Ut_DcpWrongApplets::testQueryBadApplets()
{
    DcpWrongApplets* wa = DcpWrongApplets::instance();

    // empty:
    QVERIFY(wa->queryBadApplets().isEmpty());

    // one applet:
    DcpAppletMetadata metadata(QString("fake"));
    mark_applet_as_bad (qPrintable(metadata.fullBinary()));
    QSet<QString> badApplets = wa->queryBadApplets();
    QCOMPARE (badApplets.count(), 1);

    // the applet gets returned:
    QVERIFY (badApplets.contains(metadata.binary()));
    // the applet gets disabled:
    DcpAppletObject* applet =
        DcpAppletDb::instance()->applet(QString("fake-name"));
    QVERIFY (applet);
    QVERIFY (applet->metadata()->isDisabled());
}


void Ut_DcpWrongApplets::testDisabled()
{
    // checks that the default is the enabled state:
    QCOMPARE (DcpWrongApplets::sm_Disabled, false);

    // test instance in case supervisor is disabled
    connectedSignals.clear();
    DcpWrongApplets::disable();
    DcpWrongApplets* wa = DcpWrongApplets::instance();
    QVERIFY (DcpWrongApplets::sm_Instance);

    // checks that it gets disabled:
    QCOMPARE (DcpWrongApplets::sm_Disabled, true);

    // check that it did not connect any signals:
    QVERIFY (connectedSignals.isEmpty());
    // check repeated call does not create another instance:
    QCOMPARE (wa, DcpWrongApplets::instance());

    // test that it stays disabled on destroyinstance
    DcpWrongApplets::destroyInstance();
    QVERIFY (!DcpWrongApplets::sm_Instance);
    QCOMPARE (DcpWrongApplets::sm_Disabled, true);

}


void Ut_DcpWrongApplets::testConnectSupervisorSignals()
{
    // check if signals get connected:
    DcpWrongApplets::connectSupervisorSignals();

    QVERIFY(connectedSignals.contains(SIGTERM));
    QVERIFY(connectedSignals.contains(SIGHUP));
    QVERIFY(connectedSignals.contains(SIGINT));
    QVERIFY(connectedSignals.contains(SIGQUIT));
    QVERIFY(connectedSignals.contains(SIGILL));
    QVERIFY(connectedSignals.contains(SIGSEGV));
    QVERIFY(connectedSignals.contains(SIGBUS));
    QVERIFY(connectedSignals.contains(SIGABRT));
    QVERIFY(connectedSignals.contains(SIGFPE));
}


void Ut_DcpWrongApplets::testInstanceNDestroy()
{
    // some cleanup:
    DcpWrongApplets::sm_Disabled = false;
    connectedSignals.clear();
    MGConfItem conf(dcpTimeStampPath);
    conf.unset();
    QVERIFY (!conf.value().isValid());

    // test instance in case supervisor is enabled
    DcpWrongApplets* wa = DcpWrongApplets::instance();
    QVERIFY (DcpWrongApplets::sm_Instance);
    QCOMPARE (wa, DcpWrongApplets::sm_Instance);

    // ensure that removeBadsOnTimeStampChange gets called
    QVERIFY (conf.value().isValid());

    // ensure that badapplets get filled: FIXME
    // QVERIFY (!wa->m_BadApplets.isEmpty());

    // -- test destroyinstance --
    DcpWrongApplets::destroyInstance();
    QVERIFY (!DcpWrongApplets::sm_Instance);

    // calling it repeatedly does not do harm:
    DcpWrongApplets::destroyInstance();
}


void Ut_DcpWrongApplets::testIsAppletRecentlyCrashed()
{
    DcpWrongApplets* wa = DcpWrongApplets::instance();
    QVERIFY(!wa->isAppletRecentlyCrashed(exampleAppletPath));
    mark_applet_as_bad (exampleAppletPath);
    QVERIFY(wa->isAppletRecentlyCrashed(exampleAppletPath));
}


void Ut_DcpWrongApplets::testGConfRecursiveRemove()
{
    // create some fake path hierarchy:
    MGConfItem gc1("/usr/fake/key");
    gc1.set(QString("one"));
    MGConfItem gc2("/usr/fake/key2");
    gc2.set(QString("two"));
    MGConfItem gc3("/usr/fake2/key2");
    gc3.set(QString("three"));
    MGConfItem gc4("/usr/fake3");
    gc4.set(QString("four"));

    gconf_recursive_remove("/usr");

    QVERIFY (!gc1.value().isValid());
    QVERIFY (!gc2.value().isValid());
    QVERIFY (!gc3.value().isValid());
    QVERIFY (!gc4.value().isValid());
}


void Ut_DcpWrongApplets::testRemoveBadsOnDcpTimeStampChange()
{
    // -- test that it removes bad applets on timestamp change: --
    mark_applet_as_bad (exampleAppletPath);
    MGConfItem conf(dcpTimeStampPath);
    QVERIFY (conf.value().toString().isEmpty()); // no timestamp yet
    DcpWrongApplets* wa = DcpWrongApplets::instance();
    wa->removeBadsOnDcpTimeStampChange();

    QVERIFY (conf.value().isValid()); // the new timestamp was set
    // the applet crash was forgotten:
    QVERIFY(! wa->isAppletRecentlyCrashed(exampleAppletPath));


    // test that it does not remove them when timestamp does not change:
    mark_applet_as_bad (exampleAppletPath);
    wa->removeBadsOnDcpTimeStampChange();
    // the applet crash was not forgotten:
    QVERIFY(wa->isAppletRecentlyCrashed(exampleAppletPath));
}

int main (int argc, char** argv)
{
    // this is necessery because we request the path of the application etc.
    QCoreApplication app(argc, argv);

    Ut_DcpWrongApplets test;
    return QTest::qExec(&test, argc, argv);
}


