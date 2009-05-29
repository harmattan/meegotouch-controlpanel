#include "dcpmainpage.h"

#include <QtDebug>

#include "dcpmaincategory.h"
#include "dcpdescriptioncomponent.h"
#include "dcprecentlyusedcomponent.h"
#include "pages.h"
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
	DcpCategoryPage()
{
    setHandle(Pages::MAIN);
    setReferer(Pages::NOPAGE);
    setBackButtonEnabled(false);
}


void DcpMainPage::createContent()
{
    DcpCategoryPage::createContent();
    setTitle(DcpMain::settingsTitle);

    m_Category->setMaxColumns(2);

    // most recent used items:
    DcpRecentlyUsedComponent* recentlyComp = new DcpRecentlyUsedComponent(m_Category, this);

    connect(recentlyComp, SIGNAL(openSubPage(Pages::Handle)),
                this, SIGNAL(openSubPage(Pages::Handle)));
    m_Category->add(recentlyComp);

    // category descriptions:
    for (int i=0; true; i++)
       {
        DcpCategoryInfo info = DcpMain::CategoryInfos[i];
        if (info.title == "")
             break;

        DcpDescriptionComponent *component = new DcpDescriptionComponent(
                m_Category, info.title);
        component->setDescription("<span>" + info.description + "</span>");
        component->setSubPage(info.subPageId);
        connect(component, SIGNAL(openSubPage(Pages::Handle)),
                this, SIGNAL(openSubPage(Pages::Handle)));
        m_Category->append(component);
    }
    setBackButtonEnabled(false);
}



