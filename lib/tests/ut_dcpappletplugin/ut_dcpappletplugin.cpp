#include <QObject>
#include <QGraphicsSceneMouseEvent>

#include "dcpappletplugin.h"


#include "ut_dcpappletplugin.h"
#include "qpluginloader-fake.h"
#include "dcpappletmetadata-fake.h"
#include "mdesktopentry-stub.h"

void Ut_DcpAppletPlugin::init()
{
}

void Ut_DcpAppletPlugin::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_DcpAppletPlugin::initTestCase()
{
}

void Ut_DcpAppletPlugin::cleanupTestCase()
{
}

/**
 * checks if appletloader calls applet's init function
 */
void Ut_DcpAppletPlugin::testLoadBinaryOk()
{
    DcpAppletMetadataFake::appletType = 
        DcpAppletMetadataFake::TYPE_BINARY;
    qPluginLoaderFakeSuccessful = true;
    DcpAppletMetadata *metadata = new DcpAppletMetadata("dummy-binary");
    m_subject = new DcpAppletPlugin(metadata);
    QVERIFY(m_subject->applet());
    QVERIFY(
        dynamic_cast<DcpAppletPluginApplet*>(m_subject->applet())->initialized()
        );
    delete metadata;
}

/**
 * checks if appletloader returns 0 on load error and
 * errorMsg() contains the load error message coming from the QPluginLoader
 */
void Ut_DcpAppletPlugin::testLoadBinaryError()
{
    DcpAppletMetadataFake::appletType = 
        DcpAppletMetadataFake::TYPE_BINARY;
    qPluginLoaderFakeSuccessful = false;
    DcpAppletMetadata *metadata = new DcpAppletMetadata("dummy-binary");
    m_subject = new DcpAppletPlugin(metadata);
    QVERIFY(!m_subject->applet());
    QVERIFY(m_subject->errorMsg().contains(fakeErrorMsg));
    delete metadata;
}

/**
 * TODO
 */
void Ut_DcpAppletPlugin::testLoadDsl()
{
    DcpAppletMetadataFake::appletType = 
        DcpAppletMetadataFake::TYPE_DSL;
    QSKIP("TODO: test DSL loading", SkipAll);
}


/**
 * checks if metadata() returns the same pointer that was given in
 * initialization
 */
void Ut_DcpAppletPlugin::testMetadata()
{
    DcpAppletMetadata *metadata = new DcpAppletMetadata("dummy-binary");
    m_subject = new DcpAppletPlugin(metadata);
    QVERIFY(m_subject->metadata() == metadata);
    delete metadata;
}

QTEST_APPLESS_MAIN(Ut_DcpAppletPlugin)
