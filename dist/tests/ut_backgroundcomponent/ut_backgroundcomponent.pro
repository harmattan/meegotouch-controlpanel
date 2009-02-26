include(../common_top.pri)
TARGET = ut_backgroundcomponent


# the required components for the test:
DEPENDPATH += ../../src/page/main \ 
         ../../src/base/dcpcomponent \
         ../../src/pagefactory \

HEADERS += ../../src/page/main/dcpbackgroundcomponent.h \
         ../../src/base/dcpcomponent/dcpcomponent.h \
         ../../src/pagefactory/pages.h \
         ut_backgroundcomponent.h \

SOURCES += ../../src/page/main/dcpbackgroundcomponent.cpp\
         ../../src/base/dcpcomponent/dcpcomponent.cpp \
         ut_backgroundcomponent.cpp \

include(../common_bottom.pri)

