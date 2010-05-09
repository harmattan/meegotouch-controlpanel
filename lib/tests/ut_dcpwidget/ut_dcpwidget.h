#ifndef UT_DCPWIDGET_H
#define UT_DCPWIDGET_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DcpWidget class declaration
#include <dcpwidget.h>

Q_DECLARE_METATYPE(DcpWidget*);

class Ut_DcpWidget : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testCreation();
    void testWidgetId();
    void testBack();
    void testPagePans();
private:
    DcpWidget* m_subject;
};

#endif
