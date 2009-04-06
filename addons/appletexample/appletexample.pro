TEMPLATE 	= app
OBJECTS_DIR 	= .objects
MOC_DIR 	= .moc
CONFIG		+= build_all silent warn_on

# old one (has to be removed):
INCLUDEPATH 	+= $$[QT_INSTALL_HEADERS]/dui -I ../languageapplet
# new one:
INCLUDEPATH += /usr/include/dui

LIBS 		+= -L./lib -ldui


# Input
HEADERS		+= mainwindow.h \
		       mainview.h

SOURCES		+= main.cpp  \
		       mainwindow.cpp \
		       mainview.cpp
