#ifndef MOSTUSEDCOUNTERPRIVATE_H
#define MOSTUSEDCOUNTERPRIVATE_H

#include <DuiGConfItem>
#include <QString>
#include <QMap>

class MostUsedCounter;
class MostUsedCounterPrivate
{
public:
    static MostUsedCounter *sm_Instance;
    QMap<QString, DuiGConfItem*> data;
};

#endif // MOSTUSEDCOUNTERPRIVATE_H
