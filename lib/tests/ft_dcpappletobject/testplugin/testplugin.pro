TEMPLATE = lib
CONFIG += plugin gui dui duicontrolpanel debug

HEADERS = testapplet.h testappletwidget.h
SOURCES = testapplet.cpp testappletwidget.cpp

TARGET = $$qtLibraryTarget(testapplet)

DATADIR = /usr/lib/duicontrolpanel-tests/ft_dcpappletobject-data

DEFINES += DATADIR=\\\"$$(DATADIR)\\\"

desktop.file = testapplet.desktop
desktop.path = $$DATADIR
target.path = $$DATADIR

INSTALLS += target desktop
