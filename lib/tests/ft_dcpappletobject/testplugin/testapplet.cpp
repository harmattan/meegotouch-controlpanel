#include <MTheme>
#include <QtDebug>
#include <DcpWidget>
#include <DcpBrief>
#include "testapplet.h"
#include "testappletwidget.h"

Q_EXPORT_PLUGIN2(testapplet, TestApplet)

TestApplet::~TestApplet()
{
    qDebug() << "TestApplet destructor";
}

void TestApplet::init()
{
    qDebug() << "TestApplet init";
    MTheme::loadCSS(DATADIR "/testapplet.css");
}

DcpWidget *TestApplet::constructWidget(int widgetId)
{
    return new TestAppletWidget();
}

QString TestApplet::title() const
{
    return "Test title 1";
}

QVector<MAction*> TestApplet::viewMenuItems()
{
    return QVector<MAction*>();
}

DcpBrief *TestApplet::constructBrief(int)
{
    return new DcpBrief();
}
