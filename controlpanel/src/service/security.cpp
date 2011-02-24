#include "security.h"

#include <sys/creds.h>
#include <QString>
#include <DcpAppletDb>
#include <DcpAppletMetadata>
#include <dcpdebug.h>

void Security::restrictTo (DcpAppletMetadata* metadata)
{
    long result = creds_confine (qPrintable(metadata->fullBinary()));
    qDebug ("XXX %ld", result);
}

void Security::loadAppletRestricted (const QString& appletName)
{
    DcpAppletDb* db = DcpAppletDb::instance();
    dcp_failfunc_unless (db);
    DcpAppletMetadata* metadata = db->metadata (appletName);
    dcp_failfunc_unless (metadata);
    restrictTo (metadata);
}

