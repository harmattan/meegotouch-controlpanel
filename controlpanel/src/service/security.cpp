#include "security.h"
#include "pagefactory.h"
#include "dcpappletmanager.h"

#include <sys/creds.h>
#include <QString>
#include <DcpAppletMetadata>
#include <dcpdebug.h>

void Security::restrictTo (DcpAppletMetadata* metadata)
{
    if (!PageFactory::isInProcessApplets()) {
        creds_confine (qPrintable(metadata->fullBinary()));
    }
}

void Security::loadAppletRestricted (const QString& appletName)
{
    DcpAppletManager* db = DcpAppletManager::instance();
    dcp_failfunc_unless (db);
    DcpAppletMetadata* metadata = db->metadata (appletName);
    dcp_failfunc_unless (metadata);

    // restrict:
    restrictTo (metadata);

    // load:
    db->applet (appletName);
}

