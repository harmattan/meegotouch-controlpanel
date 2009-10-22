#include "mainwindow.h"
#include "service/duicontrolpanelservice.h"
#include <DcpDebug>
#include <Retranslator>
#include <DuiApplication>

int main(int argc, char *argv[])
{
//    qInstallMsgHandler(DcpDebug::dcpMsg);

    DuiControlPanelService* service = new DuiControlPanelService();

    DuiApplication app(argc, argv);
    app.setAnimator(0);

    Retranslator retranslator;
    QObject::connect(&app, SIGNAL(localeSettingsChanged()),
                     &retranslator, SLOT(retranslate()));
 
    MainWindow win;
    service->createStartPage();
    win.show();

    return app.exec();
}

//#include "main.moc"

