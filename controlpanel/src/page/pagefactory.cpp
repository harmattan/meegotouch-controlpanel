/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel.
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include <QtDBus>
#include "pagefactory.h"

#include "dcpappletpage.h"
#include "dcpappletcategorypage.h"
#include "dcpcategories.h"
#include "category.h"
#include "dcpremotebriefreceiver.h"

#include <DcpAppletDb>
#include <DcpAppletIf>
#include <DcpAppletMetadata>
#include <DcpAppletObject>
#include <DcpWidgetTypes>
#include <DcpRetranslator>
#include "dcpappletlauncherif.h"

#include <MApplication>
#include <MComponentCache>
#include <MApplicationWindow>
#include <MPannableViewport>
#include <MSceneManager>
#include <QTimer>

// this also specifies if the applet views should be shown inprocess or outprocess
DcpAppletLauncherIf * PageFactory::sm_AppletLauncher = 0;

#include "dcpdebug.h"


PageFactory *PageFactory::sm_Instance = 0;

PageFactory::PageFactory ():
    QObject (),
    m_Win (0)
{
    // run appletLoaded for all applets:
    DcpAppletDb* db = DcpAppletDb::instance();
    connect (db, SIGNAL(appletLoaded(DcpAppletObject*)),
             this, SLOT(onAppletLoaded(DcpAppletObject*)));
    QList<DcpAppletObject*> loadedApplets = db->loadedApplets();
    foreach (DcpAppletObject* applet, loadedApplets) {
        onAppletLoaded (applet);
    }
}

PageFactory::~PageFactory ()
{
    delete sm_AppletLauncher;

    sm_AppletLauncher = 0;
    sm_Instance = 0;
    if (m_Win) {
        // close help pages if any:
        closeHelpPage();

        // delete the m_Win if not already deleted:
        m_Win->close ();
    }
}

void
PageFactory::destroy()
{
    if (sm_Instance)
      delete sm_Instance;
    sm_Instance = 0;
}


/*
 * Whenever someone wants an applet to be activated (started, shown on the
 * screen atc.) a signal is sent to the applet's metadata. Then the applets
 * metadata will send a signal, so the pagefactory can open a new page for
 * it.
 *
 * If an applet wants to start up an other applet we also got a signal here
 * so we can start up the applet. In this case we will have an external
 * referer for the applets main page.
 */
 void
PageFactory::onAppletLoaded (DcpAppletObject *applet)
{
    connect (applet, SIGNAL (activate (int)),
             this, SLOT (appletWantsToStart (int)));
    connect (applet, SIGNAL (requestPluginActivation (QString)),
             this, SLOT (changeToAppletPage (QString)));
}


PageFactory * 
PageFactory::instance ()
{
    if (!sm_Instance)
        sm_Instance = new PageFactory();
    return sm_Instance;
}

DcpPage* 
PageFactory::createPage (
        const PageHandle &handle)
{
    PageHandle myHandle = handle;
    DcpPage *page = 0;

    DCP_DEBUG ("****************************");
    DCP_DEBUG ("*** handle = %s", DCP_STR (myHandle.getStringVariant()));
    DCP_DEBUG ("****************************");
    switch (myHandle.id) {
        case PageHandle::NOPAGE:
        case PageHandle::MAIN:
            /*
             * Creating the main page. If the ID is is PageHandle::NOPAGE we
             * also create the main page, for which we can handle pages that has
             * no valid referer. These pages are going to open the main page
             * when closed.
             */
            DCP_DEBUG ("## MAIN ##");
            page = createMainPage();
            break;
        case PageHandle::APPLET:
            DCP_DEBUG ("## APPLET ##");
            page = createAppletPage (myHandle);
            break;

        case PageHandle::APPLETCATEGORY:
        default:
            page = createAppletCategoryPage (myHandle);
    }

    if (page) {
        page->setHandle (myHandle);
    }

    return page;
}


void PageFactory::preloadBriefReceiver ()
{
    // this loads the helper process a little bit earlier so that it can preload
    // some applets
    DcpRemoteBriefReceiver* receiver = DcpRemoteBriefReceiver::instance ();

    // this preloads an applet launcher process when the receiver has finished
    if (receiver) {
        connect (receiver, SIGNAL (firstConnected()),
                 this, SLOT (preloadAppletLauncher()));
    }
}

void PageFactory::mainPageFirstShown()
{
    MApplicationPage* mainPage = qobject_cast<MApplicationPage*>(sender());
    if (!mainPage) return;

    // disconnect so as not to receive this event any more:
    disconnect (mainPage, SIGNAL(appeared()),
                this, SLOT(mainPageFirstShown()));

    // unfortunately appeared signal comes before the page becomes visible on
    // the screen so this function gets called after a delay to start some
    // heavier
    QTimer::singleShot (1000, this, SLOT(preloadBriefReceiver()));
}

/*!
 * Creates the main page that shows most of the applets.
 */
DcpPage *
PageFactory::createMainPage ()
{
    DcpPage* mainPage = new DcpAppletCategoryPage (
                DcpCategories::instance()->mainPageCategory());
    registerPage (mainPage);
    connect (mainPage, SIGNAL(appeared()),
             this, SLOT(mainPageFirstShown()));

    return mainPage;
}

/*!
 * Creates an applet page for the default widget of the applet variant
 * represented by the metadata. Also will try to re-use the already existing
 * applet page referenced by the appletPage class member.
 */
DcpPage *
PageFactory::createAppletPage (PageHandle &handle)
{
    DcpAppletObject *applet = DcpAppletDb::instance()->applet (handle.param);

    /*
     * If the applet does not have a main view then we show the page which
     * contains its briefview instead.
     */
    if (applet && applet->metadata() && !applet->metadata()->hasMainView())
    {
        PageHandle handle (PageHandle::APPLETCATEGORY, applet->metadata()->category());
        return createAppletCategoryPage(handle);
    }

    /*
     * this prevents openning the same page multiple times,
     * if more signals are coming, for example if user clicks double
     */
    if (applet && handle.widgetId < 0) { // fixup unknown widgetid for the comparing
        handle.widgetId = applet->getMainWidgetId();
    }
    if (m_LastAppletPage && m_LastAppletPage->handle() == handle) {
        return 0;
    }

    /*
     * We do not cache appletpages (only with back mechanism).
     */
    DcpAppletPage* appletPage = new DcpAppletPage(applet, handle.widgetId);
    registerPage (appletPage);

    // we do this because we need to know if the page has a widget or not
    // TODO
    appletPage->createContent();

    if (!appletPage->hasWidget() && !appletPage->hasError()) {
        // the applet does not provide a page (e.g. just a dialog)
        return 0;
    } else {
        handle.widgetId = appletPage->widgetId();
        m_LastAppletPage = appletPage;
        return appletPage;
    }
}


/*!
 * Creates the applet page based on the applet's metadata
 */
DcpPage*
PageFactory::createAppletPage (DcpAppletMetadata* metadata)
{
    PageHandle handle;
    handle.id = PageHandle::APPLET;
    handle.param = metadata->name();
    return createAppletPage (handle);
}

bool
PageFactory::changeToAppletPage (const QString& appletName)
{
    PageHandle handle;
    handle.id = PageHandle::APPLET;
    handle.param = appletName;
    return changePage (handle);
}

/*!
 * Creates an applet category page, a page that shows a group of applets the
 * same way the main page shows applets.
 */
DcpPage *
PageFactory::createAppletCategoryPage (const PageHandle& handle)
{
    PageHandle::PageTypeId id = handle.id;
    dcp_failfunc_unless (id == PageHandle::APPLETCATEGORY, 0);

    const Category *info =
        DcpCategories::instance()->categoryById (handle.param);

    if (!info) {
        DCP_WARNING ("Category info for page %s not found.",
                     qPrintable (handle.param));
        return 0;
    }

    /*
     * If the category contains one applet only, then we do not require the user
     * to click on that, but switch to the appletPage directly
     * This functionality has to be enabled from the category config file.
     */
    if (info->appletAutoStart() && info->children().count() == 0) {
        // TODO might make sense to move this to class Category
        DcpAppletDb* db = DcpAppletDb::instance();
        bool withUncategorized = info->containsUncategorized();
        DcpAppletMetadataList list = db->listByCategory (info->referenceIds(),
                    withUncategorized ? DcpCategories::hasCategory : NULL);
        if (list.count() == 1) {
            DcpAppletMetadata* metadata = list.at(0);
            if (metadata->hasMainView()) {
                changeToAppletPage (metadata->name());
                return 0;
            }
        }
    }

    DcpAppletCategoryPage* appletCategoryPage = new DcpAppletCategoryPage (info);
    registerPage (appletCategoryPage);

    return appletCategoryPage;
}

DcpPage*
PageFactory::currentPage ()
{
    if (m_Win == 0) return 0;
    return qobject_cast<DcpPage*>(m_Win->currentPage());
}

/*!
 * If applets should run out of process, this method ensures
 * (through dbus) that an appletlauncher instance will soon be
 * running.s
 */
void PageFactory::preloadAppletLauncher ()
{
#if 1
    if (isInProcessApplets()) return;
    dcp_failfunc_unless (sm_AppletLauncher->isValid());
    sm_AppletLauncher->prestart ();
#endif
}

bool PageFactory::maybeRunOutOfProcess (const QString& appletName)
{
    DcpAppletDb* db = DcpAppletDb::instance();
    DcpAppletMetadata* metadata = db->metadata(appletName);
    if (!metadata || !metadata->isValid()) return false;
    QString binary = metadata->binary();

    /* 
     * Only run out of process if:
     *    - applet launcher interface is created (means: we have to)
     *    - we have an applet binary (shared object)
     *    - the shared object is not already loaded into the process
     *    - the applet is not declarative
     */
    bool runOutProcess = !isInProcessApplets() &&
        !binary.isEmpty() &&
        !db->isAppletLoaded (appletName) &&
        binary != "libdeclarative.so";

    if (runOutProcess) {
        dcp_failfunc_unless (sm_AppletLauncher->isValid(), false);
        sm_AppletLauncher->appletPage (metadata->fileName());
    }

    return runOutProcess;
}


/*!
 * Creates a new page and sets as the current page.
 *
 * Returns true if the page change was successful, otherwise it
 * returns false.
 */
bool
PageFactory::changePage (const PageHandle &handle, bool dropOtherPages)
{
    if (dropOtherPages) {
        closeHelpPage();
        // in outprocess mode we should also drop pages running in other instances
        // (if any):
        if (!isInProcessApplets()) {
            emit resetAppletLauncherProcesses ();
        }
    }

    // if we could run it out of process then we do not change the page:
    if (handle.id == PageHandle::APPLET && maybeRunOutOfProcess(handle.param)) {
        return false;
    }

    DcpPage *page;

    // we drop the window if needed
    if (dropOtherPages && !isCurrentPage (handle)) {
        newWin ();
    }

    // if it is already open, we switch back to it:
    if (tryOpenPageBackward(handle)) {
        return true;
    }

    /*
     * Creating the page with the given handle.
     */
    page = createPage (handle);
    if (!page) {
        DCP_DEBUG ("Page is not created...");
        return false;
    }

    DcpDebug::end("activate_applet");

    /*
     * Time to show the new page.
     */
    appear (page);
    return true;
}

bool
PageFactory::isCurrentPage (const PageHandle &handle)
{
    DcpPage* page = currentPage();
    if (page && page->handle() == handle) {
        return true;
    }
    return false;
}

void
PageFactory::raiseMainWindow()
{
    MApplicationWindow* win = window();
    dcp_failfunc_unless (win);
    win->show();
    win->raise();
    win->activateWindow();
}

void
PageFactory::appear (MApplicationPage* page)
{
    dcp_failfunc_unless (page);
    MApplicationWindow* win = window ();
    dcp_failfunc_unless (win);

    MApplicationPage* currentPage = win->currentPage();
    if (currentPage == 0 || currentPage == page) {
        // make it appear without animation:
        MSceneManager* smanager = win->sceneManager();
        dcp_failfunc_unless (smanager);
        smanager->appearSceneWindowNow (page, MSceneWindow::DestroyWhenDismissed);
    } else {
        // with animation:
        page->appear (win,MSceneWindow::DestroyWhenDismissed);
    }
}

void
PageFactory::appletWantsToStart (int pageId)
{
    DcpAppletObject *applet = qobject_cast<DcpAppletObject*> (sender());

    dcp_failfunc_unless (applet);

    QString appletName = applet->metadata()->name();

    qDebug ("Applet '%s' wants to start, widgetId: %d",
            DCP_STR(appletName), pageId);

    PageHandle handle (PageHandle::APPLET, appletName, pageId);
    changePage (handle);
}

/*!
 * This function does all the common stuff that is needed to be done when a new 
 * page is created. The function connects to signals and adds the 'Quit' action
 * to the menu of the page.
 */
void 
PageFactory::registerPage (
        DcpPage* page)
{
    connect (page, SIGNAL(openSubPage (const PageHandle &)), 
            this, SLOT(changePage(const PageHandle &)));
}


/*!
 * Returns the page history including the current page
 */
QList< MSceneWindow * > PageFactory::pageHistory ()
{
    QList< MSceneWindow * > pageList;
    if (!m_Win) return pageList;
    MSceneManager* manager = m_Win->sceneManager();
    if (!manager) return pageList;
    pageList = manager->pageHistory();
    pageList.append (m_Win->currentPage()); // TODO might want to avoid this (PERF)
    return pageList;
}

/*!
 * This function will try to activate the page by dismissing pages, that is if a
 * page with the given handle is already opened the function will dismiss all
 * the pages that are on the top of the requested page.
 *
 * This function will return true if the operation was successfull, the
 * requested page is on top.
 */
bool
PageFactory::tryOpenPageBackward (const PageHandle &handle)
{
    DcpPage *page;
    int foundAtIndex = -1;
    int n;

    /*
     * We try to find the requested page in the stack.
     */
    QList< MSceneWindow * > history = pageHistory();
    for (n = 0; n < history.count(); n++) {
        page = qobject_cast<DcpPage*> (history.at(n));

        if (page && page->handle() == handle) {
            foundAtIndex = n;

            // move the page to its top
            MPannableViewport* pannv = page->pannableViewport();
            if (pannv) pannv->setPosition (QPointF(0,0));
            break;
        }
    }

    /*
     * If not found we return false. This means a new page has to be created in
     * order to open the requested applet widget.
     */
    if (foundAtIndex == -1) {
        DCP_DEBUG ("Page not found, returning false");
        return false;
    }

    /*
     * We close all the pages that are above the requested page.
     */
    while (history.count() > foundAtIndex+1) {
        MSceneWindow *mPage = history.takeLast();

        // the page can refuse its closing, then we stop:
        if (!mPage->dismiss ()) {
            break;
        }
    }

    /*
     * A simple debug tool to print the page stack.
     */
    #ifdef DEBUG
    for (n = 0; n < history.size(); ++n) {
        page = qobject_cast<DcpPage*> (history[n]);
        DCP_DEBUG ("page[%d] = %s", n,
                DCP_STR(page->handle().getStringVariant()));
    }
    #endif

    return true;
}

void PageFactory::setInProcessApplets (bool inProcess)
{
    if (!inProcess && !sm_AppletLauncher) {
        sm_AppletLauncher = new DcpAppletLauncherIf();
    } else
    if (inProcess && sm_AppletLauncher) {
        delete sm_AppletLauncher;
        sm_AppletLauncher = 0;
    }
}

void PageFactory::onDisplayEntered ()
{
    // we preload an appletlauncher instance in case we are again
    // on the categorypage (most likely the user tapped the back button
    // on an applet)
    if (qobject_cast<DcpAppletCategoryPage*>(currentPage()))
    {
        preloadAppletLauncher();
    }
}

MApplicationWindow* PageFactory::window ()
{
    if (!m_Win && !MApplication::windows().isEmpty()) {
        m_Win =
            qobject_cast<MApplicationWindow*>(MApplication::windows().at(0));
    }
    if (!m_Win) newWin();
    return m_Win;
}

void PageFactory::newWin ()
{
    if (!m_Win && !MApplication::windows().isEmpty()) {
        m_Win =
            qobject_cast<MApplicationWindow*>(MApplication::windows().at(0));
    }
    if (m_Win) {
        m_LastAppletPage = 0;
        delete m_Win;
        m_Win = 0;
    }

#ifndef DISABLE_LAUNCHER
    m_Win = MComponentCache::mApplicationWindow();
#else // DISABLE_LAUNCHER
    m_Win = new MApplicationWindow();
#endif
    m_Win->setAttribute (Qt::WA_DeleteOnClose, true);

#ifndef FREE_ORIENTATION
    // Fixes the orientation to portrait mode
    m_Win->setPortraitOrientation();
    m_Win->setOrientationLocked(true);
#endif // FREE_ORIENTATION

    m_Win->setStyleName ("CommonApplicationWindowInverted");

    // Connect some signals for the new window:
    connect (m_Win, SIGNAL(displayEntered()), this, SLOT(onDisplayEntered()));

    // filters out unnecessery retranslate events:
    m_Win->installEventFilter(DcpRetranslator::instance());
    // filters out close event if the page would refuse it:
    m_Win->installEventFilter(this);
}

/*! This function is a filter on the MApplicationWindow
 * Its purpose is to filter out close event in case the page would refuse it.
 */
bool PageFactory::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Close) {
        DcpAppletPage* appletPage = qobject_cast<DcpAppletPage*>(currentPage());
        if (appletPage && appletPage->preventQuit()) {
            event->ignore ();
            return true;
        }
    }
    // standard event processing
    return QObject::eventFilter(obj, event);
}

void
PageFactory::closeHelpPage()
{
    if (!m_Win) return;

    QDBusConnection connection = QDBusConnection::sessionBus();
    QDBusMessage message = QDBusMessage::createMethodCall(
        "com.nokia.userguide", "/", "com.nokia.UserGuideIf", "closePage");
    QList<QVariant> args;
    args.append((uint)m_Win->winId());
    message.setArguments(args);

    connection.asyncCall(message);
}

