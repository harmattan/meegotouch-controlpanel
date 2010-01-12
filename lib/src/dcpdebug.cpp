/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include "dcpdebug.h"

#include <stdio.h>
#include <stdlib.h>
#include <QTime>
#include <QHash>

#ifdef DEBUG_SUPPRESS_COLOR
#  define TERM_RED     ""
#  define TERM_YELLOW  ""
#  define TERM_GREEN   ""
#  define TERM_NORMAL  ""
#  define TERM_BOLD    ""
#else 
#  define TERM_RED     "\033[1;33m"
#  define TERM_YELLOW  "\033[1;31m"
#  define TERM_GREEN   "\033[1;32m"
#  define TERM_NORMAL  "\033[0;39m"
#  define TERM_BOLD    "\033[1m"
#endif





static const char* DEBUG_PREFIX = "(DCP)";
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

/*
 * We have an enhanced version of this function, that has a non-compatible
 * argument list. This function is deprecated and should not be used, all
 * reference should be changed.
 */
void 
DcpDebug::dcpMsg (
        QtMsgType   type, 
        const char *msg)
{
    switch (type) {
        case QtDebugMsg:
            fprintf (stderr, "%s%s\n", DEBUG_PREFIX, msg);
            break;

        case QtWarningMsg:
            fprintf (stderr, "%s* %s *\n", DEBUG_PREFIX, msg);
            break;

        case QtCriticalMsg:
            fprintf (stderr, "%s** %s **\n", DEBUG_PREFIX, msg);
            break;

        case QtFatalMsg:
            fprintf (stderr, "Fatal: %s%s\n", DEBUG_PREFIX, msg);
            fflush (stderr);
            abort();
    }

    fflush (stderr);
}

/*
 * This function is used to print debug and error messages, an enhanced version
 * of the DcpDebug::dcpMsg(). Please use this function anly through macros (like
 * DCP_DEBUG() for example) so the change in the function interface does not
 * mean the change of all the code calling it).
 */
void 
DcpDebug::dcpPrintMsg (
        QtMsgType     type,
        const char   *function,
        const char   *formatstring,
        ...)
{
    va_list args;

    va_start (args, formatstring);
    switch (type) {
        case QtDebugMsg:
            fprintf (stderr, "%s%s%s: ",
                    TERM_GREEN, function, TERM_NORMAL);
            vfprintf (stderr, formatstring, args);
            break;

        case QtWarningMsg:
            fprintf (stderr, "%s%s%s: ",
                    TERM_YELLOW, function, TERM_NORMAL);
            vfprintf (stderr, formatstring, args);
            break;

        case QtCriticalMsg:
            fprintf (stderr, "%s%s%s: ",
                    TERM_RED, function, TERM_NORMAL);
            vfprintf (stderr, formatstring, args);
            break;

        case QtFatalMsg:
            fprintf (stderr, "%s%s%s: ",
                    TERM_GREEN, function, TERM_NORMAL);
            vfprintf (stderr, formatstring, args);
            fprintf (stderr, "\n%s%s%s: Aborting program.",
                    TERM_RED TERM_BOLD, function, TERM_NORMAL);
            putchar('\n');
            fflush (stderr);
            abort();
    }
    va_end (args);

    putchar('\n');
    fflush (stderr);
}

