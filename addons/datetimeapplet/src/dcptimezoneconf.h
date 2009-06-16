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
    QMultiMap<QString, DcpTimeZoneData*> getMap() const;
    DcpTimeZoneData defaultTimeZone() const;

protected:
    DcpTimeZoneConf();
    QStringList supportedTimeZones();
    void initCountry();

private:
    Q_DISABLE_COPY(DcpTimeZoneConf);
    static DcpTimeZoneConf *sm_Instance;
    QMultiMap<QString, QString> m_CountryMap;
    QMultiMap<QString, DcpTimeZoneData*> m_ItemMap;
};
#endif // DCPTIMEZONECONF_H

