include(../../lib/dcpconfig.pri)
TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += $$DEPENDPATH ../../lib/src/include

OBJECTS_DIR = tmp
MOC_DIR = tmp

# Input
HEADERS += $$system(find ./ -name \'*.h\')
SOURCES += $$system(find ./ -name \'*.cpp\')

CONFIG += meegotouch build_all warn_on debug

# a fake check target so as not to stop the testing:
QMAKE_EXTRA_TARGETS += check

