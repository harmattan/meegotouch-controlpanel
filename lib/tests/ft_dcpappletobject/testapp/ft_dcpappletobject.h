#ifndef FT_DCPAPPLETOBJECT_H
#define FT_DCPAPPLETOBJECT_H

#include <QtTest/QtTest>
#include <QObject>
#include <MApplication>

// the real unit/DcpAppletObject class declaration
#include "dcpappletobject.h"

Q_DECLARE_METATYPE(DcpAppletObject*);

class Ft_DcpAppletObject : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testLoad();
    void testLoadManyTimes();
    void testGetters();
    

private:
    void testApplet(const char *desktopfile);
    void doAppletTest (const char *desktopfile);

    MApplication*  m_app;
};

#endif
