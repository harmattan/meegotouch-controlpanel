#include "dcptime.h"

/*#include <time.h>*/
/*#include <linux/types.h>*/

#include <qmtime.h>


DcpTime::DcpTime(QObject *parent) : QObject(parent)
{
}

DcpTime::~DcpTime()
{
}

void DcpTime::getTime(int &hour, int &min)
{
/*
    QDateTime datetime;
    QString timeZone;
    mTime.getNetTime(datetime, timeZone);
*/
    Maemo::QmTime mTime;
    QTime time;

    time = mTime.time();
    time = QTime::currentTime();

    hour = time.hour();
    min = time.minute();
}

void DcpTime::setTime(int hour, int min)
{
	Maemo::QmTime mTime;
	QDateTime newTime;
	newTime.setTime(QTime(hour, min, 0));

	if(mTime.getAutosync()){
		if(!mTime.setAutosync(false)){
			qCritical("Could not turn off network time autosync");
		}
	}

	if(!mTime.setTime(newTime)){
		qCritical("Could not set time to %s", mTime.toString().toUtf8().data());
	}

/*    clock_enable_autosync(false);
    time_get_local(&currentTime);
	time_set_time(fullTime);
	*/
}

void DcpTime::getDate(int &year, int &month, int &day)
{
    Maemo::QmTime mTime;
/*    QDateTime datetime;
    QString timeZone;*/
    QDate date;

/*    mTime.getNetTime(datetime, timeZone);*/
    date = mTime.date();
    date = QDate::currentDate();

    year = date.year();
    month = date.month();
    day = date.day();
}

void DcpTime::setDate(int year, int month, int day)
{
	Maemo::QmTime mTime;
	QDateTime newDate;

	if(mTime.getAutosync()){
		if(!mTime.setAutosync(false)){
			qCritical("Could not turn off network time autosync");
		}
	}

	newDate.setDate(QDate(year, month, day));
	if(!mTime.setTime(newDate)){
		qCritical("Could not set time to %s", mTime.toString().toUtf8().data());
	}

}

/*void DcpTime::timeOrSettingsChanged(Maemo::QmTime::WhatChanged what)*/
void DcpTime::timeOrSettingsChanged(int what)
{
	(void)what;
	timeOrDateChanged();
}

