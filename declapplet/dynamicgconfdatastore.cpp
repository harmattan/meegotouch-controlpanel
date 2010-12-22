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

#include "dynamicgconfdatastore.h"

#include <MGConfItem>
#include <dcpdebug.h>

DynamicGConfDataStore::DynamicGConfDataStore(QObject* parent):
    MDataStore ()
{
    setParent (parent);
}


DynamicGConfDataStore::~DynamicGConfDataStore()
{
    qDeleteAll (m_GConf.values());
}

void DynamicGConfDataStore::ensureKeyInit (const QString& key)
{
    if (m_GConf.contains (key)) return;

    MGConfItem* item = new MGConfItem (key);
    connect(item, SIGNAL(valueChanged()), this, SLOT(gconfValueChanged()));
    m_GConf.insert (key, item);
}

QVariant DynamicGConfDataStore::value(const QString &key) const
{
    const_cast<DynamicGConfDataStore*>(this)->ensureKeyInit (key);
    QVariant st = m_GConf[key]->value ();
//    qWarning ("DGCD: %s == %s", qPrintable (key), qPrintable (st.toString()));
    return st;
}


bool DynamicGConfDataStore::setValue(const QString &key, const QVariant &value)
{
    ensureKeyInit (key);
    m_GConf[key]->set (value);
//    qWarning ("DGCD: %s := %s", qPrintable (key), qPrintable (value.toString()));
    return true;
}


QStringList DynamicGConfDataStore::allKeys() const
{
    return m_GConf.keys();
}


bool DynamicGConfDataStore::contains (const QString &key) const
{
    return key.startsWith ("/");
}


bool DynamicGConfDataStore::createValue (const QString &key,
                                         const QVariant &value)
{
    return setValue (key, value);
}


void DynamicGConfDataStore::remove(const QString &key)
{
    setValue (key, QVariant());
}


void DynamicGConfDataStore::clear()
{
    qWarning ( "%s: not clearing anything, because the result would be "
               "unpredictable", Q_FUNC_INFO);
}


void DynamicGConfDataStore::gconfValueChanged()
{
    MGConfItem* sender = qobject_cast<MGConfItem*>(this->sender());
    dcp_failfunc_unless (sender);
    emit valueChanged (sender->key(), sender->value());
}

