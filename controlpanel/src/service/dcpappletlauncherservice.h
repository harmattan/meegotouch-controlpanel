#ifndef DCPAPPLETLAUNCHERSERVICE_H
#define DCPAPPLETLAUNCHERSERVICE_H

#include <MApplicationService>
#include "pages.h"

class DcpAppletLauncherService: public MApplicationService
{
        Q_OBJECT
public:
    DcpAppletLauncherService ();

    virtual bool registerService ();
    virtual bool unregisterService ();
    bool maybeAppletRealStart ();

public slots:
    bool appletPage (const QString& appletName);
    void prestart ();

private:
    void sheduleApplet (const QString& appletName);
    PageHandle m_PageHandle;
};


#endif // DCPAPPLETLAUNCHERSERVICE_H
