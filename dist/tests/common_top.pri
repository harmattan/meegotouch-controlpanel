# this is the top of each test's project file

TEMPLATE = app
DEPENDPATH += .

OBJECTS_DIR = ../../tmp
MOC_DIR = ../../tmp

CONFIG  += qtestlib debug silent warn_on dui

QMAKE_EXTRA_TARGETS += check
check.depends = $$TARGET
check.commands = ./$$TARGET

