/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpappletcategorypage.h"
#include <DcpMainCategory>
#include <QDebug>
#include <DcpBriefComponent>

#include <DcpAppletDb>
#include <DcpAppletMetadata>

//#define DEBUG
#include "dcpdebug.h"

DcpAppletCategoryPage::DcpAppletCategoryPage (
        const DcpCategoryInfo  *categoryInfo) :
    DcpCategoryPage (),
    m_CategoryInfo (categoryInfo)
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

    loadContent();
}

const QString 
DcpAppletCategoryPage::appletCategory() const 
{
    return m_CategoryInfo->appletCategory;
}

void 
DcpAppletCategoryPage::setCategoryInfo (
        const DcpCategoryInfo *categoryInfo) 
{
    m_CategoryInfo = categoryInfo;
}

void 
DcpAppletCategoryPage::loadContent ()
{
    bool                    withUncategorized;
    const char             *names[3];
    DcpAppletMetadataList   list;

    if (!m_CategoryInfo)
        return;

    withUncategorized = m_CategoryInfo && 
            m_CategoryInfo->subPageId == PageHandle::Applications;

    names[0] = m_CategoryInfo->titleId;
    names[1] = m_CategoryInfo->appletCategory;
    names[2] = 0;

    list = DcpAppletDb::instance()->listByCategory (names, 2, 
                withUncategorized ? dcp_category_name_enlisted : NULL);
    
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

    m_Category->appendWidget (component);
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

