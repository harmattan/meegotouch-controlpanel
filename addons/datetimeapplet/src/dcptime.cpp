
#include "dcptime.h"

#include <clockd/libtime.h>
#include <linux/types.h>
#include <time.h>

void DcpTime::setTime(int hour, int min = 0, int sec = 0) {

	int tmpHour = hour * (60*60);
	int tmpMin = min * 60 ;
	int tmpSec = sec % 60;

	int fullTime = tmpHour + tmpMin + tmpSec;

	time_set_time(fullTime);

}

void DcpTime::setSystemTime() {

	int tmpTime = time_get_time();//time(NULL);

	m_Hour = tmpTime % (24*60*60) / (60*60);
	m_Min = tmpTime % (60*60) / 60 ;
	m_Sec = tmpTime % 60;
}
