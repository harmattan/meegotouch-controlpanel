#include "briefsupplier.h"

#include <QtDebug>
#include <QTimerEvent>
#include <QCoreApplication>
#include <QLocalServer>
#include <QLocalSocket>
#include <QTextStream>

#include <dcpappletdb.h>
#include <dcpappletobject.h>
#include <dcpbrief.h>
#include <dcpwidgettypes.h>
#include <dcpappletmetadata.h>
#include <dcpretranslator.h>

#include "bsuppliercommands.h"
#include "reader.h"

using namespace BSupplier;

#define returnIf(test, st, param)  \
    if (test) { qWarning(st ": \"%s\"",qPrintable(param)); return; }

BriefSupplier::BriefSupplier():
    m_Input (new Reader(this)),
    m_Output (new QTextStream (stdout, QIODevice::WriteOnly))
{
    // init the stream:
    m_Output->setCodec ("UTF-8");
    connect (m_Input, SIGNAL (newCommand(QString)),
             this, SLOT (onCommandArrival(QString)));

    // init the server:
    QLocalServer* server = new QLocalServer (this);
    connect (server, SIGNAL (newConnection()),
             this, SLOT (onNewConnection()));
    QLocalServer::removeServer (BServerId);
    bool ok = server->listen (BServerId);
    if (!ok) {
        qWarning ("Brief supplier process is not able to listen");
    }

    // init the db:
    DcpAppletMetadataList list = DcpAppletDb::instance ()->list ();
    // load all applet translations:
    DcpRetranslator::instance()->ensureTranslationsAreLoaded(list);
}

BriefSupplier::~BriefSupplier()
{
    delete m_Output;
}

void BriefSupplier::onNewConnection ()
{
    static int connectionCount = 0;
    connectionCount++;
    if (connectionCount == 1) {
        QLocalServer* server = qobject_cast<QLocalServer*>(sender());
        Q_ASSERT (server);
        QLocalSocket* socket = server->nextPendingConnection ();
        setIODevice (socket);
    }
}

void BriefSupplier::onCommandArrival (const QString& command)
{
    if (command.startsWith(CmdWatch)) {
        watch (command.mid (CmdWatch.count()));
    } else if (command.startsWith(CmdUnwatch)) {
        unwatch (command.mid (CmdUnwatch.count()));
    } else if (command.startsWith(CmdSwitchToggle)) {
        switchToggle (command.mid (CmdSwitchToggle.count()));
    } else {
        qWarning ("Brief supplier: could not understand %s",
                  qPrintable (command));
    }
}

void BriefSupplier::preload (const QString& appletName)
{
    m_PreloadApplets.append (appletName); // TODO XXX implement
}

void BriefSupplier::watch (const QString& appletName)
{
    returnIf (appletName.isEmpty(), "Empty appletname", appletName);
    qDebug () << "Watching:" << appletName;

    DcpAppletObject* applet = DcpAppletDb::instance ()->applet (appletName);
    returnIf (!applet, "No such applet", appletName);

    DcpBrief* brief = applet->brief();
    if (brief) {
        connect (applet, SIGNAL (briefChanged()),
                this, SLOT (onBriefChanged()));
        DcpAppletMetadata* metadata = applet->metadata();
        if (metadata) {
            metadata->markActive();
            DcpRetranslator::instance()->ensureTranslationLoaded(metadata);
        }
        outputBrief (applet);
    }
}

void BriefSupplier::unwatch (const QString& appletName)
{
    returnIf (appletName.isEmpty(), "No appletName was specified", appletName);
    qDebug () << "Watching:" << appletName;

    DcpAppletObject* applet = DcpAppletDb::instance ()->applet (appletName);
    returnIf (!applet, "No such applet", appletName);
    DcpBrief* brief = applet->brief();
    if (!brief) return;

    // make it inactive
    disconnect (applet, SIGNAL (briefChanged()),
                this, SLOT (onBriefChanged()));

    DcpAppletMetadata* metadata = applet->metadata();
    if (metadata) {
        metadata->markInactive();
    }
}

void BriefSupplier::onBriefChanged ()
{
    DcpAppletObject* applet = qobject_cast<DcpAppletObject*>(sender());
    returnIf (!applet, "Strange error in onBriefChanged()", QString());

    outputBrief (applet);
}

void BriefSupplier::outputBrief (DcpAppletObject* applet)
{
    Q_ASSERT (applet);

    DcpBrief* brief = applet->brief();
    if (!brief) return;

    DcpAppletMetadata* metadata = applet->metadata();

    // get the values from the applet:
    QString appletName = metadata ? metadata->name() : QString();
    // the applet name is the id we use:
    returnIf (appletName.isEmpty(), "Applet without name", appletName);

    int widgetTypeID = brief->widgetTypeID();
    QString titleText = brief->titleText();
    QString valueText = brief->valueText();
    QString helpId =
        applet->interfaceVersion() < 5 ? QString() : brief->helpId();

    QString icon;
    QString image;
    bool toggle;
    switch (widgetTypeID) {
        case DcpWidgetType::Toggle:
        case DcpWidgetType::Button:
            toggle = brief->toggle();
            break;
        case DcpWidgetType::Image:
            icon = brief->icon();
            image = brief->image();
            break;
        default:
            break;
    }

    // send them:
    outputStart();
    output (OutputName, appletName);
    output (OutputWidgetTypeID, widgetTypeID);
    output (OutputValueText, valueText);
    output (OutputIcon, image.isEmpty() ? icon : image);
    if (widgetTypeID == DcpWidgetType::Toggle ||
        widgetTypeID == DcpWidgetType::Button)
    {
        output (OutputToggle, (int)toggle);
    }
    output (OutputTitleText, titleText);
    output (OutputHelpId, helpId);
    outputEnd();
}

void BriefSupplier::switchToggle (const QString& appletName)
{
    returnIf (appletName.isEmpty(), "No appletName was specified", appletName);
    DcpAppletObject* applet = DcpAppletDb::instance ()->applet (appletName);
    returnIf (!applet, "No such applet", appletName);

    applet->setToggle (!applet->toggle());
}

void BriefSupplier::outputStart ()
{
    *m_Output << OutputBegin << "\n";
}

void BriefSupplier::outputEnd ()
{
    *m_Output << OutputEnd << "\n";
    m_Output->flush();
    qobject_cast<QLocalSocket*>(m_Output->device())->flush();
}

void BriefSupplier::output (const char* key, const QString& value)
{
    if (!value.isEmpty ()) {
        // the key and value is separated by the first "="
        *m_Output << key << "=" << value << "\n";
    }
}

void BriefSupplier::output (const char* key, int value)
{
    output (key, QString::number (value));
}

// starts loading the briefs in the background:
void BriefSupplier::startLoading ()
{
    startTimer (0);
}

// loads a briefs in the background if there is nothing else to do
void BriefSupplier::timerEvent ( QTimerEvent * event )
{
    Q_UNUSED (event);
#if 0
    // if there is nothing else to do, then lets load an applet:
    while (!qApp->hasPendingEvents())  {
        // if there is no more applet, then stop:
        if (m_LoadingPos >= m_AppletNames.count ()) {
            killTimer (event->timerId ());
            break;
        }

        QString name = m_AppletNames.at(m_LoadingPos);
        m_LoadingPos++;

        DcpAppletDb* db = DcpAppletDb::instance();
        if (db->isAppletLoaded (name)) continue;

        DcpAppletObject* applet = db->applet (name);
        if (applet) {
            applet->brief ();
        }

        // only load one applet
        if (applet->applet() != 0) {
            qWarning ("XXX preloaded: %s", qPrintable (name));
            break;
        }
    }
#endif
}

void BriefSupplier::setIODevice (QIODevice* device)
{
    m_Output->setDevice (device);
    m_Input->setIODevice (device);
    m_Input->start ();
}

