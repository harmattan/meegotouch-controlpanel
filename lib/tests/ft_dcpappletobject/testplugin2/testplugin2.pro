include ($$[QT_INSTALL_DATA]/mkspecs/dcpconfig.pri)

TEMPLATE = lib
CONFIG += plugin gui meegotouch debug

INCLUDEPATH += ../../../src/include

HEADERS = \
    testapplet2.h \
    testappletwidget2.h \

SOURCES = \
    testapplet2.cpp \
    testappletwidget2.cpp \

TARGET = $$qtLibraryTarget(testapplet2)

DATADIR = /usr/lib/duicontrolpanel-tests/ft_dcpappletobject-data

DEFINES += DATADIR=\\\"$$DATADIR\\\"

desktop.files = testapplet2.desktop
desktop.path = $$DATADIR
target.path = $$DATADIR
css.files = testapplet2.css
css.path = $$DATADIR

INSTALLS += target desktop css
