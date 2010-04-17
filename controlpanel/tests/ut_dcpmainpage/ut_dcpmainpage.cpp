#include <QObject>
#include <QGraphicsSceneMouseEvent>

#include <dcpmainpage.h>


#include "ut_dcpmainpage.h"

void Ut_DcpMainPage::init()
{
    m_subject = new DcpMainPage();
}

void Ut_DcpMainPage::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_DcpMainPage::initTestCase()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpMainPage::testCreation()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpMainPage::testCreateContent()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpMainPage::testCreateContentLate()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpMainPage::testReload()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpMainPage::testShown()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpMainPage::testBack()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpMainPage::testRetranslateUi()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpMainPage::testHideEvent()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_DcpMainPage::cleanupTestCase()
{
}

QTEST_MAIN(Ut_DcpMainPage)
