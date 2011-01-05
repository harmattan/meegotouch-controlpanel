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

#include "specialicon.h"

#include "dcpskeleton.h"

#include <MButton>
#include <QGraphicsLinearLayout>

SpecialIcon::SpecialIcon()
{
    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout (this);
    MButton* button1 = new MButton ("Open a page");
    MButton* button2 = new MButton ("Open Date & Time");
    layout->addItem (button1);
    layout->addItem (button2);
    connect (button1, SIGNAL (clicked()), this, SLOT(onClick1()));
    connect (button2, SIGNAL (clicked()), this, SLOT(onClick2()));
}

void SpecialIcon::onClick1()
{
    emit changeWidget (DcpSkeleton::Main);
}

void SpecialIcon::onClick2()
{
    emit activatePluginByName ("Date & Time");
}

