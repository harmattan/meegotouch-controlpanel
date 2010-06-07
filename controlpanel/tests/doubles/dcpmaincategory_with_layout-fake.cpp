/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel.
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#include "dcpmaincategory.h"

#include <MLayout>
#include <MGridLayoutPolicy>
#include <MLinearLayoutPolicy>
#include <MSceneManager>

#include <QtDebug>
#include <MSeparator>

#include "dcpdebug.h"

const QString DcpMainCategory::sm_SeparatorObjectName = "DcpSmallSeparator";

DcpMainCategory::DcpMainCategory (
        const QString &title, 
        QGraphicsWidget *parent,
        const QString& logicalId) 
: DcpComponent (0, title, parent, logicalId),
    m_ColCount (0),
    m_RowCount (0),
    m_ItemCount (0),
    m_CreateSeparators (false)
{
 m_Layout = new MLayout (this);                                                                                    
    m_Layout->setAnimation(0);                                                                                        
                                                                                                                      
    m_LandscapeLayout = new MGridLayoutPolicy (m_Layout);                                                             
    m_PortraitLayout = new MLinearLayoutPolicy (m_Layout, Qt::Vertical);                                              
                                                                                                                      
    m_Layout->setLandscapePolicy (m_LandscapeLayout);                                                                 
    m_Layout->setPortraitPolicy (m_PortraitLayout);                                                                   
                                                                                                                      
    setLayout (m_Layout);               
}


void 
DcpMainCategory::deleteItems ()
{
}

void 
DcpMainCategory::setHorizontalSpacing (
        int space)
{
    Q_UNUSED(space);
}

void 
DcpMainCategory::setVerticalSpacing (
        int space)
{
    Q_UNUSED(space);
}

void
DcpMainCategory::appendWidget (
        QGraphicsWidget *component)
{
                                                                                                                    
    m_LandscapeLayout->addItem (component, m_RowCount, m_ColCount);                                                   
    m_PortraitLayout->addItem (component);                                    
}

void 
DcpMainCategory::createContents ()
{
}


void 
DcpMainCategory::setCreateSeparators (
        bool create)
{
    m_CreateSeparators = create;
}

void 
DcpMainCategory::setMaxColumns (
        int columns)
{
    m_MaxColumns = columns;
}

int 
DcpMainCategory::maxColumns ()
{
    return m_MaxColumns;
}

QGraphicsWidget*
DcpMainCategory::widgetAt (int)
{
    return 0;
}


