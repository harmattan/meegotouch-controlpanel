#ifndef DATETIMEBRIEF_H
#define DATETIMEBRIEF_H

#include <DcpBrief>
#include "dcpdatetime.h"
class DuiLocale;
class DcpTime;

class DateTimeBrief: public DcpBrief{
    Q_OBJECT
public:
    explicit DateTimeBrief(int partId = DcpDateTime::Main);
    virtual ~DateTimeBrief();
    virtual QString valueText() const;

private:
    int m_PartId;
    DuiLocale* m_Locale;
    DcpTime* m_Time;
};


#endif // DATETIMEBRIEF_H
