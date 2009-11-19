include(../lib/dcpconfig.pri)
QMAKE_LIBDIR += ../lib/lib/ 
QMAKE_RPATH = -Wl
message($$QMAKE_RPATH)
TEMPLATE = lib
TARGET = lib/declarative
DEPENDPATH += .
INCLUDEPATH += $$DEPENDPATH ../lib/src/include
OBJECTS_DIR = .obj
MOC_DIR = .moc

# Input
HEADERS += $$system(find ./ -name \'*.h\')
SOURCES += $$system(find ./ -name \'*.cpp\')

CONFIG += plugin gui dui silent debug
LIBS += -lduicontrolpanel

# a fake check target so as not to stop the testing:
QMAKE_EXTRA_TARGETS += check

target.path += $$DCP_APPLET_DIR

INSTALLS += target
QT += xml

