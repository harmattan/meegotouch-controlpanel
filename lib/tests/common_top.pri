include(./../../dcpconfig.pri)

INCLUDEPATH +=/usr/include/dui

SRCDIR = ./../../src

DEPENDPATH = $$INCLUDEPATH

CONFIG += debug

QT += testlib

TEMPLATE = app

DEFINES += QT_NO_DEBUG_OUTPUT
#DEFINES += QT_NO_WARNING_OUTPUT
DEFINES += UNIT_TEST

target.path = $${DCP_INSTALL_LIB}/libduicontrolpanel-tests                                  
INSTALLS += target                                                              
include(check.pri)
QMAKE_LIBSDIR += ./../../lib/ 
LIBS += -lduicontrolpanel 
QMAKE_CXXFLAGS += -Werror
message($$target.path)
