XML = com.nokia.DuiControlPanelIf.xml
servicexml.files = service_interface/$$XML
servicexml.path = $$DCP_PREFIX/share/dbus-1/interfaces
INSTALLS += servicexml

system(m-servicefwgen com.nokia.DuiControlPanelIf)
#
# I don't know why this was here, the m-servicefwgen generates all the files
# we need. I leave it here in case someone needs it, will be removed soon.
#
#system(qdbusxml2cpp -c DuiControlPanelIfProxy \
#    -p mcontrolpanelifproxy.h:mcontrolpanelifproxy.cpp \
#    $$XML)

