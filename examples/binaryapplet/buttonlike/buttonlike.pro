include(../../common.pri)
TEMPLATE      = lib
CONFIG       += plugin gui meegotouch silent debug

MOC_DIR	      = .moc
OBJECTS_DIR   = .objects

HEADERS       = dcpskelbuttonapplet.h \
                dcpskelbuttonbrief.h

SOURCES       = dcpskelbuttonapplet.cpp \
                dcpskelbuttonbrief.cpp

css.files     = skelbuttonapplet.css
DESTDIR       = ../lib
TARGET        = $$qtLibraryTarget(dcpskelbuttonapplet)
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

