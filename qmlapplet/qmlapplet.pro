include(../lib/dcpconfig.pri)
QMAKE_LIBDIR += ../lib/lib/ 
TEMPLATE = lib
TARGET = lib/qml
DEPENDPATH += .
INCLUDEPATH += $$DEPENDPATH ../lib/src/include
OBJECTS_DIR = ../tmp
MOC_DIR = ../tmp

# Input
HEADERS += $$system(find ./ -name \'*.h\') \
    dcpqmlgconfitem.h
SOURCES += $$system(find ./ -name \'*.cpp\')

CONFIG += plugin gui meegotouch silent debug 
QT += declarative
LIBS += -lduicontrolpanel

# a fake check target so as not to stop the testing:
QMAKE_EXTRA_TARGETS += check

target.path += $$DCP_APPLET_DIR

INSTALLS += target
QT += xml


