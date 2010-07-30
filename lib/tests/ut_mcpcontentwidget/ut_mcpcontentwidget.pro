include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ut_mcpcontentwidget

TEST_SOURCES = \
    $$SRCDIR/widget/mcpcontentwidget.cpp \

# unit test and unit
SOURCES += \
    ut_mcpcontentwidget.cpp \
    ../doubles/mtheme-fake.cpp \
    ../../../controlpanel/tests/doubles/dcpappletmetadata-fake.cpp \
    ../../../controlpanel/tests/doubles/dcpappletplugin-fake.cpp \
    ../../../controlpanel/tests/doubles/mlayout-fake.cpp \
    ../../../controlpanel/tests/doubles/mgridlayoutpolicy-fake.cpp \
    ../../../controlpanel/tests/doubles/mabstractlayoutpolicy-fake.cpp \
    ../doubles/mimagewidget-fake.cpp \
    $$TEST_SOURCES \

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_mcpcontentwidget.h \
    ../../../controlpanel/tests/doubles/dcpappletplugin-applet.h \
    $$SRCDIR/widget/mcpcontentwidget.h \

# base classes
HEADERS += \


# service classes
HEADERS += \

include(../common_bot.pri)

