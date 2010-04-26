/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpmostusedcounter.h"
#include "dcpmostusedcounter_p.h"

#include <QString>
#include <QDebug>

#include "dcpdebug.h"

MostUsedCounter* MostUsedCounterPrivate::sm_Instance = NULL;

MostUsedCounter::MostUsedCounter () : d_ptr(new MostUsedCounterPrivate())
{
    d_ptr->m_Conf = new MGConfDataStore(MOSTUSEDCOUNTER_GCONFKEY);
}

MostUsedCounter::~MostUsedCounter ()
{
    delete d_ptr->m_Conf;
    delete d_ptr;
}

MostUsedCounter *
MostUsedCounter::instance ()
{
    if (!MostUsedCounterPrivate::sm_Instance)
        MostUsedCounterPrivate::sm_Instance = new MostUsedCounter;

    return MostUsedCounterPrivate::sm_Instance;
}

void
MostUsedCounter::destroy ()
{
    delete MostUsedCounterPrivate::sm_Instance;
    MostUsedCounterPrivate::sm_Instance = 0;
}

/*!
 * Increments the usage counter for the given GConf key, returns the new value.
 */
int
MostUsedCounter::incrementUsageCount (const QString &key)
{
    DCP_DEBUG ("*** key = '%s'", DCP_STR(key));

    int count = d_ptr->m_Conf->value(key).toInt() + 1;
    d_ptr->m_Conf->createValue(key, count);
    return count;
}

/*!
 * \brief returns the usage counter for the given GConf key.
 */
int
MostUsedCounter::getUsageCount (const QString &key)
{
    DCP_DEBUG ("*** key = '%s'", DCP_STR(key));

    // if key does not exist or not convertible, 0 is returned (default value)
    return d_ptr->m_Conf->value(key).toInt();
}

/*!
 * \brief Removes the usage counter key from the database. 
 */
void
MostUsedCounter::dropKey (const QString &key)
{
    d_ptr->m_Conf->setValue(key,QVariant());
}


