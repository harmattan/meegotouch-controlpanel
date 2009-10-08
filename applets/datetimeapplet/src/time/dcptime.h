#ifndef DCPTIME_H
#define DCPTIME_H

class QDateTime;
#include <QObject>
namespace Maemo {
    namespace QmTime {
        class QmTime;
    };
};

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

    void setDateTime(const QDateTime& newDate);

signals:
    void timeOrDateChanged();

private slots:
    void timeOrSettingsChanged(int what);

private:
    Maemo::QmTime::QmTime* m_Time;
};

#endif // DCPTIME_H
