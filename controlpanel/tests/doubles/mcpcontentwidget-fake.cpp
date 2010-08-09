/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of mcontrolpanel.
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#include <McpContentWidget>
#include <QHash>

class DcpAppletObject;
static QHash<const McpContentWidget*, DcpAppletObject*> applets;

McpContentWidget::McpContentWidget(DcpAppletObject* applet, QGraphicsItem*): d_ptr(0)
{
    setApplet(applet);
}

McpContentWidget::~McpContentWidget(){}

void McpContentWidget::setApplet(DcpAppletObject* applet)
{
    applets[this] = applet;
}

DcpAppletObject* McpContentWidget::applet() const{ return applets[this]; }

void McpContentWidget::setMattiID(const QString&) {}
QString McpContentWidget::mattiID() const {return QString(); }
void McpContentWidget::updateContents(){}
void McpContentWidget::retranslateUi(){}
void McpContentWidget::showEvent(QShowEvent*){}
void McpContentWidget::hideEvent(QHideEvent*){}
void McpContentWidget::constructRealWidget(){}
void McpContentWidget::updateText(){}
void McpContentWidget::updateImage(){}
void McpContentWidget::setImageFromFile(const QString&){}
void McpContentWidget::setImageName(const QString&){}

