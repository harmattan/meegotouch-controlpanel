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
        // FIXME for compatibility we do not drop the credentials yet if the
        // library does not specify credential for itself
        creds_t myCreds = creds_gettask (0);
        creds_confine2 (qPrintable(metadata->fullBinary()), 0, myCreds);
        creds_free (myCreds);
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

