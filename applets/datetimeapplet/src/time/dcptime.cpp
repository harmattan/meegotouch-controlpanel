#include <qmtime.h>

#include "dcptime.h"
#include <QTime>

DcpTime::DcpTime(QObject *parent) : QObject(parent),
    m_Time(new Maemo::QmTime::QmTime(this))
{
    connect (m_Time, SIGNAL(timeOrSettingsChanged (QmTime::WhatChanged)),
             this, SIGNAL(timeOrDateChanged()));
}

DcpTime::~DcpTime()
{
}

void DcpTime::getTime(int &hour, int &min)
{
    QTime time;

    time = QTime::currentTime();

    hour = time.hour();
    min = time.minute();
}

void DcpTime::setTime(int hour, int min)
{
	QDateTime newTime;
	newTime.setTime(QTime(hour, min, 0));
	newTime.setDate(QDate::currentDate());

	if(m_Time->getAutosync()){
		if(!m_Time->setAutosync(false)){
			qCritical("Could not turn off network time autosync");
		}
	}

	if(!m_Time->setTime(newTime)){
		qCritical("Could not set time to %s", newTime.toString().toUtf8().data());
	}
}

void DcpTime::getDate(int &year, int &month, int &day)
{
    QDate date;

    date = m_Time->date();

    year = date.year();
    month = date.month();
    day = date.day();
}

void DcpTime::setDate(int year, int month, int day)
{
	QDateTime newDate;
	newDate.setDate(QDate(year, month, day));
	newDate.setTime(QTime::currentTime());
    setDateTime (newDate);
}

void DcpTime::setDateTime(const QDateTime& newDate)
{
    if(m_Time->getAutosync()){
		if(!m_Time->setAutosync(false)){
			qCritical("Could not turn off network time autosync");
		}
	}

	if(!m_Time->setTime(newDate)){
		qCritical("Could not set time to %s", newDate.toString().toUtf8().data());
	}
}

