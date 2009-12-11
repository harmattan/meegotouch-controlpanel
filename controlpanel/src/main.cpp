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

int startApplication(int argc, char* argv[])
{
    DuiApplication app(argc, argv);
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
        if (s == "-h" || s == "-help") {
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
        } else if (s == "-destopdir") {
            if (i + 1 < argc) {
                i++;
                desktopDir = argv[i + 1];
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

    int result = startApplication(argc, argv);

    // destructors
    DcpWrongApplets::destroyInstance();

    return result;
}

