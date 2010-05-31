include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ft_dcpcontentitem

TEST_SOURCES = \
    $$SRCDIR/widget/dcpcontentitem.cpp \

# unit test and unit
SOURCES += \
    ft_dcpcontentitem.cpp \
#   ../doubles/mcontentitem-fake.cpp \
#   ../doubles/mtheme-fake.cpp \
#   ../../../controlpanel/tests/doubles/dcpappletmetadata-fake.cpp \
#   ../../../controlpanel/tests/doubles/dcpappletplugin-fake.cpp \
#   ../../../controlpanel/tests/doubles/dcpappletobject-fake.cpp \
    $$TEST_SOURCES \

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ft_dcpcontentitem.h \
#    ../../../controlpanel/tests/doubles/dcpappletplugin-applet.h \
    $$SRCDIR/widget/dcpcontentitem.h \

# base classes
HEADERS += \


# service classes
HEADERS += \

include(../common_bot.pri)

