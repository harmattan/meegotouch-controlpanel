CONFIG += ordered dui
TEMPLATE = subdirs
SUBDIRS += \
    src\
    testsuites\

include(check.pri)
