#ifndef DCPICUCONVERSIONS_H
#define DCPICUCONVERSIONS_H

#include <unicode/unistr.h>
#include <QString>

QString unicodeStringToQString(const icu::UnicodeString &sourceStr);
icu::UnicodeString qStringToUnicodeString(const QString &sourceStr);

#endif // DCPICUCONVERSIONS_H
