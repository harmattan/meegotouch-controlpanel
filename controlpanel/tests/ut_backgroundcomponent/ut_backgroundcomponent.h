#ifndef UT_BACKGROUNDCOMPONENT_H
#define UT_BACKGROUNDCOMPONENT_H

#include <QtTest/QtTest>
#include "dcpbackgroundcomponent.h"

class Ut_BackgroundComponent: public QObject{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    // tests:
	void titleTest();

private:
    DcpBackgroundComponent* bgCompo;
};


#endif // UT_BACKGROUNDCOMPONENT_H
