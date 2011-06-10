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
#include <QSignalSpy>

#include "dcpappletmanager.h"
#include "dcpappletmetadata.h"

#include "ut_dcpappletmanager.h"
#include "qdir-fake.h"

void Ut_DcpAppletManager::init()
{
    m_subject = new DcpAppletManager();
}

void Ut_DcpAppletManager::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_DcpAppletManager::initTestCase()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpAppletManager::cleanupTestCase()
{
}

void Ut_DcpAppletManager::testSingleInstance()
{
    DcpAppletManager *mng = DcpAppletManager::instance();
    QVERIFY(mng == DcpAppletManager::instance());
    DcpAppletManager::destroyInstance();
}

void Ut_DcpAppletManager::testLoadDesktopFile()
{
    QString fileName = "foo";
    bool ret = m_subject->loadDesktopFile(fileName);
    QVERIFY(ret);
    QVERIFY(m_subject->containsFile(fileName));
    QVERIFY(m_subject->m_AppletsByFile[fileName]->fileName() == fileName);
    QCOMPARE(m_subject->appletNames()[0], fileName + "-name");
    QCOMPARE(m_subject->containsName(fileName + "-name"), true);
    QCOMPARE(m_subject->appletNames().count(), 1);
}

void Ut_DcpAppletManager::testLoadMetadata()
{
    m_subject->addDesktopDir("testdir");
    QStringList dirContent;
    dirContent << "file1.desktop" << "file2.desktop" << "file3.desktop";
    QDirFake::createFakeDir("testdir", dirContent);
    m_subject->loadMetadata();
    foreach (QString file, dirContent) {
        QVERIFY(m_subject->containsFile(file));
    }
    QVERIFY(m_subject->m_AppletsByFile.size());
}

void Ut_DcpAppletManager::testLoadMetadataAsync()
{
    m_subject->addDesktopDir("testdir");
    QStringList dirContent;
    dirContent << "file1.desktop" << "file2.desktop" << "file3.desktop";
    QDirFake::createFakeDir("testdir", dirContent);
    QSignalSpy spy(m_subject, SIGNAL(metadataLoaded()));
    m_subject->loadMetadataAsync();
    QVERIFY(m_subject->isMetadataLoadStarted());

    // run event loop for 100 ms
    QEventLoop loop;
    QTimer::singleShot(100, &loop, SLOT(quit()));    
    loop.exec();

    QCOMPARE(spy.count(), 1);
    foreach (QString file, dirContent) {
        m_subject->containsFile(file);
    }
    QVERIFY(m_subject->isMetadataLoaded());
}

void Ut_DcpAppletManager::testDesktopDirs()
{
    QStringList dirContent1;
    dirContent1 << "file11.desktop" << "file12.desktop" << "file13.desktop";
    QDirFake::createFakeDir("testdir1", dirContent1);
    m_subject->addDesktopDir("testdir1");
    QStringList dirContent2;
    dirContent2 << "file21.desktop" << "file22.desktop" << "file23.desktop";
    QDirFake::createFakeDir("testdir2", dirContent2);
    m_subject->addDesktopDir("testdir2");

    QVERIFY(m_subject->m_DesktopDirs.contains("testdir1"));
    QVERIFY(m_subject->m_DesktopDirs.contains("testdir2"));
    
    m_subject->loadMetadata();
    foreach (QString file, dirContent1 + dirContent2) {
        QVERIFY(m_subject->containsFile(file));
    }
    
    m_subject->clearData();
    QVERIFY(!m_subject->m_DesktopDirs.contains("testdir1"));
    QVERIFY(!m_subject->m_DesktopDirs.contains("testdir2"));
}


bool testCheckFunction(const QString &cat)
{
    if (cat == "file1.desktop-category") {
        return false;
    }
    return true;
}

void Ut_DcpAppletManager::testAccessors()
{
    m_subject->addDesktopDir("testdir");
    QStringList dirContent;
    dirContent << "file1.desktop" << "file2.desktop" << "file3.desktop";
    QDirFake::createFakeDir("testdir", dirContent);
    QSet<QString> origFiles = QSet<QString>::fromList(dirContent);
    m_subject->loadMetadata();

    // test list()
    DcpAppletMetadataList metadataList = m_subject->list();
    QSet<QString> files;
    foreach (DcpAppletMetadata *metadata, metadataList) {
        files.insert(metadata->fileName());
    }
    QCOMPARE(origFiles, files);

    // test listByCategory(QString)
    foreach (QString fileName, dirContent) {
        QString fakeCategory = fileName + "-category";
        DcpAppletMetadataList metadataList = 
            m_subject->listByCategory(fakeCategory);
        QCOMPARE(metadataList.length(), 1);
        QCOMPARE(metadataList[0]->fileName(), fileName);
    }

    // test listByCategory(QStringList, CheckFunction)
    QStringList categories;
    categories << "file2.desktop-category";
    // expected applets: file1.desktop from testCheckFunction, 
    //                   file2.desktop from categories
    metadataList = m_subject->listByCategory(categories, testCheckFunction);
    QStringList filteredFiles;
    foreach (DcpAppletMetadata *metadata, metadataList) {
        filteredFiles.append(metadata->fileName());
    }
    QCOMPARE(filteredFiles.size(), 2);
    QVERIFY(filteredFiles.contains("file1.desktop"));
    QVERIFY(filteredFiles.contains("file2.desktop"));

    // test applet()
    foreach (QString fileName, dirContent) {
        QString fakeName = fileName + "-name";
        DcpAppletObject *obj = m_subject->applet(fakeName);
        QVERIFY(obj);
    }
    QCOMPARE(m_subject->isAppletLoaded("file1.desktop-name"), true);
    QCOMPARE(m_subject->loadedApplets().count(), 3);


}

void Ut_DcpAppletManager::testUseless()
{
    m_subject->listMostUsed();

}

QTEST_MAIN(Ut_DcpAppletManager)
