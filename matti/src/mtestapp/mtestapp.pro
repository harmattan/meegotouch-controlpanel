include(base.pri)
include(../../config.pri)
TEMPLATE = lib
CONFIG += dll link_pkgconfig create_prl debug dui
TARGET = mtestapp
DEPENDPATH += .
INCLUDEPATH += .
QMAKE_CFLAGS += -Werror


target.path=$$LIB_INSTALL_LOCATION

pc_file.path=$$LIB_INSTALL_LOCATION/pkgconfig
pc_file.files=mtestapp.pc

HEADERS += \
	mtestapp.h \
	mtestpagefactory.h 

headers.path=$$HEADER_INSTALL_LOCATION
headers.files=$$HEADERS

SOURCES += \
	mtestapp.cpp \
	mtestpagefactory.cpp \

INSTALLS +=  \
    target  \
    headers \
    pc_file \


QMAKE_EXTRA_TARGETS += check 
check.depends = $$DESTDIR/lib$${TARGET}.so.$$VERSION
check.commands = $$system(true)

