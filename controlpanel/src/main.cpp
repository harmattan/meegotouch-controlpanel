/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include <cstdio>
#include <sys/wait.h>
#include <csignal>
#include <DuiApplicationWindow>
#include <DcpDebug>
#include <DcpRetranslator>
#include <DuiApplication>
#include <DuiLocale>
#include "service/duicontrolpanelservice.h"
#include "dcpappletdb.h"
#include "appleterrorsdialog.h"
#include "dcpwrongapplets.h"

#include "dcpdebug.h"

/*!
 * In this function we fork to a child and then wait until the child is
 * terminated. Then we try to decide what happened with the child process, if it
 * is crashed then we for again.
 * Here we don't want to load use DcpWrongApplets::queryBadApplets() to
 * investigate the disabled applet's list, because that would lead to a
 * situation where we load all the applet *.desktop files in the parent and in
 * the child as well. That would slow down the initialization of the
 * application.
 */
void 
startSupervising()
{
    DCP_DEBUG ("");

    while (fork() > 0) {
        DCP_DEBUG ("FORKED a child");

        /*
         * We forked to a child that will do the actual job. We just wait until
         * it exits.
         */
        int result = 0;
        wait (&result);

        /*
         * If the child exited because of a signal and the signal shows that it
         * was a crash we continue (fork again) to start up the program with the
         * applet disabled. Please note that the child process will end up with
         * these signals only if it found a fawlty applet. It catches all these
         * signals and it will call exit() if the crash happened inside the
         * duicontrolpanel code.
         */
        if (WIFSIGNALED(result)) {
            switch (WTERMSIG(result)) {
                case SIGILL:
                case SIGSEGV:
                case SIGBUS:
                case SIGABRT:
                case SIGFPE:
                    DCP_WARNING ("Child has been aborted.");
                    continue;
            }
        }
        
        /*
         * If this was not an applet crash we exit.
         */
        exit (result);
    }
}

/* 
 * this redefines the signal handler for TERM and INT signals, so as to be able
 * to use aboutToQuit signal from qApp also in these cases 
 */
void 
onTermSignal (
        int param)
{
    DCP_DEBUG ("");

    Q_UNUSED(param);
    if (qApp) {
        qApp->quit();
    }
}

int 
startApplication (int argc, char* argv[])
{
    DCP_DEBUG ("");

    DuiApplication app(argc, argv);
    signal(SIGTERM, &onTermSignal);
    signal(SIGINT, &onTermSignal);

    // install the new translations if locale changes:
    QObject::connect(&app, SIGNAL(localeSettingsChanged()),
                     DcpRetranslator::instance(), SLOT(retranslate()));

    // init servicefw api:
    DuiControlPanelService* service = new DuiControlPanelService();

    // mainwindow:
    DuiApplicationWindow win;
    service->createStartPage();
    win.show();

    return app.exec();
}


int main(int argc, char *argv[])
{
    // parse options
    QString desktopDir;
    for (int i = 1; i < argc; ++i) {
        QString s(argv[i]);
        if (s == "-h" || s == "-help" || s == "--help" ) {
            QTextStream out(stdout);
            out << "Usage: " << argv[0] <<
                " [LIBDUI OPTION]... [-desktopdir DIR]\n\n";
            out << "  -desktopdir DIR     Load .desktop files from DIR\n";
            out << "  -nosupervisor       Disables applet supervisor";
            out << "\n\n";
            break;
        } else if (s == "-nosupervisor") {
            qDebug() << "Applet supervisor is disabled.";
            DcpWrongApplets::disable();
        } else if (s == "-desktopdir") {
            if (i + 1 < argc) {
                i++;
                desktopDir = argv[i];
                qDebug() << "Using desktopdir:" << desktopDir;
            }
        }
    }

    if (!DcpWrongApplets::isDisabled()) {
        startSupervising();
    }

    /*!
     * FIXME: If we have a desktop directory we have to load the desktop files
     * now. We could delay it by changing the DcpAppletDb class implementation.
     */
    if (desktopDir.isEmpty()) {
        DCP_DEBUG ("### Not creating DcpAppletDb, we can do it later.");
         //DcpAppletDb::instance ();
    } else {
        DCP_DEBUG ("### Creating DcpAppletDb in directory '%s'.", 
                DCP_STR(desktopDir));
        DcpAppletDb::instance (desktopDir);
    }

    DCP_DEBUG ("### Starting up application.");
    int st = startApplication (argc, argv);

    DcpAppletDb::destroy();

    return st;
}

