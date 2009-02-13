#include "duimaincategory.h"

DuiMainCategory::DuiMainCategory(
        const QString& title=tr("Settings"), QGraphicsWidget *parent=0
) : DuiSettingsCategory(title, parent)
{
}


void DuiMainCategory::add(DuiSettingsComponent *component)
{
    DuiGridLayout* layout = qobject_cast<DuiGridLayout*>(this->layout());
    ...
    DuiSettingsCategory::add(component);
}


void DuiMainCategory::add(DuiSettingsComponent *component,
                          DuiSettingsComponent *component)
{
}


void DuiMainCategory::createContents()
{
    setLayout(new DuiGridLayout(this));
}


void DuiMainCategory::onOrientationChange (const Dui::Orientation &orientation)
{
    Q_UNUSED (orientation);
}
