DISABLE_LAUNCHER {
    DEFINES += DISABLE_LAUNCHER
    TARGET = ../duicontrolpanel.launch
} else {
    QMAKE_CXXFLAGS += -fPIC -fvisibility=hidden -fvisibility-inlines-hidden
    QMAKE_LFLAGS += -pie -rdynamic
    TARGET = ../duicontrolpanel.launch
    invoker_trg = ../duicontrolpanel
    invoker.depends = duicontrolpanel.invoker
    invoker.commands = cp $$invoker.depends $$invoker_trg
    QMAKE_EXTRA_TARGETS += invoker
    # ugly hack that makes invoker_inst happy
    system(touch $$invoker_trg)
    invoker_inst.path = $$DCP_PREFIX/bin
    invoker_inst.files = $$invoker_trg
    invoker_inst.depends = invoker
    INSTALLS += invoker_inst
    QMAKE_CLEAN += $$invoker_trg
}

appletlauncher.files += dcpappletlauncher
appletlauncher.path += $$DCP_PREFIX/bin
INSTALLS += appletlauncher


