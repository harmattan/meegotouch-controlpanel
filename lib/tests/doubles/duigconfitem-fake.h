#ifndef DUIGCONFITEM_FAKE_H__
#define DUIGCONFITEM_FAKE_H__

#include <DuiGConfItem>
#include <QMap>

struct DuiGConfItemFake {
    DuiGConfItemFake(const QString &key_) : key(key_) {}
    QString key;
    QVariant val;
};

static QMap<const DuiGConfItem*,DuiGConfItemFake*> fakeMap;
#define FAKE() fakeMap[this]


DuiGConfItem::DuiGConfItem(const QString &key, QObject *parent)
{
    Q_UNUSED(parent);
    fakeMap.insert(this, new DuiGConfItemFake(key));
}

DuiGConfItem::~DuiGConfItem()
{
    fakeMap.remove(this);
    delete FAKE();
}

QVariant DuiGConfItem::value() const
{
    return FAKE()->val;
}

QVariant DuiGConfItem::value(const QVariant &def) const
{
    if (FAKE()->val != QVariant::Invalid)
        return FAKE()->val;
    return def;
}

void DuiGConfItem::set(const QVariant &val)
{
    FAKE()->val = val;
}


void DuiGConfItem::unset()
{
    FAKE()->val = QVariant::Invalid;
}

QList<QString> DuiGConfItem::listDirs() const
{
    QList<QString> dummy;
    return dummy;
}

QList<QString> DuiGConfItem::listEntries() const
{
    QList<QString> dummy;
    return dummy;
}

#endif
