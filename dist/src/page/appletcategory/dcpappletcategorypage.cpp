#include "dcpappletcategorypage.h"
#include <QDebug>
#include "dcpmaincategory.h"
#include "dcpappletdb.h"
#include "dcpappletmetadata.h"

#include "dcpbriefcomponent.h"

DcpAppletCategoryPage::DcpAppletCategoryPage(const QString &appletCategory) 
                      : DcpCategoryPage(),
                        m_AppletCategory(appletCategory)
{
    setHandle(Pages::APPLETCATEGORY);
    setReferer(Pages::MAIN);
}

DcpAppletCategoryPage::~DcpAppletCategoryPage()
{
}

void DcpAppletCategoryPage::createContent()
{
    DcpCategoryPage::createContent();
    m_Category->setMaxColumns(2);
    m_Category->setVerticalSpacing(0);
    m_Category->setCreateSeparators();
    m_Category->setDoNotRemoveLastSeparator();

    loadContent();
}

void DcpAppletCategoryPage::loadContent()
{
    DcpAppletDb::instance()->refresh();
    DcpAppletMetadataList list = DcpAppletDb::instance()->listByCategory(appletCategory());

    if (!list.isEmpty())
    {
        bool odd =list.size() % 2 == 1;
    	DcpAppletMetadataList::const_iterator i;
        for (i = list.begin(); i != list.end(); ++i)
        {
            addComponent(*i, i == list.end() - 1 && odd);
        }
    }

    setTitle(appletCategory());
    m_LoadedAppletCategory = appletCategory();
}

void DcpAppletCategoryPage::addComponent(DcpAppletMetadata *metadata, bool odd)
{
    DcpBriefComponent *component = new DcpBriefComponent(metadata, m_Category);

    component->setSubPage(Pages::APPLET, metadata->name());
    connect(component, SIGNAL(openSubPage(Pages::Handle)),
            this, SIGNAL(openSubPage(Pages::Handle)));
    if (odd)
    {	
        m_Category->add(component);
    } else {
        m_Category->append(component);
    }
}

void DcpAppletCategoryPage::reload()
{
    if (m_LoadedAppletCategory != appletCategory()) {
        m_Category->deleteItems();
        loadContent();
    }
}

void DcpAppletCategoryPage::back()
{
    cleanup();
    DcpCategoryPage::back();
}

void DcpAppletCategoryPage::cleanup()
{

    DcpAppletMetadataList list = DcpAppletDb::instance()->listByCategory(appletCategory());

    if (!list.isEmpty())
    {
    	DcpAppletMetadataList::const_iterator i;
        for (i = list.begin(); i != list.end(); ++i)
        {
            DcpAppletMetadata *metadata = *i;
            qDebug() << "Cleaning up metadata" << metadata->name();
            metadata->cleanup();
        }
    }
   
}
