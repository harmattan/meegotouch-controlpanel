include(../dcpconfig.pri)
shell_scripts.commands += $$system(./gen-tests-xml.sh > tests.xml)
shell_scripts.files += runtests.sh tests.xml

# fixed path required by TATAM
shell_scripts.path += $$DCP_PREFIX/share/libduicontrolpanel-tests

INSTALLS    += shell_scripts
