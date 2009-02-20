#include "duisettingsaccountspage.h"
//#include "duisimplecategory.h"
#include "duimaincategory.h"
#include "duiaccountcomponent.h"
#include <QtDebug>



DuiSettingsAccountPage::DuiSettingsAccountPage()
                       : DuiSettingsCategoryPage() 
{
    m_PageId = Pages::ACCOUNTS;
}


void DuiSettingsAccountPage::createContent()
{
    DuiSettingsCategoryPage::createContent();
    m_Category->setTitle(tr("Accounts"));
    DuiAccountComponent *flickrAccount = new DuiAccountComponent(m_Category, "Flickr");
    DuiAccountComponent *googleAccount = new DuiAccountComponent(m_Category, "Google");
    flickrAccount->setSubPageId(Pages::APPLET);                                     connect(flickrAccount, SIGNAL(openSubPage(Pages::Id)),                         	this, SIGNAL(openSubPage(Pages::Id)));  
    m_Category->add(flickrAccount, googleAccount);
}

