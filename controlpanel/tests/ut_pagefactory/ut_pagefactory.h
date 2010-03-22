#ifndef UT_PAGEFACTORY_H
#define UT_PAGEFACTORY_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/PageFactory class declaration
#include <pagefactory.h>

Q_DECLARE_METATYPE(PageFactory*);

class Ut_PageFactory : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testInstance();
    void testCreatePage();
    void testCurrentPage();
    void testChangePage();
    void testCreateAppletPage();
    void testCreateAppletCategoryPage();
    void testAppletWantsToStart();
    void testMainPageFirstShown();
    void testRegisterPage(); 
};

#endif
