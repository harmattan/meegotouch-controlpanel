include(../../lib/dcpconfig.pri)

MOSTUSED {
    DEFINES += MOSTUSED
}

QMAKE_LIBDIR += ../../lib/lib/

include (launchers/launchers.pri)

TEMPLATE = app
DEPENDPATH += $$system(find . -type d) \
              ../../lib/src/include
INCLUDEPATH += $$DEPENDPATH

OBJECTS_DIR = ../tmp
MOC_DIR = ../tmp

# this has to be above finds, because it generates .h .cpp files
include (service/service.pri)

# Input
HEADERS += $$system(find ./ -name \'*.h\')
SOURCES += $$system(find ./ -name \'*.cpp\')
SOURCES += ../../briefsupplier/src/bsuppliercommands.cpp

CONFIG += build_all warn_on debug

DISABLE_LAUNCHER {
    CONFIG += meegotouch
} else {
    CONFIG += meegotouch-boostable
}

QT += network dbus
LIBS += -lduicontrolpanel

# a fake check target so as not to stop the testing:
QMAKE_EXTRA_TARGETS += check

target.path += $$DCP_PREFIX/bin

message("The install path for the executable will be: "$$target.path)

include (rfs.pri)

INSTALLS += target

# You can enable delayed applet loading with uncommenting this line:
DEFINES += DISABLE_DELAYED_LOADING

contains(DCP_BUILD_FEATURES,coverage) {
  QMAKE_EXTRA_TARGETS += coverage
  coverage.commands = $$system(true)
}

# disable internal deprecation warnings:
DEFINES += DCP_DISABLE_DEPRECATION_WARNING

# Meego specific configurations:
meego {
    DEFINES += FREE_ORIENTATION
}

