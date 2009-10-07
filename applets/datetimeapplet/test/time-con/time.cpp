
#include <stdlib.h>

#include "../../src/time/dcptime.h"

int main(int argc, char *argv[])
{
	if(argc < 3){
		qCritical("Please give two param as delta hours and delta minutes");
		return -1;
	}

	int hour, min;
	DcpTime dcpTime;

	qDebug("Get current time");
	dcpTime.getTime(hour, min);
	qDebug(QString("Old time: %1:%2").arg(hour).arg(min).toUtf8().data());

	qDebug("Adjust time");
	/* adjust time by first and second command lines parameters as delta hour and delta minutes */
	hour += atoi(argv[1]);
	min += atoi(argv[2]);

	qDebug(QString("Set time to: %1:%2").arg(hour).arg(min).toUtf8().data());
	dcpTime.setTime(hour, min);
}

