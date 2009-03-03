# this is the top of each test's project file

TEMPLATE = app
DEPENDPATH += .

OBJECTS_DIR = ../../tmp
MOC_DIR = ../../tmp

INCLUDEPATH += $$[QT_INSTALL_HEADERS]/dui
LIBS += -ldui

CONFIG  += qtestlib debug silent warn_on

QMAKE_EXTRA_TARGETS += check
check.depends = $$TARGET
check.commands = ./$$TARGET

