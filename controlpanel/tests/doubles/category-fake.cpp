#include "category.h"

#include <QHash>

class CategoryPriv
{
public:
    QString name;
    QString parentId;

    QString title;
    QString titleId;

    QString subtitle;
    QString subtitleId;

    QString iconId;
};

static QHash<QString, CategoryPriv> categoryFiles;
static QHash<const Category*, CategoryPriv*> categoryPrivs;

void Category_setData (const QString& fileName,
                       const QString& name,
                       const QString& parentId,
                       const QString& title,
                       const QString& titleId,
                       const QString& subtitle,
                       const QString& subtitleId,
                       const QString& iconId)
{
    if (!categoryFiles.contains(fileName)) {
        categoryFiles.insert (fileName, CategoryPriv());
    }
    categoryFiles[fileName].name = name;
    categoryFiles[fileName].parentId = parentId;
    categoryFiles[fileName].title = title;
    categoryFiles[fileName].titleId = titleId;
    categoryFiles[fileName].subtitle = subtitle;
    categoryFiles[fileName].subtitleId = subtitleId;
    categoryFiles[fileName].iconId = iconId;
}

Category::Category(const QString& fileName)
{
    if (categoryFiles.contains(fileName)) {
        categoryPrivs.insert (this,
                new CategoryPriv(categoryFiles.value(fileName)));
    } else {
        categoryPrivs.insert (this, new CategoryPriv);
    }
}

Category::~Category ()
{
    delete categoryPrivs.value(this);
    categoryPrivs.remove (this);
}

QString Category::value (int) const
{
    return QString();
}

QStringList Category::valueList (int) const
{
    return QStringList();
}

QString Category::parentId() const
{
    return categoryPrivs.value(this)->parentId;
}

QString Category::titleId() const
{
    return categoryPrivs.value(this)->titleId;
}

QString Category::subtitleId() const
{
    return categoryPrivs.value(this)->subtitleId;
}

QString Category::name () const
{
    return categoryPrivs.value(this)->name;
}

QString Category::title() const
{
    return categoryPrivs.value(this)->title;
}

QString Category::subtitle() const
{
    return categoryPrivs.value(this)->subtitle;
}

QString Category::iconId() const
{
    return categoryPrivs.value(this)->iconId;
}

QStringList Category::referenceIds() const
{
    QStringList result;
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
    return name().isEmpty();
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
    return 0;
}

bool Category::containsUncategorized () const
{
    return false;
}

bool Category::orderLessThan (const Category *c1, const Category *c2)
{
    return c1->order() < c2->order();
}

