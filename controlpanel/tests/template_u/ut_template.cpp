#include <QObject>
#include <QGraphicsSceneMouseEvent>

mkutclassinclude
mkutclassinclude_p

#include "ut_mkutclassname.h"

void Ut_MkUtClassName::init()
{
    m_subject = new MkUtClassName();
}

void Ut_MkUtClassName::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ut_MkUtClassName::initTestCase()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_MkUtClassName::cleanupTestCase()
{
}

QTEST_MAIN(Ut_MkUtClassName)
