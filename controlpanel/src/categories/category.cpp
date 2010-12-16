#include "category.h"

#include <QSettings>

enum {
    ParentId,
    NameId,
    NameLogicalId,
    ValueId,
    ValueLogicalId,
    IconId,
    AliasesId,
    TranslationId,
    OrderId,
    KeyIdMax
};

const char* keys[KeyIdMax] = {
    "Parent",
    "Name",
    "Name-logical-id",
    "Value",
    "Value-logical-id",
    "Icon",
    "Aliases",
    "Translation-catalogs",
    "Order"
};

Category::Category(const QString& fileName):
    m_Settings (new QSettings (fileName, QSettings::IniFormat))
{
}

Category::~Category ()
{
    delete m_Settings;
}

inline QString Category::value (int key) const
{
    return m_Settings->value (keys[key]).toString();
}

inline QStringList Category::valueList (int key) const
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
    qDebug ("XXX valid? %p %d %s", m_Settings, m_Settings->status(),
           qPrintable(name()));

    return m_Settings && (m_Settings->status() == QSettings::NoError) &&
           !name().isEmpty();
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
    return m_Settings->value (keys[OrderId], 9999).toInt();
}

bool Category::containsUncategorized () const
{
    return idMatch ("Uncategorized");
}

bool Category::orderLessThan (const Category *c1, const Category *c2)
{
    return c1->order() < c2->order();
}

