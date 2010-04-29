/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include "dcpappletcategorypage.h"
#include "dcpappletbuttons.h"
#include <DcpMainCategory>
#include <QDebug>

#include <DcpAppletDb>
#include <DcpAppletMetadata>
#include <DcpAppletObject>
#include <DcpRetranslator>

#include "dcpdebug.h"

DcpAppletCategoryPage::DcpAppletCategoryPage (
        const DcpCategoryInfo  *categoryInfo) :
    DcpPage (),
    m_CategoryInfo (categoryInfo)
{
}

DcpAppletCategoryPage::~DcpAppletCategoryPage ()
{
}

void 
DcpAppletCategoryPage::createContent ()
{
    DcpPage::createContent ();

    m_Category = new DcpAppletButtons(m_CategoryInfo);
    setCentralWidget (m_Category);
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
DcpAppletCategoryPage::reload ()
{
    DCP_DEBUG ("");

    if (m_LoadedAppletCategory != appletCategory()) {
        m_Category->setCategoryInfo (m_CategoryInfo);
    }

    DcpPage::reload();
}

void DcpAppletCategoryPage::back ()
{
    DcpPage::back();
}

void
DcpAppletCategoryPage::retranslateUi()
{
    // briefwidgets take care of themselves, so we only update title here
    setTitle(qtTrId(m_TitleId));
}

void
DcpAppletCategoryPage::setTitleId(const char* titleId)
{
    m_TitleId = titleId;
    retranslateUi();
}

