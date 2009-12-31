/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpmostusedcounter.h"

#include <QString>
#include <QDebug>

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

int 
MostUsedCounter::add (
        const QString &name)
{
    if (name != "") {
        QMap<QString, DuiGConfItem*>::const_iterator i = m_Data.find(name);
		
        if (i == m_Data.end ()) { 
            DuiGConfItem* item = new DuiGConfItem(name);
            m_Data[name] = item;
            int tmp = item->value().toInt();
            item->set(++tmp);
			
            return item->value().toInt();
        }
	
        int tmp = i.value()->value().toInt();
        i.value()->set(++tmp);
	
        return i.value()->value().toInt();
    }

	return 0;
}

int 
MostUsedCounter::get (
        const QString &name)
{
    if (name != "") {
        QMap<QString, DuiGConfItem*>::const_iterator i = m_Data.find(name);
		
        if (i == m_Data.end()) { 
            DuiGConfItem* item = new DuiGConfItem(name);
            m_Data[name] = item;
	
            return item->value().toInt();
        }
		
        return i.value()->value().toInt();
	}

	return 0;
}

void 
MostUsedCounter::clear (
        const QString &name)
{
    if (name != "") {
        QMap<QString, DuiGConfItem*>::const_iterator i = m_Data.find(name);

        if (i == m_Data.end()) { 
			return;
        }
	
        i.value()->unset();
    }
}
