#ifndef TIMEVIEW_H
#define TIMEVIEW_H

#include "dcpwidget.h"

#include <clock/settingalarm.h>


#include <clockd/libtime.h>

#include <linux/types.h>
#include <time.h>

class CClock {

public:
	CClock() :
		m_Hour(0),
		m_Min(0),
		m_Sec(0)
 	{}

	void setTime(int hour, int min = 0, int sec = 0) {

		int tmpHour = hour * (60*60);
		int tmpMin = min * 60 ;
		int tmpSec = sec % 60;

		int fullTime = tmpHour + tmpMin + tmpSec;

		time_set_time(fullTime);

	}

	void setSystemTime() {

		int tmpTime = time_get_time();//time(NULL);

		m_Hour = tmpTime % (24*60*60) / (60*60);
		m_Min = tmpTime % (60*60) / 60 ;
		m_Sec = tmpTime % 60;
	}

	int hour() {
		return m_Hour;
	}

	int min() {
		return m_Min;
	}

	int sec() {
		return m_Sec;
	}

private:

	int m_Hour;
	int m_Min;
	int m_Sec;
};


class DuiContainer;

class TimeView : public DcpWidget
{
    Q_OBJECT

public:
    TimeView(QGraphicsWidget *parent = 0);
    virtual ~TimeView();

protected:
    void initWidget();

private:
    DuiContainer *m_Container;

	SettingAlarm *m_TimePicker;

	CClock m_Clock;

private slots:
    virtual void orientationChanged();
};
#endif // TIMEVIEW_H

