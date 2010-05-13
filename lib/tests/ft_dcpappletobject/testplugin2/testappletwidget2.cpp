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
#include "testappletwidget2.h"

TestAppletWidget2::TestAppletWidget2(QGraphicsWidget *parent)
    : DcpWidget(parent)
{
    MLayout *layout = new MLayout(this);
    MLinearLayoutPolicy *layoutPolicy = 
        new MLinearLayoutPolicy(layout, Qt::Vertical);
    layout->setPolicy(layoutPolicy);

    MLabel *widget = new MLabel("Test applet2", this);
    layoutPolicy->addItem(widget, Qt::AlignLeft);

    setLayout(layout);

}

TestAppletWidget2::~TestAppletWidget2()
{
}
