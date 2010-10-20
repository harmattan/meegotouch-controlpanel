include(../../lib/dcpconfig.pri)

QMAKE_LIBDIR += ../../lib/lib/ 
TEMPLATE = app
DEPENDPATH += ../../lib/src/include
INCLUDEPATH += $$DEPENDPATH

TARGET = ../duicontrolpanel-briefsupplier

OBJECTS_DIR = ../tmp
MOC_DIR = ../tmp

# Input
HEADERS += $$system(find ./ -name \'*.h\')
SOURCES += $$system(find ./ -name \'*.cpp\')

CONFIG += meegotouch build_all warn_on debug
QT += network
LIBS += -lduicontrolpanel

# a fake check target so as not to stop the testing:
QMAKE_EXTRA_TARGETS += check

target.path += $$DCP_PREFIX/bin

INSTALLS += target \

contains(DCP_BUILD_FEATURES,coverage) {
  QMAKE_EXTRA_TARGETS += coverage
  coverage.commands = $$system(true)
}

# disable internal deprecation warnings:
DEFINES += DCP_DISABLE_DEPRECATION_WARNING

