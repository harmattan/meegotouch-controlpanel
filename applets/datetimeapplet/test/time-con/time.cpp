
#include <stdlib.h>
#include <qmtime.h>

int main(int argc, char *argv[])
{
	if(argc < 3){
		qCritical("Please give two param as delta hours and delta minutes");
		return -1;
	}

	Maemo::QmTime mTime;
	QDateTime newTimeDate;
	QTime time;
	int hour, min;

	qDebug("Get current time");
/*	time = mTime.time();*/
	time = QTime::currentTime();

	hour = time.hour();
	min = time.minute();

	qDebug("Adjust time");
	/* adjust time by first and second command lines parameters as delta hour and delta minutes */
	hour += atoi(argv[1]);
	min += atoi(argv[2]);

	qDebug("Assemble new time");
	newTimeDate.setTime(QTime(hour, min, 0));

	qDebug("Check autosync");
	if(mTime.getAutosync()){
		if(!mTime.setAutosync(false)){
			qCritical("Could not turn off network time autosync");
		}
	}

	time = newTimeDate.time();
	qDebug(QString("Set time to %1:%2").arg(time.hour()).arg(time.minute()).toUtf8().data());
	if(!mTime.setTime(newTimeDate)){
/*		qCritical("Could not set time");*/
		qCritical(QString("Could not set time to %1").arg(newTimeDate.toString()).toUtf8().data());
	}
}

