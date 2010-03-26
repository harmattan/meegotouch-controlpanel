#ifndef UT_DCPAPPLETBUTTONS_H
#define UT_DCPAPPLETBUTTONS_H

#include <QtTest/QtTest>
#include <QObject>
class DuiApplication;
// the real unit/DcpAppletButtons class declaration
#include <dcpappletbuttons.h>

Q_DECLARE_METATYPE(DcpAppletButtons*);

class Ut_DcpAppletButtons : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testCreation();
    void testAddComponent();
    void testReload();
    void testCreateContents();
    

private:
    DcpAppletButtons* m_subject;
    DuiApplication *app;
};

#endif
