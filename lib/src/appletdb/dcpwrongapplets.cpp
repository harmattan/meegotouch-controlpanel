/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include <signal.h>
#include <execinfo.h>

#include <DuiGConfItem>
#include <QFileInfo>
#include <QDateTime>
#include <QtDebug>
#include <QApplication>

#include "dcpwrongapplets.h"
#include "dcpappletdb.h"
#include "dcpappletmetadata.h"


#define DEBUG
#include "dcpdebug.h"

#define KEY_SEPARATOR "/"

DcpWrongApplets* DcpWrongApplets::sm_Instance = 0;
bool DcpWrongApplets::sm_Disabled = false;
const QString keyPath = "/apps/duicontrolpanel/badplugins";


/*********************************************************************************
 * Here some signal handlers are implemented.
 */
#define BACKTRACE_SIZE 128

bool
backtrace_line_is_an_applet (
        const char     *line,
        char          **start,
        char          **end)
{
    *start = strstr(line, "/usr/lib/duicontrolpanel/applets/");
    if (*start == 0)
        return false;

    *end = *start;
    while (**end != '\0' && **end != '(')
        ++(*end);

    return true;
}

void
mark_applet_as_bad (
        const char   *full_path)
{
    DuiGConfItem  conf (keyPath + full_path + KEY_SEPARATOR + "CrashDateTime" );
    QDateTime     now = QDateTime::currentDateTime ();

    conf.set (now.toString());
}

void
some_crash_happened (
        void)
{
    void     *backtrace_array [BACKTRACE_SIZE];
    char    **backtrace_strings;
    size_t    backtrace_size;
    char     *start, *end;

    DCP_WARNING ("Crash...");
    backtrace_size = backtrace (backtrace_array, BACKTRACE_SIZE);
    backtrace_strings = backtrace_symbols (backtrace_array, backtrace_size);

    /*
     * Let's print the backtrace from the stack.
     */
    fprintf (stderr, "--- Crash backtrace of DuiControlPanel ---\n");
    for (size_t i = 0; i < backtrace_size; i++) {
        fprintf (stderr, "%03u %s\n", i, backtrace_strings[i]);
    }
    fprintf (stderr, "------------------------------------------\n");
    fflush (stderr);

    /*
     * Let's see if any of the functions is actually in some applet.
     */
    for (size_t i = 0; i < backtrace_size; i++) {
        if (!backtrace_line_is_an_applet (backtrace_strings[i], &start, &end))
            continue;

        *end = '\0';
        DCP_WARNING ("*** This is an applet: '%s'", start);
        mark_applet_as_bad (start);
        break;
    }
}

void
termination_signal_handler (
        int signum)
{
    DCP_DEBUG ("*** signum = %d", signum);
    switch (signum) {
        case SIGTERM:
        case SIGHUP:
        case SIGINT:
        case SIGQUIT:
            /*
             * These are the signals that are not caused by any bug in the code.
             * We can do something with these, but now we just exit.
             */
            exit (1);
            break;
       
        case SIGILL:
        case SIGSEGV:
        case SIGBUS:
        case SIGABRT:
        case SIGFPE:
            /*
             * And here are those that are caused by errors.
             */
            some_crash_happened ();
            exit (1);
            break;
    }

    raise (signum);
}

/*********************************************************************************
 * Other parts of the code.
 */
DcpWrongApplets::DcpWrongApplets ()
{
    DCP_DEBUG ("");
    signal (SIGTERM, termination_signal_handler);
    signal (SIGHUP,  termination_signal_handler);
    signal (SIGINT,  termination_signal_handler);
    signal (SIGQUIT,  termination_signal_handler);

    signal (SIGILL,  termination_signal_handler);
    signal (SIGSEGV, termination_signal_handler);
    signal (SIGBUS, termination_signal_handler);
    signal (SIGABRT, termination_signal_handler);
    signal (SIGFPE,  termination_signal_handler);

    connect (qApp, SIGNAL(aboutToQuit()),
             this, SLOT(deleteLater()));

    // init cache:
    m_BadApplets = queryBadApplets();
}

DcpWrongApplets::~DcpWrongApplets ()
{
}


QSet <QString> 
DcpWrongApplets::queryBadApplets ()
{
    QSet <QString> badApplets;

    DCP_DEBUG ("");
    DcpAppletMetadataList metadataList = DcpAppletDb::instance()->list();

    /*
     * We go through all the applets and we check each and every one of them in
     * the GConf database.
     */
    foreach (DcpAppletMetadata *metadata, metadataList) {
        if (isAppletRecentlyCrashed (metadata))
            badApplets.insert (metadata->binary());
    }
    
    return badApplets;
}

DcpWrongApplets *
DcpWrongApplets::instance ()
{
    if (!sm_Instance) 
	    sm_Instance = new DcpWrongApplets();

    return sm_Instance;
}

void 
DcpWrongApplets::destroyInstance ()
{
    if (sm_Instance) {
        delete sm_Instance;
        sm_Instance = 0;
    }
}

const QSet<QString> &
DcpWrongApplets::badApplets () const
{
    return m_BadApplets;
}

bool 
DcpWrongApplets::isAppletRecentlyCrashed (
		const DcpAppletMetadata       *metadata)
{
    return isAppletRecentlyCrashed (metadata->fullBinary());
}

bool 
DcpWrongApplets::isAppletRecentlyCrashed (
		const QString       &fullSoPath)
{
    DuiGConfItem conf (keyPath + fullSoPath + KEY_SEPARATOR + "CrashDateTime" );
    QString      lastCrashDate = conf.value().toString ();

    /*
     * If the applet protection has been disabled or the applet has no entry in
     * the GConf database.
     */
    if (sm_Disabled || lastCrashDate.isEmpty())
        return false;

    /*
     * Check if the applet file was modified since the crash.
     */
    if (QFileInfo (fullSoPath).lastModified() > 
            QDateTime::fromString (lastCrashDate)) {
        conf.unset ();
        return false;
    }

    return true;
}

void
DcpWrongApplets::disable ()
{
    sm_Disabled = true;
    destroyInstance ();
}

