/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpcategory.h"
#include <QGraphicsLayout>

DcpCategory::DcpCategory(const QString& title, QGraphicsWidget *parent,
                         const QString& logicalId) :
    DcpComponent(0, title, parent, logicalId)
{
}

void DcpCategory::add(DcpComponent *component)
{
    m_Children.append(component);
}

void DcpCategory::remove(DcpComponent *component)
{
    m_Children.remove(m_Children.indexOf(component));
}

DcpComponent* DcpCategory::child(int i) const
{
   return m_Children.at(i);
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

