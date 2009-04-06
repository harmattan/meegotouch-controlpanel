QMAKE_LIBDIR += ../../lib/lib
TEMPLATE      = lib
CONFIG       += plugin gui dui silent
LIBS         += -ldui -lduicontrolpanel
INCLUDEPATH  += $$[QT_INSTALL_HEADERS]/dui \
                ../../lib/src/appletif
# new one:
INCLUDEPATH += /usr/include/dui

MOC_DIR	      = .moc
OBJECTS_DIR   = .objects

HEADERS       = displayapplet.h \
		        displaywidget.h \
                displaytranslation.h \
                dummywidget.h

SOURCES       = displayapplet.cpp \
		        displaywidget.cpp \
                dummywidget.cpp 


TARGET        = $$qtLibraryTarget(displayapplet)
css.files     = displayapplet.css 
DESTDIR       = lib

target.path += $$(DEBIAN_DESTDIR)$$[QT_INSTALL_LIBS]/duicontrolpanel/applets
css.path    += $$(DEBIAN_DESTDIR)/usr/share/themes/dui/duicontrolpanel

message("The plugin will be installed to: " $$target.path)
message("CSS path will be: " $$css.path)

INSTALLS += \
	    target \
        css
