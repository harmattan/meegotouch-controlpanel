#ifndef UT_MAINTRANSLATIONS_H
#define UT_MAINTRANSLATIONS_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/maintranslations class declaration
#include <maintranslations.h>


class Ut_maintranslations : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testFindCategoyInfo();
    void testIsCategoryNameEnlisted();
};

#endif
