/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#ifndef DCPAPPLETCATEGORYPAGE_FAKE_H
#define DCPAPPLETCATEGORYPAGE_FAKE_H
#include "dcpappletcategorypage.h"

DcpAppletCategoryPage::DcpAppletCategoryPage (
        const DcpCategoryInfo  *categoryInfo) :
    m_CategoryInfo (categoryInfo)
{
}

DcpAppletCategoryPage::~DcpAppletCategoryPage ()
{
}


void 
DcpAppletCategoryPage::createContent ()
{
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
}


void 
DcpAppletCategoryPage::reload ()
{
}

void DcpAppletCategoryPage::back ()
{
}

void 
DcpAppletCategoryPage::cleanup ()
{
}

void
DcpAppletCategoryPage::retranslateUi()
{
}

void
DcpAppletCategoryPage::setTitleId(const char *titleId)
{
   Q_UNUSED(titleId);
}

#endif // DCPAPPLETCATEGORYPAGE_FAKE_H
