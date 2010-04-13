#ifndef FT_DCPSINGLECOMPONENT_H
#define FT_DCPSINGLECOMPONENT_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DcpSingleComponent class declaration
#include <dcpsinglecomponent.h>

Q_DECLARE_METATYPE(DcpSingleComponent*);

class Ft_DcpSingleComponent : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testCreation();
    void testTitle();
    void testSubtitle();
    void testActivate();
    

private:
    DcpSingleComponent* m_subject;
};

#endif
