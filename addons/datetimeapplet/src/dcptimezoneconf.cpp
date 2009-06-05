#include "dcptimezoneconf.h"
#include "dcptimezonedata.h"

#include <duiicuconversions.h>
#include <QDebug>

DcpTimeZoneConf *DcpTimeZoneConf::sm_Instance = 0;

DcpTimeZoneConf* DcpTimeZoneConf::instance()
{
    if (!sm_Instance) {
        sm_Instance = new DcpTimeZoneConf();
    }

    return sm_Instance;
}

DcpTimeZoneConf::~DcpTimeZoneConf()
{
    if (sm_Instance) {
        delete sm_Instance;
    }

    m_ItemMap.clear();
}

QMap<int, DcpTimeZoneData*> DcpTimeZoneConf::getMap() const
{
    return m_ItemMap;
}

DcpTimeZoneData DcpTimeZoneConf::defaultTimeZone() const
{
    UnicodeString defaultZone;
    icu::TimeZone::createDefault()->getDisplayName(defaultZone);
    QString zoneId = DuiIcuConversions::unicodeStringToQString(defaultZone);
    qDebug() << "DEFAULT TIME ZONE : " << zoneId;
    DcpTimeZoneData timeZone(zoneId);
    return timeZone;
}

//! protected constructor
DcpTimeZoneConf::DcpTimeZoneConf()
                :QObject()
{
    // fill up m_ItemMap
    QStringList list = this->supportedTimeZones();
    QStringListIterator iter(list);
    int count = 1;
    while (iter.hasNext()) {
        QString item = iter.next();
        if (item.contains("Europe") || item.contains("America") || 
            item.contains("Asia") || item.contains("Australia") ||
            item.contains("Indian") || item.contains("Africa") ||
            item.contains("Pacific") || item.contains("Mideast") ||
            item.contains("Brazil") || item.contains("Atlantic") ||
            item.contains("Arctic") || item.contains("Antarctica"))
            m_ItemMap[count++] = new DcpTimeZoneData(iter.next());
    }
}

QStringList DcpTimeZoneConf::supportedTimeZones()
{
    icu::StringEnumeration *stringEnum = icu::TimeZone::createEnumeration();
    QStringList result;
    UErrorCode status = U_ZERO_ERROR;
    const UnicodeString *next = stringEnum->snext(status);
    while (next != 0) {
        result << DuiIcuConversions::unicodeStringToQString(*next);
        next = stringEnum->snext(status);
    }

    delete stringEnum;
    return result;
}

