#ifndef MEMORYCATEGORY_H
#define MEMORYCATEGORY_H

#include "category.h"

#include <QHash>

class MemoryCategory: public Category
{
public:
    MemoryCategory (const QString& name,
                    const QString& titleId = QString(),
                    const QString& parentId = QString(),
                    const QString& subtitleId = QString(),
                    const QString& subtitle = QString(),
                    const QString& iconId = QString(),
                    int order = 0,
                    const QStringList& compatibilityIds = QStringList());

protected:
    virtual QString value (int key) const;

private:
    QHash<int, QString> data;
};


#endif // MEMORYCATEGORY_H

