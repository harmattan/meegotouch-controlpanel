#ifndef UT_DCPPAGE_H
#define UT_DCPPAGE_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DcpPage class declaration
#include <dcppage.h>
Q_DECLARE_METATYPE(DcpPage*);

class Ut_DcpPage : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testCreateContents();
    void testHandle();
    void testReferer();
    void testMainLayout();
    void testAppendWidget();
private:
    DcpPage* m_subject;
};

#endif
