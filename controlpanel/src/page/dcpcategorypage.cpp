#include "dcpcategorypage.h"

#include <DuiLinearLayoutPolicy>

#include "dcpmaincategory.h"


DcpCategoryPage::DcpCategoryPage () :
        DcpPage()
{
}

void 
DcpCategoryPage::createContent ()
{
    DcpPage::createContent();
    m_Category = new DcpMainCategory ("");
    appendWidget (m_Category);
}

void 
DcpCategoryPage::organizeContent (
                const Dui::Orientation& ori)
{
    DcpPage::organizeContent (ori);
    m_Category->onOrientationChange (ori);
}
