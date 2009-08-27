#include "dcpappletcategorypage.h"
#include "dcpmaincategory.h"
#include <QDebug>
#include "dcpbriefcomponent.h"

#include <DcpAppletDb>
#include <DcpAppletMetadata>


DcpAppletCategoryPage::DcpAppletCategoryPage(const QString &appletCategory) :
		DcpCategoryPage(),
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
    Q_ASSERT(!appletCategory().isEmpty());

    DcpAppletDb::instance()->refresh();
    DcpAppletMetadataList list = DcpAppletDb::instance()->listByCategory(appletCategory());

    if (!list.isEmpty()) {
        // we do not treat 1 item as odd,
        // because it does not have to be spanned in two columns
        bool odd = list.size() % 2 == 1 && list.size() > 1;
    	DcpAppletMetadataList::const_iterator i;
        for (i = list.begin(); i != list.end(); ++i)
            addComponent(*i, i == list.end() - 1 && odd);
    }

    m_LoadedAppletCategory = appletCategory();
}

void DcpAppletCategoryPage::addComponent(DcpAppletMetadata *metadata, bool odd)
{
    DcpBriefComponent *component = new DcpBriefComponent(metadata, m_Category);

    component->setSubPage(Pages::APPLET, metadata->name());
    connect(component, SIGNAL(openSubPage(Pages::Handle)),
            this, SIGNAL(openSubPage(Pages::Handle)));
    if (odd)
        m_Category->add(component);
    else
        m_Category->append(component);
}

void DcpAppletCategoryPage::reload()
{
    if (m_LoadedAppletCategory != appletCategory()) {
        m_Category->deleteItems();
        loadContent();
    }
    DcpCategoryPage::reload();
}

void DcpAppletCategoryPage::back()
{
    cleanup();
    DcpCategoryPage::back();
}

void DcpAppletCategoryPage::cleanup()
{
    DcpAppletMetadataList list = DcpAppletDb::instance()->listByCategory(appletCategory());

    if (!list.isEmpty()) {
    	DcpAppletMetadataList::const_iterator i;
        for (i = list.begin(); i != list.end(); ++i) {
            DcpAppletMetadata *metadata = *i;
            qDebug() << "Cleaning up metadata" << metadata->name();
            metadata->cleanup();
        }
    }
}
