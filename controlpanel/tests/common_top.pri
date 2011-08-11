include(./../../lib/dcpconfig.pri)

INCLUDEPATH += ../doubles

SRCDIR = ./../../src

LIBDCPSRC =../../../lib/src
LIBDCPINCLUDE=../../../lib/src/include
LIBDCPFAKES=../../../lib/tests/doubles
STUBSDIR = ../doubles
CONFIG += debug

QT += testlib

TEMPLATE = app

DEFINES += QT_NO_DEBUG_OUTPUT
#DEFINES += QT_NO_WARNING_OUTPUT
DEFINES += UNIT_TEST

# disable internal deprecation warnings:
DEFINES += DCP_DISABLE_DEPRECATION_WARNING

target.path = $${DCP_INSTALL_LIB}/duicontrolpanel-tests
INSTALLS += target
include(check.pri)
include(coverage.pri)
LIBS = ../../../lib/lib/libduicontrolpanel.so
QMAKE_CXXFLAGS += -Wno-deprecated
message($$target.path)

contains(DCP_BUILD_FEATURES,coverage) {
    OBJECTS_DIR=.tmp
    MOC_DIR=.tmp
}
else {
    OBJECTS_DIR=../.tmp
    MOC_DIR=../.tmp
}


INCLUDEPATH += $$LIBDCPINCLUDE

