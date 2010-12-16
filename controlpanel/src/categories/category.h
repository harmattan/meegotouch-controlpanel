#ifndef CATEGORY_H
#define CATEGORY_H

#include <QStringList>
class QSettings;

/*!
 * A class that describes an applet category that should appear inside the
 * control panel. It is read from an ini file.
 */
class Category
{
public:
    Category(const QString& fileName);
    ~Category();

    QString parentId () const;

    QString titleId () const;
    QString subtitleId () const;
    QString name () const;
    QString title () const;
    QString subtitle () const;

    QString iconId () const;
    int order () const;

    QStringList referenceIds () const;

    bool idMatch (const QString& id) const;

    bool isValid () const;
    void addChild (const Category* child);
    QList<const Category*> children () const;

    bool containsUncategorized () const;
    static bool orderLessThan (const Category* cat1, const Category* cat2);

protected:
    QString value (int key) const;
    QStringList valueList (int key) const;

private:
    QSettings* m_Settings;
    QList<const Category*> m_Children;
};


#endif // CATEGORY_H

