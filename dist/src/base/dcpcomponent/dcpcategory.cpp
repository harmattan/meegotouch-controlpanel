#include "dcpcategory.h"
#include <QGraphicsLayout>

DcpCategory::DcpCategory(const QString& title,
                                 QGraphicsWidget *parent) :
    DcpComponent(0, title, parent)				
{
}

void 
DcpCategory::add(DcpComponent *component)
{
    m_Children.append(component);
}

void
DcpCategory::remove(DcpComponent *component)
{
    m_Children.remove(m_Children.indexOf(component));
}

DcpComponent*
DcpCategory::child(int i) const
{
   return m_Children.at(i);
}

void
DcpCategory::onOrientationChange (const Dui::Orientation &orientation)
{
/*  disabled because of optimization
 *  DcpComponent::onOrientationChange(orientation);
    foreach (DcpComponent* component, m_Children) {
        component->onOrientationChange(orientation);
    }
 */
}

