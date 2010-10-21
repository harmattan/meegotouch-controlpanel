#include <MApplication>

#include <DcpRetranslator>
#include "briefsupplier.h"
#include "fakeapplicationservice.h"

int main (int argc, char* argv[])
{
    MApplication app(argc, argv, new FakeApplicationService());

    // install the new translations if locale changes:
    /* TODO XXX maybe we should not handle translations at all because
     * controlpanel already has to, otherwise it can not show even the title
     * of the applets?
     */
    DcpRetranslator* retranslator = DcpRetranslator::instance();
    QObject::connect(&app, SIGNAL(localeSettingsChanged()),
                     retranslator, SLOT(retranslate()));

    BriefSupplier supplier;
    QObject::connect(&app, SIGNAL(localeSettingsChanged()),
                     &supplier, SLOT(onLocaleChange()));

    return app.exec();
}

