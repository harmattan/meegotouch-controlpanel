/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpappletcategorypage.h"
#include <DcpMainCategory>
#include <QDebug>
#include <DcpBriefComponent>

#include <DcpAppletDb>
#include <DcpAppletMetadata>

#define DEBUG
#include "dcpdebug.h"

DcpAppletCategoryPage::DcpAppletCategoryPage (
        const QString &appletCategory) :
    DcpCategoryPage (),
    m_AppletCategory (appletCategory)
{
    // FIXME: This is clearly wrong.
    setHandle  (PageHandle::APPLETCATEGORY);
    setReferer (PageHandle::MAIN);
}

DcpAppletCategoryPage::~DcpAppletCategoryPage ()
{
}


void 
DcpAppletCategoryPage::createContent ()
{
    DcpCategoryPage::createContent ();
    m_Category->setMaxColumns (2);
    m_Category->setVerticalSpacing (0);
    m_Category->setCreateSeparators ();
    m_Category->setDoNotRemoveLastSeparator ();

    loadContent();
}

const QString 
DcpAppletCategoryPage::appletCategory() const 
{
    return m_AppletCategory;
}

void 
DcpAppletCategoryPage::setAppletCategory (
        const QString &appletCategory) 
{
    m_AppletCategory=appletCategory;
}

void 
DcpAppletCategoryPage::loadContent ()
{
    bool odd;

    Q_ASSERT(!appletCategory().isEmpty());
    
    DCP_DEBUG ("*** appletCategory() = '%s'", DCP_STR (appletCategory()));
    /*
     * I had to comment this out, because it destroyed the metadata already
     * exists and then everything went wrong.
     */
    //DcpAppletDb::instance()->refresh();

    DcpAppletMetadataList list = DcpAppletDb::instance()->listByCategory (
            appletCategory());

    foreach (DcpAppletMetadata *item, list) {
        /*
         * We do not treat 1 item as odd, because it does not have to be spanned
         * in two columns.
         */
        odd = list.size() % 2 == 1 && list.size() > 1;
        DCP_DEBUG ("*** applet '%s'", DCP_STR (item->name()));
        addComponent (item, odd);
    }

    m_LoadedAppletCategory = appletCategory ();
}

void 
DcpAppletCategoryPage::addComponent (
		DcpAppletMetadata *metadata,
        bool               odd)
{
    DcpBriefComponent *component = new DcpBriefComponent (metadata, m_Category);

    component->setSubPage (PageHandle::APPLET, metadata->name());
    
    if (odd)
        m_Category->add (component);
    else
        m_Category->append (component);
}

void 
DcpAppletCategoryPage::reload ()
{
    DCP_DEBUG ("");

    if (m_LoadedAppletCategory != appletCategory()) {
        m_Category->deleteItems();
        loadContent();
    }

    DcpCategoryPage::reload();
}

void DcpAppletCategoryPage::back ()
{
    cleanup();
    DcpCategoryPage::back();
}

void 
DcpAppletCategoryPage::cleanup ()
{
    DcpAppletMetadataList list = DcpAppletDb::instance()->listByCategory (
            appletCategory());

    if (!list.isEmpty()) {
    	DcpAppletMetadataList::const_iterator i;
        for (i = list.begin(); i != list.end(); ++i) {
            DcpAppletMetadata *metadata = *i;
            qDebug() << "Cleaning up metadata" << metadata->name();
            metadata->cleanup ();
        }
    }
}

