include(./../../lib/dcpconfig.pri)

INCLUDEPATH +=/usr/include/dui ../doubles

SRCDIR = ./../../src

DEPENDPATH = $$INCLUDEPATH

QMAKE_LIBDIR += ../../../lib/lib/ /usr/lib/
LIBDCPINCLUDE=../../../lib/src/include
LIBDCPFAKES=../../../lib/tests/doubles
STUBSDIR = ../stubs
CONFIG += dui debug

QT += testlib

TEMPLATE = app

DEFINES += QT_NO_DEBUG_OUTPUT
#DEFINES += QT_NO_WARNING_OUTPUT
DEFINES += UNIT_TEST

coverage {
    message("Coverage options enabled")
    QMAKE_CXXFLAGS += --coverage
    QMAKE_LFLAGS += --coverage
}

target.path = $${DCP_INSTALL_LIB}/duicontrolpanel-tests
INSTALLS += target
include(check.pri)
LIBS +=  -L/usr/lib -lduicontrolpanel
QMAKE_CXXFLAGS += -Werror
message($$target.path)

