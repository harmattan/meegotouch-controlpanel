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
#include "dcpappletlauncherif.h"

#include <MApplication>
#include <MApplicationWindow>
#include <QTimer>

// this also specifies if the applet views should be shown inprocess or outprocess
DcpAppletLauncherIf * PageFactory::sm_AppletLauncher = 0;

#include "dcpdebug.h"


PageFactory *PageFactory::sm_Instance = 0;

PageFactory::PageFactory (): 
    QObject ()
{
    connect (MApplication::activeWindow (),
            SIGNAL(pageChanged(MApplicationPage *)),
            this, SLOT(pageChanged(MApplicationPage *)));
    connect (MApplication::activeWindow (), SIGNAL(displayEntered()),
            this, SLOT(onDisplayEntered()));

    connect (DcpAppletDb::instance(), SIGNAL(appletLoaded(DcpAppletObject*)),
             this, SLOT(onAppletLoaded(DcpAppletObject*)));
}

PageFactory::~PageFactory ()
{
    delete sm_AppletLauncher;
    sm_Instance = 0;
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

        if (page->isContentCreated ()) {
            page->reload ();
        }
    }

    return page;
}


void PageFactory::preloadBriefReceiver ()
{
    // this loads the helper process a little bit earlier so that it can preload
    // some applets
    DcpRemoteBriefReceiver* receiver = DcpRemoteBriefReceiver::instance ();

    // this preloads an applet launcher process when the receiver has finished
    connect (receiver, SIGNAL (firstConnected()),
             this, SLOT (preloadAppletLauncher()));
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

    if (applet && applet->metadata() &&
        applet->metadata()->widgetTypeID() == DcpWidgetType::Button)
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
        return 0; // m_LastAppletPage.data();
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

    DcpAppletCategoryPage* appletCategoryPage = new DcpAppletCategoryPage (info);
    registerPage (appletCategoryPage);

#ifdef SKIP_CATEGORIES_WITH_ONE_APPLET
    /*
     * If the category contains one applet only, then we do not require the user
     * to click on that, but switch to the appletPage directly
     *
     */
    if (appletCategoryPage->appletCount() == 1)
    {
        DcpAppletMetadata* metadata = appletCategoryPage->appletMetadata(0);
        if (metadata) {
            return createAppletPage (metadata);
        }
    }
#endif

    return appletCategoryPage;
}

DcpPage*
PageFactory::currentPage ()
{
    MApplicationWindow* win = MApplication::activeApplicationWindow();
    if (win == 0) return 0;

    return qobject_cast<DcpPage*>(win->currentPage());
}

/*!
 * If applets should run out of process, this method ensures
 * (through dbus) that an appletlauncher instance will soon be
 * running.s
 */
void PageFactory::preloadAppletLauncher ()
{
    if (!sm_AppletLauncher) return;
    dcp_failfunc_unless (sm_AppletLauncher->isValid());
    sm_AppletLauncher->prestart ();
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
    bool runOutProcess = sm_AppletLauncher &&
        !binary.isEmpty() &&
        !db->isAppletLoaded (appletName) &&
        binary != "libdeclarative.so";

    /*
    qDebug ("running applet out of process: %d %d %d",
            !binary.isEmpty(), !db->isAppletLoaded (appletName),
            binary != "libdeclarative.so");
     */

    if (runOutProcess) {
        dcp_failfunc_unless (sm_AppletLauncher->isValid(), false);
        sm_AppletLauncher->appletPage (appletName);
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
    // if we could run it out of process then we do not change the page:
    if (handle.id == PageHandle::APPLET && maybeRunOutOfProcess(handle.param)) {
        return false;
    }

    DcpPage *page;

    // if it is already open, we switch back to it:
    if (tryOpenPageBackward(handle))
        return true;

    // we drop all the other pages if needed:
    if (dropOtherPages) {
        foreach (MApplicationPage* page, m_Pages) {
            delete page;
        }
        m_Pages.clear ();
    }

    /*
     * Creating the page with the given handle.
     */
    page = createPage (handle);
    if (!page) {
        DCP_DEBUG ("Page is not created...");
        return false;
    }

    MWindow* win = MApplication::instance()->activeWindow();
    dcp_failfunc_unless (win, false);

    /*
     * Time to show the new page.
     *
     * Destroy policy: cached pages should not be destroyed,
     * applet pages should be destroyed only when coming back from them
     * to ensure there is no leak
     */
    if (handle.id == PageHandle::APPLET) {
        page->appear (win,MSceneWindow::DestroyWhenDismissed);
    } else {
        page->appear (win,MSceneWindow::KeepWhenDone);
    }
    return true;
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
 * This function will be called when the current page has been changed. It will
 * maintain a list of pages so the pagefactory will always know what pages are
 * in the stack. This is needed so the duicontrolpanel can page back to a
 * requested page.
 */
void
PageFactory::pageChanged (MApplicationPage *page)
{
    if (m_Pages.empty()) {
        DCP_DEBUG ("List is empty, adding");
        m_Pages.append (page);
    } else if (m_Pages.size() >= 2 && 
            page == m_Pages.at(m_Pages.size() - 2)) {
        DCP_DEBUG ("Last page removed, removing...");
        m_Pages.takeLast();
    } else if (m_Pages.contains(page)) {
        DCP_WARNING ("It should not contain this page!");
    } else {
        DCP_DEBUG ("New page added!");
        m_Pages.append (page);
    }
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
    for (n = 0; n < m_Pages.size(); ++n) {
        page = qobject_cast<DcpPage*> (m_Pages[n]);

        if (page && page->handle() == handle) {
            foundAtIndex = n;
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
    while (m_Pages.size() > foundAtIndex + 1) {
        MApplicationPage *mPage = m_Pages.takeLast();
        mPage->dismiss();
    }

    /*
     * A simple debug tool to print the page stack.
     */
    #ifdef DEBUG
    for (n = 0; n < m_Pages.size(); ++n) {
        page = qobject_cast<DcpPage*> (m_Pages[n]);
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
    if (!m_Pages.isEmpty() &&
        qobject_cast<DcpAppletCategoryPage*>(m_Pages.last()))
    {
        preloadAppletLauncher();
    }
}

