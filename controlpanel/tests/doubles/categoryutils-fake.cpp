#include "categoryutils.h"

bool CategoryUtils::isVisible(const Category*)
{
    return true;
}

bool CategoryUtils::isEmpty (const Category*)
{
    return false;
}

DcpAppletMetadataList CategoryUtils::metadataList (const Category* category)
{
    DcpAppletMetadataList list;
    return list;
}

