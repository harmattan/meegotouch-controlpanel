#ifndef DCPTIME_H
#define DCPTIME_H

#include <QTime>

class DcpTime : public QObject
{
	Q_OBJECT

public:
    DcpTime(QObject *parent = 0);
    ~DcpTime();

    void getTime(int &hour, int &min);
    void setTime(int hour, int min);

    void getDate(int &year, int &month, int &day);
    void setDate(int year, int month, int day);

private slots:
    void timeOrSettingsChanged(int what);
signals:
    void timeOrDateChanged();
};

#endif // DCPTIME_H
