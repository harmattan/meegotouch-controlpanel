#ifndef UT_DCPBRIEF_H
#define UT_DCPBRIEF_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DcpBrief class declaration
#include <dcpbrief.h>

Q_DECLARE_METATYPE(DcpBrief*);

class Ut_DcpBrief : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testCreation();
    void testWidgetTypeID();
    void testValueText();
    void testIcon();
    void testToggleIconId();
    void testAlign();
    void testToggle();
    void testImage();
    void testActivate();
    void testTitleText();
    

private:
    DcpBrief* m_subject;
};

#endif
