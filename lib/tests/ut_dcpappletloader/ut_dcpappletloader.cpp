#include <QObject>
#include <QGraphicsSceneMouseEvent>

#include "dcpappletloader.h"


#include "ut_dcpappletloader.h"
#include "qpluginloader-fake.h"
#include "duidesktopentry-stub.h"

void Ut_DcpAppletLoader::init()
{
    m_metadata = new DcpAppletMetadata("dummy-path");
}

void Ut_DcpAppletLoader::cleanup()
{
    delete m_subject;
    m_subject = 0;
    delete m_metadata;
    m_metadata = 0;
}

void Ut_DcpAppletLoader::initTestCase()
{
}

void Ut_DcpAppletLoader::cleanupTestCase()
{
}

void Ut_DcpAppletLoader::testLoadOk()
{
    qPluginLoaderFakeSuccessful = true;
    m_subject = new DcpAppletLoader(m_metadata);
    QVERIFY(m_subject->applet());
    QVERIFY(dynamic_cast<DcpAppletLoaderApplet*>(m_subject->applet())->initialized());
}

void Ut_DcpAppletLoader::testLoadError()
{
    qPluginLoaderFakeSuccessful = false;
    m_subject = new DcpAppletLoader(m_metadata);
    QVERIFY(!m_subject->applet());
    QVERIFY(m_subject->errorMsg().contains(fakeErrorMsg));
}

void Ut_DcpAppletLoader::testMetadata()
{
    m_subject = new DcpAppletLoader(m_metadata);
    QVERIFY(m_subject->metadata() == m_metadata);
}

QTEST_MAIN(Ut_DcpAppletLoader)
