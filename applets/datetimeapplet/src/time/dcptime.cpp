#include "dcptime.h"

#include <time.h>
#include <linux/types.h>
#include <clockd/libtime.h>


void DcpTime::setTime(int hour, int min, int sec)
{

	int tmpHour = hour * (60*60);
	int tmpMin = min * 60 ;
	int tmpSec = sec % 60;

	int fullTime = tmpHour + tmpMin + tmpSec;

	time_set_time(fullTime);
}

