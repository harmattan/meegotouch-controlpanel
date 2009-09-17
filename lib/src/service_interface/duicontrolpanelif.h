#ifndef DUICONTROLPANELIF_H
#define DUICONTROLPANELIF_H

/*
 * automatically generated with the command line :
 * /usr/bin/dui-servicefwgen com.nokia.DuiControlPanelIf
 */
#include <QObject>

#include <duiservicefwbaseif.h>
#include <duicontrolpanelifproxy.h>

class DuiControlPanelIf : public DuiServiceFwBaseIf
{
Q_OBJECT

public:
    bool appletPage( const QString &appletName )
    {
        return qobject_cast<DuiControlPanelIfProxy*>(interfaceProxy)->appletPage( appletName ).value();
    }
    void categoryPage( const QString &category )
    {
        static_cast<DuiControlPanelIfProxy*>(interfaceProxy)->categoryPage( category );
    }
    void mainPage(  )
    {
        static_cast<DuiControlPanelIfProxy*>(interfaceProxy)->mainPage(  );
    }

public:
    // @param preferredService, define the preferred service provider. Leave empty if no preferred provider. In most cases, this should be left empty.
    DuiControlPanelIf( const QString& preferredService = "", QObject* parent = 0 )
        : DuiServiceFwBaseIf( DuiControlPanelIfProxy::staticInterfaceName(), parent )
    {
        // Resolve the provider service name
        service = resolveServiceName( interface, preferredService );

        bool serviceNameInvalid = service.contains( " " ); // "not provided" - when the service wouldn't run
        if ( serviceNameInvalid ) {
            service.clear();
        }

        if (!service.isEmpty()) {
            // Construct the D-Bus proxy
            interfaceProxy = new DuiControlPanelIfProxy( service, "/", QDBusConnection::sessionBus(), this );

        }
    }

    void setService(const QString & service)
    {
        if (service.isEmpty()) return;

        this->service = service;

        if ( interfaceProxy ) {
            delete interfaceProxy;
            interfaceProxy = 0;
        }
        interfaceProxy = new DuiControlPanelIfProxy( service, "/", QDBusConnection::sessionBus(), this );
        {

        }
    }
signals:


};
#endif
