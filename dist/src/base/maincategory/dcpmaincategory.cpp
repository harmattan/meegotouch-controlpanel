#include "dcpmaincategory.h"

#include <duigridlayout.h>
#include <duideviceprofile.h>
#include <QtDebug>

DcpMainCategory::DcpMainCategory(
        const QString& title, QGraphicsWidget *parent
) : DcpCategory(title, parent), m_ColCount(0), m_RowCount(0)
{
    m_Layout = new DuiGridLayout();

    setLayout(m_Layout);
}


void DcpMainCategory::add(DcpComponent *component)
{
    // rowspan = 2
    m_Layout->addItem(component, m_RowCount, 0 /* column */,
                    1 /* rowspan */, 2 /* columnspan */);
    DcpCategory::add(component);
    m_RowCount++;
}


void DcpMainCategory::append(DcpComponent *component)
{
    m_Layout->addItem(component, m_RowCount, m_ColCount);
    DcpCategory::add(component);
    m_ColCount++;
    if (m_ColCount > m_MaxColumns)
    {
        m_ColCount = 0;
        m_RowCount++;
    }
}



void DcpMainCategory::createContents()
{
}

