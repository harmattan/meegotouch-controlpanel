#ifndef DCPTIMEZONECONF_H
#define DCPTIMEZONECONF_H

#include <QObject>
#include <QStringList>

class DcpTimeZoneConf : public QObject
{
    Q_OBJECT

public:
    static DcpTimeZoneConf* instance();
    virtual ~DcpTimeZoneConf();
    QStringList supportedTimeZones();

protected:
    DcpTimeZoneConf();

private:
    Q_DISABLE_COPY(DcpTimeZoneConf);
    static DcpTimeZoneConf *sm_Instance;
};
#endif // DCPTIMEZONECONF_H

