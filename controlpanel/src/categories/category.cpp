#include "category.h"

Category::~Category ()
{
}

QStringList Category::valueList (int key) const
{
    return value (key).split(QChar(','));
}

QString Category::parentId() const
{
    return value (ParentId);
}

QString Category::titleId() const
{
    return value (NameLogicalId);
}

QString Category::subtitleId() const
{
    return value (ValueLogicalId);
}

QString Category::name () const
{
    return value (NameId);
}

QString Category::title() const
{
    QString id = titleId();
    QString translated = qtTrId(qPrintable(id));

    if (translated == id)
        return "!! " + name ();
    else
        return translated;
}

QString Category::subtitle() const
{
    QString id = subtitleId();
    QString translated = qtTrId(qPrintable(id));

    if (translated == id)
        return "!! " + value (ValueId);
    else
        return translated;
}

QString Category::iconId() const
{
    return value (IconId);
}

QStringList Category::referenceIds() const
{
    QStringList result = valueList (AliasesId);
    result.prepend (name());
    result.prepend (titleId());
    return result;
}

bool Category::idMatch(const QString& id) const
{
    foreach (QString refId, referenceIds()) {
        if (refId == id) return true;
    }
    return false;
}

bool Category::isValid() const
{
    return !name().isEmpty();
}


void Category::addChild(const Category* child)
{
    m_Children.append (child);
}

QList<const Category*> Category::children() const
{
    return m_Children;
}

int Category::order () const
{
    bool ok;
    int result = value (OrderId).toInt(&ok);
    return ok ? result : 999999;
}

bool Category::containsUncategorized () const
{
    return idMatch ("Uncategorized");
}

bool Category::orderLessThan (const Category *c1, const Category *c2)
{
    return c1->order() < c2->order();
}

