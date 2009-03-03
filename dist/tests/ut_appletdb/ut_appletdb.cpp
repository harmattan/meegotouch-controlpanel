#include "ut_appletdb.h"
#include "dcpappletmetadata.h"
#include <QList>
#include <DuiApplication>
const QString APPLETDIR="/usr/lib/dcp";
DuiApplication* app;


void Ut_DcpAppletDb::addPathTest()
{
    
} 
void Ut_DcpAppletDb::categoryTest()
{
    QList<DcpAppletMetadata*>* emptyList = m_Db->listByCategory("NOSUCHCATEGORY");
    QVERIFY(emptyList->isEmpty());
    delete emptyList;
    
    QList<DcpAppletMetadata*>* twoInAList = m_Db->listByCategory("NO");
    QVERIFY(twoInAList->count() == 2) ;
    delete twoInAList;
} 
void Ut_DcpAppletDb::initTestCase()
{
    int argc = 1;
    char* argv = (char*) "./ut_appletdb";
    qDebug() << "XXX";
    app = new DuiApplication(argc, &argv);
}

void Ut_DcpAppletDb::cleanupTestCase(){
    delete app;
}

void Ut_DcpAppletDb::init(){
    m_Db = new DcpAppletDb(APPLETDIR);
}

void Ut_DcpAppletDb::cleanup() {
}

QTEST_APPLESS_MAIN(Ut_DcpAppletDb)

