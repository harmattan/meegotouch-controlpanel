#include <cstdio>
#include <DuiApplicationWindow>
#include "service/duicontrolpanelservice.h"
#include "dcpappletdb.h"
#include "appleterrorsdialog.h"
#include <DcpDebug>
#include <DcpRetranslator>
#include <DuiApplication>
#include "dcpwrongapplets.h"
#include <sys/wait.h>
#include <csignal>

void startSupervising()
{
    while (fork() > 0) {
        qDebug() << "FORKED a child";
        // we are in parent process ( = supervisor )
        // and a child was successfully started ( = gui )
        QSet<QString> oldBadApplets = DcpWrongApplets::queryBadApplets();

        // wait for child to terminate:
        int result = 0;
        wait (&result);

        // check if there were additional applets marked as wrong
        QSet<QString> newBadApplets = DcpWrongApplets::queryBadApplets();
        newBadApplets.subtract(oldBadApplets);
        if (newBadApplets.isEmpty()) {
            exit (result);
        }
    }
}

/* this redefines the signal handler for TERM and INT signals,
 * so as to be able to use aboutToQuit signal from qApp
 * also in these cases */
void onTermSignal(int param)
{
    if (qApp) {
        qApp->quit();
    }
}

int startApplication(int argc, char* argv[])
{
    DuiApplication app(argc, argv);
    signal(SIGTERM, &onTermSignal);
    signal(SIGINT, &onTermSignal);
    app.setAnimator(0);

    DuiControlPanelService* service = new DuiControlPanelService();

    DcpRetranslator retranslator;
    QObject::connect(&app, SIGNAL(localeSettingsChanged()),
                     &retranslator, SLOT(retranslate()));

    DuiApplicationWindow win;
    service->createStartPage();
    win.show();
    AppletErrorsDialog::showAppletErrors();

    return app.exec();
}


int main(int argc, char *argv[])
{
    qInstallMsgHandler(DcpDebug::dcpMsg);

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

    if (desktopDir.isEmpty()) {
         DcpAppletDb::initInstance();
    } else {
         DcpAppletDb::initInstance(desktopDir);
    }

    return startApplication(argc, argv);
}

