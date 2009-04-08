QMAKE_LIBDIR += ../../lib/lib/ 
include (../common.pri)
TEMPLATE = app
TARGET = ../duicontrolpanel
DEPENDPATH += $$system(find ./ -type d)
INCLUDEPATH += $$DEPENDPATH $$system(find ../../lib/src -type d)
message($$INCLUDEPATH)
OBJECTS_DIR = ../tmp
MOC_DIR = ../tmp


# Input
HEADERS += $$system(find ./ -name \'*.h\')
SOURCES += $$system(find ./ -name \'*.cpp\')

CONFIG += build_all warn_on debug

INCLUDEPATH += $$[QT_INSTALL_HEADERS]/dui
INCLUDEPATH += /usr/include/dui
LIBS += -ldui -lduicontrolpanel

# a fake check target so as not to stop the testing:
QMAKE_EXTRA_TARGETS += check

target.path += $${PREFIX}/bin

message("The install path for the executable will be: "$$target.path)

INSTALLS += target

