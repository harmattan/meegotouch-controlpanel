#include "dcpaccountspage.h"
#include "dcpmaincategory.h"
#include "dcpaccountcomponent.h"
#include <QtDebug>
#include "duilabel.h"
#include "duilinearlayout.h"


DcpAccountPage::DcpAccountPage()
                       : DcpCategoryPage() 
{
    setHandle(Pages::ACCOUNTS);
    setReferer(Pages::MAIN);
}


void DcpAccountPage::createContent()
{
    DcpCategoryPage::createContent();
    m_Category->setTitle(tr("Accounts"));
    DcpAccountComponent *flickrAccount = new DcpAccountComponent(m_Category, "Flickr");
    DcpAccountComponent *googleAccount = new DcpAccountComponent(m_Category, "Google");
    flickrAccount->setSubPage(Pages::APPLET);
    connect(flickrAccount, SIGNAL(openSubPage(Pages::Handle)),
            this, SIGNAL(openSubPage(Pages::Handle))); 
    m_Category->setMaxColumns(2); 
    m_Category->append(flickrAccount);
    m_Category->append(googleAccount);
    panLayout()->addItem(new DuiLabel("Halihaw!"));
}
