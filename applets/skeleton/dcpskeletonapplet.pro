include(../../lib/dcpconfig.pri)
QMAKE_LIBDIR += ../../lib/lib/
TEMPLATE      = lib
CONFIG       += plugin gui dui silent debug
LIBS         += -lduicontrolpanel
INCLUDEPATH  += ../../lib/src/include

MOC_DIR	      = .moc
OBJECTS_DIR   = .objects

HEADERS       = dcpskeletonapplet.h \
		dcpskeletonwidget.h \
                translations.h \
                dcpskeletonbrief.h

SOURCES       = dcpskeletonapplet.cpp \
		dcpskeletonwidget.cpp \
                dcpskeletonbrief.cpp



css.files     = skeletonapplet.css 
DESTDIR       = lib

desktop.files += *.desktop
desktop.path = $$DCP_DESKTOP_DIR
target.path += $$DCP_APPLET_DIR
css.path    += $$DCP_THEME_DIR/style

message("The plugin will be installed to: " $$target.path)
message("CSS path will be: " $$css.path)

INSTALLS += \
	    target \
        css \
        desktop

