/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel.
**
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#include <MLayout>
#include <MLinearLayoutPolicy>
#include <MLabel>
#include "dcpskeletonwidget.h"
#include "dcpskeleton.h"

const int widgetWidth = 100;

SkeletonWidget::SkeletonWidget(QGraphicsWidget *parent)
	    :DcpWidget(parent)
{
    setReferer(DcpSkeleton::NoReferer);
    initWidget();
}

SkeletonWidget::~SkeletonWidget()
{
}


void SkeletonWidget::initWidget()
{
    MLayout *mainLayout = new MLayout(this);
    mainLayout->setAnimation(0);
    MLinearLayoutPolicy *mainLayoutPolicy = 
            new MLinearLayoutPolicy(mainLayout, Qt::Horizontal);
    mainLayout->setPolicy(mainLayoutPolicy);
	
    m_aboutLabel = new MLabel("About", this);
	
    mainLayoutPolicy->addItem(m_aboutLabel, Qt::AlignLeft);
    setLayout(mainLayout);

    qDebug("Bad applet 1 aborted when creating the widget");
    abort();
}

