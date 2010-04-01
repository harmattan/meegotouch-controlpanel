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

