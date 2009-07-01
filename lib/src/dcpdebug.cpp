#include "dcpdebug.h"

#include <QTime>
#include <QHash>

static const QString& prefix = "(DCP)";
static QHash<QString, QTime> starttimes;

void DcpDebug::time(const QString& msg) {
    qDebug() << prefix << QTime::currentTime().toString("mm:ss.zzz") << msg;
}

void DcpDebug::start(const QString& msg) {
    starttimes.insert(msg, QTime::currentTime());
    time(msg + " begins");
}

void DcpDebug::end(const QString& msg) {
    QTime last = starttimes.take(msg);
    time(msg + " ends, elapsed time: " + QString::number(
                last.msecsTo(QTime::currentTime())));
}

