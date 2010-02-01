include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ft_dcpappletdb

TEST_SOURCES = \
    $$SRCDIR/appletdb/dcpappletdb.cpp 

# unit test and unit
SOURCES += \
    ft_dcpappletdb.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ft_dcpappletdb.h \
    $$SRCDIR/appletdb/dcpappletdb.h \

# base classes
HEADERS += \


# service classes
HEADERS += \

DATADIR = $${DCP_INSTALL_LIB}/libduicontrolpanel-tests/ft_dcpappletdb-data/
desktops1.files += ft_dcpappletdb-data/desktops/*.desktop
desktops1.path = $${DATADIR}/desktops
desktops2.files += ft_dcpappletdb-data/desktops2/*.desktop
desktops2.path = $${DATADIR}/desktops2
desktops3.files += ft_dcpappletdb-data/desktops3/*.desktop
desktops3.path = $${DATADIR}/desktops3

INSTALLS += desktops1 desktops2 desktops3

include(../common_bot.pri)
