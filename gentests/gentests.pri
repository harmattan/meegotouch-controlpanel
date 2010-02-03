include(lib/dcpconfig.pri)
shell_scripts.commands += gentests/gen-tests-xml.sh > gentests/tests.xml
shell_scripts.files += gentests/runtests.sh gentests/tests.xml
shell_scripts.path += $$DCP_PREFIX/share/duicontrolpanel-tests
shell_scripts.CONFIG += no_check_exist

INSTALLS    += shell_scripts
