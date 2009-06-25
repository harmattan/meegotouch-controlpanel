#include <QtGui>
#include <QDebug>
#include "displayapplet.h"
#include "displaywidget.h"
#include "displaytranslation.h"
#include "dummywidget.h"
#include "dcpwidget.h"
#include "dcpdisplay.h"
#include <DuiAction>
#include "displaybrief.h"

Q_EXPORT_PLUGIN2(displayapplet, DisplayApplet)

void DisplayApplet::init(QString part)
{
    m_WidgetIndex = DcpDisplay::Main;
};

DcpWidget* DisplayApplet::constructWidget(int widgetId)
{
	switch (widgetId)
    {
        case DcpDisplay::Main:
                    return pageMain();
                    break;
        case DcpDisplay::Page1:
                    return page1();
                    break;
        case DcpDisplay::Page2:
                    return page2();
                    break;

        default:
                    qDebug() << "Page Unknown";
                    return 0;
                    break;
    };
}

DcpWidget* DisplayApplet::pageMain()
{
	return new DisplayWidget();
}


DcpWidget* DisplayApplet::page1()
{
	return new DummyWidget("Page 1");
}

DcpWidget* DisplayApplet::page2()
{
	return new DummyWidget("Page 2");
}

QString DisplayApplet::title() const
{
        return DcpDisplay::AppletTitle;
}

QVector<DuiAction*> DisplayApplet::viewMenuItems()
{
    QVector<DuiAction*> vector;
    return vector;
}

DcpBrief* DisplayApplet::constructBrief()
{
    return new DisplayBrief();
}

