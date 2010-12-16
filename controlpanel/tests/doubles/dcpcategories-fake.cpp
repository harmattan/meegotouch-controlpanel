#include "dcpcategories.h"
#include "category.h"
#include "category-fake.h"

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
    Category_setData ("file1",
                      "FAKE-CATEGORY",
                      "MainPage",
                      "Title",
                      "fake-category",
                      "Value line",
                      "qtn_subtitle",
                      "icon");
    Category_setData ("file2",
                      "ZERO",
                      "MainPage",
                      "Zero title",
                      "",
                      "",
                      "",
                      "");
    Category_setData ("file3",
                      "MainPage",
                      "",
                      "MainPage Title",
                      "qtn_sett_main_title",
                      "",
                      "",
                      "");

    m_Categories.append (new Category ("file1"));
    m_Categories.append (new Category ("file2"));
    m_Categories.append (new Category ("file3"));

    foreach (Category* cat, m_Categories) {
        foreach (QString id, cat->referenceIds()) {
            m_CategoryById.insert (id, cat);
        }
    }
}


bool DcpCategories::hasCategory (const QString& id)
{
    return instance()->categoryById(id) != 0;
}

