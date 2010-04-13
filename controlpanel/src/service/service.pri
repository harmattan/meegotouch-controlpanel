services.files = service/*service
services.path = $$DCP_PREFIX/share/dbus-1/services
INSTALLS += services

# generate the adaptor class:
system(qdbusxml2cpp -c DuiControlPanelIfAdaptor -a duicontrolpanelifadaptor.h:duicontrolpanelifadaptor.cpp ../../../lib/src/service_interface/com.nokia.DuiControlPanelIf.xml)

