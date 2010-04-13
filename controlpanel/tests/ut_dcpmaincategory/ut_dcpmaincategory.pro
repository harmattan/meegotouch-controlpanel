include(../common_top.pri)
CONFIG += dui duicontrolpanel
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
    ../doubles/duiapplication-fake.cpp \
    ../doubles/duiapplicationwindow-fake.cpp \
    ../doubles/duiwindow-fake.h \
    ../doubles/duilayout-fake.cpp \
    ../doubles/duiabstractlayoutpolicy-fake.cpp \
    ../doubles/duilinearlayoutpolicy-fake.cpp \
    ../doubles/duigridlayoutpolicy-fake.cpp \
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


