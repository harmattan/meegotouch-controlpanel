#ifndef MLOCALE_FAKE_H
#define MLOCALE_FAKE_H

#include <MLocale>

QList<QString> MLocale_installedCatalogs();
QList<QString> MLocale_catalogs(const MLocale* locale);

#endif // MLOCALE_FAKE_H

