#include "duicontrolpanelservice.h"
#include "pagefactory.h"

#include "duicontrolpanelifadaptor.h"
#include <QtDebug>

static const char* serviceName = "com.nokia.DuiControlPanel";

DuiControlPanelService::DuiControlPanelService()
{
    // memory owned by QDBusAbstractAdaptor instance and must be on the heap
    new DuiControlPanelIfAdaptor(this);

    QDBusConnection connection(QDBusConnection::sessionBus());

    bool ret = connection.registerService(serviceName);
    qDebug() << "Registering service" << serviceName
             << (ret ? "successfully" : "failed");

    ret = connection.registerObject("/", this);
    qDebug() << "Registering object for service"
             << (ret ? "successfully" : "failed");
}

void
DuiControlPanelService::appletPage(const QString& appletName)
{
    Pages::Handle handle;
    handle.id = Pages::APPLET;
    handle.param = appletName;
    PageFactory::instance()->changePage(handle);
}

void
DuiControlPanelService::categoryPage(const QString& category)
{
    Pages::Handle handle;
    handle.id = Pages::APPLETCATEGORY;
    handle.param = category;
    PageFactory::instance()->changePage(handle);
}

void
DuiControlPanelService::mainPage()
{
    Pages::Handle handle;
    handle.id = Pages::MAIN;
    handle.param = "";
    PageFactory::instance()->changePage(handle);
}

