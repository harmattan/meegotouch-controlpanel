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

#ifndef FAKEAPPLICATIONSERVICE_H
#define FAKEAPPLICATIONSERVICE_H

#include <MApplicationService>

class FakeApplicationService: public MApplicationService
{
    Q_OBJECT
public:
    FakeApplicationService();

    virtual bool isRegistered ();
    virtual bool registerService ();

private:
	
};


#endif // FAKEAPPLICATIONSERVICE_H
