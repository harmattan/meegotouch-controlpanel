#ifndef MOSTUSEDCOUNTERPRIVATE_H
#define MOSTUSEDCOUNTERPRIVATE_H

#include <QString>
#include <DuiGConfDataStore>

class MostUsedCounter;

class MostUsedCounterPrivate
{
public:
    static MostUsedCounter *sm_Instance;
    DuiGConfDataStore* m_Conf;
};

#endif // MOSTUSEDCOUNTERPRIVATE_H
