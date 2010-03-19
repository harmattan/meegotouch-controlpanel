#ifndef FT_DCPPAGE_H
#define FT_DCPPAGE_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DcpPage class declaration
#include <dcppage.h>
Q_DECLARE_METATYPE(DcpPage*);

class Ft_DcpPage : public QObject
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
private:
    DcpPage* m_subject;
};

#endif
