#include "duicontrolpanelservice.h"
#include "pagefactory.h"

#include "duicontrolpanelifadaptor.h"
#include <QtDebug>

static const char* serviceName = "com.nokia.DuiControlPanel";

DuiControlPanelService::DuiControlPanelService()
{
    // by default open the main page:
    m_StartPage = new Pages::Handle();
    mainPage();

    // memory owned by QDBusAbstractAdaptor instance and must be on the heap
    new DuiControlPanelIfAdaptor(this);

    QDBusConnection connection = QDBusConnection::sessionBus();

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

    Pages::Handle handle = {Pages::APPLET, appletName};
    sheduleStart(handle);
}

void
DuiControlPanelService::sheduleStart(const Pages::Handle& handle)
{
    if (m_StartPage == 0) {
        PageFactory::instance()->changePage(handle);
    } else {
        *m_StartPage = handle;
    }
}

void
DuiControlPanelService::categoryPage(const QString& category)
{
    Pages::Handle handle;
    handle.id = Pages::APPLETCATEGORY;
    handle.param = category;
    sheduleStart(handle);
}

void
DuiControlPanelService::mainPage()
{
    Pages::Handle handle;
    handle.id = Pages::MAIN;
    handle.param = "";
    sheduleStart(handle);
}

// this method gets called after mainwindow has been created,
// so after it has been called, the pages can be created for real
void
DuiControlPanelService::createStartPage()
{
    Q_ASSERT(m_StartPage);  // createStartPage should not be called twice
    PageFactory::instance()->changePage(*m_StartPage);
    delete m_StartPage;
    m_StartPage = 0;
}

