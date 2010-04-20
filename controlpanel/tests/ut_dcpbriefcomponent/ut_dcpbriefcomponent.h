#ifndef UT_DCPBRIEFCOMPONENT_H
#define UT_DCPBRIEFCOMPONENT_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DcpBriefComponent class declaration
#include <dcpbriefcomponent.h>

Q_DECLARE_METATYPE(DcpBriefComponent*);
class DcpAppletObject;
class Ut_DcpBriefComponent : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testCreation();
    void testApplet();
    void testActivate();
    

private:
    DcpBriefComponent* m_subject;
    DcpAppletObject* m_applet;
};

#endif
