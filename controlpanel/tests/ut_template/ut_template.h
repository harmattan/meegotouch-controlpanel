#ifndef UT_MKUTCLASSNAME_H
#define UT_MKUTCLASSNAME_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/MkUtClassName class declaration
#include <mkutclassname.h>

Q_DECLARE_METATYPE(MkUtClassName*);

class Ut_MkUtClassName : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();

    MKUTCLASSMEMBERS

private:
    MkUtClassName* m_subject;
};

#endif
