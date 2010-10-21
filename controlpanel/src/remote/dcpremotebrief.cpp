#include "dcpremotebrief.h"
#include "dcpremotebrief_p.h"

#include "dcpremotebriefreceiver.h"


DcpRemoteBriefPriv::DcpRemoteBriefPriv (const QString& name):
    appletName (name)
{
}


DcpRemoteBrief::DcpRemoteBrief (const QString& appletName, QObject* parent):
    priv (new DcpRemoteBriefPriv (appletName))
{
    setParent (parent);
    DcpRemoteBriefReceiver::instance ()->watch (this);
}

DcpRemoteBrief::~DcpRemoteBrief ()
{
    DcpRemoteBriefReceiver::instance ()->unwatch (this);

    /*
     * This is disabled because restarting the process takes time, so
     * it is only destroyed at controlpanel closing by the opsystem
     *
    if (DcpRemoteBriefReceiver::instance ()->watchCount () == 0) {
        delete DcpRemoteBriefReceiver::instance ();
    }
    */

    delete priv;
}


int DcpRemoteBrief::widgetTypeID () const
{
    bool ok;
    int value = this->value (BSupplier::OutputWidgetTypeID).toInt (&ok);
    return ok ? value : DcpBrief::widgetTypeID ();
}


QString DcpRemoteBrief::valueText () const
{
    QString st = value (BSupplier::OutputValueText);
    return st;
}


QString DcpRemoteBrief::icon () const
{
    return value (BSupplier::OutputIcon);
}


bool DcpRemoteBrief::toggle () const
{
    QString value = this->value (BSupplier::OutputToggle);
    return value == "1";
}


void DcpRemoteBrief::setToggle (bool toggle)
{
    if (this->toggle () != toggle) {
        DcpRemoteBriefReceiver::instance ()->switchToggle (name ());
    }
}


QString DcpRemoteBrief::name () const
{
    return priv->appletName;
}

QString DcpRemoteBrief::titleText () const
{
    return value (BSupplier::OutputTitleText);
}


QString DcpRemoteBrief::helpId () const
{
    return value (BSupplier::OutputHelpId);
}

QString DcpRemoteBrief::value (const char* id) const
{
    return priv->values.value (id);
}

void DcpRemoteBrief::setValue (const char* id, const QString& value)
{
    priv->values[id] = value;
}

void DcpRemoteBrief::emitChange ()
{
    emit valuesChanged ();
}
