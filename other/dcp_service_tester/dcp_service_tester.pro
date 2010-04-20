include(../../lib/dcpconfig.pri)
TEMPLATE = app
TARGET = ./dcp_service_tester
DEPENDPATH += .
INCLUDEPATH += $$DEPENDPATH ../../lib/src/include

OBJECTS_DIR = tmp
MOC_DIR = tmp

# Input
HEADERS += $$system(find ./ -name \'*.h\')
SOURCES += $$system(find ./ -name \'*.cpp\')

CONFIG += meegotouch build_all warn_on debug duicontrolpanel

# a fake check target so as not to stop the testing:
QMAKE_EXTRA_TARGETS += check

