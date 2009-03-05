#include "dcpmainpage.h"

#include <QtDebug>

#include <duilinearlayout.h>
#include <duimultilayout.h>
#include <duilabel.h>
#include <duipannableviewport.h>

#include "dcpmaincategory.h"
#include "dcpdescriptioncomponent.h"
#include "dcprecentlyusedcomponent.h"
#include "pages.h"
#include "maintranslations.h"

#include "dcpbuttoncomponent.h"

DcpMainPage::DcpMainPage() :
	DcpCategoryPage()
{
    m_PageId = Pages::MAIN;
    m_Referer = Pages::NOPAGE;
}


void DcpMainPage::createContent()
{
    DcpCategoryPage::createContent();
    setTitle(DcpMain::settingsTitle);
    // most recent used items:
    DcpRecentlyUsedComponent* recentlyComp = new DcpRecentlyUsedComponent(
                                                    m_Category);


    m_Category->add(recentlyComp);

DcpButtonComponent *tmp = new DcpButtonComponent(m_Category);
m_Category->append(tmp);

    // category descriptions:

    m_Category->setMaxColumns(2);
    for (int i=0; true; i++)
       {
        DcpCategoryInfo info = DcpMain::CategoryInfos[i];
        if (info.title == "")
             break;

        DcpDescriptionComponent *component = new DcpDescriptionComponent(
                m_Category, info.title);
        component->setDescription("<span>" + info.description + "</span>");
        component->setSubPageId(Pages::ACCOUNTS);
        connect(component, SIGNAL(openSubPage(Pages::Id)),
                this, SIGNAL(openSubPage(Pages::Id)));
        m_Category->append(component);
    }

    // reset settings:
    DcpDescriptionComponent *resetSettings = new DcpDescriptionComponent(
            m_Category, DcpMain::resetSettingsTitle);
    resetSettings->setDescription(DcpMain::resetSettingsDescription);
    resetSettings->setFullRowSize ();
    connect(resetSettings, SIGNAL(openSubPage(Pages::Id)),
            this, SLOT(onResetSettingsClicked()));
    m_Category->add(resetSettings);

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
    if ( profile->orientation() == Dui::Portrait ) {
        qDebug() << "XXX mode changes to Angle0";
        profile->setOrientationAngle (DuiDeviceProfile::Angle0);
    } else {
        qDebug() << "XXX mode changes to Angle90";
        profile->setOrientationAngle (DuiDeviceProfile::Angle90);
    }
}
// --

