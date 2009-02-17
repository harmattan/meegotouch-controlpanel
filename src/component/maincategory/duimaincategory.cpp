#include "duimaincategory.h"

#include <duigridlayout.h>
#include <duideviceprofile.h>
#include <QtDebug>

DuiMainCategory::DuiMainCategory(
        const QString& title, QGraphicsWidget *parent
) : DuiSettingsCategory(title, parent)
{
    m_Layout = new DuiGridLayout();

    setLayout(m_Layout);
}


void DuiMainCategory::add(DuiSettingsComponent *component)
{
    // rowspan = 2
    m_Layout->addItem(component, m_Layout->rowCount(), 0 /* column */,
                    1 /* rowspan */, 2 /* columnspan */);
    DuiSettingsCategory::add(component);
}


void DuiMainCategory::add(DuiSettingsComponent *component1,
                          DuiSettingsComponent *component2)
{
    int row = m_Layout->rowCount();
    m_Layout->addItem(component1, row, 0 /* column */);
    m_Layout->addItem(component2, row, 1 /* column */);

    DuiSettingsCategory::add(component1);
    DuiSettingsCategory::add(component2);
}



void DuiMainCategory::createContents()
{
}


void DuiMainCategory::onOrientationChange (const Dui::Orientation &orientation)
{
    Q_UNUSED(orientation);
}

