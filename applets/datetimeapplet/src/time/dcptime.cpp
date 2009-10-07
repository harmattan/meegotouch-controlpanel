#include <qmtime.h>

#include "dcptime.h"

DcpTime::DcpTime(QObject *parent) : QObject(parent)
{
}

DcpTime::~DcpTime()
{
}

void DcpTime::getTime(int &hour, int &min)
{
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
	newTime.setDate(QDate::currentDate());

	if(mTime.getAutosync()){
		if(!mTime.setAutosync(false)){
			qCritical("Could not turn off network time autosync");
		}
	}

	if(!mTime.setTime(newTime)){
		qCritical("Could not set time to %s", newTime.toString().toUtf8().data());
	}
}

void DcpTime::getDate(int &year, int &month, int &day)
{
    Maemo::QmTime mTime;
    QDate date;

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
	newDate.setDate(QDate(year, month, day));
	newDate.setTime(QTime::currentTime());

	if(mTime.getAutosync()){
		if(!mTime.setAutosync(false)){
			qCritical("Could not turn off network time autosync");
		}
	}

	if(!mTime.setTime(newDate)){
		qCritical("Could not set date to %s", newDate.toString().toUtf8().data());
	}

}

/* Original declaration of the slot:
 * void DcpTime::timeOrSettingsChanged(Maemo::QmTime::WhatChanged what)
 * Some settings may affect time and date. Let treat it as if all may have affect,
 * for now.
 */
void DcpTime::timeOrSettingsChanged(int what)
{
	(void)what;

	timeOrDateChanged();
}

