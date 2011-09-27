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

#ifndef DCPAPPLETOBJECT_H
#define DCPAPPLETOBJECT_H

#include "dcpappletplugin.h" 
#include <QString>
#include <QVariant>
class DcpAppletIf;
class DcpAppletMetadata;
class DcpBrief;
class DcpWidget;

class DcpAppletObjectPrivate;

/*!
 * \class DcpAppletObject
 * \brief This class represents all informations about the applet.
 *
 * \details It both gives access to the binary libs of the applet,
 * and its desktop file.
 */


class DcpAppletObject : public DcpAppletPlugin
{
    Q_OBJECT
public:
    DcpAppletObject(DcpAppletMetadata *metadata);
    DcpAppletObject(DcpAppletMetadata *metadata, bool tryLoad);
    virtual ~DcpAppletObject();

    QString toggleIconId () const;

    int widgetTypeID () const;

    Qt::Alignment align () const;
    bool toggle () const;

    QString text1 () const;
    QString text2 () const;

    QString iconName() const;
    QString imageName() const;
    int getMainWidgetId () const;

    QString helpId () const;

    DcpBrief* brief() const;
    QVariant value() const;
    QVariantList possibleValues() const;
    int minValue() const;
    int maxValue() const;
    int sliderSteps() const;

    int briefVersion() const;

signals:
    void briefChanged ();
    void activate (int pageId);
    void requestPluginActivation (const QString& pluginName);

public slots:
    void slotClicked ();
    void setToggle (bool checked);
    bool activatePluginByName (const QString &name) const;
    void activateSlot(int widgetId = -1);
    void setValue(const QVariant& value);

protected:
    void setBrief (DcpBrief* brief);

    DcpAppletObjectPrivate *const d_ptr;
    Q_DISABLE_COPY (DcpAppletObject);
};

#endif

