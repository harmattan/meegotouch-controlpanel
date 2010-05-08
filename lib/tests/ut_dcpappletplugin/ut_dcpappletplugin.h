#ifndef UT_DCPAPPLETPLUGIN_H
#define UT_DCPAPPLETPLUGIN_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DcpAppletPlugin class declaration
#include "dcpappletplugin.h"
#include "dcpappletmetadata.h"

Q_DECLARE_METATYPE(DcpAppletPlugin*);

class Ut_DcpAppletPlugin : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testLoadBinaryOk();
    void testLoadBinaryError();
    void testLoadDsl();
    void testMetadata();
    void testInterfaceVersion();

private:
    DcpAppletPlugin* m_subject;
};

#endif
