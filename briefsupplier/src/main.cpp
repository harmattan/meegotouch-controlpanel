#include <MApplication>

#include <DcpRetranslator>
#include "briefsupplier.h"
#include "fakeapplicationservice.h"

#include <sys/time.h>
#include <sys/resource.h>

#include <dcpdebug.h>
#define LOW_PRIORITY

int main (int argc, char* argv[])
{
#ifdef LOW_PRIORITY
    setpriority(PRIO_PROCESS, 0, 19);
#endif // LOW_PRIORITY

    MApplication app(argc, argv, new FakeApplicationService());

    // install the new translations if locale changes:
    DcpRetranslator* retranslator = DcpRetranslator::instance();
    QObject::connect(&app, SIGNAL(localeSettingsChanged()),
                     retranslator, SLOT(retranslate()));

    BriefSupplier supplier;
    QObject::connect(&app, SIGNAL(localeSettingsChanged()),
                     &supplier, SLOT(onLocaleChange()));

    return app.exec();
}

