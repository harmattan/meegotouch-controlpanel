#ifndef DCPTIME_H
#define DCPTIME_H

#include <QTime>

namespace DcpTime {
    void getTime(int &hour, int &min);
    void setTime(int hour, int min);
};

#endif // DCPTIME_H
