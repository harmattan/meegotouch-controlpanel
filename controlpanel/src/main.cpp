#include "mainwindow.h"
#include "service/duicontrolpanelservice.h"
#include "dcpappletdb.h"
#include <DcpDebug>
#include <DcpRetranslator>
#include <DuiApplication>

int main(int argc, char *argv[])
{
    qInstallMsgHandler(DcpDebug::dcpMsg);

    DuiControlPanelService* service = new DuiControlPanelService();

    DuiApplication app(argc, argv);
    app.setAnimator(0);

    QStringList args = app.arguments();
    int i = args.indexOf("-desktopdir", 1);
    if (i >= 1 && i + 1 < args.size()) {
        const QString &desktopDir = args.at(i+1);
        qDebug() << "using desktopdir" << desktopDir;
        DcpAppletDb::initInstance(desktopDir);
    } else {
        DcpAppletDb::initInstance();
    }

    DcpRetranslator retranslator;
    QObject::connect(&app, SIGNAL(localeSettingsChanged()),
                     &retranslator, SLOT(retranslate()));
 
    MainWindow win;
    service->createStartPage();
    win.show();

    return app.exec();
}

//#include "main.moc"

