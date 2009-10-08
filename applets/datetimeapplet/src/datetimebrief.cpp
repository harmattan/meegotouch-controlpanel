#include "datetimebrief.h"
#include <DcpWidgetTypes>
#include "dcptimezoneconf.h"
#include "dcptimezonedata.h"
#include "datehint.h"
#include "dcptime.h"

#include <DuiLocale>
#include <QDateTime>
#include <QTimer>
#include <QtDebug>


DateTimeBrief::DateTimeBrief(int partId)
    : m_PartId(partId), m_Locale(new DuiLocale()), m_Time(new DcpTime(this))
{
    if (partId == DcpDateTime::Time || partId == DcpDateTime::Main
           || partId == DcpDateTime::None)
    {
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SIGNAL(valuesChanged()));
        int durationMs = 1000;
//        if (partId == DcpDateTime::Time) {
            durationMs*=60;
//        }
        timer->start(durationMs);
    }
    DateHint::startHintIfNeeded();
    connect (m_Time, SIGNAL(timeOrDateChanged()),
             this, SIGNAL(valuesChanged()));
}

DateTimeBrief::~DateTimeBrief()
{
    delete m_Locale;
}

QString DateTimeBrief::valueText() const
{
    QString result;
    QDateTime now = QDateTime::currentDateTime();

    switch (m_PartId) {
        case DcpDateTime::TimeZone:
            result = DcpTimeZoneConf::instance()->defaultTimeZone().gmt() + " "+
                       DcpTimeZoneConf::instance()->defaultTimeZone().city(); 
            break;
        case DcpDateTime::Date:
            result = m_Locale->formatDateTime(now, DuiLocale::DateFull,
                                           DuiLocale::TimeNone);
            break;
       case DcpDateTime::Time:
            result = m_Locale->formatDateTime(now, DuiLocale::DateNone,
                                           DuiLocale::TimeShort);
            break;
        default:
            result = m_Locale->formatDateTime(now, DuiLocale::DateShort,
//                                           DuiLocale::TimeMedium); 
                                           DuiLocale::TimeShort); 
            break;
    }

    return result;
}


