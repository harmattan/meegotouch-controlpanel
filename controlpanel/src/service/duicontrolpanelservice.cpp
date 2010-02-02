/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include "duicontrolpanelservice.h"
#include "pagefactory.h"

#include "duicontrolpanelifadaptor.h"
#include <QtDebug>

static const char* serviceName = "com.nokia.DuiControlPanel";

#define DEBUG
#include "dcpdebug.h"

DuiControlPanelService::DuiControlPanelService ()
{
    DCP_DEBUG ("");
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
DuiControlPanelService::appletPage (
        const QString& appletName)
{

    DCP_DEBUG ("");
    PageHandle handle (PageHandle::APPLET, appletName, 0, true);
    sheduleStart(handle);

    // TODO this hack prevents a servicefw issue, that the app does not get the
    // first query Result means nothing...
    return true;
}

void
DuiControlPanelService::sheduleStart (
                const PageHandle &handle)
{
    DCP_DEBUG ("");
    if (m_StartPage == 0) {
        PageFactory::instance()->changePage(handle);
    } else {
        m_StartPage->id = handle.id;
        m_StartPage->param = handle.param;
    }
}

void
DuiControlPanelService::categoryPage (
        const QString& category)
{
    DCP_DEBUG ("");
    PageHandle handle;
    handle.id = PageHandle::APPLETCATEGORY;
    handle.param = category;
    sheduleStart(handle);
}

void
DuiControlPanelService::mainPage()
{
    DCP_DEBUG ("");
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
    DCP_DEBUG ("");
    // createStartPage should not be called twice
    Q_ASSERT(m_StartPage);  
    PageFactory::instance()->changePage(*m_StartPage);
    delete m_StartPage;
    m_StartPage = 0;
}

