#ifndef DCPTIMEZONECONF_H
#define DCPTIMEZONECONF_H

#include <QObject>
#include <QStringList>
#include <QMap>

class DcpTimeZoneData;

class DcpTimeZoneConf : public QObject
{
    Q_OBJECT

public:
    static DcpTimeZoneConf* instance();
    virtual ~DcpTimeZoneConf();
    QMap<int, DcpTimeZoneData*> getMap() const;
    DcpTimeZoneData defaultTimeZone() const;

protected:
    DcpTimeZoneConf();
    QStringList supportedTimeZones();

private:
    Q_DISABLE_COPY(DcpTimeZoneConf);
    static DcpTimeZoneConf *sm_Instance;
    QMap<int, DcpTimeZoneData*> m_ItemMap;
};
#endif // DCPTIMEZONECONF_H

