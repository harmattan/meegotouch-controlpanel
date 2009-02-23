#include "dcpaccountspage.h"
#include "dcpmaincategory.h"
#include "dcpaccountcomponent.h"
#include <QtDebug>



DcpAccountPage::DcpAccountPage()
                       : DcpCategoryPage() 
{
    m_PageId = Pages::ACCOUNTS;
    m_Referer = Pages::MAIN;
}


void DcpAccountPage::createContent()
{
    DcpCategoryPage::createContent();
    m_Category->setTitle(tr("Accounts"));
    DcpAccountComponent *flickrAccount = new DcpAccountComponent(m_Category, "Flickr");
    DcpAccountComponent *googleAccount = new DcpAccountComponent(m_Category, "Google");
    flickrAccount->setSubPageId(Pages::APPLET);                                     connect(flickrAccount, SIGNAL(openSubPage(Pages::Id)),                         	this, SIGNAL(openSubPage(Pages::Id)));  
    m_Category->add(flickrAccount, googleAccount);
}

