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

