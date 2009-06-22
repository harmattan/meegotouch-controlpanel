#include "dcpcategorypage.h"

#include <QtDebug>

#include <duilinearlayoutpolicy.h>

#include "dcpmaincategory.h"


DcpCategoryPage::DcpCategoryPage() :
	DcpPage()
{
}


void DcpCategoryPage::createContent()
{
    DcpPage::createContent();
    m_Category = new DcpMainCategory("");
    append(m_Category);
}


void DcpCategoryPage::organizeContent(const Dui::Orientation& ori)
{
    DcpPage::organizeContent(ori);
    m_Category->onOrientationChange(ori);
    qDebug() << "XXX category page organize";
}

