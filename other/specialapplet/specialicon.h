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

#ifndef SPECIALICON_H
#define SPECIALICON_H

#include <DcpWidget>

class SpecialIcon: public DcpWidget
{
    Q_OBJECT

public:
    SpecialIcon();

protected slots:
    void onClick1();
    void onClick2();

private:

};


#endif // SPECIALICON_H
