/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpmainpage.h"

#include <QtDebug>
#include <DuiApplication>
#include <DcpBriefComponent>
#include <DcpSingleComponent>
#include <DcpMainCategory>
#include <Pages>
#include <DcpApplet>
#include <QGraphicsLinearLayout>
#include <DuiContainer>

#include "dcpcategorycomponent.h"
#include "maintranslations.h"

#include "duiwidgetcreator.h"
DUI_REGISTER_WIDGET_NO_CREATE(DcpMainPage)

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

}

/*!
 * this function is called when the main page has been shown. here we start to
 * load the applets and put categoryies and brief widgets into the window, here
 * the progressive load starts.
 */
void
DcpMainPage::shown ()
{
    DCP_DEBUG ("##################################################");
    DCP_DEBUG ("### Main page has been shown #####################");
    DCP_DEBUG ("##################################################");

    if (m_HasContent)
    {
        m_RecentlyComp->reload(); 
        createContentsLate ();
//       m_RecentlyComp->show(); 
       return;
    }
   
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
    // FIXME: what if we would not need DcpComponent as parent?
    m_RecentlyComp->hide();
    m_RecentlyComp->setParentItem(centralWidget());

    m_OtherComp = new DuiContainer();
    DcpMainCategory *otherCategories = new DcpMainCategory(
            DcpMain::otherCategoriesTitleId,
            0,
            DcpMain::otherCategoriesTitleId);
    otherCategories->setMaxColumns(2);
    for (int i = 0;; i++) {
        DcpSingleComponent *button;
        const DcpCategoryInfo  *info;

        info = &DcpMain::CategoryInfos[i];
        if (info->titleId == 0)
             break;

        button = new DcpSingleComponent(otherCategories, info->titleId, qtTrId(info->titleId));
        button->setSubPage(info->subPageId, info->titleId);
        otherCategories->appendWidget(button);
        m_CategoryButtons.append(button);
    }
    m_OtherComp->setCentralWidget(otherCategories);

    layout->addItem(m_OtherComp);
    setEscapeButtonMode(DuiEscapeButtonPanelModel::CloseMode);
    retranslateUi();

#ifdef DISABLE_DELAYED_LOADING
    createContentsLate ();
    m_HasContent = true;

    emit firstShown ();
#endif // DISABLE_DELAYED_LOADING
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

    m_RecentlyComp->createContentsLate ();

    /*
     * Most recent used items. If this category is empty it is not visible so we
     * will add to the layout later.
     * Use 
     * # gconftool-2 --recursive-unset /apps/duicontrolpanel/usagecount
     * to test this piece of code.
     */
    if (!m_RecentlyComp->hasLoadingItems() && !m_RecentlyComp->getItemCount()) {
        m_RecentlyComp->hide();
    } else {
        mainLayout ()->insertItem (0,m_RecentlyComp);
        m_RecentlyComp->show();
    }
}

void
DcpMainPage::retranslateUi ()
{
    setTitle (qtTrId(DcpMain::settingsTitleId));

    /*
     * We always retranslate the 'most used' category, see NB #156882.
     */
    m_RecentlyComp->retranslateUi ();

    m_OtherComp->setTitle(qtTrId(DcpMain::otherCategoriesTitleId));

    for (int i=0; i<m_CategoryButtons.count(); i++) {
        DcpSingleComponent* comp = m_CategoryButtons.at(i);
        comp->setTitle(qtTrId(DcpMain::CategoryInfos[i].titleId));
    }
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

