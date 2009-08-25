#ifndef MOSTUSEDCOUNTER_H
#define MOSTUSEDCOUNTER_H

#include <DuiGConfItem>

#include <QString>
#include <QMap>

class MostUsedCounter {

	public:

		static MostUsedCounter* instance();

		~MostUsedCounter();

		int add(QString name);
		
		int get(QString name);
	
	private:

		static MostUsedCounter *sm_Instance;

		MostUsedCounter();

		QMap<QString, DuiGConfItem*> m_Data;
};


#endif // MOSTUSEDCOUNTER_H

