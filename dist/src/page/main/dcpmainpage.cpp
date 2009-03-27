#include "dcpmainpage.h"

#include <QtDebug>

#include <duilinearlayout.h>
#include <duimultilayout.h>
#include <duilabel.h>
#include <duipannableviewport.h>

#include "dcpappletdb.h"
#include "dcpmaincategory.h"
#include "dcpdescriptioncomponent.h"
#include "dcprecentlyusedcomponent.h"
#include "pages.h"
#include "maintranslations.h"

#include "dcpbuttoncomponent.h"
#include "dcplabelcomponent.h"

#include "dcpappletmetadata.h"

#include "dcpmostusedcategory.h"

DcpMainPage::DcpMainPage() :
	DcpCategoryPage()
{
    setHandle(Pages::MAIN);
    setReferer(Pages::NOPAGE);
}


void DcpMainPage::createContent()
{
    DcpCategoryPage::createContent();
    setTitle(DcpMain::settingsTitle);

    m_Category->setMaxColumns(2);

    // most recent used items:
    DcpRecentlyUsedComponent* recentlyComp = new DcpRecentlyUsedComponent(
                                                    m_Category);

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

}



void DcpMainPage::organizeContent(Dui::Orientation ori)
{
    DcpPage::organizeContent(ori);
    m_Category->onOrientationChange(ori);
}


// ----- FOR TESTING -----
#include <duideviceprofile.h>
void DcpMainPage::onResetSettingsClicked()
{
    DuiDeviceProfile *profile = DuiDeviceProfile::instance();
   // m_Category->onOrientationChange(profile->orientation());

    if ( profile->orientation() == Dui::Portrait ) {
        profile->setOrientationAngle (DuiDeviceProfile::Angle0);
    } else {
        profile->setOrientationAngle (DuiDeviceProfile::Angle90);
    }
}
// --

