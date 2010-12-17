#include "filecategory.h"

#include <QSettings>

const char* FileCategory::keys[KeyIdMax] = {
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

FileCategory::FileCategory(const QString& fileName):
    m_Settings (new QSettings (fileName, QSettings::IniFormat))
{
}

FileCategory::~FileCategory ()
{
    delete m_Settings;
}

inline QString FileCategory::value (int key) const
{
    return m_Settings->value (keys[key]).toString();
}

bool FileCategory::isValid() const
{
    return m_Settings && (m_Settings->status() == QSettings::NoError) &&
           Category::isValid();
}

