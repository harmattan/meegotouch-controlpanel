#include "dcptimezoneconf.h"
#include "dcptimezonedata.h"

#include <QFile>
#include <unicode/timezone.h>
#include <unicode/strenum.h>
#include <qmtime.h>
#include "dcpicuconversions.h"
// #include <duiconf.h>
#include <QDebug>

DcpTimeZoneConf *DcpTimeZoneConf::sm_Instance = 0;
static const QString zonePath = "/usr/share/zoneinfo/";
static const QString defaultZoneKey = "system/timezone";

DcpTimeZoneConf* DcpTimeZoneConf::instance()
{
    if (!sm_Instance) {
        sm_Instance = new DcpTimeZoneConf();
    }

    return sm_Instance;
}

DcpTimeZoneConf::~DcpTimeZoneConf()
{
    m_ItemMap.clear();
    sm_Instance = 0;
}

QMultiMap<QString, DcpTimeZoneData*> DcpTimeZoneConf::getMap() const
{
    return m_ItemMap;
}


DcpTimeZoneData DcpTimeZoneConf::defaultTimeZone() const
{
    /* QVariant zoneId;
    QString zone;
    m_Conf->getValue("/system/timezone", zoneId);
    if (zoneId.toString().isEmpty()) {
        zone = "Europe/London";
    } else {
        zone = zoneId.toString();
    }*/
    Maemo::QmTime time;
    QString z;
    bool st = time.getTimezone(z);
    qDebug() << "getTimezone status:" << st << "value:" << z;
    if (z.startsWith(':')) {
        z.remove(0, 1);
    }
//    QString zone = m_Settings.value(defaultZoneKey, "Europe/London").toString();

    DcpTimeZoneData timeZone(z);
    return timeZone;
}

void DcpTimeZoneConf::setDefaultTimeZone(QString zoneId)
{
    // m_Conf->set("/system/timezone", zoneId);
    m_Settings.setValue(defaultZoneKey, zoneId);

    Maemo::QmTime time;
    bool st = time.setTimezone(":" + zoneId);
    if (!st) {
        qCritical() << "Could not save timezone:" << zoneId;
    }
}

void DcpTimeZoneConf::initCountry()
{
    // collect informations from zone.tab
    QFile *file = new QFile(zonePath + "zone.tab");
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QMultiMap<QString, QString> zoneMap;
    while (!file->atEnd()) {
        QString line = file->readLine();
        if (!line.startsWith("#")) {
            QStringList item = line.split(QRegExp("\\s"), QString::SkipEmptyParts);
            zoneMap.insert(item.at(0), item.at(2));
        }
    }
    file->close();
    delete file;

    // collect informations from iso3166.tab
    file = new QFile(zonePath + "iso3166.tab");
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!file->atEnd()) {
        QString line = file->readLine();
        if (!line.startsWith("#")) {
            QStringList item = line.split(QRegExp("\\s"), QString::SkipEmptyParts);
            QMultiMap<QString, QString>::const_iterator iter = zoneMap.find(item.at(0));
            while (iter != zoneMap.end() && iter.key() == item.at(0)) {
                QString country;
                for (int i = 1; i < item.size(); i++) {
                    if (i != item.size() - 1) {
                        country += item.at(i) + " ";
                    } else {
                        country += item.at(i);
                    }
                }

		/* TODO find better slution for long names or file a bug to the
		 * proper component */
                if (country == "South Georgia & the South Sandwich Islands")
                    country = "South Georgia & the South Sandw...";

                m_CountryMap.insert(iter.value(), country);
                ++iter;
            }
        }
    }
    file->close();
    delete file;
}

//! protected constructor
DcpTimeZoneConf::DcpTimeZoneConf()
                :QObject(), m_Settings("Nokia","DuiControlPanel")
{
    // create m_Conf and cache keys under /system
    // m_Conf = new DuiConf();
    // m_Conf->addDir("/system", true);

    // fill up m_CountryMap
    this->initCountry();

    // fill up itemMap
    QMap<int, DcpTimeZoneData*> itemMap;
    QStringList list = this->supportedTimeZones();
    QStringListIterator iter(list);
    int count = 1;
    while (iter.hasNext()) {
        QString item = iter.next();
        if (item.startsWith("Europe") || item.startsWith("America") || 
            item.startsWith("Asia")   || item.startsWith("Australia") ||
            item.startsWith("Indian") || item.startsWith("Africa") ||
            item.startsWith("Pacific") || item.startsWith("Mideast") ||
            item.startsWith("Brazil") || item.startsWith("Atlantic") ||
            item.startsWith("Arctic") || item.startsWith("Antarctica"))
            itemMap[count++] = new DcpTimeZoneData(item);
    }

    // check countries in itemMap and fill up m_ItemMap
    QMapIterator<int, DcpTimeZoneData*> itera(itemMap);
    while (itera.hasNext()) {
        itera.next();
        QMultiMap<QString, QString>::const_iterator it = m_CountryMap.find(itera.value()->timeZone());
        while (it != m_CountryMap.end() && it.key() == itera.value()->timeZone()) {
            itera.value()->setCountry(it.value());
            m_ItemMap.insert(itera.value()->country(), itera.value());
            ++it;
        }
    }
}

QStringList DcpTimeZoneConf::supportedTimeZones()
{
    icu::StringEnumeration *stringEnum = icu::TimeZone::createEnumeration();
    QStringList result;
    UErrorCode status = U_ZERO_ERROR;
    const UnicodeString *next = stringEnum->snext(status);
    while (next != 0) {
        result << unicodeStringToQString(*next);
        next = stringEnum->snext(status);
    }
    delete stringEnum;
    return result;
}

