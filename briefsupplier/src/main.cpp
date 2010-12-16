#include <MApplication>

#include <DcpRetranslator>
#include "dcpappletdb.h"
#include "dcpwrongapplets.h"
#include "dcpmostusedcounter.h"
#include "briefsupplier.h"
#include "fakeapplicationservice.h"

#include <sys/time.h>
#include <sys/resource.h>

#include <dcpdebug.h>
#include "syslog.h"
#define LOW_PRIORITY

void cleanup ()
{
    // free up singletons:
    DcpRetranslator::destroy();
    DcpAppletDb::destroy();
    DcpWrongApplets::destroyInstance();
    MostUsedCounter::destroy();

    // free up application:
    delete MApplication::instance();
}

/*
 * this redefines the signal handler for TERM and INT signals, so as to be able
 * to use aboutToQuit signal from qApp also in these cases
 */
void onTermSignal (int)
{
    if (qApp) {
        qApp->quit();
    }
}

int main (int argc, char* argv[])
{
    openlog ("dcp-briefsupplier", LOG_PID, LOG_USER);
#ifdef LOW_PRIORITY
    setpriority(PRIO_PROCESS, 0, 19);
#endif // LOW_PRIORITY

    MApplication* app = new MApplication(argc, argv, new FakeApplicationService());

    signal(SIGTERM, &onTermSignal);
    signal(SIGINT, &onTermSignal);

    // install the new translations if locale changes:
    DcpRetranslator* retranslator = DcpRetranslator::instance();
    /*
    QObject::connect(&app, SIGNAL(localeSettingsChanged()),
                     retranslator, SLOT(retranslate()));
     */

#ifdef SUPERVISOR
    // handle the arguments:
    for (int i = 1; i < argc; ++i) {
        QString s(argv[i]);

        if (s == "-nosupervisor") {
            qDebug() << "Applet supervisor is disabled.";
            DcpWrongApplets::disable();
        }
    }

    // start supervisor:
    if (!DcpWrongApplets::isDisabled()) {
        DcpWrongApplets::connectSupervisorSignals();
        DcpWrongApplets::instance();
    }
#else
    DcpWrongApplets::disable();
#endif

    BriefSupplier supplier;
    QObject::connect(app, SIGNAL(localeSettingsChanged()),
                     &supplier, SLOT(onLocaleChange()));

    int result = app->exec();

    cleanup ();
    return result;
}

