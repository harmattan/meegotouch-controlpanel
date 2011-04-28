include(../common_top.pri)
INCLUDEPATH += $$system(find $$SRCDIR -type d)
TARGET = ut_dcpappletmetadata
TEST_SOURCES = $$SRCDIR/appletdb/dcpappletmetadata.cpp

DEFINES -= APPLET_LIBS=\\\"\"$$DCP_APPLET_DIR\"\\\"
DEFINES += APPLET_LIBS=\\\"\"so.applet\"\\\"

# unit test and unit
SOURCES += ut_dcpappletmetadata.cpp \
           ../doubles/mdesktopentry-fake.cpp \
           ../doubles/fileDatas.cpp \
           ../doubles/mlocale-fake.cpp \
           ../doubles/mgconfitem-fake.cpp \
           ../doubles/sysinfo-fake.cpp \
           $$TEST_SOURCES

# base classes
SOURCES += 

# unit test and unit
HEADERS += ut_dcpappletmetadata.h \
           ../doubles/fileDatas.h \
           ../doubles/mlocale-fake.h \
           $$SRCDIR/appletdb/dcpappletmetadata.h \

# base classes
HEADERS += 

# service classes
HEADERS += 

desktops.files = ut_dcpappletmetadata-data/desktops/*.desktop
desktops.path = $${DCP_TESTS_INSTALL_LIB}/ut_dcpappletmetadata-data/desktops

INSTALLS += desktops

include(../common_bot.pri)
