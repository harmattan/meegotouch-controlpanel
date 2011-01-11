#include <QDir>

QStringList QDir::entryList ( const QStringList &, Filters, SortFlags) const
{
    static QStringList list;
    return list;
}

