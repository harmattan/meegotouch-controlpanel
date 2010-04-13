services.files = service/*service
services.path = $$DCP_PREFIX/share/dbus-1/services
INSTALLS += services

# generate the adaptor class:
system(qdbusxml2cpp -c DuiControlPanelIfAdaptor -a mcontrolpanelifadaptor.h:mcontrolpanelifadaptor.cpp ../../../lib/src/service_interface/com.nokia.DuiControlPanelIf.xml)

