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

#ifndef DCPREMOTEAPPLETOBJECT_H
#define DCPREMOTEAPPLETOBJECT_H

#include <DcpAppletObject>

class DcpRemoteAppletObject: public DcpAppletObject
{
    Q_OBJECT
public:
    DcpRemoteAppletObject(DcpAppletMetadata* metadata, QObject* parent = 0);

protected:
    virtual bool loadPluginFile (const QString &binaryPath);

private:
	
};


#endif // DCPREMOTEAPPLETOBJECT_H
