#ifndef DCPTIMEZONEDATA_H
#define DCPTIMEZONEDATA_H

#include <QString>

class DcpTimeZoneData 
{   
public: 
    DcpTimeZoneData(QString timezone);
    virtual ~DcpTimeZoneData();
    QString timeZone() const;
    QString country() const;
    QString city() const;
    QString gmt() const;

protected:
   void init(); 
    
private:
    QString m_TimeZone;
    QString m_Country;
    QString m_City;
    QString m_Gmt;
};
#endif // DCPTIMEZONEDATA_H

