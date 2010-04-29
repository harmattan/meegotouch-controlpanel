include(./../../lib/dcpconfig.pri)

INCLUDEPATH += ../doubles

SRCDIR = ./../../src

QMAKE_LIBDIR += ../../../lib/lib/ /usr/lib/
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

target.path = $${DCP_INSTALL_LIB}/duicontrolpanel-tests
INSTALLS += target
include(check.pri)
include(coverage.pri)
LIBS += -L/usr/lib -lduicontrolpanel
QMAKE_CXXFLAGS += -Werror
message($$target.path)

OBJECTS_DIR = ../.obj
MOC_DIR = ../.moc

INCLUDEPATH += $$LIBDCPINCLUDE

