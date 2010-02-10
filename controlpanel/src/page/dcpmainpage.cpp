/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpmainpage.h"

#include <QtDebug>
#include <DuiApplication>

#include <DcpMainCategory>
#include <Pages>
#include <DcpApplet>
#include <QGraphicsLinearLayout>

#include "dcpdescriptioncomponent.h"
#include "dcpcategorycomponent.h"
#include "maintranslations.h"

#define DEBUG
#include "../../../lib/src/dcpdebug.h"

/*!
 * \class DcpMainPage
 * \brief The main page of duicontrolpanel.
 *
 * Displays a list of the applet categories and emits a signal if one of them is
 * to be opened.  Also has a recent used items list at the top, which contains
 * buttons to directly access the most commonly used applets (without searching
 * for them in the categories.
 */
DcpMainPage::DcpMainPage() :
    DcpPage (), 
    m_RecentlyComp (0),
    m_HasContent (false)
{
    setEscapeButtonMode (DuiEscapeButtonPanelModel::CloseMode);
    connect (this, SIGNAL(windowShown()),
            this, SLOT(shown()));

    setTitle (qtTrId(DcpMain::settingsTitleId));
}


void
DcpMainPage::shown ()
{
    DCP_DEBUG ("##################################################");
    DCP_DEBUG ("### Main page has been shown #####################");
    DCP_DEBUG ("##################################################");

    if (m_HasContent)
        return;
    
    createContentsLate ();
    m_HasContent = true;
    
    emit firstShown ();
}

/*!
 * Creates the empty category containers inside the main page.
 */
void
DcpMainPage::createContent ()
{
    DCP_DEBUG ("");
    QGraphicsLinearLayout *layout;
    DcpPage::createContent ();

    layout = mainLayout ();

    /*
     * Most recent used items. If this category is empty it is not visible so we
     * will add to the layout later.
     * Use 
     * # gconftool-2 --recursive-unset /apps/duicontrolpanel/usagecount
     * to test this piece of code.
     */
    m_RecentlyComp = new DcpCategoryComponent (
            0,
            DcpApplet::MostUsedCategory,
            DcpMain::mostRecentUsedTitleId);
    layout->addItem(m_RecentlyComp);

    /*
     * All the other categories.
     */
    for (int i = 0;; i++) {
        DcpCategoryComponent   *component;
        const DcpCategoryInfo  *info;

        info = &DcpMain::CategoryInfos[i];
        if (info->titleId == 0)
             break;

        component = new DcpCategoryComponent (0, info);
        layout->addItem (component);
    }

    setEscapeButtonMode (DuiEscapeButtonPanelModel::CloseMode);
    retranslateUi ();
}

/*!
 * The main page is usually the first page to start, so we want to show it as
 * soon as possible. First we show the page without the applet brief widgets in
 * it, then when it appeared on the screen we load the content. This second step
 * is implemented here.
 */
void
DcpMainPage::createContentsLate ()
{
    QGraphicsLinearLayout *layout;

    DCP_DEBUG ("");

    layout = mainLayout ();

    /* 
     * recently used item load finish will start the load process of the other
     * containers:
     */
    m_LoadedContainers = 0;
    connect (m_RecentlyComp, SIGNAL(loadFinished()),
             this, SLOT(loadNextContainer()));

    m_RecentlyComp->createContentsLate ();

    /*
     * Most recent used items. If this category is empty it is not visible so we
     * will add to the layout later.
     * Use 
     * # gconftool-2 --recursive-unset /apps/duicontrolpanel/usagecount
     * to test this piece of code.
     */
    if (!m_RecentlyComp->hasLoadingItems()) {
        mainLayout ()->removeItem (m_RecentlyComp);
        m_RecentlyComp->hide();
    }
}

void
DcpMainPage::loadNextContainer ()
{
    // disconnect last item
    disconnect (sender(), SIGNAL(loadFinished()),
                this, SLOT(loadNextContainer()));

    QGraphicsLinearLayout* layout = mainLayout();
    m_LoadedContainers++;
    if (layout->count() <= m_LoadedContainers) {
        // finished loading the page
        return;
    }

    DcpCategoryComponent* comp =
       dynamic_cast<DcpCategoryComponent*> (layout->itemAt(m_LoadedContainers));

    // handle next item:
    connect (comp, SIGNAL(loadFinished()),
             this, SLOT(loadNextContainer()));
    comp->createContentsLate ();
}

void
DcpMainPage::retranslateUi ()
{
    QGraphicsLinearLayout *layout = mainLayout();

    DCP_DEBUG ("");
    /*
     * The title of the main window.
     */
    setTitle (qtTrId(DcpMain::settingsTitleId));

    /*
     * All the category component capable to retlanslate the UI for itself e.g.
     * they know the title id, they can localize themselves.
     * Please note that we only retlanslate those that are currently visible.
     */
    for (int i = 0; i < layout->count(); ++i) {
        DcpCategoryComponent* comp =
            dynamic_cast<DcpCategoryComponent*> (layout->itemAt(i));

        comp->retranslateUi();
    }
    // no need to update briefs, they take care of themselves
}


void 
DcpMainPage::reload ()
{
    DCP_DEBUG ("WARNING: RELOADING");
    /*
     * Refreshing the 'most recently used' category. This category category will
     * be turned off when it just become empty (a highly unlikely event), and
     * will be turned on if it was empty and now become non-empty.
     */
    if (m_RecentlyComp) {
        bool was_visible;

        was_visible = m_RecentlyComp->getItemCount() != 0;

        m_RecentlyComp->reload ();
        bool should_be_visible = m_RecentlyComp->hasLoadingItems();

        /*
         * If the 'most recetly used' category is empty we hide it, if not empty
         * we show it.
         */
        if (!should_be_visible && was_visible) {
            mainLayout ()->removeItem (m_RecentlyComp);
            m_RecentlyComp->hide();
        } else if (should_be_visible && !was_visible) {
            mainLayout ()->insertItem (0, m_RecentlyComp);
            m_RecentlyComp->show();
            m_RecentlyComp->retranslateUi ();
        }
    }

    /*
     * DcpBriefWidget takes care of all the other things
     * FIXME: No, I'm not sure about that.
     * I do think so: DcpBriefWidget::showEvent()
     */
    DcpPage::reload ();
}

// if clicked fast, back button can be pressed instead of close
void 
DcpMainPage::back()
{
    qApp->quit();
}

