#ifndef UT_DCPAPPLETMETADATA_H
#define UT_DCPAPPLETMETADATA_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DcpAppletMetadata class declaration
#include <dcpappletmetadata.h>

Q_DECLARE_METATYPE(DcpAppletMetadata*);

class Ut_DcpAppletMetadata : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void testCreateAndDestroy();
    void testIsValid();
    void testIsModified();
    void testName();
    void testFileName();
    void testCategory();
    void testGetSetBinaryDir();
    void testBinary();
    void testFullBinary();
    void testWidgetTypeID();
    void testAlign();
    void testToggle();
//    void testText1(); it can't be tested
    void testText2();
    void testImage();
    void testOrder();
    void testUsage();
    void testPart();
    void testApplet();
    void testSetGetParent();
    void testParentName();
    void testCleanup();

    void testBriefChanged();

private:
    DcpAppletMetadata* m_subject;
    QString            desktopOrigFile,desktopTestFile,desktopBadTestFile;
    QString            appletDir,appletSo;
};

#endif
