QMAKE_LIBDIR += ../../lib/lib/
TEMPLATE      = lib
CONFIG       += plugin gui dui silent debug
LIBS         += -lduicontrolpanel
INCLUDEPATH  += ../../lib/src/include

MOC_DIR	      = .moc
OBJECTS_DIR   = .objects

HEADERS       = displayapplet.h \
		        displaywidget.h \
                displaytranslation.h \
                dummywidget.h \
                displaybrief.h

SOURCES       = displayapplet.cpp \
		        displaywidget.cpp \
                dummywidget.cpp \
                displaybrief.cpp



css.files     = displayapplet.css 
DESTDIR       = lib

desktop.files += *.desktop
desktop.path = $$(DEBIAN_DESTDIR)/usr/lib/duicontrolpanel
target.path += $$(DEBIAN_DESTDIR)$$[QT_INSTALL_LIBS]/duicontrolpanel/applets
css.path    += $$(DEBIAN_DESTDIR)/usr/share/duicontrolpanel/themes/style

message("The plugin will be installed to: " $$target.path)
message("CSS path will be: " $$css.path)

INSTALLS += \
	    target \
        css \
        desktop

