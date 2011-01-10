include(../common_top.pri)

INCLUDEPATH += $$system(find $$SRCDIR/categories -type d)

TARGET = ut_category

TEST_SOURCES = \
    $$SRCDIR/categories/category.cpp \
    $$SRCDIR/categories/memorycategory.cpp \
    $$SRCDIR/categories/filecategory.cpp \

# unit test and unit
SOURCES += \
    ut_category.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_category.h \
    $$SRCDIR/categories/memorycategory.h \
    $$SRCDIR/categories/filecategory.h \
    $$SRCDIR/categories/category.h \

# base classes
HEADERS += \


# service classes
HEADERS += \


