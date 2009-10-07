
#include <stdlib.h>

#include "../../src/time/dcptime.h"

int main(int argc, char *argv[])
{
	if(argc < 4){
		qCritical("Please give three param as delta years and delta months and delta days");
		return -1;
	}

	int year, month, day;

	DcpTime dcpTime;

	qDebug("Get current date");
	dcpTime.getDate(year, month, day);
	qDebug(QString("Old date: %1:%2:%3").arg(year).arg(month).arg(day).toUtf8().data());

	qDebug("Adjust date");
	/* adjust time by first and second command lines parameters as delta hour and delta minutes */
	year += atoi(argv[1]);
	month += atoi(argv[2]);
	day += atoi(argv[3]);

	qDebug(QString("Set date to: %1:%2:%3").arg(year).arg(month).arg(day).toUtf8().data());
	dcpTime.setDate(year, month, day);
}

