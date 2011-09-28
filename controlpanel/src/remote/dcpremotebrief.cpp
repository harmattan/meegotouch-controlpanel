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

#include "dcpremotebrief.h"
#include "dcpremotebrief_p.h"

#include "dcpremotebriefreceiver.h"

#include <QVariant>


DcpRemoteBriefPriv::DcpRemoteBriefPriv (const QString& name):
    appletName (name)
{
}


DcpRemoteBrief::DcpRemoteBrief (const QString& appletName, QObject* parent):
    priv (new DcpRemoteBriefPriv (appletName))
{
    setParent (parent);
    DcpRemoteBriefReceiver* receiver = DcpRemoteBriefReceiver::instance();
    if (receiver) {
        receiver->watch (this);
    }
}

DcpRemoteBrief::~DcpRemoteBrief ()
{
    DcpRemoteBriefReceiver* receiver = DcpRemoteBriefReceiver::instance();
    if (receiver) {
        receiver->unwatch (this);
        /*
         * This is disabled because restarting the process takes time, so
         * it is only destroyed at controlpanel closing by the opsystem
         *
        if (receiver->watchCount () == 0) {
            delete receiver;
        }
        */
    }

    delete priv;
}


int DcpRemoteBrief::widgetTypeID () const
{
    bool ok;
    int value = this->get (BSupplier::OutputWidgetTypeID).toInt (&ok);
    return ok ? value : DcpBrief::widgetTypeID ();
}


QString DcpRemoteBrief::valueText () const
{
    QString st = get (BSupplier::OutputValueText);
    return st;
}


QString DcpRemoteBrief::icon () const
{
    return get (BSupplier::OutputIcon);
}

void DcpRemoteBrief::setValue (const QVariant& value)
{
    if (this->value() != value) {
        DcpRemoteBriefReceiver* receiver = DcpRemoteBriefReceiver::instance();
        if (receiver) {
            receiver->setValue (name (), value);
        }
    }
}

QVariant DcpRemoteBrief::value () const
{
    return get (BSupplier::OutputValue);
}

int DcpRemoteBrief::minValue () const
{
    bool ok;
    int value = this->get (BSupplier::OutputMinValue).toInt (&ok);
    return ok ? value : DcpBrief::minValue ();
}

int DcpRemoteBrief::maxValue () const
{
    bool ok;
    int value = this->get (BSupplier::OutputMaxValue).toInt (&ok);
    return ok ? value : DcpBrief::maxValue ();
}

int DcpRemoteBrief::sliderSteps () const
{
    bool ok;
    int value = this->get (BSupplier::OutputValueStep).toInt (&ok);
    return ok ? value : DcpBrief::sliderSteps ();
}

QString DcpRemoteBrief::name () const
{
    return priv->appletName;
}

QString DcpRemoteBrief::titleText () const
{
    return get (BSupplier::OutputTitleText);
}


QString DcpRemoteBrief::helpId () const
{
    return get (BSupplier::OutputHelpId);
}

QVariantList DcpRemoteBrief::possibleValues () const
{
    QString listStr = get (BSupplier::OutputPossibleValues);
    if (listStr.isEmpty()) return QVariantList();

    QStringList list = listStr.split (BSupplier::ParamSeparator);
    QVariantList vlist;
    foreach (QString item, list) {
        vlist << item;
    }
    return vlist;
}

QString DcpRemoteBrief::get (const char* id) const
{
    return priv->values.value (id).trimmed();
}

void DcpRemoteBrief::set (const char* id, const QString& value)
{
    priv->values[id] = value;
}

void DcpRemoteBrief::emitChange ()
{
    emit valuesChanged ();
}


