include(../dcpconfig.pri)
shell_scripts.commands += ./gen-tests-xml.sh > tests.xml
shell_scripts.files += runtests.sh tests.xml
shell_scripts.path += $$DCP_PREFIX/share/libduicontrolpanel-tests

INSTALLS    += shell_scripts
