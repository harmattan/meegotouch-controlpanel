#include "mainwindow.h"

#include <DuiApplication>
#include <DuiLocale>
#include <QtDebug>
#include <DuiTheme>

/*
#include <clockd/libtime.h>

#include <linux/types.h>
#include <time.h>

class CClock {

public:
	CClock(){};

	void setTime(int hour, int min = 0, int sec = 0) {

		struct tm *tmpTm = gmtime((const time_t*)time_get_time()); 

		tmpTm->tm_hour = hour;
		tmpTm->tm_min = min;
		tmpTm->tm_sec = sec;

//		time_set_time(time);


	/*int    tm_sec   Seconds [0,60]. 
	int    tm_min   Minutes [0,59]. 
	int    tm_hour  Hour [0,23]. 
	int    tm_mday  Day of month [1,31]. 
	int    tm_mon   Month of year [0,11]. 
	int    tm_year  Years since 1900. 
	int    tm_wday  Day of week [0,6] (Sunday =0). 
	int    tm_yday  Day of year [0,365]. 
	int    tm_isdst Daylight Savings flag.

	}

	void getTime() {

		struct tm *tmpTm = gmtime((const time_t*)time_get_time()); 

		qDebug() << tmpTm->tm_hour << ":" << tmpTm->tm_min << ":"<< tmpTm->tm_sec;

		Q_ASSERT(0);
	}

	//time_t time = time_get_time();
	//int time_set_time(time_t tick);

};*/

int main(int argc, char *argv[])
{

//	CClock c;

//	c.getTime();

	 DuiApplication* app = new DuiApplication(argc, argv);

//    DuiTheme::instance()->changeTheme("common");
//    DuiTheme::loadCSS("duicontrolpanel.css");
/*    DuiTheme::instance()->clearPixmapDirectories();
    DuiTheme::instance()->addPixmapDirectory("/usr/share/themes/dui/duicontrolpanel", true);*/

    DuiLocale locale;
    locale.addTranslationPath("./ts");
    locale.addTranslationPath("/usr/share/dui/l10n");
    locale.installCategoryCatalog(DuiLocale::DuiLcMessages, "duicontrolpanel");
    qDebug() << trid("dcp_test", "Teesttt");

    MainWindow* win = new MainWindow();
    win->show();
    int ret = app->exec();
    delete win;
    win = 0;
    return ret;
}
