include(../common_top.pri)

CONFIG += meegotouch

INCLUDEPATH += $$system(find $$SRCDIR -type d)
INCLUDEPATH += $${LIBDCPINCLUDE}
INCLUDEPATH += $${SRCDIR}/component/
APPLETDBINCLUDE = $${LIBDCPINCLUDE}/../appletdb
INCLUDEPATH += $${APPLETDBINCLUDE}
INCLUDEPATH += $${STUBSDIR}

TARGET = ut_dcpappletwidget

TEST_SOURCES = \
    $$SRCDIR/component/dcpappletwidget.cpp \

# unit test and unit
SOURCES += \
    *.cpp \
    $$LIBDCPFAKES/dcpwidget-fake.cpp \
    $$LIBDCPFAKES/dcpstylablewidget-fake.cpp \
    $$TEST_SOURCES \

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    *.h \
    $$SRCDIR/component/dcpappletwidget.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


