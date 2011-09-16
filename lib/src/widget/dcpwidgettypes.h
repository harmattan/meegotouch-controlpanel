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

/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#ifndef DCPWIDGETTYPES_H
#define DCPWIDGETTYPES_H
#include <QString>

enum Q_DECL_DEPRECATED WIDGETTYPEID {
    DCPBRIEFWIDGETINVALID = 0,
    DCPLABEL,           //"DcpLabel"
    DCPLABEL2,          //"DcpLabel2"
    DCPLABELBUTTON,     //"DcpLabelButton"
    DCPLABEL2BUTTON,    //"DcpLabel2Button"
    DCPLABEL2IMAGE,     //"DcpLabel2Image"
    DCPLABEL2TOGGLE,    //"DcpLabel2Toggle"
    WIDGETN
};

namespace DcpWidgetType
{
        enum Id {
            BriefInvalid = 100,
            Label,
            Toggle,
            Image,
            Button,
            Special,
            Slider,
            IdMax
        };
        const QString  
        names[IdMax - BriefInvalid] = 
        {
            "DcpBriefWidgetInvalid",
            "Label",
            "Toggle",
            "Image",
            "Button",
            "Special",
            "Slider"
        };
        bool isIdValid(int id); 
};

static const QString  
Q_DECL_DEPRECATED WIDGETNAME[] = 
{
    "DcpBriefWidgetInvalid",
    "DcpLabel",
    "DcpLabel2",
    "DcpLabelButton",
    "DcpLabel2Button",
    "DcpLabel2Image",
    "DcpLabel2Toggle",
};

#define DCP_WIDGET_TYPE_VALID(type) ((type) >= DCPLABEL && \
                                     (type) <= DCPLABEL2TOGGLE)

#endif // DCPWIDGETTYPES_H
