#ifndef MGCONFITEM_FAKE_H__
#define MGCONFITEM_FAKE_H__

#include <MGConfItem>
#include <QMap>

struct MGConfItemFake {
    MGConfItemFake(const QString &key_) : key(key_) {}
    QString key;
    QVariant val;
};

static QMap<const MGConfItem*, MGConfItemFake*> fakeMap;
#define FAKE() fakeMap[this]


MGConfItem::MGConfItem(const QString &key, QObject *parent)
{
    Q_UNUSED(parent);
    fakeMap.insert(this, new MGConfItemFake(key));
}

MGConfItem::~MGConfItem()
{
    fakeMap.remove(this);
    delete FAKE();
}

QVariant MGConfItem::value() const
{
    return FAKE()->val;
}

QVariant MGConfItem::value(const QVariant &def) const
{
    if (FAKE()->val != QVariant::Invalid)
        return FAKE()->val;
    return def;
}

void MGConfItem::set(const QVariant &val)
{
    FAKE()->val = val;
}


void MGConfItem::unset()
{
    FAKE()->val = QVariant::Invalid;
}

QList<QString> MGConfItem::listDirs() const
{
    QList<QString> dummy;
    return dummy;
}

QList<QString> MGConfItem::listEntries() const
{
    QList<QString> dummy;
    return dummy;
}

#endif
