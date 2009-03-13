TEMPLATE = app
TARGET = ../duicontrolpanel
DEPENDPATH += $$system(find ./ -type d)
INCLUDEPATH += $$DEPENDPATH

OBJECTS_DIR = ../tmp
MOC_DIR = ../tmp


# Input
HEADERS += $$system(find ./ -name \'*.h\')
SOURCES += $$system(find ./ -name \'*.cpp\')

CONFIG += build_all silent warn_on debug

INCLUDEPATH += $$[QT_INSTALL_HEADERS]/dui
LIBS += -ldui

# a fake check target so as not to stop the testing:
QMAKE_EXTRA_TARGETS += check

include (../common.pri)
target.path += $${PREFIX}/bin
message("The install path for the executable will be: "$$target.path)

INSTALLS += target 

