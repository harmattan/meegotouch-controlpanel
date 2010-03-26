#ifndef FT_PAGEFACTORY_H
#define FT_PAGEFACTORY_H

#include <QtTest/QtTest>
#include <QObject>
// the real unit/PageFactory class declaration
#include <pagefactory.h>
class DuiApplication;
Q_DECLARE_METATYPE(PageFactory*);

class Ft_PageFactory : public QObject
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
    void testAppletWantsToStart();
private:
    DuiApplication *app;
};

#endif
