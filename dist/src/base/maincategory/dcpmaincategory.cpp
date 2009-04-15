#include "dcpmaincategory.h"

#include <duilayout.h>
#include <duigridlayoutpolicy.h>
#include <duilinearlayoutpolicy.h>

#include <duiproxywidget.h>

#include <duideviceprofile.h>
#include <duibasiclayoutanimator.h>
#include <QtDebug>


DcpMainCategory::DcpMainCategory(
        const QString& title, QGraphicsWidget *parent
) : DcpCategory(title, parent), m_ColCount(0), m_RowCount(0), m_ItemCount(0)
{
    m_Layout = new DuiLayout();

    m_LandscapeLayout = new DuiGridLayoutPolicy(m_Layout);

    m_Layout->setPolicy(m_LandscapeLayout);
    m_PortraitLayout = new DuiLinearLayoutPolicy(m_Layout, Qt::Vertical);

//    m_Layout->setAnimator(NULL);

    DuiBasicLayoutAnimator* animator = new DuiBasicLayoutAnimator();
    animator->setAnimationSpeed(150);
    m_Layout->setAnimator(animator);

    setLayout(m_Layout);

    m_LandscapeLayout->setColumnSpacing(0, 12);
}


void DcpMainCategory::add(DcpComponent *component)
{
    if (m_ColCount > 0) {
        m_ColCount = 0;
        m_RowCount++;
    }
    component->setParent(this);
//    qDebug() << "XXX add" << m_RowCount << 0;
    m_LandscapeLayout->addItemAtPosition(component,
                                         m_RowCount, 0 /* column */,
              1 /* rowspan */, m_MaxColumns /* columnspan */);
    m_PortraitLayout->addItemAtPosition(component,
                                        m_ItemCount);

    DcpCategory::add(component);
    m_RowCount++;
    m_ItemCount++;
}


void DcpMainCategory::append(DcpComponent *component)
{
    if (m_ColCount >= m_MaxColumns)
    {
        m_ColCount = 0;
        m_RowCount++;
    }
    component->setParent(this);

//    qDebug() << "XXX append" << m_RowCount << m_ColCount;
    m_LandscapeLayout->addItemAtPosition(component,
                                         m_RowCount, m_ColCount);
    m_PortraitLayout->addItemAtPosition(component,
                                        m_ItemCount);

    DcpCategory::add(component);
    m_ColCount++;
    m_ItemCount++;
}


void DcpMainCategory::createContents()
{
}


void 
DcpMainCategory::onOrientationChange (const Dui::Orientation &orientation)
{
    if (orientation == Dui::Portrait) {
        m_Layout->setPolicy(m_PortraitLayout);
    } else {
        m_Layout->setPolicy(m_LandscapeLayout);
    }

    DcpCategory::onOrientationChange(orientation);
}   
