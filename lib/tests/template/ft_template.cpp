#include <QObject>
#include <QGraphicsSceneMouseEvent>

mkftclassinclude
mkftclassinclude_p

#include "ft_mkftclassname.h"

void Ft_MkFtClassName::init()
{
    m_subject = new MkFtClassName();
}

void Ft_MkFtClassName::cleanup()
{
    delete m_subject;
    m_subject = 0;
}

void Ft_MkFtClassName::initTestCase()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ft_MkFtClassName::cleanupTestCase()
{
}

QTEST_MAIN(Ft_MkFtClassName)
