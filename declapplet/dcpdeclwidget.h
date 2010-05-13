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

#ifndef DCPDECLWIDGET_H
#define DCPDECLWIDGET_H

#include "dcpwidget.h"

class DcpDeclWidget: public DcpWidget
{
    Q_OBJECT
public:
    DcpDeclWidget(const QString& xmlPath);

private:
    void createErrorLabel(const QString& text);

};


#endif // DCPDECLWIDGET_H
