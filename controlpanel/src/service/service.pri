services.files = service/*service
services.path = $$DCP_PREFIX/share/dbus-1/services
services.commands = $$system(qdbusxml2cpp -c DuiControlPanelIfAdaptor -a duicontrolpanelifadaptor.h:duicontrolpanelifadaptor.cpp ../../../lib/src/service_interface/com.nokia.DuiControlPanelIf.xml)
INSTALLS += services

