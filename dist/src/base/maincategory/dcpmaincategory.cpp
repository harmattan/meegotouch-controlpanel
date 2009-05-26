#include "dcpmaincategory.h"

#include <duilayout.h>
#include <duigridlayoutpolicy.h>
#include <duilinearlayoutpolicy.h>

#include <duiscenemanager.h>
#include <duibasiclayoutanimator.h>
#include <QtDebug>


DcpMainCategory::DcpMainCategory(
        const QString& title, QGraphicsWidget *parent
) : DcpCategory(title, parent), m_ColCount(0), m_RowCount(0), m_ItemCount(0)
{
    m_Layout = new DuiLayout(this);
    m_Layout->setAnimator(NULL);

    m_LandscapeLayout = new DuiGridLayoutPolicy(m_Layout);

    m_Layout->setPolicy(m_LandscapeLayout);
    m_PortraitLayout = new DuiLinearLayoutPolicy(m_Layout, Qt::Vertical);

    m_Layout->setContentsMargins(0,0,0,0);
    m_LandscapeLayout->setContentsMargins(0,0,0,0);
    setLayout(m_Layout);

    m_LandscapeLayout->setHorizontalSpacing(12);
    m_LandscapeLayout->setVerticalSpacing(12);
}


void DcpMainCategory::add(DcpComponent *component)
{
    if (m_ColCount > 0) {
        m_ColCount = 0;
        m_RowCount++;
    }
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


void DcpMainCategory::polishEvent ()
{
    onOrientationChange(DuiSceneManager::instance()->orientation());
}

