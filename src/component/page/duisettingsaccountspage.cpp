#include "duisettingsaccountspage.h"
//#include "duisimplecategory.h"
#include "duimaincategory.h"
#include "duiaccountcomponent.h"
#include <QtDebug>



DuiSettingsAccountPage::DuiSettingsAccountPage() : DuiSettingsCategoryPage() 
{
}


void DuiSettingsAccountPage::createContent()
{
    DuiSettingsCategoryPage::createContent();
    m_Category->setTitle(tr("Accounts"));
    DuiAccountComponent *flickrAccount = new DuiAccountComponent(m_Category, "Flickr");
    DuiAccountComponent *googleAccount = new DuiAccountComponent(m_Category, "Google");
    m_Category->add(flickrAccount, googleAccount);
}

