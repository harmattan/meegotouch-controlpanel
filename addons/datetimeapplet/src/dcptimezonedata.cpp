#include "dcptimezonedata.h"

#include <duiicuconversions.h>
#include <QStringList>

DcpTimeZoneData::DcpTimeZoneData(QString timezone)
                :m_TimeZone(timezone),
                 m_Country(""),
                 m_City(""),
                 m_Gmt("")
{
    init();
}

DcpTimeZoneData::~DcpTimeZoneData()
{
}

QString DcpTimeZoneData::timeZone() const
{
    return m_TimeZone;
}

QString DcpTimeZoneData::country() const
{
    return m_Country;
}

void DcpTimeZoneData::setCountry(QString country) 
{
    m_Country = country;
}

QString DcpTimeZoneData::city() const
{
    return m_City;
}

QString DcpTimeZoneData::gmt() const
{
    return m_Gmt;
}

void DcpTimeZoneData::init()
{
    // set GMT offset
    icu::UnicodeString uZone = DuiIcuConversions::qStringToUnicodeString(m_TimeZone);
    int32_t offset = icu::TimeZone::createTimeZone(uZone)->getRawOffset();
    double value = offset / 3600000;
    if (value != 0) {
        if (value > 0) {
            m_Gmt = QString("GMT+%1").arg(value);
        } else {
            m_Gmt = QString("GMT%1").arg(value);
        }
    } else {
        m_Gmt = "GMT+0";
    }

    // set Country/City
    QStringList item = m_TimeZone.split("/");
    switch (item.size()) {
        case 1:
            m_Country = item.at(0);
            break;
        case 2:
            m_Country = item.at(0);
            m_City = item.at(1);
            break;
        case 3:
            m_Country = item.at(0) + "/" + item.at(1);
            m_City = item.at(2);
            break;
        default:
            break;
    }
}
