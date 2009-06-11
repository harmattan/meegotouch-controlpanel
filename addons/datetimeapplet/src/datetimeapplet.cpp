#include <QtGui>
#include <QDebug>
#include "datetimeapplet.h"
#include "dcpdatetime.h"
#include "datetimewidget.h"
#include "timezoneview.h"
#include "dcpwidget.h"
#include "duilocale.h"
#include <DuiAction>
#include "datetimebrief.h"
#include "datetimetranslation.h"

Q_EXPORT_PLUGIN2(displayapplet, DateTimeApplet)

void DateTimeApplet::init()
{
    m_WidgetIndex = DcpDateTime::Main;
};

DcpWidget* DateTimeApplet::constructWidget(int widgetId)
{
    switch (widgetId) {
        case DcpDateTime::TimeZone:
            return pageTimeZone();
            break;
        case DcpDateTime::Main:
        default:
            return pageMain();
            break;
    }
}

DcpWidget* DateTimeApplet::pageMain()
{
    return new DateTimeWidget();
}

DcpWidget* DateTimeApplet::pageTimeZone()
{
    return new TimeZoneView();
}

QString DateTimeApplet::title() const
{
        return DcpDateTime::AppletTitle;
}

QVector<DuiAction*> DateTimeApplet::viewMenuItems()
{
    QVector<DuiAction*> vector;
    return vector;
}

DcpBrief* DateTimeApplet::constructBrief()
{
    return new DateTimeBrief();
}

