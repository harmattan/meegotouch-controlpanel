#include "briefsupplier.h"

#include <QtDebug>
#include <QCoreApplication>
#include <QLocalServer>
#include <QLocalSocket>

#include <dcpappletdb.h>
#include <dcpappletobject.h>
#include <dcpbrief.h>
#include <dcpwidgettypes.h>
#include <dcpappletmetadata.h>
#include <dcpretranslator.h>

#include "bsuppliercommands.h"
#include "stream.h"

using namespace BSupplier;

#define returnIf(test, st, param)  \
    if (test) { qWarning(st ": \"%s\"",qPrintable(param)); return; }

BriefSupplier::BriefSupplier():
    m_Stream (new Stream(this))
{
    // init the stream:
    connect (m_Stream, SIGNAL (newCommand(QString)),
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
    delete m_Stream;
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

void BriefSupplier::outputBrief (DcpAppletObject* applet, bool textOnly)
{
    Q_ASSERT (applet);

    DcpBrief* brief = applet->brief();
    if (!brief) return;

    DcpAppletMetadata* metadata = applet->metadata();

    // get the values from the applet:
    QString appletName = metadata ? metadata->name() : QString();
    // the applet name is the id we use:
    returnIf (appletName.isEmpty(), "Applet without name", appletName);

    QString titleText = brief->titleText();
    QString valueText = brief->valueText();
    int widgetTypeID = -1;
    QString helpId;
    QString icon;
    QString image;
    bool toggle;

    if (!textOnly) {
        widgetTypeID = brief->widgetTypeID();
        helpId = applet->interfaceVersion() < 5 ? QString() : brief->helpId();

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
    }

    // send them:
    outputStart();
    output (OutputName, appletName);
    output (OutputTitleText, titleText);
    output (OutputValueText, valueText);

    if (!textOnly) {
        output (OutputWidgetTypeID, widgetTypeID);
        output (OutputIcon, image.isEmpty() ? icon : image);
        if (widgetTypeID == DcpWidgetType::Toggle ||
            widgetTypeID == DcpWidgetType::Button)
        {
            output (OutputToggle, (int)toggle);
        }
        output (OutputHelpId, helpId);
    }

    outputEnd();
}

void BriefSupplier::switchToggle (const QString& appletName)
{
    returnIf (appletName.isEmpty(), "No appletName was specified", appletName);
    DcpAppletObject* applet = DcpAppletDb::instance ()->applet (appletName);
    returnIf (!applet, "No such applet", appletName);

    applet->setToggle (!applet->toggle());
}

void BriefSupplier::onLocaleChange ()
{
    DcpAppletDb* db = DcpAppletDb::instance();
    DcpAppletMetadataList metadataList = db->list ();
    foreach (DcpAppletMetadata* metadata, metadataList) {
        if (metadata->isActive ()) {
            DcpAppletObject* applet = db->applet (metadata->name());
            outputBrief (applet, true);
        }
    }
}

void BriefSupplier::outputStart ()
{
    m_Stream->writeLine (OutputBegin);
}

void BriefSupplier::outputEnd ()
{
    m_Stream->writeLine (OutputEnd);
    m_Stream->flush ();
}

void BriefSupplier::output (const char* key, const QString& value)
{
    if (!value.isEmpty ()) {
        // the key and value is separated by the first "="
        m_Stream->writeLine (QString(key) + "=" + value);
    }
}

void BriefSupplier::output (const char* key, int value)
{
    output (key, QString::number (value));
}

void BriefSupplier::setIODevice (QIODevice* device)
{
    m_Stream->setIODevice (device);
}

