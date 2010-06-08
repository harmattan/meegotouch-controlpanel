include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ut_dcpcontentbutton

TEST_SOURCES = \
    $$SRCDIR/widget/dcpcontentbutton.cpp \

# unit test and unit
SOURCES += \
    ut_dcpcontentbutton.cpp \
    ../doubles/mtheme-fake.cpp \
    ../../../controlpanel/tests/doubles/dcpappletmetadata-fake.cpp \
    ../../../controlpanel/tests/doubles/dcpappletplugin-fake.cpp \
    $$TEST_SOURCES \

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_dcpcontentbutton.h \
    ../../../controlpanel/tests/doubles/dcpappletplugin-applet.h \
    $$SRCDIR/widget/dcpcontentbutton.h \

# base classes
HEADERS += \


# service classes
HEADERS += \

include(../common_bot.pri)

