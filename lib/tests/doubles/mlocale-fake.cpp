#include "mlocale-fake.h"

#include <QHash>
#include <QList>
#include <QString>

class FakeLocale {
    public:
        QList<QString> catalogs;
};

static const MLocale* defLocale = 0;
static QHash<const MLocale*, FakeLocale*> priv;

QList<QString> MLocale_installedCatalogs()
{
    return MLocale_catalogs(defLocale);
}

QList<QString> MLocale_catalogs(const MLocale* locale)
{
    return priv[locale]->catalogs;
}

MLocale::MLocale(QObject *parent):
    QObject(parent), d_ptr(0)
{
    priv.insert (this, new FakeLocale);
}

MLocale::MLocale(const MLocale &other, QObject *parent):
    QObject(parent), d_ptr(0)
{
    priv.insert (this, new FakeLocale);
    priv[this]->catalogs = priv[&other]->catalogs;
}

MLocale::MLocale(const QString &localeName, QObject *parent):
    QObject(parent), d_ptr(0)
{
    Q_UNUSED (localeName);
    priv.insert (this, new FakeLocale);
}

MLocale::~MLocale()
{
}

void MLocale::installTrCatalog(const QString &name)
{
    priv[this]->catalogs.append (name);
}

void MLocale::setDefault(const MLocale &locale)
{
    defLocale = &locale;
}


