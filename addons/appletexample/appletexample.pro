TEMPLATE 	= app
OBJECTS_DIR 	= .objects
MOC_DIR 	= .moc
CONFIG		+= build_all silent warn_on dui

# old one (has to be removed):
INCLUDEPATH 	+= ../languageapplet

LIBS 		+= -L./lib 


# Input
HEADERS		+= mainwindow.h \
		       mainview.h

SOURCES		+= main.cpp  \
		       mainwindow.cpp \
		       mainview.cpp
