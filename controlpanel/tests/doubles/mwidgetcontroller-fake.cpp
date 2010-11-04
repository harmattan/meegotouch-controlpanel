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

#include <MWidgetController>

void MWidgetController::setView(MWidgetView*) {}
MWidgetController::MWidgetController(QGraphicsItem *parent){ QGraphicsItem::setParentItem(parent); }
void MWidgetController::setObjectName (const QString&) {}
void MWidgetController::setStyleName (QString const&) {}
MWidgetController::~MWidgetController() {}

