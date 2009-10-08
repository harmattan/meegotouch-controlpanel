#include "datehint.h"
#include "dcptime.h"

#include <QDateTime>
#include <networktime.h>
#include <QtDebug>

static const QDateTime minimalDateTime = QDateTime(QDate(2005,1,1));
DateHint* DateHint::sm_Instance = 0;


DateHint::DateHint(QObject* parent):
    QObject(parent),
    m_NetworkTime(new Cellular::NetworkTime(this))
{
    connect (m_NetworkTime, SIGNAL(dateTimeChanged (QDateTime, int, int)),
             this, SLOT(onDateTimeChanged(QDateTime, int, int)));
}

void
DateHint::startHintIfNeeded()
{
    if (!isDateValid() && !sm_Instance)
    {
        QDateTime proposal = Cellular::NetworkTime().dateTime();
        qDebug() << "XXX date proposal:" << proposal;
        if (isDateValid(proposal)) {
            DcpTime time;
            time.setDateTime(proposal);
            qDebug() << "XXX immediate date hint was applied";
        } else {
            sm_Instance = new DateHint();
            qDebug() << "XXX waiting for a correct date hint to arrive";
        }
    }
}

bool
DateHint::isDateValid()
{
    return isDateValid(QDateTime::currentDateTime());
}

bool
DateHint::isDateValid(const QDateTime& dt)
{
    return dt >= minimalDateTime;
}

void
DateHint::onDateTimeChanged (QDateTime dateTime, int timezone, int dst)
{
    Q_UNUSED(timezone);
    Q_UNUSED(dst);

    qDebug() << "XXX Proposed date hint:" << dateTime;
    if (!isDateValid() && isDateValid(dateTime)){
        DcpTime time;
        time.setDateTime(dateTime);
        qDebug() << "XXX date hint was applied";
    } else {
        qDebug() << "XXX date hint was dropped";
    }

    if (isDateValid()) {
        sm_Instance->deleteLater(); // suicide, if not needed anymore
        sm_Instance = 0;
    }
}


