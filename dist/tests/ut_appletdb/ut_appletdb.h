#ifndef UT_APPLETDB_H
#define UT_APPLETDB_H

#include <QtTest/QtTest>
#include "dcpappletdb.h"

class Ut_DcpAppletDb: public QObject{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    // tests:
	void addPathTest();
    void categoryTest();

private:
    DcpAppletDb* m_Db;
};


#endif // UT_APPLETDB_H
