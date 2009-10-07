
#include <DuiApplication>
#include <DuiLocale>
#include <DuiLabel>
#include <DuiButton>
/*#include <DuiLinearLayout>*/
#include <DuiLinearLayoutPolicy>
#include <QGraphicsLinearLayout>
#include <QtDebug>

#include <settingalarm.h>

#include "../../src/time/dcptime.h"
#include "page.h"


TestPage::TestPage()
{
	dcpTime = new DcpTime();
	grabKeyboard();
}

TestPage::~TestPage()
{
	ungrabKeyboard();
	qDebug(QString("\\[\\e[32m\\] Setting time to %1:%2").arg(clock->hours()).arg(clock->minutes()).toUtf8().data());
	dcpTime->setTime(clock->hours(), clock->minutes());
	delete dcpTime;
}

void TestPage::createContent()
{
	DuiApplicationPage::createContent();
	setObjectName("TestPage");
	setBackButtonEnabled(false);

	DuiLayout *hbox = new DuiLayout(centralWidget());
	DuiLinearLayoutPolicy *hboxpol = new DuiLinearLayoutPolicy(hbox, Qt::Horizontal);
	DuiLayout *vbox = new DuiLayout();
	DuiLinearLayoutPolicy *vboxpol = new DuiLinearLayoutPolicy(vbox, Qt::Vertical);

	hboxpol->addItem(vbox);

	int hour, min;
	dcpTime->getTime(hour, min);
	clock = new SettingAlarm(hour, min);
	clock->setMinimumSize(QSize(400, 400));
	clock->setMaximumSize(QSize(400, 400));
	hboxpol->addItem(clock);
	hboxpol->setAlignment(clock, Qt::AlignCenter);

	DuiLabel *label = new DuiLabel("Use up/down arrows to adjust hours and left/right arrows to adjust minutes.");
	vboxpol->addItem(label);

	timeLabel = new DuiLabel();
	vboxpol->addItem(timeLabel);

	dateLabel = new DuiLabel();
	vboxpol->addItem(dateLabel);

	zoneLabel = new DuiLabel();
	vboxpol->addItem(zoneLabel);

	DuiButton *btn;

	btn = new DuiButton("Hour up");
	vboxpol->addItem(btn);
	connect(btn, SIGNAL(pressed()), this, SLOT(hourUpPressed()));

	btn = new DuiButton("Hour down");
	vboxpol->addItem(btn);
	connect(btn, SIGNAL(pressed()), this, SLOT(hourDownPressed()));

	btn = new DuiButton("Min up");
	vboxpol->addItem(btn);
	connect(btn, SIGNAL(pressed()), this, SLOT(minUpPressed()));

	btn = new DuiButton("Min down");
	vboxpol->addItem(btn);
	connect(btn, SIGNAL(pressed()), this, SLOT(minDownPressed()));

	/*    timer.setInterval(1000);
	      connect(&timer, SIGNAL("timeout()"), this, SLOT("timeout()"));*/
	timeOrDateChanged();

	connect(dcpTime, SIGNAL(timeOrDateChanged()), this, SLOT(timeOrDateChanged()));
}

void TestPage::timeOrDateChanged()
{
	int hour, min;
	dcpTime->getTime(hour, min);
	timeLabel->setText(QString("Time to set on exit:  %1:%2").arg(hour).arg(min));
	clock->setHours(hour);
	clock->setMinutes(min);

	int year, month, day;
	dcpTime->getDate(year, month, day);
	dateLabel->setText(QString("Date to set on exit:  %1-%2-%3").arg(year).arg(month).arg(day));

	zoneLabel->setText(QString("Time-zone to set on exit:  %1").arg("time-zone"));
}

void TestPage::timeout()
{
	int hour, min;
	dcpTime->getTime(hour, min);
	timeLabel->setText(QString("Time to set on exit:  %1:%2").arg(hour).arg(min));
}

void TestPage::adjustTime(int a_hour, int a_min)
{
	int hour, min;
	dcpTime->getTime(hour, min);
	hour += a_hour;
	min += a_min;
	clock->setHours(hour);
	clock->setMinutes(min);
	qDebug(QString("\\[\\e[32m\\] Setting time to %1:%2").arg(hour).arg(min).toUtf8().data());
	dcpTime->setTime(hour, min);
	timeOrDateChanged();
}

void TestPage::hourUpPressed()
{
	qDebug("\\[\\e[32m\\] Button pressed: hour up");
	adjustTime(1, 0);
}

void TestPage::hourDownPressed()
{
	qDebug("\\[\\e[32m\\] Button pressed: hour down");
	adjustTime(-1, 0);
}

void TestPage::minUpPressed()
{
	qDebug("\\[\\e[32m\\] Button pressed: min up");
	adjustTime(0, 1);
}

void TestPage::minDownPressed()
{
	qDebug("\\[\\e[32m\\] Button pressed: min down");
	adjustTime(0, -1);
}

void TestPage::keyPressEvent(QKeyEvent *event)
{
	qDebug("\\[\\e[32m\\] Key pressed");
	switch(event->key()){
		case Qt::Key_W :
		case Qt::Key_Up :
			adjustTime(1, 0);
			break;
		case Qt::Key_S :
		case Qt::Key_Down :
			adjustTime(-1, 0);
			break;
		case Qt::Key_A :
		case Qt::Key_Left :
			adjustTime(0, -1);
			break;
		case Qt::Key_D :
		case Qt::Key_Right :
			adjustTime(0, 1);
			break;
		default:
			this->QGraphicsWidget::keyPressEvent(event);
			break;
	}
}

