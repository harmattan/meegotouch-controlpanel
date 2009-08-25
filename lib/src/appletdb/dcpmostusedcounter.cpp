

#include "dcpmostusedcounter.h"

#include <QString>
#include <QDebug>

MostUsedCounter* MostUsedCounter::sm_Instance = NULL;

static const QString& MOSTUSEDPATH = "/duicontrolpanel/";

MostUsedCounter* MostUsedCounter::instance()
{
    if (!sm_Instance)
        sm_Instance = new MostUsedCounter;
    return sm_Instance;
}


MostUsedCounter::MostUsedCounter()
{
}

MostUsedCounter::~MostUsedCounter()
{

	QMap<QString, DuiGConfItem*>::const_iterator i = m_Data.constBegin();
	
	while (i != m_Data.constEnd()) {
		delete i.value();
		++i;
	}
}

int MostUsedCounter::add(QString name)
{

	QMap<QString, DuiGConfItem*>::const_iterator i = m_Data.find(name);
	
	if (i== m_Data.end()) { 
		DuiGConfItem* item = new DuiGConfItem(MOSTUSEDPATH + name);
		m_Data[name] = item;
		int tmp = item->value().toInt();
		item->set(++tmp);
		
		qDebug() << qPrintable(MOSTUSEDPATH + name) << "  :  " << item->value().toInt();
		
		return item->value().toInt();
	}

	int tmp = i.value()->value().toInt();
	i.value()->set(++tmp);

	qDebug() << qPrintable(MOSTUSEDPATH + name) << "  :  " << i.value()->value().toInt();

	return i.value()->value().toInt();
}

int MostUsedCounter::get(QString name)
{

	QMap<QString, DuiGConfItem*>::const_iterator i = m_Data.find(name);
	
	if (i== m_Data.end()) { 
		DuiGConfItem* item = new DuiGConfItem(MOSTUSEDPATH + name);
		m_Data[name] = item;

		qDebug() << (MOSTUSEDPATH + name) << "  :  " << item->value().toInt();

		return item->value().toInt();
	}

	qDebug() << (MOSTUSEDPATH + name) << "  :  " << i.value()->value().toInt();

	return i.value()->value().toInt();

}
