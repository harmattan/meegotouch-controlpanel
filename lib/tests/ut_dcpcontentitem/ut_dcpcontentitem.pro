include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ut_dcpcontentitem

TEST_SOURCES = \
    $$SRCDIR/widget/dcpcontentitem.cpp \

# unit test and unit
SOURCES += \
    *.cpp \
    ../doubles/mcontentitem-fake.cpp \
    ../doubles/mtheme-fake.cpp \
    ../../../controlpanel/tests/doubles/dcpappletmetadata-fake.cpp \
    ../../../controlpanel/tests/doubles/dcpappletplugin-fake.cpp \
    $$TEST_SOURCES \

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    *.h \
    $$SRCDIR/widget/dcpcontentitem.h \

# base classes
HEADERS += \


# service classes
HEADERS += \

include(../common_bot.pri)

