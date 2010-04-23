#ifndef UT_DCPCATEGORYPAGE_H
#define UT_DCPCATEGORYPAGE_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DcpCategoryPage class declaration
#include <dcpcategorypage.h>

Q_DECLARE_METATYPE(DcpCategoryPage*);

class Ut_DcpCategoryPage : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testCreateContents();
    

private:
    DcpCategoryPage* m_subject;
};

#endif
