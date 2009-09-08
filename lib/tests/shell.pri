shell_scripts.commands += $$system(touch tests.xml)
shell_scripts.files += runtests.sh tests.xml

# fixed path required by TATAM
shell_scripts.path += $$(DEBIAN_DESTDIR)/usr/share/libduicontrolpanel-tests

INSTALLS    += shell_scripts
