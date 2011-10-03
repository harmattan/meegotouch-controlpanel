include(../common_top.pri)

CONFIG += meegotouch

INCLUDEPATH += $$system(find $$SRCDIR -type d)
INCLUDEPATH += $${LIBDCPINCLUDE}
APPLETDBINCLUDE = $${LIBDCPINCLUDE}/../appletdb
INCLUDEPATH += $${APPLETDBINCLUDE}
INCLUDEPATH += $${APPLETDBINCLUDE}/../appletmanager
INCLUDEPATH += $${STUBSDIR}

TARGET = ut_dcpappletbuttons

TEST_SOURCES = \
    $$SRCDIR/component/dcpappletbuttons.cpp \
    $$SRCDIR/page/pages.cpp \
    $$SRCDIR/categories/category.cpp \
    $$SRCDIR/categories/memorycategory.cpp \
    $$SRCDIR/categories/categoryutils.cpp \
    $$SRCDIR/component/dcpmaincategory.cpp \
    $$SRCDIR/component/dcpappletwidget.cpp \

# unit test and unit
SOURCES += \
    *.cpp \
    $$STUBSDIR/dcpappletplugin-fake.cpp \
    $$STUBSDIR/dcpremoteappletobject-fake.cpp \
    $$STUBSDIR/dcpappletmanager-fake.cpp \
    $$LIBDCPFAKES/mgconfitem-fake.cpp \
    $$LIBDCPFAKES/mhelpbutton-fake.cpp \
    $$LIBDCPFAKES/mlocale-fake.cpp \
    $$STUBSDIR/dcpappletmetadata-fake.cpp \
    $$STUBSDIR/dcpretranslator-fake.cpp \
    $$STUBSDIR/mwidgetcontroller-fake.cpp \
    $$STUBSDIR/dcpcontentitem-fake.cpp \
    $$STUBSDIR/dcpcontentitemcellcreator-fake.cpp \
    $$STUBSDIR/qgraphicsobject-fake.cpp \
    $$STUBSDIR/mlist-fake.cpp \
    $$STUBSDIR/mtheme-fake.cpp \
    $$STUBSDIR/dcpcategories-fake.cpp \
    $$STUBSDIR/qgraphicslinearlayout-fake.cpp \
    $$TEST_SOURCES \

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_dcpappletbuttons.h \
    $$STUBSDIR/dcpappletplugin-applet.h \
    $$SRCDIR/component/dcpappletbuttons.h \
    $$SRCDIR/component/dcpmaincategory.h \
    $$SRCDIR/component/dcpappletwidget.h \
    $$SRCDIR/categories/category.h \
    $$SRCDIR/categories/dcpcategories.h \
    $$SRCDIR/component/dcpcontentitemcellcreator.h \
    $$SRCDIR/remote/dcpremoteappletobject.h \
    $$SRCDIR/appletmanager/dcpappletmanager.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


