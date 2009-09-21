#include <QtGui>
#include <QDebug>
#include <duitheme.h>
#include "datetimeapplet.h"
#include "dcpdatetime.h"
#include "datetimewidget.h"
#include "timezoneview.h"

#include "date/dateview.h"
#include "time/timeview.h"

#include <DcpWidget>
#include "duilocale.h"
#include <DuiAction>
#include "datetimebrief.h"
#include "datetimetranslation.h"


Q_EXPORT_PLUGIN2(displayapplet, DateTimeApplet)

void DateTimeApplet::init()
{
    DuiTheme::loadCSS(QString(CSSDIR) + "datetimeapplet.css");
    m_Title = DcpDateTime::AppletTitle;
};

DcpWidget* DateTimeApplet::constructWidget(int widgetId)
{
    switch (widgetId) {
        case DcpDateTime::TimeZone:
            m_Title = DcpDateTime::TimeZoneTitle;
            return pageTimeZone();
            break;
        case DcpDateTime::Date:
            m_Title = DcpDateTime::DateDialogTitle;
            return pageDate();
            break;
        case DcpDateTime::Time:
            m_Title = DcpDateTime::TimeDialogTitle;
            return pageTime();
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

DcpWidget* DateTimeApplet::pageDate()
{
    return new DateView();
}

DcpWidget* DateTimeApplet::pageTime()
{
    return new TimeView();
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

DcpBrief* DateTimeApplet::constructBrief(int partId)
{
    return new DateTimeBrief(partId);
}

int DateTimeApplet::partID(const QString& part)
{
    if (m_Parts.isEmpty()){
        m_Parts.insert(DcpDateTime::KeyNone, DcpDateTime::None);
        m_Parts.insert(DcpDateTime::KeyMain, DcpDateTime::Main);
        m_Parts.insert(DcpDateTime::KeyDate, DcpDateTime::Date);
        m_Parts.insert(DcpDateTime::KeyTime, DcpDateTime::Time);
        m_Parts.insert(DcpDateTime::KeyTimeZone, DcpDateTime::TimeZone);
    }
    return m_Parts[part];
}

