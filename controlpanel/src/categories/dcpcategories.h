#ifndef DCPCATEGORIES_H
#define DCPCATEGORIES_H

#include <QList>
#include <QHash>
#include <QString>
class Category;

class DcpCategories
{
public:
    static DcpCategories* instance();
    static void destroy();
    ~DcpCategories();

    Category* categoryById (const QString& id) const;
    QList<const Category*> categoryChildren (const QString& id) const;

    static bool hasCategory (const QString& id);

    Category* mainPageCategory () const {
        return categoryById (mainPageCategoryName());
    }
    static QString mainPageCategoryName () { return "MainPage"; }

private:
    DcpCategories();
    static DcpCategories* sm_Instance;

    QList<Category*> m_Categories;
    QHash<QString, Category*> m_CategoryById;
};

#endif // DCPCATEGORIES_H

