#ifndef UT_DCPMAINCATEGORY_H
#define UT_DCPMAINCATEGORY_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DcpMainCategory class declaration
#include <dcpmaincategory.h>

Q_DECLARE_METATYPE(DcpMainCategory*);

class Ut_DcpMainCategory : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testCreation();
    void testAppendWidget(); 
    void testMaxColums(); 
    void testGetItemCount(); 
    void testMLayout(); 
    void testHorizontalSpacing(); 
    void testVerticalSpacing(); 
    void testCreateSeparators(); 
    void testDeleteItems(); 
    void testCreateContents(); 
    void testAppendSeparatorsIfNeeded(); 
    void testIncrementRowAndCol(); 

private:
    DcpMainCategory* m_subject;
};

#endif
