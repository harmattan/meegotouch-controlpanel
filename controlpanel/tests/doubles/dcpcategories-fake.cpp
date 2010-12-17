#include "dcpcategories.h"
#include "memorycategory.h"

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
    add (new MemoryCategory (
                      "FAKE-CATEGORY",
                      "fake-category",
                      "MainPage",
                      "qtn_subtitle",
                      "Value line",
                      "icon"));

    add (new MemoryCategory (
                      "ZERO",
                      "",
                      "",
                      "MainPage",
                      "",
                      ""));

    add (new MemoryCategory (
                      "MainPage",
                      "qtn_sett_main_title",
                      "",
                      "",
                      "",
                      ""));
}

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

