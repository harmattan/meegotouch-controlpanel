/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include "dcpcomponent.h"

#include <QtDebug>
#include <QGraphicsLayout>

#define DEBUG
#include "dcpdebug.h"

DcpComponent::DcpComponent (
		DcpCategory *category, const QString& title,
                           QGraphicsWidget *parent,
                           const QString& logicalId) :
				DuiWidget(parent),
                m_Title(title),
                m_LogicalId(logicalId),
                m_Category(category)
{
}

DcpComponent* DcpComponent::child(int i) const
{
    Q_UNUSED(i);
    return 0;
}



void DcpComponent::onOrientationChange(const Dui::Orientation& orientation)
{
    Q_UNUSED(orientation);
}
