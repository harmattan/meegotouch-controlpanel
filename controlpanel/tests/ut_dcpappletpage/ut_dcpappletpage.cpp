#include <QObject>
#include <QGraphicsSceneMouseEvent>

#include <dcpappletpage.h>
#include <dcpappletobject.h>

#include "ut_dcpappletpage.h"

void Ut_DcpAppletPage::init()
{
    m_subject = new DcpAppletPage(0);
}

void Ut_DcpAppletPage::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_DcpAppletPage::initTestCase()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpAppletPage::cleanupTestCase()
{
}

QTEST_APPLESS_MAIN(Ut_DcpAppletPage)
