include(../common_top.pri)
CONFIG += meegotouch
INCLUDEPATH += $$system(find $$SRCDIR -type d)
INCLUDEPATH += ../doubles 
INCLUDEPATH += $$LIBDCPSRC/appletdb 

TARGET = ft_dcpsinglecomponent

TEST_SOURCES = \
    $$SRCDIR/component/dcpsinglecomponent.cpp \
    $$SRCDIR/categories/category.cpp \
    $$SRCDIR/categories/memorycategory.cpp \
    $$SRCDIR/page/pages.cpp \
    $$SRCDIR/page/dcppage.cpp \
    ../doubles/pagefactory-fake.cpp \

# unit test and unit
SOURCES += \
    ft_dcpsinglecomponent.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ft_dcpsinglecomponent.h \
    $$SRCDIR/component/dcpsinglecomponent.h \
    $$SRCDIR/page/pages.h \
    $$SRCDIR/page/dcppage.h \
    $$SRCDIR/page/pagefactory.h \
    $$SRCDIR/categories/category.h \
    $$SRCDIR/categories/memorycategory.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


