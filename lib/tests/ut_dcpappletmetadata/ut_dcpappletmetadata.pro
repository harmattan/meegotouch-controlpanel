include(../common_top.pri)
INCLUDEPATH += $$system(find $$SRCDIR -type d)
TARGET = ut_dcpappletmetadata
TEST_SOURCES = $$SRCDIR/appletdb/dcpappletmetadata.cpp
# unit test and unit
SOURCES += ut_dcpappletmetadata.cpp \
    $$TEST_SOURCES

# base classes
SOURCES += 

# unit test and unit
HEADERS += ut_dcpappletmetadata.h \
    $$SRCDIR/appletdb/dcpappletmetadata.h

# base classes
HEADERS += 

# service classes
HEADERS += 

desktops.files = ut_dcpappletmetadata-data/desktops/*.desktop
desktops.path = $${DCP_INSTALL_LIB}/libduicontrolpanel-tests/ut_dcpappletmetadata-data/desktops

INSTALLS += desktops
