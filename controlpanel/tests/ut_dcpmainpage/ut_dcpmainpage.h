#ifndef UT_DCPMAINPAGE_H
#define UT_DCPMAINPAGE_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DcpMainPage class declaration
#include <dcpmainpage.h>

Q_DECLARE_METATYPE(DcpMainPage*);

class Ut_DcpMainPage : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testCreation();
    void testCreateContent();
    void testCreateContentLate();
    void testReload();
    void testShown();
    void testBack();
    void testRetranslateUi();
    void testHideEvent();
private:
    DcpMainPage* m_subject;
};

#endif
