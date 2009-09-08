
INCLUDEPATH +=/usr/include/dui

SRCDIR = ./../../src

DEPENDPATH = $$INCLUDEPATH

CONFIG += debug

QT += testlib

TEMPLATE = app

DEFINES += QT_NO_DEBUG_OUTPUT
#DEFINES += QT_NO_WARNING_OUTPUT
DEFINES += UNIT_TEST

target.path = $$(DEBIAN_DESTDIR)/usr/lib/libduicontrolpanel-tests                                  
INSTALLS += target                                                              
include(check.pri)
#LIBS += ./../../lib/libduicontrolpanel.so -lduicontrolpanel 
LIBS += -lduicontrolpanel 
QMAKE_CXXFLAGS += -Werror

