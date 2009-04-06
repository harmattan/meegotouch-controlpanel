include (../common.pri)
TEMPLATE = app
TARGET = ../duicontrolpanel
DEPENDPATH += $$system(find ./ -type d)
INCLUDEPATH += $$DEPENDPATH ../../lib/src/appletif

OBJECTS_DIR = ../tmp
MOC_DIR = ../tmp


# Input
HEADERS += $$system(find ./ -name \'*.h\')
SOURCES += $$system(find ./ -name \'*.cpp\')

CONFIG += build_all silent warn_on debug

INCLUDEPATH += $$[QT_INSTALL_HEADERS]/dui
INCLUDEPATH += /usr/include/dui
LIBS += -ldui

# a fake check target so as not to stop the testing:
QMAKE_EXTRA_TARGETS += check

target.path += $${PREFIX}/bin

install_headers.path = $${PREFIX}/include/qt4/dui/ 
install_headers.files = dcpappletif.h
message("The install path for the executable will be: "$$target.path)

INSTALLS += target install_headers

