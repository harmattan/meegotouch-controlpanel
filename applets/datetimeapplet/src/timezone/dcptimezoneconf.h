#ifndef DCPTIMEZONECONF_H
#define DCPTIMEZONECONF_H

#include <QObject>
#include <QStringList>
#include <QMap>
#include <QSettings>

// class DuiConf;
class DcpTimeZoneData;

class DcpTimeZoneConf : public QObject
{
    Q_OBJECT

public:
    static DcpTimeZoneConf* instance();
    virtual ~DcpTimeZoneConf();
    QMultiMap<QString, DcpTimeZoneData*> getMap() const;
    DcpTimeZoneData defaultTimeZone() const;
    void setDefaultTimeZone(const QString& zoneId);
    QString approxZoneId(int timezone, const QString& countryCode);

protected:
    DcpTimeZoneConf();
    QStringList supportedTimeZones();
    void initCountry();

private:
    Q_DISABLE_COPY(DcpTimeZoneConf);
    static DcpTimeZoneConf *sm_Instance;
    QMultiMap<QString, QString> m_ZoneMap;      // US -> America/Denver, America/Indiana/Vevay etc.
    QMultiMap<QString, QString> m_CountryMap;   // Europe/Berlin -> Germany etc.
    QMultiMap<QString, DcpTimeZoneData*> m_ItemMap; // Germany -> data etc.
    QSettings m_Settings;
    // DuiConf *m_Conf;
};
#endif // DCPTIMEZONECONF_H

