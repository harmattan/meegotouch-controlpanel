#ifndef FT_MKFTCLASSNAME_H
#define FT_MKFTCLASSNAME_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/MkFtClassName class declaration
#include "mkftclassname.h"

Q_DECLARE_METATYPE(MkFtClassName*);

class Ft_MkFtClassName : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();

    MKFTCLASSMEMBERS

private:
    MkFtClassName* m_subject;
};

#endif
