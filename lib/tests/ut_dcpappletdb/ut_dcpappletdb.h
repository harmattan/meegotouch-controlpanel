 #ifndef UT_DCPAPPLETDB_H
#define UT_DCPAPPLETDB_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DcpAppletDb class declaration
#include <dcpappletdb.h>

Q_DECLARE_METATYPE(DcpAppletDb*);

class Ut_DcpAppletDb : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void testCreateAndDestroy();
    void testInstance();
    void testAddContainNameFile();
    void testAddPath();
    void testAppletNames();
    void testApplet();
    void testEraseEntry();
    void testListByCategory();
    void testListMostUsed();
    void testRefresh();

private:
    DcpAppletDb* m_subject;
    QString  emptyDesktopDir, testDesktopDir, testDesktopDir2, testDesktopDir3;
    QString  desktopTestFile, desktopTestFile2;
    QString  desktopDateTimeFile, desktopDisplayFile;
    QString  browserEntryName, datetimeEntryName, displayEntryName;
    QCoreApplication* qap;
};

#endif

