include(../../lib/dcpconfig.pri)
QMAKE_LIBDIR += ../../lib/lib/ 
TEMPLATE = app
TARGET = ../duicontrolpanel
DEPENDPATH += include 
INCLUDEPATH += $$DEPENDPATH ../../lib/src/include
message($$INCLUDEPATH)
OBJECTS_DIR = ../tmp
MOC_DIR = ../tmp

# this has to be above finds, because it generates .h .cpp files
include (service/service.pri)

# Input
HEADERS += $$system(find ./ -name \'*.h\')
HEADERS += include/*
SOURCES += $$system(find ./ -name \'*.cpp\')

CONFIG += dui build_all warn_on debug
LIBS += -lduicontrolpanel -ltime

# a fake check target so as not to stop the testing:
QMAKE_EXTRA_TARGETS += check

target.path += $$DCP_PREFIX/bin

message("The install path for the executable will be: "$$target.path)

desktop_entry.path = $$DCP_PREFIX/share/applications
desktop_entry.files = duicontrolpanel.desktop

INSTALLS += target \
            desktop_entry


