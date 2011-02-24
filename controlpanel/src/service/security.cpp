#include "security.h"
#include "pagefactory.h"

#include <sys/creds.h>
#include <QString>
#include <DcpAppletDb>
#include <DcpAppletMetadata>
#include <dcpdebug.h>

#include <syslog.h>

void Security::restrictTo (DcpAppletMetadata* metadata)
{
    if (!PageFactory::isInProcessApplets()) {
        long result = creds_confine (qPrintable(metadata->fullBinary()));
        syslog (LOG_DEBUG, "XXX %ld", result);
    }
}

void Security::loadAppletRestricted (const QString& appletName)
{
    DcpAppletDb* db = DcpAppletDb::instance();
    dcp_failfunc_unless (db);
    DcpAppletMetadata* metadata = db->metadata (appletName);
    dcp_failfunc_unless (metadata);

    // restrict:
    restrictTo (metadata);
    
    // load:
    db->applet (appletName);
}

