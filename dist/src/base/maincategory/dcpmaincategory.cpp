#include "dcpmaincategory.h"

#include <duigridlayout.h>
#include <duilinearlayout.h>
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
    if (m_ColCount > 0) {
        m_ColCount = 0;
        m_RowCount++;
    }
    m_Layout->addItem(component, m_RowCount, 0 /* column */,
                    1 /* rowspan */, m_MaxColumns /* columnspan */);

    DcpCategory::add(component);
    m_ColSpans[component] = m_MaxColumns;
    m_RowCount++;
}


void DcpMainCategory::append(DcpComponent *component)
{
    DcpCategory::add(component);
    m_Layout->addItem(component, m_RowCount, m_ColCount);
    m_ColCount++;
    if (m_ColCount >= m_MaxColumns)
    {
        m_ColCount = 0;
        m_RowCount++;
    }
    m_ColSpans[component] = 0;
}



void DcpMainCategory::createContents()
{
}

void 
DcpMainCategory::onOrientationChange (const Dui::Orientation &orientation)
{
    if (orientation == Dui::Portrait)
    {
        DuiLinearLayout *layout = new DuiLinearLayout(Qt::Vertical);
        foreach(DcpComponent *component, m_Children)
        {
            component->onOrientationChange(orientation);
            layout->addItem(component);
        }
        setLayout(layout);
        qDebug() << "Changing orientation to Dui::Portrait";
        //delete m_Layout;
       // m_Layout = 0;
    }
    else
    if (0)
    {
        //DuiLinearLayout *layout = (DuiLinearLayout*)(this->layout());
        m_Layout = new DuiGridLayout();
        foreach(DcpComponent *component, m_Children)
        {
            component->onOrientationChange(orientation);
            if (m_ColSpans[component] == m_MaxColumns)
                add(component);
            else
                append(component);
        }
        //delete layout;
        setLayout(m_Layout);
        qDebug() << "Changing orientation to Dui::Landscape";
    }
}   
