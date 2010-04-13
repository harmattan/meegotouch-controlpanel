/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include "dcpcomponent.h"

#include <QGraphicsLayout>

#include "dcpdebug.h"

DcpComponent::DcpComponent (
        DcpComponent *category, const QString& title,
                           QGraphicsWidget *parent,
                           const QString& logicalId) :
                MWidget(parent),
                m_Title(title),
                m_LogicalId(logicalId),
                m_Category(category)
{
}

QString 
DcpComponent::mattiID () const
{
    return m_MattiID;
}

void 
DcpComponent::setMattiID (
        const QString &mattiID)
{
    m_MattiID = mattiID;
}

