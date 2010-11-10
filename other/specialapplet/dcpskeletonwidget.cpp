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


#include "dcpskeletonwidget.h"
#include "dcpskeleton.h"
#include <mlayout.h>
#include <mlinearlayoutpolicy.h>
#include <mlabel.h>
#include <QTimer>

SkeletonWidget::SkeletonWidget(QGraphicsWidget *parent)
	    :DcpWidget(parent)
{
    setReferer(DcpSkeleton::NoReferer);
    initWidget();

    // this demonstrates the usage of the progress indicator:
    setProgressIndicatorVisible (true);
    QTimer::singleShot ( 3000, this, SLOT(loadingFinished()) );
}

void
SkeletonWidget::loadingFinished()
{
    setProgressIndicatorVisible (false);
}

SkeletonWidget::~SkeletonWidget()
{
}


void SkeletonWidget::initWidget()
{
    MLayout *mainLayout = new MLayout(this);
    MLinearLayoutPolicy *mainLayoutPolicy =
            new MLinearLayoutPolicy(mainLayout, Qt::Horizontal);
    mainLayout->setPolicy(mainLayoutPolicy);
	
    //% "This is a skeleton applet, a minimal binaryapplet for controlpanel"
	m_aboutLabel = new MLabel(qtTrId("dcp_skel_appl_label"), this);
	m_aboutLabel->setStyleName("LabelAbout");
	
	mainLayoutPolicy->addItem(m_aboutLabel, Qt::AlignLeft);
    setLayout(mainLayout);
}

