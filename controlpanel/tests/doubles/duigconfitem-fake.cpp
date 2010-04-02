#ifndef STUB_DUIGCONFITEM_H
#define STUB_DUIGCONFITEM_H

#include <DuiGConfItem>
#include <QHash>
#include <QList>
#include <QtDebug>

#include "duigconfitem_priv.h"

// stub class for duigconfitem which simulates its exact work,
// when gconf is working
//
// it simulates the followings:
// - changing a value for a key
// - emitting the itemChanged signal

static QHash<QString, QVariant> gconf_database;
static int gconfItemConstructCount = 0;
static QList<DuiGConfItemPrivate*> gconfitemprivates;

DuiGConfItem::DuiGConfItem  (const QString &key, QObject *)
{
    priv = new DuiGConfItemPrivate;
    priv->key = key;
    gconfItemConstructCount++;
    gconfitemprivates.append(this->priv);
    connect (priv, SIGNAL(valueChanged()),
             this, SIGNAL(valueChanged()));
}

DuiGConfItem::~DuiGConfItem ()
{
    gconfitemprivates.removeOne(priv);
    delete priv;
    gconfItemConstructCount--;
}

void gconf_changevalue(const QString& key, const QVariant& value)
{
    gconf_database[key] = value;
    foreach(DuiGConfItemPrivate * priv, gconfitemprivates)
    {
        if (priv->key == key) {
            priv->emitChangedSignal();
        }
    }
}

QString DuiGConfItem::key () const
{
    return priv->key;
}

QVariant DuiGConfItem::value () const
{
    return value(QVariant());
}

QVariant DuiGConfItem::value (const QVariant &def) const
{
    return gconf_database.contains(key()) ? gconf_database.value(key()) : def;
}

void DuiGConfItem::set (const QVariant &val)
{
    gconf_changevalue(key(), val);
}


#endif // STUB_DUIGCONFITEM_H

