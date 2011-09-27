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
/* vim:set et sw=4 ts=4 sts=4: */

#include "dcpbrief.h"
#include "dcpwidgettypes.h"

#include "dcpdebug.h"
#include <QVariant>
DcpBrief::~DcpBrief()
{
}

/*!
 *
 * Default implementation of the widgetTypeID() virtual function. This function
 * should return an invalid value so that we know that we should search the
 * desktop file for a textual representation of the required widget type.
 */
int
DcpBrief::widgetTypeID () const
{
    return DcpWidgetType::BriefInvalid;
}

QString 
DcpBrief::icon() const
{
    return QString();
}

QString 
DcpBrief::toggleIconId() const
{
    return QString();
}

QString 
DcpBrief::valueText() const
{
    return QString();
}

QString
DcpBrief::titleText () const
{
    return QString();
}

Qt::Alignment 
DcpBrief::align() const
{
    return Qt::AlignLeft;
}

bool 
DcpBrief::toggle() const
{
    return false;
}

QString 
DcpBrief::image() const
{
    return QString();
}

void 
DcpBrief::setToggle (bool)
{
}

void 
DcpBrief::activate ()
{
    emit activateSignal();
}

QString DcpBrief::helpId() const
{
    // default is no help
    return QString();
}

int DcpBrief::minValue() const
{
    return 0;
}

int DcpBrief::maxValue() const
{
    return 100;
}

int DcpBrief::sliderSteps() const
{
    return 0;
}

void DcpBrief::setValue(const QVariant& value)
{
    // for compatibility with DcpBrief::toggle
    if (value.isValid() &&
        (widgetTypeID () == DcpWidgetType::Toggle ||
         widgetTypeID () == DcpWidgetType::Button))
    {
        bool newState = value.toBool();
        setToggle (newState);
    }
}

QVariant DcpBrief::value() const
{
    // for compatibility with DcpBrief::toggle
    if (widgetTypeID () == DcpWidgetType::Toggle ||
        widgetTypeID () == DcpWidgetType::Button)
    {
        return QVariant (toggle());
    }

    return QVariant();
}

QVariantList DcpBrief::possibleValues() const
{
    return QVariantList();
}

