XML = com.nokia.DuiControlPanelIf.xml
servicexml.files = service_interface/$$XML
servicexml.path = $$DCP_PREFIX/share/dbus-1/interfaces
INSTALLS += servicexml

system(m-servicefwgen -p com.nokia.DuiControlPanelIf)

