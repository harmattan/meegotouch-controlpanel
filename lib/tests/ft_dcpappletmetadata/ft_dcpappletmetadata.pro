include(../common_top.pri)
INCLUDEPATH += $$system(find $$SRCDIR -type d)
TARGET = ft_dcpappletmetadata

TEST_SOURCES = $$SRCDIR/appletdb/dcpappletmetadata.cpp

DEFINES -= APPLET_LIBS=\\\"\"$$DCP_APPLET_DIR\"\\\"
DEFINES += APPLET_LIBS=\\\"\"so.applet\"\\\"

# unit test and unit
SOURCES += ft_dcpappletmetadata.cpp \
           $$TEST_SOURCES

# base classes
SOURCES += 

# function test and unit
HEADERS += ft_dcpappletmetadata.h \
           $$SRCDIR/appletdb/dcpappletmetadata.h

# base classes
HEADERS += 

# service classes
HEADERS += 

desktops.files = ft_dcpappletmetadata-data/desktops/*.desktop
desktops.path = $${DCP_INSTALL_LIB}/libduicontrolpanel-tests/ft_dcpappletmetadata-data/desktops

INSTALLS += desktops

include(../common_bot.pri)

