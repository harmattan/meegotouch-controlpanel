#ifndef FT_DCPBRIEFCOMPONENT_H
#define FT_DCPBRIEFCOMPONENT_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/DcpBriefComponent class declaration
#include <dcpbriefcomponent.h>

Q_DECLARE_METATYPE(DcpBriefComponent*);
class DcpAppletObject;
class Ft_DcpBriefComponent : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testCreation();
    void testActivate();
    

private:
    DcpAppletObject* m_applet;
    DcpBriefComponent* m_subject;
};

#endif
