/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpcategory.h"
#include <QGraphicsLayout>

#define DEBUG
#include "../../../lib/src/dcpdebug.h"

#if 0
DcpCategory::DcpCategory(
        const QString& title, 
        QGraphicsWidget *parent,
        const QString& logicalId) :
    DcpComponent (0, title, parent, logicalId)
{
}

int 
DcpCategory::childCount() const 
{ 
    DCP_DEBUG ("Returning %d", m_Children.count());
    return m_Children.count(); 
}

void
DcpCategory::add (
        DcpComponent *component)
{
    DCP_DEBUG ("Adding %p", component);
    m_Children.append (component);
}


void
DcpCategory::remove (
        DcpComponent *component)
{
    m_Children.remove (m_Children.indexOf(component));
}


DcpComponent *
DcpCategory::child(int i) const
{
    DCP_DEBUG ("returning item %p at %d", m_Children.at (i), i);
    return m_Children.at (i);
}

void DcpCategory::onOrientationChange (const Dui::Orientation &orientation)
{
/*  disabled because of optimization
 *  DcpComponent::onOrientationChange(orientation);
    foreach (DcpComponent* component, m_Children) {
        component->onOrientationChange(orientation);
    }
 */
}
#endif
