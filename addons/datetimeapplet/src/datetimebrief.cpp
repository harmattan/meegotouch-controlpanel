#include "datetimebrief.h"
#include "dcpwidgettypes.h"
#include "dcptimezoneconf.h"
#include "dcptimezonedata.h"

#include <duilocale.h>
#include <QDateTime>
#include <QTimer>

DateTimeBrief::DateTimeBrief(int partId)
    : m_PartId(partId)
{
    if (partId == DcpDateTime::Time || partId == DcpDateTime::Main
           || partId == DcpDateTime::None)
    {
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SIGNAL(valuesChanged()));
        int durationMs = 1000;
        if (partId == DcpDateTime::Time) {
            durationMs*=60;
        }
        timer->start(durationMs);
    }
}

QString DateTimeBrief::valueText() const
{
    QString result;
    DuiLocale locale;
    QDateTime now = QDateTime::currentDateTime();
    switch (m_PartId) {
        case DcpDateTime::TimeZone:
            result = DcpTimeZoneConf::instance()->defaultTimeZone().gmt() + " "+
                       DcpTimeZoneConf::instance()->defaultTimeZone().city();
            break;
        case DcpDateTime::Date:
            result = locale.formatDateTime(now, DuiLocale::DateFull,
                                           DuiLocale::TimeNone);
            break;
       case DcpDateTime::Time:
            result = locale.formatDateTime(now, DuiLocale::DateNone,
                                           DuiLocale::TimeShort);
            break;
        default:
            result = locale.formatDateTime(now, DuiLocale::DateShort,
                                           DuiLocale::TimeMedium);
            break;
    }
    return result;
}


