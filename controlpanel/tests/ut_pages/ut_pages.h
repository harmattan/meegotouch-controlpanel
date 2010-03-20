#ifndef UT_PAGES_H
#define UT_PAGES_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/PageHandle class declaration
#include <pages.h>

Q_DECLARE_METATYPE(PageHandle*);

class Ut_PageHandle : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testCreation();
    void testGetStringVariant();    

};

#endif
