#include "dcpmainpage.h"

#include <QtDebug>
#include <DuiApplication>

#include <DcpMainCategory>
#include <Pages>
#include <DcpApplet>

#include "dcpdescriptioncomponent.h"
#include "dcpcategorycomponent.h"
#include "maintranslations.h"

/*!
 * \class DcpMainPage
 * \brief The main page of duicontrolpanel.
 *
 * Displays a list of the applet
 * categories and emits a signal if one of them is to be opened.
 * Also has a recent used items list at the top, which contains buttons
 * to directly access the most commonly used applets (without searching
 * for them in the categories.
 */

DcpMainPage::DcpMainPage() :
	DcpCategoryPage(), m_RecentlyComp(0)
{
    setHandle(Pages::MAIN);
    setReferer(Pages::NOPAGE);
    setBackButtonEnabled(false);
}

DcpMainPage::~DcpMainPage() 
{}



void DcpMainPage::createContent()
{
    DcpCategoryPage::createContent();

    m_Category->setMaxColumns(1);

    // most recent used items:
    m_RecentlyComp = new DcpCategoryComponent(m_Category,
                                 DcpApplet::MostUsedCategory, this);

    connect(m_RecentlyComp, SIGNAL(openSubPage(Pages::Handle)),
            this, SIGNAL(openSubPage(Pages::Handle)));
    m_Category->add(m_RecentlyComp);

    // category descriptions:
    for (int i=0; true; i++) {
        DcpCategoryInfo info = DcpMain::CategoryInfos[i];
        if (info.titleId == 0)
             break;
        DcpCategoryComponent *component = new DcpCategoryComponent(m_Category,
                                 info.appletCategory, this);

        connect(component, SIGNAL(openSubPage(Pages::Handle)),
            this, SIGNAL(openSubPage(Pages::Handle)));

        m_Category->append(component);
    }

    setBackButtonEnabled(false);

    retranslateUi();
}

void DcpMainPage::retranslateUi()
{
    setTitle(trid(DcpMain::settingsTitleId, DcpMain::settingsTitleDefault));
    m_RecentlyComp->setTitle(trid(DcpMain::mostRecentUsedTitleId,
                                      DcpMain::mostRecentUsedTitleDefault));
    for (int i=m_Category->childCount()-1; i>=1; i--) {
        DcpCategoryComponent* comp =
            qobject_cast<DcpCategoryComponent*>(m_Category->child(i));
        comp->setTitle(trid(DcpMain::CategoryInfos[i-1].titleId,
                                       DcpMain::CategoryInfos[i-1].titleDefault));
    }
    // no need to update briefs, they take care of themselves
}

void DcpMainPage::reload()
{
    // refresh the most recent items sequence:
    if (m_RecentlyComp){
        m_RecentlyComp->reload();
    }

    // DcpBriefWidget takes care of all the other things
    DcpCategoryPage::reload();
}

// if clicked fast, back button can be pressed instead of close
void DcpMainPage::back()
{
    qApp->quit();
}

