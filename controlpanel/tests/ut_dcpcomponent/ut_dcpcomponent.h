#ifndef UT_DCPCOMPONENT_H
#define UT_DCPCOMPONENT_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DcpComponent class declaration
#include <dcpcomponent.h>

Q_DECLARE_METATYPE(DcpComponent*);

class Ut_DcpComponent : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testSubPage();
    void testTitle();
    void testCategory();
    void testLogicalId();    
    void testMattiID();    
    DcpComponent *m_subject;    
};

#endif
