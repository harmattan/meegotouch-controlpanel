include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR -type d)

TARGET = ut_dcpcategories

TEST_SOURCES = \
    $$SRCDIR/categories/dcpcategories.cpp \
    $$SRCDIR/categories/category.cpp \
    $$SRCDIR/categories/filecategory.cpp \
    $$SRCDIR/categories/memorycategory.cpp \

# unit test and unit
SOURCES += \
    *.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_dcpcategories.h \
    $$SRCDIR/categories/dcpcategories.h \
    $$SRCDIR/categories/category.h \
    $$SRCDIR/categories/filecategory.h \
    $$SRCDIR/categories/memorycategory.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


