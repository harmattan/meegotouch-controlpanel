QMAKE_LIBDIR += ../../../lib/lib/
TEMPLATE      = lib
CONFIG       += plugin gui dui silent
LIBS         += -lduicontrolpanel
INCLUDEPATH  += $$system(find ../../../lib/src/ -type d)

MOC_DIR	      = .moc
OBJECTS_DIR   = .objects

HEADERS       = datetimeapplet.h \
		        datetimewidget.h \
                updatebutton.h \
                datetimebrief.h \
                datetimetranslation.h

SOURCES       = datetimeapplet.cpp \
		        datetimewidget.cpp \
                updatebutton.cpp \
                datetimebrief.cpp


TARGET        = $$qtLibraryTarget(datetimeapplet)
css.files     = datetimeapplet.css 
DESTDIR       = ../lib

target.path += $$(DEBIAN_DESTDIR)$$[QT_INSTALL_LIBS]/duicontrolpanel/applets
css.path    += $$(DEBIAN_DESTDIR)/usr/share/themes/dui/duicontrolpanel

message("The plugin will be installed to: " $$target.path)
message("CSS path will be: " $$css.path)

INSTALLS += \
	    target \
        css
