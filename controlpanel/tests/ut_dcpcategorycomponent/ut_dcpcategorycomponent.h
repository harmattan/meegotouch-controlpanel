#ifndef UT_DCPCATEGORYCOMPONENT_H
#define UT_DCPCATEGORYCOMPONENT_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DcpCategoryComponent class declaration
#include <dcpcategorycomponent.h>

Q_DECLARE_METATYPE(DcpCategoryComponent*);

class Ut_DcpCategoryComponent : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testCreation();
    void testCreateContents();
    void testRetranslateUi();
    void testTitle();
    void testReload();
    void testGetItemCount();
    

private:
    DcpCategoryComponent* m_subject;
};

#endif
