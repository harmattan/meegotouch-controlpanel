include(../common_top.pri)
OBJECTS_DIR = .tmp                                                                                                
MOC_DIR = .tmp 

INCLUDEPATH += $$system(find $$SRCDIR -type d)
INCLUDEPATH += $${LIBDCPINCLUDE}
APPLETDBINCLUDE = $${LIBDCPINCLUDE}/../appletdb
INCLUDEPATH += $${APPLETDBINCLUDE}
INCLUDEPATH += $${LIBDCPFAKES}
INCLUDEPATH += $${STUBSDIR}

TARGET = ut_dcpappletbuttons

TEST_SOURCES = \
    $$SRCDIR/page/dcpappletbuttons.cpp \
    $$SRCDIR/page/pages.cpp \
    $$SRCDIR/component/dcpcomponent.cpp \
    $$SRCDIR/component/dcpmaincategory.cpp \
    ../doubles/stubbase.cpp \

# unit test and unit
SOURCES += \
    ut_dcpappletbuttons.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_dcpappletbuttons.h \
    $$SRCDIR/page/dcpappletbuttons.h \
    $$SRCDIR/component/*.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


