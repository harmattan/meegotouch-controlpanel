
INCLUDEPATH +=/usr/include/dui

SRCDIR = ./../../src

DEPENDPATH = $$INCLUDEPATH

CONFIG += debug

QT += testlib

TEMPLATE = app

DEFINES += QT_NO_DEBUG_OUTPUT
#DEFINES += QT_NO_WARNING_OUTPUT
DEFINES += UNIT_TEST

LIBS += ./../../lib/libduicontrolpanel.so

QMAKE_CXXFLAGS += -Werror

