#include <QObject>
#include <QGraphicsSceneMouseEvent>

#include "dcpappletloader.h"


#include "ut_dcpappletloader.h"
#include "qpluginloader-fake.h"
#include "dcpappletmetadata-fake.h"
#include "duidesktopentry-stub.h"

void Ut_DcpAppletLoader::init()
{
}

void Ut_DcpAppletLoader::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_DcpAppletLoader::initTestCase()
{
}

void Ut_DcpAppletLoader::cleanupTestCase()
{
}

/**
 * checks if appletloader calls applet's init function
 */
void Ut_DcpAppletLoader::testLoadBinaryOk()
{
    DcpAppletMetadataFake::appletType = 
        DcpAppletMetadataFake::TYPE_BINARY;
    qPluginLoaderFakeSuccessful = true;
    DcpAppletMetadata *metadata = new DcpAppletMetadata("dummy-binary");
    m_subject = new DcpAppletLoader(metadata);
    QVERIFY(m_subject->applet());
    QVERIFY(
        dynamic_cast<DcpAppletLoaderApplet*>(m_subject->applet())->initialized()
        );
    delete metadata;
}

/**
 * checks if appletloader returns 0 on load error and
 * errorMsg() contains the load error message coming from the QPluginLoader
 */
void Ut_DcpAppletLoader::testLoadBinaryError()
{
    DcpAppletMetadataFake::appletType = 
        DcpAppletMetadataFake::TYPE_BINARY;
    qPluginLoaderFakeSuccessful = false;
    DcpAppletMetadata *metadata = new DcpAppletMetadata("dummy-binary");
    m_subject = new DcpAppletLoader(metadata);
    QVERIFY(!m_subject->applet());
    QVERIFY(m_subject->errorMsg().contains(fakeErrorMsg));
    delete metadata;
}

/**
 * TODO
 */
void Ut_DcpAppletLoader::testLoadDsl()
{
    DcpAppletMetadataFake::appletType = 
        DcpAppletMetadataFake::TYPE_DSL;
    QSKIP("TODO: test DSL loading", SkipAll);
}


/**
 * checks if metadata() returns the same pointer that was given in
 * initialization
 */
void Ut_DcpAppletLoader::testMetadata()
{
    DcpAppletMetadata *metadata = new DcpAppletMetadata("dummy-binary");
    m_subject = new DcpAppletLoader(metadata);
    QVERIFY(m_subject->metadata() == metadata);
    delete metadata;
}

QTEST_MAIN(Ut_DcpAppletLoader)
