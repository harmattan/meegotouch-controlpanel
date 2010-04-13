include(../common_top.pri)
CONFIG += m mcontrolpanel
INCLUDEPATH += $$system(find $$SRCDIR -type d)
INCLUDEPATH += ../doubles 

TARGET = ut_dcpmaincategory

TEST_SOURCES = \
    $$SRCDIR/component/dcpmaincategory.cpp \

# unit test and unit
SOURCES += \
    ut_dcpmaincategory.cpp \
    $$SRCDIR/page/pages.cpp \
    ../doubles/dcpcomponent-fake.cpp \
    ../doubles/mapplication-fake.cpp \
    ../doubles/mapplicationwindow-fake.cpp \
    ../doubles/mwindow-fake.h \
    ../doubles/mlayout-fake.cpp \
    ../doubles/mabstractlayoutpolicy-fake.cpp \
    ../doubles/mlinearlayoutpolicy-fake.cpp \
    ../doubles/mgridlayoutpolicy-fake.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_dcpmaincategory.h \
    $$SRCDIR/component/dcpmaincategory.h \
    $$SRCDIR/component/dcpcomponent.h \
    $$SRCDIR/page/pages.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


