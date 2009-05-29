#include "dcptimezoneconf.h"

#include <duiicuconversions.h>

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
}

//! protected constructor
DcpTimeZoneConf::DcpTimeZoneConf()
                :QObject()
{
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

