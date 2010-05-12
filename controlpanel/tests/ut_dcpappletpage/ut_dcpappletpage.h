#ifndef UT_DCPAPPLETPAGE_H
#define UT_DCPAPPLETPAGE_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DcpAppletPage class declaration
#include <dcpappletpage.h>

Q_DECLARE_METATYPE(DcpAppletPage*);

class Ut_DcpAppletPage : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();

    

private:
    DcpAppletPage* m_subject;
};

#endif
