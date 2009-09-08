#include "dcpicuconversions.h"

// a copy of these functions exists in DuiIcuConversions,
// but they are internal.

// it is a workaround to be able to run on desktop (without scratchbox),
// otherwise can be safely replaced with the versions there

QString unicodeStringToQString(const icu::UnicodeString &sourceStr)
{
    return QString(reinterpret_cast<const QChar*>(sourceStr.getBuffer()),
                   sourceStr.length());
}

icu::UnicodeString qStringToUnicodeString(const QString &sourceStr)
{
    return UnicodeString(static_cast<const UChar*>(sourceStr.utf16()));
}

