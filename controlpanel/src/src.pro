include(../../lib/dcpconfig.pri)

MOSTUSED {
    DEFINES += MOSTUSED
}

DISABLE_LAUNCHER {
    DEFINES += DISABLE_LAUNCHER
    TARGET = ../duicontrolpanel
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

QMAKE_LIBDIR += ../../lib/lib/ 
message($$QMAKE_LFLAGS_RPATH)
TEMPLATE = app
DEPENDPATH += include ../../lib/src/include
INCLUDEPATH += $$DEPENDPATH
message($$INCLUDEPATH)
OBJECTS_DIR = ../tmp
MOC_DIR = ../tmp

# this has to be above finds, because it generates .h .cpp files
include (service/service.pri)

# Input
HEADERS += $$system(find ./ -name \'*.h\')
HEADERS += include/*
SOURCES += $$system(find ./ -name \'*.cpp\')

CONFIG += meegotouch build_all warn_on debug
LIBS += -lduicontrolpanel

# a fake check target so as not to stop the testing:
QMAKE_EXTRA_TARGETS += check

target.path += $$DCP_PREFIX/bin

message("The install path for the executable will be: "$$target.path)

desktop_entry.path = $$DCP_PREFIX/share/applications
desktop_entry.files = duicontrolpanel.desktop
rfs.files += controlpanel-rfs.sh
rfs.path += $$system(pkg-config --variable osso_rfs_scripts_dir clean-device)


INSTALLS += target \
            rfs \
            desktop_entry 

# You can enable delayed applet loading with uncommenting this line:
DEFINES += DISABLE_DELAYED_LOADING

contains(DCP_BUILD_FEATURES,coverage) {
  QMAKE_EXTRA_TARGETS += coverage
  coverage.commands = $$system(true)
}

# disable internal deprecation warnings:
DEFINES += DCP_DISABLE_DEPRECATION_WARNING

