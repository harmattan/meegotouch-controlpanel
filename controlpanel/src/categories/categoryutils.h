#ifndef CATEGORYUTILS_H
#define CATEGORYUTILS_H

#include "category.h"

class DcpAppletMetadata;
typedef QList<DcpAppletMetadata*> DcpAppletMetadataList;

namespace CategoryUtils
{
    bool isVisible (const Category* category);
    bool isEmpty (const Category* category);
    DcpAppletMetadataList metadataList (const Category* category);

};

#endif // CATEGORYUTILS_H

