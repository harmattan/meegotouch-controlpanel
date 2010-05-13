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

#include <MLabel>
#include <MContainer>
#include <MLayout>
#include <MLinearLayoutPolicy>
#include <MButton>
#include <MButtonGroup>
#include "testappletwidget.h"

TestAppletWidget::TestAppletWidget(QGraphicsWidget *parent)
    : DcpWidget(parent)
{
    MLayout *layout = new MLayout(this);
    MLinearLayoutPolicy *layoutPolicy = 
        new MLinearLayoutPolicy(layout, Qt::Vertical);
    layout->setPolicy(layoutPolicy);

    MLabel *widget = new MLabel("Test applet1", this);
    layoutPolicy->addItem(widget, Qt::AlignLeft);

    /*
    MContainer *container = new MContainer("Test container", this);
    layoutPolicy->addItem(container);

    MButtonGroup *buttongrp = new MButtonGroup();
    for (int i = 0; i < 3; ++i) {
        MButton *button = new MButton(QString("%1").arg(i));
        buttongrp->addButton(button);
        layoutPolicy->addItem(button);
    }
*/
    setLayout(layout);

}

TestAppletWidget::~TestAppletWidget()
{
}
