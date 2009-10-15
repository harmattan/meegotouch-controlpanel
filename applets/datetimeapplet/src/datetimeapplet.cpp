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
    m_LastWidgetId = -1;
    DuiTheme::loadCSS(QString(CSSDIR) + "datetimeapplet.css");
};

DcpWidget* DateTimeApplet::constructWidget(int widgetId)
{
    m_LastWidgetId = widgetId;
    switch (widgetId) {
        case DcpDateTime::TimeZone:
            return pageTimeZone();
            break;
        case DcpDateTime::Date:
            return pageDate();
            break;
        case DcpDateTime::Time:
            return pageTime();
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
    const char* msgid;
    const char* msgdefault;
    switch (m_LastWidgetId) {
        case DcpDateTime::TimeZone:
            msgid = DcpDateTime::timeZoneTitleId;
            msgdefault = DcpDateTime::timeZoneTitleDefault;
            break;
        case DcpDateTime::Date:
            msgid = DcpDateTime::dateDialogTitleId;
            msgdefault = DcpDateTime::dateDialogTitleDefault;
            break;
        case DcpDateTime::Time:
            msgid = DcpDateTime::timeDialogTitleId;
            msgdefault = DcpDateTime::timeDialogTitleDefault;
            break;
        case DcpDateTime::Main:
        default:
            msgid = DcpDateTime::appletTitleId;
            msgdefault = DcpDateTime::appletTitleDefault;
            break;
    }
    return trid(msgid, msgdefault);
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

