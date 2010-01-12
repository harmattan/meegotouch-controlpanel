/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpmostusedcounter.h"

#include <QString>
#include <QDebug>

//#define DEBUG
#include "dcpdebug.h"

MostUsedCounter* MostUsedCounter::sm_Instance = NULL;

MostUsedCounter::MostUsedCounter ()
{
}

MostUsedCounter::~MostUsedCounter ()
{
    QMap<QString, DuiGConfItem*>::const_iterator i = m_Data.constBegin();

    while (i != m_Data.constEnd()) {
        delete i.value();
        ++i;
    }
}

MostUsedCounter *
MostUsedCounter::instance ()
{
    if (!sm_Instance)
        sm_Instance = new MostUsedCounter;

    return sm_Instance;
}

void 
MostUsedCounter::destroy ()
{
    delete sm_Instance;
    sm_Instance = 0;
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

    QMap<QString, DuiGConfItem*>::const_iterator i = m_Data.find(key);

    if (i == m_Data.end ()) { 
        DuiGConfItem *item = new DuiGConfItem(key);
        m_Data[key] = item;
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

    QMap<QString, DuiGConfItem*>::const_iterator i = m_Data.find(key);
    if (i == m_Data.end()) {
        DuiGConfItem *item = new DuiGConfItem(key);
        m_Data[key] = item; 
        
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

    QMap<QString, DuiGConfItem*>::const_iterator i = m_Data.find (key);
    if (i != m_Data.end()) {
        i.value()->unset();
        delete i.value();
        m_Data.remove (key);
    }
}
