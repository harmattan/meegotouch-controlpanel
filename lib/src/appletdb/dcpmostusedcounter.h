#ifndef MOSTUSEDCOUNTER_H
#define MOSTUSEDCOUNTER_H

#include <DuiGConfItem>

#include <QString>
#include <QMap>

class MostUsedCounter {

	public:

		static MostUsedCounter* instance();
                static void destroy();

		~MostUsedCounter();

		int add(const QString& name);
		int get(const QString& name);
		void clear(const QString& name);
	
	private:

		static MostUsedCounter *sm_Instance;

		MostUsedCounter();

		QMap<QString, DuiGConfItem*> m_Data;
};


#endif // MOSTUSEDCOUNTER_H

