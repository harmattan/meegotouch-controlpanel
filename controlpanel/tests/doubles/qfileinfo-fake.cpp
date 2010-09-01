#include "qfileinfo-fake.h"

#include <QSet>
#include <QHash>
#include <QFileInfo>
#include <QString>

static QSet<QString> existingFiles;
static QHash<const QFileInfo*, QString> priv;
class QFileInfoPrivate {};

void qfileinfo_setExists (const QString& filePath, bool exists)
{
    if (exists) {
        existingFiles.insert (filePath);
    } else {
        existingFiles.remove (filePath);
    }
}

QFileInfo::QFileInfo ( const QString & file )
{
    priv[this] = file;
}


bool QFileInfo::exists () const
{
    return existingFiles.contains (this->filePath());
}

QString QFileInfo::filePath () const
{
    return priv[this];
}

