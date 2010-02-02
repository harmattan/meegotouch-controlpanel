#ifndef UT_DCPCATEGORY_H
#define UT_DCPCATEGORY_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DcpCategory class declaration
#include <dcpcategory.h>

Q_DECLARE_METATYPE(DcpCategory*);

class Ut_DcpCategory : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testCreateAndDestroy();
    void testAdd();
    void testRemove();
    void testChildCount();  
    void testChild();  
    void testCategory();  

    

private:
    DcpCategory* m_subject;
};

#endif
