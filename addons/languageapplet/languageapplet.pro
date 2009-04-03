QMAKE_LIBDIR  += ../../lib/lib
TEMPLATE      = lib
CONFIG       += plugin gui dui
LIBS         += -ldui -lduicontrolpanel
INCLUDEPATH  += $$[QT_INSTALL_HEADERS]/dui\
                ../../lib/src/appletif

MOC_DIR	      = .moc
OBJECTS_DIR   = .objects

HEADERS       = languageapplet.h \
                languagewidget.h \
                languagebutton.h \
                servicescontainer.h \
                servicesbutton.h \
                servicesbuttonblock.h \
                dcplanguage.h \
                displaywidget.h \
                keyboardwidget.h \
                languagetranslation.h

SOURCES       = languageapplet.cpp \
                languagewidget.cpp \
                languagebutton.cpp \
                servicescontainer.cpp \
                servicesbutton.cpp \
                servicesbuttonblock.cpp \
                displaywidget.cpp \
                keyboardwidget.cpp

TARGET        = $$qtLibraryTarget(languageapplet)
css.files     = languageapplet.css
image.files   = images/*.png
DESTDIR       = lib

target.path += $$(DEBIAN_DESTDIR)$$[QT_INSTALL_LIBS]/duicontrolpanel/applets
css.path    += $$(DEBIAN_DESTDIR)/usr/share/themes/dui/duicontrolpanel
image.path  += $$(DEBIAN_DESTDIR)/usr/share/themes/dui/duicontrolpanel/images

message ("Plugin path will be: "$$target.path)
message ("CSS path will be: "$$css.path)
message ("Image path will be: "$$image.path)

INSTALLS += \
	        target \
	        css \
            image
