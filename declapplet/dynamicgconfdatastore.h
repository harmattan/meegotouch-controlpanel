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

#ifndef DYNAMICGCONFDATASTORE_H
#define DYNAMICGCONFDATASTORE_H

#include <MDataStore>
#include <QHash>
class MGConfItem;

/*! @brief Dynamic gconf datastore
 *
 * Similar to MGConfDataStore, but that one only watches all key in one
 * directory. Instead this can watch all keys, but only those, whose value
 * was requested at least once.
 */
class DynamicGConfDataStore: public MDataStore
{
    Q_OBJECT

public:
    DynamicGConfDataStore(QObject* parent = 0);
    virtual ~DynamicGConfDataStore ();
    virtual QVariant value (const QString &key) const;
    virtual bool setValue (const QString &key, const QVariant &value);
    virtual QStringList allKeys () const;
    virtual bool contains (const QString &key) const;
    virtual bool createValue (const QString &key, const QVariant &value);
    virtual void remove (const QString &key);
    virtual void clear ();

signals:
    void valueChanged (const QString &key, const QVariant &value);

protected slots:
    void gconfValueChanged();

private:
    void ensureKeyInit (const QString& key);
    QHash<QString, MGConfItem*> m_GConf;
};


#endif // DYNAMICGCONFDATASTORE_H
