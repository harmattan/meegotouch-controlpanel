#include "duisettingscategory.h"
DuiSettingsCategory::DuiSettingsCategory(const QString& title,
                                 QGraphicsWidget *parent) :
    DuiSettingsComponent(0, title, parent)				
{
}

void 
DuiSettingsCategory::add(DuiSettingsComponent *component)
{
    m_Children.append(component);
}

void 
DuiSettingsCategory::remove(DuiSettingsComponent *component)
{
    m_Children.remove(m_Children.indexOf(component));
}

DuiSettingsComponent* 
DuiSettingsCategory::child(int i) const
{
   return m_Children.at(i);
}

void 
DuiSettingsCategory::onOrientationChange (const Dui::Orientation &orientation)
{
    foreach (DuiSettingsComponent* component, m_Children) {
        component->onOrientationChange(orientation);
    }
}
