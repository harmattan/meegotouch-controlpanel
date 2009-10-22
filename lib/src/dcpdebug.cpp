#include "dcpdebug.h"

#include <stdio.h>
#include <stdlib.h>
#include <QTime>
#include <QHash>

static const QString& DEBUG_PREFIX = "(DCP)";
static QHash<QString, QTime> starttimes;

void DcpDebug::time(const QString& msg) {
    qDebug() << DEBUG_PREFIX << QTime::currentTime().toString("mm:ss.zzz") << msg;
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

void DcpDebug::dcpMsg(QtMsgType type, const char *msg)
{
    switch (type) {
        case QtDebugMsg:
            fprintf(stderr, "%s%s\n", DEBUG_PREFIX, msg);
            break;
        case QtWarningMsg:
            fprintf(stderr, "%s* %s *\n", DEBUG_PREFIX, msg);
            break;
        case QtCriticalMsg:
            fprintf(stderr, "%s** %s **\n", DEBUG_PREFIX, msg);
            break;
        case QtFatalMsg:
            fprintf(stderr, "Fatal: %s%s\n", DEBUG_PREFIX, msg);
            abort();
    }
}

