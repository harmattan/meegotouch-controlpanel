#ifndef MOSTUSEDCOUNTER_H
#define MOSTUSEDCOUNTER_H

#include <DuiGConfItem>

#include <QString>
#include <QMap>

class MostUsedCounter {

	public:

		static MostUsedCounter* instance();

		~MostUsedCounter();

		int add(const QString& path);
		int get(const QString& path);
		void clear(const QString& path);

		//Convert desktop file full path to GConf key
                void convertPathToKey( const QString & path, QString & key );
	
	private:

		static MostUsedCounter *sm_Instance;

		MostUsedCounter();

		QMap<QString, DuiGConfItem*> m_Data;
};


#endif // MOSTUSEDCOUNTER_H

