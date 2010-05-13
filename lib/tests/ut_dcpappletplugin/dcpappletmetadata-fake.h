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

#ifndef DCPAPPLETMETADATA_FAKE_H__
#define DCPAPPLETMETADATA_FAKE_H__

#include <QString>
#include "dcpappletmetadata.h"

namespace DcpAppletMetadataFake {

// set this variable before calling DcpAppletMetadata functions
// depending on whether you want to test binary or dsl loading
enum AppletType {
    TYPE_BINARY,
    TYPE_DSL
};

static AppletType appletType = TYPE_BINARY;

} // namespace

// DcpAppletLoader::load() decides the applet type based on non-emptyness
// of the return value of fullBinary() and dslFilename()
QString DcpAppletMetadata::fullBinary() const
{
    if (DcpAppletMetadataFake::appletType == 
        DcpAppletMetadataFake::TYPE_BINARY) {
        return "dummy-binary";
    }
    return QString();
}

QString DcpAppletMetadata::dslFilename() const
{
    if (DcpAppletMetadataFake::appletType == 
        DcpAppletMetadataFake::TYPE_DSL) {
        return "dummy-dsl";
    }
    return QString();
}

#endif
