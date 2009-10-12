#include "datehint.h"
#include "mcc_country.h"
#include "dcptimezoneconf.h"

#include <qmtime.h>
#include <QDateTime>
#include <networktime.h>
#include <networkoperator.h>
#include <QtDebug>
#include <QTimer>

static const int TIMEOUT_MS = 30000; // timeout until class waits for time change signal
static const QDateTime minimalDateTime = QDateTime(QDate(2005,1,1));
DateHint* DateHint::sm_Instance = 0;


DateHint::DateHint(QObject* parent):
    QObject(parent),
    m_NetworkTime(new Cellular::NetworkTime(this))
{
    connect (m_NetworkTime, SIGNAL(dateTimeChanged (QDateTime, int, int)),
             this, SLOT(check()));
}

void
DateHint::startHintIfNeeded()
{
    if (!isDateValid() && !sm_Instance)
    {
        sm_Instance = new DateHint();
        if (!sm_Instance->check()) {
            qDebug() << "XXX waiting for a correct date hint to arrive";
            QTimer::singleShot(TIMEOUT_MS, sm_Instance, SLOT(suicide()));
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

QString mccCountryCode()
{
    // get mcc code
    QString mcc = Cellular::NetworkOperator().mcc();
//    QString mcc = "316"; // for testing without cellular network, US
//    QString mcc = "216"; // for testing without cellular network, HU
    qDebug() << "XXX reported mcc code is:" << mcc;
    if (mcc.isEmpty()) return QString();

    // translate to country code
    QString country;
    for (const char** st = mcc_country; *st != 0; st+=2) {
        if (mcc == *st) {
            country = *(st+1);
            break;
        }
    }
    qDebug() << "XXX country code for the mcc is:" << country;
    return country;
}

bool
DateHint::check ()
{
/* for debugging only
    DcpTimeZoneConf* conf = DcpTimeZoneConf::instance();
    QString tzId = conf->approxZoneId(1, mccCountryCode());
    qDebug() << "XXX approximated zone hint:" << tzId;
    if (!tzId.isEmpty()) {
        conf->setDefaultTimeZone(tzId);
        qDebug() << "XXX timezone hint was applied";
    }
*/

    QDateTime dateTime = m_NetworkTime->dateTime();

    qDebug() << "XXX Proposed date hint:" << dateTime;
    if (!isDateValid() && isDateValid(dateTime)){
        Maemo::QmTime::QmTime().setTime(dateTime);
        qDebug() << "XXX date hint was applied";

        // set timezone: TODO XXX: do not depend on time is valid or not
        DcpTimeZoneConf* conf = DcpTimeZoneConf::instance();
        QString tzId = conf->approxZoneId(timezone,
                                          mccCountryCode());
        qDebug() << "XXX approximated zone hint:" << tzId;
        if (!tzId.isEmpty()) {
            conf->setDefaultTimeZone(tzId);
            qDebug() << "XXX timezone hint was applied";
        }
    } else {
        qDebug() << "XXX date hint was dropped";
    }

    if (isDateValid()) {
        suicide();
        return true;
    }
    return false;
}

void
DateHint::suicide()
{
    qDebug() << "XXX datehint, timeout";
    sm_Instance->deleteLater();
    sm_Instance = 0;
}

