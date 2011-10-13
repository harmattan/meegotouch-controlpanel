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
#include "dcpappletmanager.h"

#include <DcpAppletIf>
#include <DcpAppletMetadata>
#include <DcpAppletObject>
#include <DcpWidgetTypes>
#include "dcptranslationmanager.h"
#include "dcpappletlauncherif.h"
#include "duicontrolpanelif.h"
#include "categoryutils.h"
#include "dcpperflogger.h"

#include <MApplication>
#include <MComponentCache>
#include <MApplicationWindow>
#include <MPannableViewport>
#include <MSceneManager>
#include <QTimer>
#include <MSheet>

// this specifies if the applet views should be shown inprocess or outprocess
bool PageFactory::sm_IsInProcessModeEnabled = true;

#include "dcpdebug.h"


PageFactory *PageFactory::sm_Instance = 0;

PageFactory::PageFactory ():
    QObject (),
    m_AppletLauncher (0),
    m_Win (0),
    m_PageWithDelayedContent (0),
    m_AppletsRegistered (false),
    m_StartupState (NothingStarted),
    m_PageChangeDisabled (false),
    m_CloseMainProcessOnQuitEnabled (false)
{
    // Run onAppletLoaded for all the applets that are already loaded
    // and run it later for the applets loaded in the future.
    DcpAppletManager* mng = DcpAppletManager::instance();
    connect (mng, SIGNAL(appletLoaded(DcpAppletObject*)),
             this, SLOT(onAppletLoaded(DcpAppletObject*)));
    QList<DcpAppletObject*> loadedApplets = mng->loadedApplets();
    foreach (DcpAppletObject* applet, loadedApplets) {
        onAppletLoaded (applet);
    }

    if (mng->isMetadataPreloaded()) {
        onMetadataPreloaded();
        if (mng->isMetadataLoaded()) {
            onMetadataLoaded();
        }
    } else {
        connect (mng, SIGNAL(metadataPreloaded()), this, 
                 SLOT(onMetadataPreloaded()));
        connect (mng, SIGNAL(metadataLoaded()), this, SLOT(onMetadataLoaded()));
    }
}

void closeMainProcess ()
{
    static bool once = false;
    if (once) return;
    once = true;

    QDBusConnection connection = QDBusConnection::sessionBus();
    QDBusMessage message = QDBusMessage::createMethodCall(
        "com.nokia.DuiControlPanel",
        "/org/maemo/m", "com.nokia.MApplicationIf", "exit");

    // do not start it if it is not running:
    message.setAutoStartService (false);

    connection.asyncCall(message);
}


PageFactory::~PageFactory ()
{
    delete m_AppletLauncher;

    m_AppletLauncher = 0;
    sm_Instance = 0;
    if (m_Win) {
        // close help pages if any:
        closeHelpPage();

        // delete the m_Win if not already deleted:
        m_Win->close ();
    }

    if (m_CloseMainProcessOnQuitEnabled) {
        closeMainProcess();
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
PageFactory::createPage (const PageHandle &handle)
{
    PageHandle myHandle = handle;
    DcpPage *page = 0;
    DcpAppletManager *mng = DcpAppletManager::instance();

    // mainpage is also a categorypage, so we simplificate it here:
    if (myHandle.id == PageHandle::APPLETCATEGORY &&
        myHandle.param == DcpCategories::mainPageCategoryName ())
    {
        myHandle.id = PageHandle::MAIN;
    }

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
            if (mng->isMetadataPreloaded()) {
                page = createMainPage();
            } else {
                // preload applet desktops that are shown on the main view
                DcpDebug::start("preload_desktops");
                // diable page change until applet desktops are fully loaded
                m_PageChangeDisabled = true;
                mng->preloadMetadataAsync();
                if (m_PageWithDelayedContent) {
                    qWarning() << "request for re-creating a main page while another one is being built";
                    break;
                }
                const Category *mainCat = 
                    DcpCategories::instance()->mainPageCategory();
                m_PageWithDelayedContent = 
                    createAppletCategoryPageIncomplete(mainCat);
                page = m_PageWithDelayedContent;
            }
            break;

        case PageHandle::APPLET:
            DCP_DEBUG ("## APPLET ##");
            // applets are already registered if this is shown
            // from a category page or the single desktop file was loaded 
            page = createAppletPage (myHandle);
            break;

        case PageHandle::APPLETCATEGORY:
        default:
            const Category *info =
                DcpCategories::instance()->categoryById (myHandle.param);
            if (!info) break;

            /*
             * if appletAutoStart=1 then the metadatas need to be loaded
             * to know if we have to create a categorypage here or an appletPage
             * Mostly this means creating the appletpage anyway.
             */
            if (info->appletAutoStart() && !mng->isMetadataLoaded()) {
                mng->loadMetadata();
            }

            if (mng->isMetadataLoaded()) {
                page = createAppletCategoryPage (myHandle);
            } else {
                if (!mng->isMetadataLoadStarted()) {
                    mng->loadMetadataAsync();
                }
                if (m_PageWithDelayedContent) {
                    qWarning() << "request for re-creating a main page while another one is being built";
                    break;
                }
                m_PageWithDelayedContent = 
                    createAppletCategoryPageIncomplete(info);
                page = m_PageWithDelayedContent;
            }
    }

    if (page) {
        page->setHandle (myHandle);
    }

    return page;
}


void PageFactory::preloadBriefReceiver ()
{
    if (m_StartupState != NothingStarted) return;
    m_StartupState = BriefSupplierStarted;

    // this loads the helper process a little bit earlier so that it can preload
    // some applets
    DcpRemoteBriefReceiver* receiver = DcpRemoteBriefReceiver::instance ();

    // this preloads an applet launcher process when the receiver has finished
    if (receiver) {
        connect (receiver, SIGNAL (firstConnected()),
                 this, SLOT (preloadAppletLauncher()));
        receiver->startProcess ();
    }
}


void
PageFactory::completeCategoryPage ()
{
    DcpDebug::start("completeCategoryPage");
    if (m_PageWithDelayedContent) {
        DcpDebug::start("createBody");
        m_PageWithDelayedContent->createBody();
        registerPage (m_PageWithDelayedContent);
        DcpDebug::end("createBody");
        DCP_PERF_RECORD_EVENT("complete_category_page");
        m_PageWithDelayedContent = 0;
        QTimer::singleShot (0, this, SLOT(postCompleteCategoryPage()));
    } else {
        if (DcpAppletManager::instance()->mainPageAppletFound()) {
            // there's a main page applet which was not loaded in the 
            // preload phase, so we have to recreate the main view
            switchToMainPageWithPageDropping();
        }
    }
    DcpDebug::end("completeCategoryPage");

    // this starts the briefsupplier process:
    if (m_StartupState == NothingStarted) {
        QTimer::singleShot (0, this, SLOT(preloadBriefReceiver()));
    }
}

void
PageFactory::postCompleteCategoryPage ()
{
    DCP_PERF_RECORD_EVENT("complete_category_page_post");
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

    return mainPage;
}

/*!
 * Creates an empty category page, its content will be created later.
 */
DcpAppletCategoryPage *
PageFactory::createAppletCategoryPageIncomplete (const Category *category)
{
    DcpAppletCategoryPage *page = new DcpAppletCategoryPage(category);
    page->setDelayedContent(true);
    return page;
}

bool
PageFactory::hasPage () const
{
    // if we do not have a window, we do not have a page
    if (!m_Win) return false;

    // if the window does not have a page
    MApplicationPage* page = m_Win->currentPage();
    if (!page) return false;

    // if we have a precached appletpage only, we do not have a page
    DcpAppletPage* appletPage = qobject_cast<DcpAppletPage*>(page);
    if (appletPage && appletPage->applet() == 0) {
        return false;
    }

    // otherwise we have a page:
    return true;
}

bool
PageFactory::popupSheetIfAny (const PageHandle& handle)
{
    DcpAppletObject* applet =
        DcpAppletManager::instance()->applet (handle.param);
    if (!applet) return false;
    DcpAppletIf* appletIf = applet->applet();
    if (!appletIf) return false;

    // fixup unknown widgetid
    int widgetId = handle.widgetId < 0 ? applet->getMainWidgetId() :
                                         handle.widgetId;

    MSheet* sheet = applet->interfaceVersion() >= 9 ?
                        appletIf->constructSheet (widgetId) : 0;
    if (sheet) {
        if (hasPage ()) {
            // if we already have a visible window, we make the sheet appear on that:
            sheet->appear (m_Win, MSceneWindow::DestroyWhenDone);

        } else {
            // sheet is the first page, so its translation might not be loaded yet
            DcpTranslationManager::instance()->ensureTranslationLoaded (
                    applet->metadata());

            // if we do not have a page yet, we can only display the sheet on a
            // new window (applet launcher process) -> systemWide

            // if we have a precached hidden window, we delete it to avoid the
            // "page" openning like animation mix with the sheet animation
            if (m_Win) {
                m_Win->close();
                m_Win = 0;
            }

            // handle the window shown event:
            connect (sheet, SIGNAL (appeared ()), this, SIGNAL (windowShown()));

#ifdef SHEET_ORIENTATION_FIX
            sheet->setSystemwideModeOrientation (
                    MSheet::FollowsCurrentAppWindowOrientation);
#endif

            sheet->appearSystemwide (MSceneWindow::DestroyWhenDone);
        }
    }

    return sheet;
}


/*!
 * Creates an applet page for the default widget of the applet variant
 * represented by the metadata. Also will try to re-use the already existing
 * applet page referenced by the appletPage class member.
 */
DcpPage *
PageFactory::createAppletPage (PageHandle &handle)
{
    bool hasApplet = !handle.param.isEmpty();
    DcpAppletObject *applet = hasApplet ?
        DcpAppletManager::instance()->applet (handle.param) : 0;

    if (hasApplet && !applet) {
        DCP_WARNING ("Could not find the applet %s", qPrintable(handle.param));
        return 0;
    }

    /* If it has a separate executable, we do not have to create a page:
     */
    if (applet && applet->metadata() &&
            applet->metadata()->startApplicationCommand()) {
        enablePageChange (false);
        return 0;
    }

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
    if (applet && m_LastAppletPage && m_LastAppletPage->handle() == handle) {
        return 0;
    }

    /*
     * We might have an empty (== does not have applet set) appletPage preloaded,
     * if not, then we create one:
     */
    DcpAppletPage* appletPage = m_LastAppletPage;
    if (! appletPage || appletPage->applet()) {
        appletPage = new DcpAppletPage (applet, handle.widgetId);
        registerPage (appletPage);
    } else {
        appletPage->setApplet (applet, handle.widgetId);
    }

    // if the page is an empty preloaded appletPage
    // or the applet has provided a widget -> we are ready
    appletPage->createContent();
    if (!applet || appletPage->hasWidget()) {
        m_LastAppletPage = appletPage;
    } else {
        /*
         * If the plugin
         * - could not be loaded
         * - it does not provide a widget (eg. it has sheet instead)
         * or some error happened, we close the page.
         */
//      QTimer::singleShot (0, appletPage, SIGNAL(backButtonClicked ()));
        delete appletPage;
        appletPage = 0;
    }

    return appletPage;
}

void
PageFactory::preloadAppletPage ()
{
    // ensures that there is a window:
    window();

    // create the page:
    PageHandle handle;
    handle.id = PageHandle::APPLET;
    DcpPage* page = createPage (handle);
    dcp_failfunc_unless (page);
    appear (page);
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

/*!
 * \brief Changes to the main view of the specified applet.
 *
 * If the applet is not in the db yet, it searches also
 * in the default applet directories.
 * This gets called for example when an applet requests another
 * applet.
 */
bool
PageFactory::changeToAppletPage (const QString& appletName)
{
    PageHandle handle;
    handle.id = PageHandle::APPLET;
    handle.param = appletName;

    // this is needed to be able to find the desktop file also in the
    // applet launcher process (where the db only contains the running applet's
    // metadata). Since it is quite a rare case, we do it only here when needed
    DcpAppletManager* db = DcpAppletManager::instance();
    if (!db->containsName (appletName)) {
        db->addDesktopDir (DESKTOP_DIR);
        db->addDesktopDir (DESKTOP_DIR2);
        db->loadMetadata ();
    }

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
        DcpAppletMetadataList list = CategoryUtils::metadataList (info);

        if (list.count() == 1) {
            DcpAppletMetadata* metadata = list.at(0);
            if (metadata->hasMainView() || metadata->hasApplicationCommand()) {
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
    if (isInProcessApplets()) return;

    dcp_failfunc_unless (verifyAppletLauncherIsOk());

    m_AppletLauncher->prestart ();
}

bool PageFactory::maybeRunOutOfProcess (const QString& appletName)
{
    DcpAppletManager* mng = DcpAppletManager::instance();
    DcpAppletMetadata* metadata = mng->metadata(appletName);
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
        !mng->isAppletLoaded (appletName) &&
        binary != "libdeclarative.so" &&
        binary != "declarative";

    if (runOutProcess) {
        dcp_failfunc_unless (verifyAppletLauncherIsOk(), false);
        m_AppletLauncher->appletPage (metadata->fileName());
    }

    return runOutProcess;
}


bool PageFactory::verifyAppletLauncherIsOk()
{
    dcp_failfunc_unless (!isInProcessApplets(), false);
    if (!m_AppletLauncher) {
        m_AppletLauncher = new DcpAppletLauncherIf();
    }
    return m_AppletLauncher->isValid();
}


/*!
 * Creates a new page and sets as the current page.
 *
 * Returns true if the page change was successful or was done in a separate
 * process, otherwise it returns false.
 */
bool
PageFactory::changePage (const PageHandle &handle, bool dropOtherPages)
{
    // this prevents handling multiple page change requests in very short time
    if (m_PageChangeDisabled) return false;

    if (dropOtherPages) {
        closeHelpPage();
        // in outprocess mode we should also drop pages running in other instances
        // (if any):
        if (!isInProcessApplets()) {
            emit resetAppletLauncherProcesses ();
        }
    }

    // if we could run it out of process then we do not change the page:
    if (handle.id == PageHandle::APPLET) {
        if (maybeRunOutOfProcess(handle.param)) {
            enablePageChange (false);
            return false;
        }

        if (popupSheetIfAny (handle)) {
            return true;
        }
    }

    DcpPage *page;

    // we drop the window if needed
    if (dropOtherPages) {
        // This seems a bit stupid, but:
        // we have to create a new window if dcp is minimized because otherwise
        // - animation is wrong if dcp is covered by a chained win
        // - already open dialogs are not closed
        // But, if we are not minimized, and just reopening the current page
        // we should not create new win, because if our window is a chain
        // parent, it has to stay that way for proper page animation
        if (m_Win && !m_Win->isInSwitcher() && tryOpenPageBackward(handle)) {
            return true;
        }
        newWin ();

    // if it is already open, we switch back to it
    } else if (tryOpenPageBackward(handle)) {
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
    if (!m_Win) return;
    m_Win->show();
    m_Win->activateWindow();
    m_Win->raise();
    qApp->flush();
    DCP_PERF_RECORD_EVENT("main_window_raised");
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
    DCP_PERF_RECORD_EVENT("page_appearing");
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

    if (qobject_cast<DcpAppletPage*>(page)) {
        connect (page, SIGNAL(mainPageIconClicked ()), this,
                 SLOT (newMainPageInSeparateProcess()));
    } else {
        connect (page, SIGNAL(mainPageIconClicked ()), this,
                 SLOT (switchToMainPageWithPageDropping ()));
    }
}

void PageFactory::switchToMainPageWithPageDropping ()
{
    DcpPage* page = createPage (PageHandle(PageHandle::MAIN));
    dcp_failfunc_unless (page);

    page->setEscapeMode (MApplicationPageModel::EscapeCloseWindow);
    page->appear ();

    // destroy all pages after the animation has finished:
    connect (page, SIGNAL (appeared()), this, SLOT(destroyPageHistory()));
}

void PageFactory::destroyPageHistory()
{
    if (!m_Win) return;
    MSceneManager* manager = m_Win->sceneManager();
    if (!manager) return;
    foreach (MSceneWindow* page, manager->pageHistory()) {
        delete page;
//      this does not do the job it seems:
//      manager->dismissSceneWindowNow (page);
    }
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
    return pageList;
}

void PageFactory::onMetadataLoaded ()
{
    DcpDebug::end("applet reg");
    m_AppletsRegistered = true;
    m_PageChangeDisabled = false;
    completeCategoryPage();
}

void PageFactory::onMetadataPreloaded ()
{
    DcpDebug::end("preload_desktops");
    completeCategoryPage();

    DcpAppletManager* mng = DcpAppletManager::instance();
    if (!mng->isMetadataLoaded()) {
        if (!mng->isMetadataLoadStarted()) {
            // start loading the other desktop files
            DcpDebug::start("applet reg");
            mng->loadMetadataAsync(); 
        }
    }
}


inline bool pagePreventsQuit (MSceneWindow* mPage)
{
    // applet page can prevent quit:
    DcpPage* page = qobject_cast<DcpPage*>(mPage);
    if (page && page->preventQuit()) {
        return true;
    }
    return false;
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
    /*
     * We try to find the requested page in the stack.
     */
    DcpPage* currentPage = this->currentPage();

    if (!currentPage) return false;

    if (currentPage && currentPage->handle() == handle) {
        // fount it: it is the current page
        return true;
    }

    int foundAtIndex = -1;
    QList< MSceneWindow * > history = pageHistory();
    for (int n = 0; n < history.count(); n++) {
        DcpPage *page = qobject_cast<DcpPage*> (history.at(n));

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

    // if the current page would like to prevent its closing, we do nothing:
    if (pagePreventsQuit (currentPage)) {
        return true;
    }

    /*
     * We close all the pages that are above the requested page.
     */
    // first we delete all pages between the found and the current:
    while (history.count() > foundAtIndex+1) {
        MSceneWindow *mPage = history.takeLast();

        // the page can refuse its closing, then we stop:
        if (pagePreventsQuit (mPage)) {
            break;
        }
        mPage->deleteLater();
    }

    // do the animation of switching back
    // this had to be sheduled after the deleteLater calls
    QTimer::singleShot (0, currentPage, SLOT(dismiss()));

    return true;
}

void PageFactory::setInProcessApplets (bool inProcess)
{
    sm_IsInProcessModeEnabled = inProcess;
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
        m_Win->close();
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

    // filters out unnecessery retranslate events:
    m_Win->installEventFilter(DcpTranslationManager::instance());
    // filters out close event if the page would refuse it:
    m_Win->installEventFilter(this);
}

/*! This function is a filter on the MApplicationWindow
 * Its purpose is to filter out close event in case the page would refuse it.
 */
bool PageFactory::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Close) {
        if (pagePreventsQuit (currentPage())) {
            event->ignore ();
            return true;
        }
    } else if (event->type() == QEvent::Show) {
        emit windowShown ();
    }
    // standard event processing
    return QObject::eventFilter(obj, event);
}

/*!
 * Disables page changing until a little time.
 */
void PageFactory::enablePageChange(bool enable)
{
    if (enable == !m_PageChangeDisabled) return;

    m_PageChangeDisabled = !enable;
    if (m_PageChangeDisabled) {
        QTimer::singleShot (2000, this, SLOT(enablePageChange()));
    }

    // does the same disabling for the back button (NB#272868):
    DcpPage* page = this->currentPage();
    if (page) {
        page->setPreventQuit (m_PageChangeDisabled);
    }
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

    // do not start userguide if it is not running:
    message.setAutoStartService (false);

    connection.asyncCall(message);
}


void
PageFactory::newMainPageInSeparateProcess()
{
    enableCloseMainProcessOnQuit (false);
    DuiControlPanelIf iface;
    if (iface.isValid()) {
        iface.mainPage();
    }
}

void PageFactory::enableUpdates (bool enable)
{
    window()->setUpdatesEnabled (enable);
}

