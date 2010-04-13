include(./../../dcpconfig.pri)

INCLUDEPATH += ../doubles

SRCDIR = ./../../src

DEPENDPATH = $$INCLUDEPATH

QMAKE_LIBDIR += ../../lib/ /usr/lib/

CONFIG += debug

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

DCP_TESTS_INSTALL_LIB = $${DCP_INSTALL_LIB}/duicontrolpanel-tests                                  
target.path = $${DCP_TESTS_INSTALL_LIB}                                 
INSTALLS += target                                                              
include(check.pri)
LIBS += -L../../lib/ -L/usr/lib -lduicontrolpanel
QMAKE_CXXFLAGS += -Werror
message($$target.path)

