#include "ut_backgroundcomponent.h"

#include <DuiApplication>

DuiApplication* app;

void Ut_BackgroundComponent::titleTest() {
    QString title = "test title";
    bgCompo->setTitle(title);
    QCOMPARE(bgCompo->title(), title);
}

void Ut_BackgroundComponent::initTestCase()
{
    int argc = 1;
    char* argv = (char*) "./ut_backgroundcomponent";
    qDebug() << "XXX";
    app = new DuiApplication(argc, &argv);
}

void Ut_BackgroundComponent::cleanupTestCase(){
    delete app;
}

void Ut_BackgroundComponent::init(){
    bgCompo = new DcpBackgroundComponent(0, QString());
    bgCompo->createContents();
}

void Ut_BackgroundComponent::cleanup() {
    delete bgCompo;
}

QTEST_APPLESS_MAIN(Ut_BackgroundComponent)

