#include "duicontrolpanelservice.h"
#include "pagefactory.h"

#include "duicontrolpanelifadaptor.h"
#include <QtDebug>

static const char* serviceName = "com.nokia.DuiControlPanel";

DuiControlPanelService::DuiControlPanelService()
{
    // by default open the main page:
    m_StartPage = new PageHandle ();
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

bool
DuiControlPanelService::appletPage(const QString& appletName)
{

    PageHandle handle (PageHandle::APPLET, appletName);
    sheduleStart(handle);

    return true; // TODO this hack prevents a servicefw issue,
                 // that the app does not get the first query
                 // Result means nothing...
}

void
DuiControlPanelService::sheduleStart (
		const PageHandle &handle)
{
    if (m_StartPage == 0) {
        PageFactory::instance()->changePage(handle);
    } else {
        m_StartPage->id = handle.id;
        m_StartPage->param = handle.param;
    }
}

void
DuiControlPanelService::categoryPage(const QString& category)
{
    PageHandle handle;
    handle.id = PageHandle::APPLETCATEGORY;
    handle.param = category;
    sheduleStart(handle);
}

void
DuiControlPanelService::mainPage()
{
    PageHandle handle;
    handle.id = PageHandle::MAIN;
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

