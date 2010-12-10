XML = com.nokia.DuiControlPanelIf
XML2 = com.nokia.DcpAppletLauncherIf
servicexml.files += service_interface/$${XML}.xml
servicexml.files += service_interface/$${XML2}.xml
servicexml.path = $$DCP_PREFIX/share/dbus-1/interfaces
message ($$servicexml.files)
INSTALLS += servicexml

# normal interface (runs controlpanel separately)
system(m-servicefwgen -p $$XML)

# chained interface
system(m-servicefwgen -p $$XML2)

