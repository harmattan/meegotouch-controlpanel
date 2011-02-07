TOPDIR=../../..
include ($$TOPDIR/dcpconfig.pri)
TEMPLATE      = lib
CONFIG       += plugin gui meegotouch silent debug
INCLUDEPATH += $$system(find $$TOPDIR -type d)
MOC_DIR	      = .moc
OBJECTS_DIR   = .objects

HEADERS       = buttonapplet.h \
                buttonbrief.h

SOURCES       = buttonapplet.cpp \
                buttonbrief.cpp

TARGET        = ../$$qtLibraryTarget(dcpbuttonapplet)

                                                                                                                      
DATADIR = /usr/lib/duicontrolpanel-tests/ft_dcpcontentbutton-data

DEFINES += DATADIR=\\\"$$DATADIR\\\"

desktop.files = buttonapplet.desktop
desktop.path = $$DATADIR
target.path = $$DATADIR
css.files = buttonapplet.css
css.path = $$DATADIR
                                                                                                                      
INSTALLS += target desktop css                   
INSTALLS += \
	    target \

