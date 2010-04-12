include(../common_top.pri)
CONFIG += dui duicontrolpanel
INCLUDEPATH += $$system(find $$SRCDIR -type d)
INCLUDEPATH += ../doubles 
INCLUDEPATH += $$LIBDCPSRC/appletdb 

TARGET = ft_dcpbriefcomponent

TEST_SOURCES = \
    $$SRCDIR/component/dcpbriefcomponent.cpp \
    $$SRCDIR/component/dcpcomponent.cpp \
    $$SRCDIR/page/pages.cpp \
    ../doubles/pagefactory-fake.cpp \
    ../doubles/dcppage-fake.cpp \
    ../doubles/dcpappletplugin-fake.cpp \
    ../doubles/duidesktopentry-fake.cpp \
    ../doubles/duigconfitem-fake.cpp \
    ../doubles/duiapplication-fake.cpp \
    ../doubles/duiapplicationpage-fake.cpp \
    ../doubles/duiapplicationwindow-fake.cpp \

# unit test and unit
SOURCES += \
    ft_dcpbriefcomponent.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ft_dcpbriefcomponent.h \
    $$SRCDIR/component/dcpbriefcomponent.h \
    $$SRCDIR/component/dcpcomponent.h \
    $$SRCDIR/page/pages.h \
    $$SRCDIR/page/dcppage.h \
    $$SRCDIR/page/pagefactory.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


