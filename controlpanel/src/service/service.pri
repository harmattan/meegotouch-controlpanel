services.files = service/*service
services.path = $$DCP_PREFIX/share/dbus-1/services
INSTALLS += services

# generate the adaptor class:
IFPATH = ../../../lib/src/service_interface
XML=com.nokia.DuiControlPanelIf.xml
system(qdbusxml2cpp -c DuiControlPanelIfAdaptor -a duicontrolpanelifadaptor.h:duicontrolpanelifadaptor.cpp $${IFPATH}/$${XML})

XML2 = com.nokia.DcpAppletLauncherIf
system(cd $$IFPATH; m-servicefwgen -a $$XML2; cd -; mv $$IFPATH/dcpappletlauncherifadaptor* .)

