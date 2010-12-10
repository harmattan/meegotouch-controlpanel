
# install desktop file:
APPEAR_IN_MENU {
    system(cp duicontrolpanel.desktop.2 duicontrolpanel.desktop)
} else {
    system(cp duicontrolpanel.desktop.1 duicontrolpanel.desktop)
}
desktop_entry.path = $$DCP_PREFIX/share/applications
desktop_entry.files = duicontrolpanel.desktop

INSTALLS += desktop_entry

