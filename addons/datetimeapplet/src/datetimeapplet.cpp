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

void DateTimeApplet::init(QString part)
{
    m_WidgetIndex = DcpDateTime::Main;
    m_Title = DcpDateTime::AppletTitle;
    m_Parts.insert(DcpDateTime::KeyNone, DcpDateTime::None);
    m_Parts.insert(DcpDateTime::KeyMain, DcpDateTime::Main);
    m_Parts.insert(DcpDateTime::KeyDate, DcpDateTime::Date);
    m_Parts.insert(DcpDateTime::KeyTime, DcpDateTime::Time);
    m_Parts.insert(DcpDateTime::KeyTimeZone, DcpDateTime::TimeZone);
    m_PartIndex = m_Parts[part];
};

DcpWidget* DateTimeApplet::constructWidget(int widgetId)
{
    if (m_PartIndex != DcpDateTime::None && !widgetId)
        widgetId = m_PartIndex;
    switch (widgetId) {
        case DcpDateTime::TimeZone:
            m_Title = DcpDateTime::TimeZoneTitle;
            return pageTimeZone();
            break;
        case DcpDateTime::Main:
        default:
            m_Title = DcpDateTime::AppletTitle;
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
        return m_Title;
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

