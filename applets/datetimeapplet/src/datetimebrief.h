#ifndef DATETIMEBRIEF_H
#define DATETIMEBRIEF_H

#include <DcpBrief>
#include "dcpdatetime.h"

class DateTimeBrief: public DcpBrief{
    Q_OBJECT
public:
    explicit DateTimeBrief(int partId = DcpDateTime::Main);
    virtual QString valueText() const;
private:
    int m_PartId;
};


#endif // DATETIMEBRIEF_H
