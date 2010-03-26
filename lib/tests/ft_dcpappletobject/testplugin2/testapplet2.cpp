#include <DuiTheme>
#include <QtDebug>
#include <DcpWidget>
#include <DcpBrief>
#include "testapplet2.h"
#include "testappletwidget2.h"

Q_EXPORT_PLUGIN2(testapplet2, TestApplet2)

TestApplet2::~TestApplet2()
{
    qDebug() << "TestApplet2 destructor";
}

void TestApplet2::init()
{
    qDebug() << "TestApplet2 init";
    DuiTheme::loadCSS(DATADIR "/testapplet2.css");
}

DcpWidget *TestApplet2::constructWidget(int widgetId)
{
    return new TestAppletWidget2();
}

QString TestApplet2::title() const
{
    return "Test title 2";
}

QVector<DuiAction*> TestApplet2::viewMenuItems()
{
    return QVector<DuiAction*>();
}

DcpBrief *TestApplet2::constructBrief(int)
{
    return new DcpBrief();
}
