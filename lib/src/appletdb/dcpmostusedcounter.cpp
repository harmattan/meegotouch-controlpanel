

#include "dcpmostusedcounter.h"

#include <QString>
#include <QDebug>

MostUsedCounter* MostUsedCounter::sm_Instance = NULL;

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

int MostUsedCounter::add(const QString& path)
{
        QString key;
        convertPathToKey( path, key );

        if ( key != "" ) {

                QMap<QString, DuiGConfItem*>::const_iterator i = m_Data.find(key);
		
		if (i== m_Data.end()) { 
                        DuiGConfItem* item = new DuiGConfItem(key);
                        m_Data[key] = item;
			int tmp = item->value().toInt();
			item->set(++tmp);
			
                        //qDebug() << "  ADD  " << key << "  :  " << item->value().toInt();
			
			return item->value().toInt();
		}
	
		int tmp = i.value()->value().toInt();
		i.value()->set(++tmp);
	
                //qDebug() << "  ADD  "  << name << "  :  " << i.value()->value().toInt();
	
		return i.value()->value().toInt();
	}

	return 0;
}

int MostUsedCounter::get(const QString& path)
{
        QString key;
        convertPathToKey( path, key );

        if (key != "") {

                QMap<QString, DuiGConfItem*>::const_iterator i = m_Data.find(key);
		
		if (i== m_Data.end()) { 
                        DuiGConfItem* item = new DuiGConfItem(key);
                        m_Data[key] = item;
	
                        //qDebug() << "  GET  " << key << "  :  " << item->value().toInt();
	
			return item->value().toInt();
		}
	
                //qDebug() <<  "  GET  "  << name << "  :  " << i.value()->value().toInt();
	
		return i.value()->value().toInt();
	}

	return 0;

}

void MostUsedCounter::clear(const QString& path)
{
        QString key;
        convertPathToKey( path, key );

        if (key != "") {

                QMap<QString, DuiGConfItem*>::const_iterator i = m_Data.find(key);

                //qDebug() <<  "  CLEAR  "  << key << "  :  " << i.value()->value().toInt();


		if (i== m_Data.end()) { 
			//DuiGConfItem* item = new DuiGConfItem(name);
			//m_Data[name] = 0;
		
			return;
		}
	
		i.value()->unset();
	}
}

void MostUsedCounter::convertPathToKey( const QString & path, QString & key )
{
    static const QString desktopExt = ".desktop";
    key = path;
    key.remove(desktopExt);
    key.replace(DESKTOP_DIR, MOSTUSEDCOUNTER_GCONFKEY);
}
