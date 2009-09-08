#ifndef DCPDATETIME_H
#define DCPDATETIME_H

namespace DcpDateTime
{
    enum {
        None = -1,
        Main = 1,
        Date,
        Time,
        TimeZone
    };
    const QString KeyNone = "";
    const QString KeyMain = "Main";
    const QString KeyDate = "Date";
    const QString KeyTime = "Time";
    const QString KeyTimeZone = "TimeZone";
    const int NoReferer = -1;
};
#endif // DCPDATETIME_H

