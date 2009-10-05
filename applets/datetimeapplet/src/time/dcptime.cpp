#include "dcptime.h"

/*#include <time.h>*/
/*#include <linux/types.h>*/
#include <qmtime.h>


void DcpTime::getTime(int &hour, int &min)
{
    Maemo::QmTime mTime;
/*    QDateTime datetime;
    QString timeZone;*/
    QTime time;

/*    mTime.getNetTime(datetime, timeZone);*/
    time = mTime.time();
    time = QTime::currentTime();

    hour = time.hour();
    min = time.minute();
}

void DcpTime::setTime(int hour, int min)
{
	Maemo::QmTime mTime;
	mTime.QDateTime::setTime(QTime(hour, min, 0));

	if(mTime.getAutosync()){
		if(!mTime.setAutosync(false)){
			qCritical("Could not turn off network time autosync");
		}
	}

	if(!mTime.setTime(mTime)){
		qCritical("Could not set time to %s", mTime.toString().toUtf8().data());
	}

/*    clock_enable_autosync(false);
    time_get_local(&currentTime);
	time_set_time(fullTime);
	*/
}

