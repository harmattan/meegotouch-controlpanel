include (../../../dcpconfig.pri)

TEMPLATE = lib
CONFIG += plugin gui meegotouch debug

INCLUDEPATH += ../../../src/include

HEADERS = \
    testapplet.h \
    testappletwidget.h \
    testwidget.h \

SOURCES = \
    testapplet.cpp \
    testappletwidget.cpp \
    testwidget.cpp \

# disable internal deprecation warnings:
DEFINES += DCP_DISABLE_DEPRECATION_WARNING

TARGET = ../$$qtLibraryTarget(testapplet)

DATADIR = /usr/lib/duicontrolpanel-tests/ft_dcpappletobject-data

DEFINES += DATADIR=\\\"$$DATADIR\\\"

desktop.files = ../testapplet.desktop
desktop.path = $$DATADIR
target.path = $$DATADIR
css.files = testapplet.css
css.path = $$DATADIR

INSTALLS += target desktop css

