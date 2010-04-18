include(./../../lib/dcpconfig.pri)

INCLUDEPATH +=/usr/include/dui ../doubles

SRCDIR = ./../../src

DEPENDPATH = $$INCLUDEPATH

QMAKE_LIBDIR += ../../../lib/lib/ /usr/lib/
LIBDCPINCLUDE=../../../lib/src/include
CONFIG += dui debug

QT += testlib

TEMPLATE = app

DEFINES += QT_NO_DEBUG_OUTPUT
#DEFINES += QT_NO_WARNING_OUTPUT
DEFINES += UNIT_TEST

target.path = $${DCP_INSTALL_LIB}/duicontrolpanel-tests
INSTALLS += target
include(check.pri)
include(coverage.pri)
LIBS +=  -L/usr/lib -lduicontrolpanel
QMAKE_CXXFLAGS += -Werror
message($$target.path)

