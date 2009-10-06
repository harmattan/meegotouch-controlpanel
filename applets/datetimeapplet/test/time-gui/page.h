#ifndef PAGE_H
#define PAGE_H

#include <DuiApplicationPage>
#include <QTimer>

class SettingAlarm;
class DuiLabel;
class DcpTime;

class TestPage : public DuiApplicationPage
{
    Q_OBJECT

public:
	TestPage();
	~TestPage();

	virtual void createContent();

private slots:
	void timeOrDateChanged();
	void timeout();
	void hourUpPressed();
	void hourDownPressed();
	void minUpPressed();
	void minDownPressed();

private:
	virtual void keyPressEvent(QKeyEvent *event);
	void adjustTime(int hour, int min);

private:
	DcpTime *dcpTime;

	SettingAlarm *clock;
	DuiLabel *timeLabel;
	DuiLabel *dateLabel;
	DuiLabel *zoneLabel;

	QTimer timer;
};

#endif

