#include "memorycategory.h"


MemoryCategory::MemoryCategory(const QString& name,
                               const QString& titleId,
                               const QString& parentId,
                               const QString& subtitleId,
                               const QString& subtitle,
                               const QString& iconId,
                               int order,
                               const QStringList& compatibilityIds)
{
    data.insert (ParentId, parentId);
    data.insert (NameId, name);
    data.insert (NameLogicalId, titleId);
    data.insert (ValueId, subtitle);
    data.insert (ValueLogicalId, subtitleId);
    data.insert (IconId, iconId);
    data.insert (AliasesId, compatibilityIds.join(QChar(',')));
    data.insert (OrderId, QString::number (order));
}

QString MemoryCategory::value(int key) const
{
    return data.value (key);
}

