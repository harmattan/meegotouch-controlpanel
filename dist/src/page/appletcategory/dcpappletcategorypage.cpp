#include "dcpappletcategorypage.h"
#include <QDebug>
#include "dcpmaincategory.h"
#include "dcpbuttoncomponent.h"
#include "dcpappletdb.h"
#include "dcpappletmetadata.h"
DcpAppletCategoryPage::DcpAppletCategoryPage(const QString &appletCategory) : DcpCategoryPage(),
    m_AppletCategory(appletCategory) 
{
    m_PageId = Pages::APPLETCATEGORY;
    m_Referer = Pages::MAIN;
}

DcpAppletCategoryPage::~DcpAppletCategoryPage()
{
} 
void DcpAppletCategoryPage::createContent()
{
    DcpCategoryPage::createContent();
    m_Category->setMaxColumns(2);
    DcpAppletDb::instance()->refresh();
    DcpAppletMetadataList list = DcpAppletDb::instance()->listByCategory(appletCategory());
    if (!list.isEmpty())
    {
        foreach(DcpAppletMetadata *metadata, list)
        {
           DcpButtonComponent *button = new DcpButtonComponent(0, metadata); 
           button->setSubPageId(Pages::APPLET);
           connect(button, SIGNAL(openSubPage(Pages::Id, const QString&)),
                this, SIGNAL(openSubPage(Pages::Id, const QString&)));
           m_Category->append(button);
        }
    }
    setTitle("Applets");
   
}

void DcpAppletCategoryPage::organizeContent(Dui::Orientation ori)
{
    Q_UNUSED(ori);
}

