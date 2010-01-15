XML = com.nokia.DuiControlPanelIf.xml
servicexml.files = service_interface/$$XML
servicexml.path = $$DCP_PREFIX/share/dbus-1/interfaces
INSTALLS += servicexml

system(dui-servicefwgen com.nokia.DuiControlPanelIf)
system(qdbusxml2cpp -c DuiControlPanelIfProxy \
                        -p duicontrolpanelifproxy.h:duicontrolpanelifproxy.cpp \
                         $$XML)

