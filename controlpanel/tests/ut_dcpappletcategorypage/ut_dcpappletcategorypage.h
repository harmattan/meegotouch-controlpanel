#ifndef UT_DCPAPPLETCATEGORYPAGE_H
#define UT_DCPAPPLETCATEGORYPAGE_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DcpAppletCategoryPage class declaration
#include <dcpappletcategorypage.h>

Q_DECLARE_METATYPE(DcpAppletCategoryPage*);

class Ut_DcpAppletCategoryPage : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testCreation();
    void testCreateContent();
    void testAppletCategory();
    void testCategoryInfo();
    void testReload();
    void testCleanup();
    void testSetTitleId();
    void testBack();
    void testRetranslateUi();
    void testAddComponent();
    

private:
    DcpAppletCategoryPage* m_subject;
};

#endif
