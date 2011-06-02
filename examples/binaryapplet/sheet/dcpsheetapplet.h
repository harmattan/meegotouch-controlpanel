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

#ifndef SHEETAPPLET_H
#define SHEETAPPLET_H

#include <DcpAppletIf>
#include <QObject>
class MAction;

class SheetApplet : public QObject, public DcpAppletIf
{
	Q_OBJECT
	Q_INTERFACES(DcpAppletIf)

public:
    virtual QString title() const;
    virtual QVector<MAction *> viewMenuItems();

    virtual MSheet* constructSheet (int widgetId);
};

#endif // SHEETAPPLET_H

