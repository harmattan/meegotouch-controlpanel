#include "datetimebrief.h"
#include "dcpwidgettypes.h"

#include <duilocale.h>
#include <QDateTime>
#include <QTimer>

DateTimeBrief::DateTimeBrief()
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SIGNAL(valuesChanged()));
    timer->start(1000);
}

QString DateTimeBrief::valueText() const
{
   QDateTime now = QDateTime::currentDateTime();
   DuiLocale locale;
   return locale.formatDateTime(now, DuiLocale::DateShort, DuiLocale::TimeMedium);
}



