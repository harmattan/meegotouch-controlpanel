include(../common_top.pri)

# FIXME: temporary solution, it will be in meegotouch
INCLUDEPATH += /usr/include/userguide
DEPENDPATH += /usr/include/userguide
LIBS += -luserguide

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TEST_SOURCES = \
    $$SRCDIR/widget/dcpcontentitem.cpp \

# unit test and unit
SOURCES += \
    ut_dcpcontentitem.cpp \
    ../doubles/mtheme-fake.cpp \
    ../../../controlpanel/tests/doubles/dcpappletmetadata-fake.cpp \
    ../../../controlpanel/tests/doubles/dcpappletplugin-fake.cpp \
    ../../../controlpanel/tests/doubles/mlayout-fake.cpp \
    ../../../controlpanel/tests/doubles/mgridlayoutpolicy-fake.cpp \
    ../../../controlpanel/tests/doubles/mabstractlayoutpolicy-fake.cpp \
    ../doubles/mimagewidget-fake.cpp \
    ../doubles/mhelpbutton-fake.cpp \
    $$TEST_SOURCES \

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_dcpcontentitem.h \
    ../../../controlpanel/tests/doubles/dcpappletplugin-applet.h \
    $$SRCDIR/widget/dcpcontentitem.h \

# base classes
HEADERS += \


# service classes
HEADERS += \

include(../common_bot.pri)

