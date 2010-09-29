include(./../../dcpconfig.pri)

INCLUDEPATH += ../doubles

SRCDIR = ./../../src

DEPENDPATH = $$INCLUDEPATH

QMAKE_LIBDIR += ../../lib/ /usr/lib/

CONFIG += debug meegotouch

QT += testlib

TEMPLATE = app

DEFINES += QT_NO_DEBUG_OUTPUT
#DEFINES += QT_NO_WARNING_OUTPUT
DEFINES += UNIT_TEST

# disable internal deprecation warnings:
DEFINES += DCP_DISABLE_DEPRECATION_WARNING


DCP_TESTS_INSTALL_LIB = $${DCP_INSTALL_LIB}/duicontrolpanel-tests                                  
target.path = $${DCP_TESTS_INSTALL_LIB}                                 
INSTALLS += target                                                              
include(check.pri)
include(coverage.pri)
LIBS += -L../../lib/ -L/usr/lib -lduicontrolpanel
message($$target.path)

contains(DCP_BUILD_FEATURES,coverage) {

    OBJECTS_DIR=.tmp
    MOC_DIR=.tmp
}
else {
    OBJECTS_DIR=../.tmp
    MOC_DIR=../.tmp
}

