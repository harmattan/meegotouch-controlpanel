#include "dcpcategories.h"
#include "memorycategory.h"
#include "filecategory.h"

#include <QDir>

DcpCategories* DcpCategories::sm_Instance = 0;

DcpCategories* DcpCategories::instance()
{
    if (!sm_Instance) {
        sm_Instance = new DcpCategories();
    }
    return sm_Instance;
}


void DcpCategories::destroy()
{
    delete sm_Instance;
}


DcpCategories::~DcpCategories()
{
    // unmarks the instance:
    sm_Instance = 0;

    // free up
    qDeleteAll (m_Categories);
}


Category* DcpCategories::categoryById(const QString& id) const
{
    return m_CategoryById.value (id);
}


QList<const Category*> DcpCategories::categoryChildren(const QString& id) const
{
    const Category* category = categoryById (id);
    return category ? category->children () : QList<const Category*>();
}


DcpCategories::DcpCategories()
{
    // add the main category:
    add (new MemoryCategory (mainPageCategoryName(), // <- name
                             "qtn_sett_main_title", "Settings" // <- translation
                            ));

    // load the available categories:
    QDir dir (DCP_CATEGORY_DIR);
    QStringList nameFilters(QString("*.cpcategory"));
    foreach (QString fileName,
             dir.entryList (nameFilters, QDir::Readable | QDir::Files))
    {
        Category* category = new FileCategory (DCP_CATEGORY_DIR "/" + fileName);

        if (category->isValid()) {
            add (category);
        } else {
            qWarning ("Non valid category: %s", qPrintable(fileName));
            delete category;
        }
    }

    // build the parent - child relationships:
    foreach (const Category* category, m_Categories) {
        categoryById (category->parentId())->addChild (category);
    }

    // sort by order:
    qSort (m_Categories.begin(), m_Categories.end(), Category::orderLessThan);
}

/*!
 * Little helper for the constructor,
 * do not use it to add more categories later
 */
void DcpCategories::add (Category* category)
{
    m_Categories.append (category);

    // hash by their ids:
    foreach (QString id, category->referenceIds()) {
        m_CategoryById.insert (id, category);
    }
}

bool DcpCategories::hasCategory (const QString& id)
{
    return instance()->categoryById(id) != 0;
}

