#ifndef MOSTUSEDCOUNTERPRIVATE_H
#define MOSTUSEDCOUNTERPRIVATE_H

#include <QString>
#include <MGConfDataStore>

class MostUsedCounter;

class MostUsedCounterPrivate
{
public:
    static MostUsedCounter *sm_Instance;
    MGConfDataStore* m_Conf;
};

#endif // MOSTUSEDCOUNTERPRIVATE_H
