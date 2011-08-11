#include "categoryutils.h"

#include "dcpappletmanager.h"
#include "category.h"
#include "dcpcategories.h"

bool CategoryUtils::isVisible (const Category* category)
{
    if (category->hideIfEmpty()) {
        return !isEmpty (category);
    }
    return true;
}

bool CategoryUtils::isEmpty (const Category* category)
{
     return metadataList (category).isEmpty();
}

DcpAppletMetadataList CategoryUtils::metadataList (const Category* category)
{
    bool withUncategorized = category->containsUncategorized();
    return DcpAppletManager::instance()->listByCategory (
             category->referenceIds(),
             withUncategorized ? DcpCategories::hasCategory : NULL);
}


