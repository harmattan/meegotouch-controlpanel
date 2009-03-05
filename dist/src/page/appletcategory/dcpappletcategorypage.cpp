#include "dcpappletcategorypage.h"
#include <QDebug>
#include "dcpmaincategory.h"
#include "dcpappletdb.h"
#include "dcpappletmetadata.h"
#include "dcpbuttoncomponent.h"
#include "duilinearlayout.h"
#include "duilabel.h"
#include <QPluginLoader>
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
    DcpAppletMetadataList list = DcpAppletDb::instance()->listByCategory(appletCategory());
    if (!list.isEmpty())
    {
        foreach(DcpAppletMetadata *metadata, list)
            m_Category->append(new DcpButtonComponent(m_Category, metadata));
    }
    else
        panLayout()->addItem(new DuiLabel("No applets in this category yet."));
}

void DcpAppletCategoryPage::organizeContent(Dui::Orientation ori)
{
    Q_UNUSED(ori);
}

