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

#ifndef TESTAPPLETWIDGET_H__
#define TESTAPPLETWIDGET_H__

#include <DcpWidget>

class TestAppletWidget : public DcpWidget
{
   Q_OBJECT

    public:
       TestAppletWidget(QGraphicsWidget *parent=0);
       virtual ~TestAppletWidget();
};

#endif
