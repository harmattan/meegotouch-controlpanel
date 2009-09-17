XML = com.nokia.DuiControlPanelIf.xml
servicexml.files = service_interface/$$XML
servicexml.commands += $$system(/usr/bin/dui-servicefwgen com.nokia.DuiControlPanelIf)
servicexml.commands += $$system( qdbusxml2cpp -c DuiControlPanelIfProxy \
                        -p duicontrolpanelifproxy.h:duicontrolpanelifproxy.cpp \
                         $$XML)
servicexml.path = $$DCP_PREFIX/share/dbus-1/interfaces
INSTALLS += servicexml

