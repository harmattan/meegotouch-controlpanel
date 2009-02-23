#include "dcpmaincategory.h"

#include <duigridlayout.h>
#include <duideviceprofile.h>
#include <QtDebug>

DcpMainCategory::DcpMainCategory(
        const QString& title, QGraphicsWidget *parent
) : DcpCategory(title, parent)
{
    m_Layout = new DuiGridLayout();

    setLayout(m_Layout);
}


void DcpMainCategory::add(DcpComponent *component)
{
    // rowspan = 2
    m_Layout->addItem(component, m_Layout->rowCount(), 0 /* column */,
                    1 /* rowspan */, 2 /* columnspan */);
    DcpCategory::add(component);
}


void DcpMainCategory::add(DcpComponent *component1,
                          DcpComponent *component2)
{
    int row = m_Layout->rowCount();
    m_Layout->addItem(component1, row, 0 /* column */);
    m_Layout->addItem(component2, row, 1 /* column */);

    DcpCategory::add(component1);
    DcpCategory::add(component2);
}


void DcpMainCategory::createContents()
{
}

