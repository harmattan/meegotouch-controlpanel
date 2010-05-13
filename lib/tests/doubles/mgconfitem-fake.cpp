#include <MGConfItem>
#include "mgconfitem-fake.h"
#include <QMap>
#include <QSet>

static QMap<QString, QVariant> database;

struct MGConfItemFake {
    MGConfItemFake(const QString &key_) : key(key_) {}
    QString key;
};

void emptyFakeGConf()
{
    database.clear();
}

static QMap<const MGConfItem*, MGConfItemFake*> fakeMap;
#define FAKE fakeMap[this]


MGConfItem::MGConfItem(const QString &key, QObject *parent)
{
    Q_UNUSED(parent);
    fakeMap.insert(this, new MGConfItemFake(key));
}

MGConfItem::~MGConfItem()
{
    delete fakeMap.take(this);
}

QVariant MGConfItem::value() const
{
    return value(QVariant());
}

QVariant MGConfItem::value(const QVariant &def) const
{
    const QVariant& item = database[FAKE->key];
    if (item != QVariant::Invalid)
        return item;
    else
        return def;
}

void MGConfItem::set(const QVariant &val)
{
    database[FAKE->key] = val;
    if (!val.isValid()) database.remove(FAKE->key);
}


void MGConfItem::unset()
{
    set (QVariant());
}

QList<QString> MGConfItem::listDirs() const
{
    QList<QString> result;
    foreach (QString key, database.keys()) {
        if (key.startsWith(FAKE->key + "/") &&
                key.count('/') > FAKE->key.count('/')+1)
        {
            key.truncate (key.indexOf ('/', FAKE->key.size()+1));
            result << key;
        }
    }
    return result.toSet().toList();;
}

QList<QString> MGConfItem::listEntries() const
{
    QList<QString> result;
    foreach (QString key, database.keys()) {
        if (key.startsWith(FAKE->key + "/") &&
                key.count('/') == FAKE->key.count('/')+1)
        {
            result << key;
        }
    }
    return result.toSet().toList();
}

