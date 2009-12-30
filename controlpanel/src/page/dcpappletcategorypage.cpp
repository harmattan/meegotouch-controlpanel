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
    Q_ASSERT (!appletCategory().isEmpty());
    
    DCP_DEBUG ("*** appletCategory() = '%s'", DCP_STR (appletCategory()));
    /*
     * I had to comment this out, because it destroyed the metadata already
     * exists and then everything went wrong.
     * FIXME: Should find a way to refresh the database without destroying the
     * existing metadata entries.
     */
    //DcpAppletDb::instance()->refresh();

    DcpAppletMetadataList list = DcpAppletDb::instance()->listByCategory (
            appletCategory());

    foreach (DcpAppletMetadata *item, list) {
        DCP_DEBUG ("*** applet '%s'", DCP_STR (item->name()));
        addComponent (item);
    }

    m_LoadedAppletCategory = appletCategory ();
}

void 
DcpAppletCategoryPage::addComponent (
		DcpAppletMetadata *metadata)
{
    DcpBriefComponent *component = new DcpBriefComponent (metadata, m_Category);

    component->setSubPage (PageHandle::APPLET, metadata->name());

    appendWidget (component);
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

