/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include "pagefactory.h"

#include <QTime>
#include <DcpPage>
#include <DcpMainPage>
#include <DcpAppletPage>
#include <DcpAppletDb>
#include <DcpAppletIf>
#include <DcpAppletMetadata>
#include <DcpAppletObject>
#include <DcpAppletCategoryPage>
#include <MainTranslations>

#include <DuiApplication>
#include <DuiApplicationWindow>
#include <DuiAction>

#include "appleterrorsdialog.h"

#include "dcpdebug.h"


PageFactory *PageFactory::sm_Instance = 0;

PageFactory::PageFactory (): 
    QObject (),
    m_MainPage (0), 
    m_AppletCategoryPage (0)
{
    connect (DuiApplication::activeWindow (),
            SIGNAL(pageChanged(DuiApplicationPage *)),
            this, SLOT(pageChanged(DuiApplicationPage *)));
}

void
PageFactory::destroy()
{
    if (sm_Instance)
      delete sm_Instance;
    sm_Instance=0;
}
 
/*!
 * This slotz should be called only once, when the main page has been shown, so
 * we can access the applet database without forcing it to be loaded early. It
 * is also important, that we have a window on the screen, so we can show a
 * dialog if we want.
 */
void
PageFactory::mainPageFirstShown ()
{
    QStringList list;

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
    list = DcpAppletDb::instance()->appletNames();
    foreach (QString name, list) {
        DCP_DEBUG ("*** LAC applet '%s'", DCP_STR (name));
        DcpAppletObject *applet = DcpAppletDb::instance()->applet(name);
        connect (applet, SIGNAL (activate (int)),
                this, SLOT (appletWantsToStart (int)));
    }

    AppletErrorsDialog::showAppletErrors();
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
/* FIXME: this does not have any sense
        case PageHandle::APPLETCATEGORY: 
            page = createAppletCategoryPage(myHandle.id);
            break;
 */
        case PageHandle::APPLET:
            DCP_DEBUG ("## APPLET ##");
            page = createAppletPage (myHandle);
            break;

        default:
            Q_ASSERT(myHandle.id > PageHandle::CATEGORY_PAGEID_START
                     && myHandle.id < PageHandle::CATEGORY_PAGEID_END);
            page = createAppletCategoryPage (myHandle.id);
    }

    if (page) {
        page->setHandle (myHandle);

        if (page->isContentCreated ()) {
            page->reload ();
        }
    }

    return page;
}

/*!
 * Creates the main page that shows most of the applets.
 */
DcpPage *
PageFactory::createMainPage ()
{
    if (!m_MainPage) {
        m_MainPage = new DcpMainPage ();
        connect (m_MainPage, SIGNAL (firstShown(void)),
                this, SLOT(mainPageFirstShown (void)));

        registerPage (m_MainPage);
    }
    else
        m_MainPage->reload();

    return m_MainPage;
}

/*!
 * Creates an applet page for the default widget of the applet variant
 * represented by the metadata. Also will try to re-use the already existing
 * applet page referenced by the appletPage class member.
 */
DcpPage *
PageFactory::createAppletPage(
        PageHandle &handle)
{
    DcpAppletObject *applet = DcpAppletDb::instance()->applet (handle.param);

    /*
     * We do not cache appletpages (only with back mechanism).
     */
    DcpAppletPage* appletPage = new DcpAppletPage(applet, handle.widgetId);

    registerPage (appletPage);

    // we do this because we need to know if the page has a widget or not
    // TODO XXX
    appletPage->createContent();

    if (!appletPage->hasWidget() && !appletPage->hasError()) {
        // the applet does not provide a page (e.g. just a dialog)
        return 0;
    } else {
        handle.widgetId = appletPage->widgetId();
        return appletPage;
    }
}

/*!
 * Creates an applet category page, a page that shows a group of applets the
 * same way the main page shows applets.
 */
DcpPage *
PageFactory::createAppletCategoryPage (
        PageHandle::PageTypeId id)
{
    const DcpCategoryInfo *info;

    DCP_DEBUG ("*** id = %d", (int) id);

    info = dcp_find_category_info (id);
    if (!info) {
        DCP_WARNING ("Category info for page type %d not found.", (int) id);
        return 0;
    }

    if (!m_AppletCategoryPage){
        m_AppletCategoryPage = new DcpAppletCategoryPage (info);
        registerPage (m_AppletCategoryPage);
    } else {
        m_AppletCategoryPage->setCategoryInfo (info);
    }

    m_AppletCategoryPage->setTitleId (info->titleId);

    return m_AppletCategoryPage;
}

DcpPage*
PageFactory::currentPage ()
{
    DuiApplicationWindow* win = DuiApplication::activeApplicationWindow();
    if (win == 0) return 0;

    return qobject_cast<DcpPage*>(win->currentPage());
}

/*!
 * Creates a new page and sets as the current page.
 */
void 
PageFactory::changePage (const PageHandle &handle)
{
    DcpPage *page;

    /*
     * this prevents openning the same page multiple times,
     * if more signals are coming, for example if user clicks double
     */
    DcpPage *currentPage = this->currentPage();
    if (currentPage && 
            handle == currentPage->handle()) 
        return;
    
    if (tryOpenPageBackward(handle))
        return;

    DCP_DEBUG ("Creating page %s",
            DCP_STR (handle.getStringVariant()));
    /*
     * Creating the page with the given handle.
     */
    page = createPage (handle);
    if (!page) {
        DCP_DEBUG ("Page is not created...");
        return;
    }

    /*
     * Time to show the new page.
     *
     * Destroy policy: cached pages should not be destroyed,
     * applet pages should be destroyed only when coming back from them
     * to ensure there is no leak
     */
    if (handle.id == PageHandle::APPLET) {
        page->appear (DuiSceneWindow::DestroyWhenDismissed);
    } else {
        page->appear (DuiSceneWindow::KeepWhenDone);
    }

    if (DuiApplication::activeWindow ()) {
        DuiApplication::activeWindow ()->raise();
    }
}

void
PageFactory::appletWantsToStart (int pageId)
{
    DcpAppletObject *applet = qobject_cast<DcpAppletObject*> (sender());

    Q_ASSERT (applet);

    DCP_DEBUG ("Applet '%s' wants to start, widgetId: %d",
               DCP_STR(applet->metadata()->name()), pageId);

    PageHandle handle (PageHandle::APPLET, applet->metadata()->name(), pageId);
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

    if (page != m_MainPage) {
        // closeAction TODO XXX on language change, move into to the page?
        DuiAction *quitAction;

        quitAction = new DuiAction (qtTrId(DcpMain::quitMenuItemTextId), page);
        quitAction->setLocation(DuiAction::ApplicationMenuLocation);

        connect(quitAction, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

        // Add actions to page
        page->addAction(quitAction);
    }
}

/*!
 * This function will be called when the current page has been changed. It will
 * maintain a list of pages so the pagefactory will always know what pages are
 * in the stack. This is needed so the duicontrolpanel can page back to a
 * requested page.
 */
void
PageFactory::pageChanged (
        DuiApplicationPage *page)
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
PageFactory::tryOpenPageBackward (
        const PageHandle &handle)
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
        int s = m_Pages.size();

        DuiApplicationPage *duiPage = m_Pages.last();
        duiPage->dismiss();

        /*
         * This is rather unfortunate, but we need this becouse otherwise the
         * libdui will not refresh the screen correctly.
         */
        QTime dieTime = QTime::currentTime().addMSecs(250);
        while( QTime::currentTime() < dieTime )
        	QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        /*
         * This is a protection so we _never_ fall into an endless loop.
         */
        if (m_Pages.size() == s) {
            DCP_WARNING ("Could not close page.");
            return false;
        }
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

