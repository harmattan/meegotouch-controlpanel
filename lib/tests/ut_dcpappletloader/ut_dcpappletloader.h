#ifndef UT_DCPAPPLETLOADER_H
#define UT_DCPAPPLETLOADER_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DcpAppletLoader class declaration
#include "dcpappletloader.h"
#include "dcpappletmetadata.h"

Q_DECLARE_METATYPE(DcpAppletLoader*);

class Ut_DcpAppletLoader : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testLoadOk();
    void testLoadError();
    void testMetadata();

private:
    DcpAppletLoader* m_subject;
    DcpAppletMetadata* m_metadata;
};

#endif
