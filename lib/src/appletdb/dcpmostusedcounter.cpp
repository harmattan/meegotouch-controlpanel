/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpmostusedcounter.h"
#include "dcpmostusedcounter_p.h"

#include <QString>
#include <QDebug>

//#define DEBUG
#include "dcpdebug.h"

MostUsedCounter* MostUsedCounterPrivate::sm_Instance = NULL;

MostUsedCounter::MostUsedCounter () : d_ptr(new MostUsedCounterPrivate())
{
}

MostUsedCounter::~MostUsedCounter ()
{
    QMap<QString, DuiGConfItem*>::const_iterator i = d_ptr->data.constBegin();

    while (i != d_ptr->data.constEnd()) {
        delete i.value();
        ++i;
    }
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
MostUsedCounter::incrementUsageCounter (
        const QString &key)
{
    DCP_DEBUG ("*** key = '%s'", DCP_STR(key));
    if (key.isEmpty())
        return 0;

    QMap<QString, DuiGConfItem*>::const_iterator i = d_ptr->data.find(key);

    if (i == d_ptr->data.end ()) { 
        DuiGConfItem *item = new DuiGConfItem(key);
        d_ptr->data[key] = item;
        int tmp = item->value().toInt();
        item->set(++tmp);

        return item->value().toInt();
    }

    int tmp = i.value()->value().toInt();
    i.value()->set (++tmp);

    return i.value()->value().toInt();
}

/*!
 * \brief returns the usage counter for the given GConf key.
 */
int 
MostUsedCounter::getUsageCounter (
        const QString &key)
{
    DCP_DEBUG ("*** key = '%s'", DCP_STR(key));
    if (key.isEmpty()) 
        return 0;

    QMap<QString, DuiGConfItem*>::const_iterator i = d_ptr->data.find(key);
    if (i == d_ptr->data.end()) {
        DuiGConfItem *item = new DuiGConfItem(key);
        d_ptr->data[key] = item; 
        
        return item->value().toInt();
    }

    return i.value()->value().toInt();
}

/*!
 * \brief Removes the usage counter key from the database. 
 */
void 
MostUsedCounter::dropKey (
        const QString &key)
{
    DCP_DEBUG ("*** key = '%s'", DCP_STR(key));
    if (key.isEmpty())
        return;

    QMap<QString, DuiGConfItem*>::const_iterator i = d_ptr->data.find (key);
    if (i != d_ptr->data.end()) {
        i.value()->unset();
        delete i.value();
        d_ptr->data.remove (key);
    }
}
