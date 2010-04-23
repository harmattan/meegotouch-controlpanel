#include <QObject>
#include <QGraphicsLinearLayout>
#include <MLinearLayoutPolicy>

#include <dcpcategorypage.h>


#include "ut_dcpcategorypage.h"

void Ut_DcpCategoryPage::init()
{
    m_subject = new DcpCategoryPage();
}

void Ut_DcpCategoryPage::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_DcpCategoryPage::initTestCase()
{
}

void Ut_DcpCategoryPage::cleanupTestCase()
{
}

void Ut_DcpCategoryPage::testCreateContents()
{
    m_subject->createContent();
    QVERIFY(m_subject->m_Category);
    QCOMPARE(m_subject->mainLayout()->itemAt(0), (QGraphicsWidget*)m_subject->m_Category);
}
QTEST_APPLESS_MAIN(Ut_DcpCategoryPage)
