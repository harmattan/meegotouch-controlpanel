#include "dcpappletlauncherservice.h"

#include "pagefactory.h"

#include "dcpappletlauncherifadaptor.h"

#include <QtDebug>
#include <MApplication>
#include <MApplicationWindow>
#include <QDBusError>
#include <DcpAppletDb>

static const char* serviceName = "com.nokia.DcpAppletLauncher";


DcpAppletLauncherService::DcpAppletLauncherService ():
    MApplicationService (serviceName)
{
}

/*
 * Pops up the applet's page if the window is already created
 * and raises it
 *
 * Returns false only if there was window but the page popup was unsuccessful
 */
bool DcpAppletLauncherService::maybeAppletRealStart ()
{
    if (m_PageHandle.id == PageHandle::NOPAGE)  return true;
    if (MApplication::windows().isEmpty())  return true;

    MWindow *win = MApplication::windows().at(0);
    Q_ASSERT (win);

    // FIXME XXX: the instance() call makes the .desktop files parsed unnecesserily
    PageFactory* pageFactory = PageFactory::instance();
    // the pagefactory starts the applet out of process and refuses to load it,
    // in case it is not already loaded, so we load it here:
    DcpAppletDb::instance()->applet (m_PageHandle.param);
    bool success = pageFactory->changePage (m_PageHandle);

    if (success) {
        unregisterService ();
    }

    win->show();

    win->activateWindow();
    win->raise();

    return success;
}

void DcpAppletLauncherService::sheduleApplet (const QString& appletName)
{
    m_PageHandle.id = PageHandle::APPLET;
    m_PageHandle.param = appletName;
    m_PageHandle.widgetId = 0;
    m_PageHandle.isStandalone = false;
}


bool DcpAppletLauncherService::appletPage (const QString& appletName)
{
    sheduleApplet (appletName);

    return maybeAppletRealStart();
}

bool DcpAppletLauncherService::registerService ()
{
    // memory owned by QDBusAbstractAdaptor instance and must be on the heap
    new DcpAppletLauncherIfAdaptor(this);

    QDBusConnection connection = QDBusConnection::sessionBus();

    bool ret = connection.registerService (serviceName);
    if (ret) {
        ret = connection.registerObject("/", this);
        if (!ret) {
            qWarning ("Error while registering the service object");
        }
    } else {
        qWarning ("Error while registering the service name");
    }

    if (!ret) {
        handleServiceRegistrationFailure();
    }
    return ret;
}

bool DcpAppletLauncherService::unregisterService ()
{
    QDBusConnection connection = QDBusConnection::sessionBus();

    connection.unregisterObject("/");
    bool ret = connection.unregisterService (serviceName);
    if (!ret) {
        QDBusError error = connection.lastError();
        qWarning ("Unregistering the service failed (%s): %s",
                qPrintable (error.name()), qPrintable (error.message()));
    }
    return ret;
}

void DcpAppletLauncherService::prestart ()
{
}

