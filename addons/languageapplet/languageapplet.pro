QMAKE_LIBDIR  += ../../lib/lib/
TEMPLATE      = lib
CONFIG       += plugin gui dui silent
LIBS         += -lduicontrolpanel

INCLUDEPATH  += $$system(find ../../lib/src/ -type d) \
             += /usr/include/duivaluespace 

MOC_DIR	      = .moc
OBJECTS_DIR   = .objects

HEADERS       = languageapplet.h \
                languagewidget.h \
                dcplanguage.h \
                displaydialog.h \
                keyboarddialog.h \
                languagetranslation.h \
                languagelistitem.h \
                dcplanguageselectcontainer.h \
                dcplanguageconf.h \
                languagebrief.h

SOURCES       = languageapplet.cpp \
                languagewidget.cpp \
                displaydialog.cpp \
                keyboarddialog.cpp \
                languagelistitem.cpp \
                dcplanguageselectcontainer.cpp \
                dcplanguageconf.cpp \
                languagebrief.cpp


TARGET        = $$qtLibraryTarget(languageapplet)
css.files     = languageapplet.css
image.files   = images/*.png
DESTDIR       = lib

target.path += $$(DEBIAN_DESTDIR)$$[QT_INSTALL_LIBS]/duicontrolpanel/applets
css.path    += $$(DEBIAN_DESTDIR)/usr/share/duicontrolpanel/themes/style
image.path  += $$(DEBIAN_DESTDIR)/usr/share/duicontrolpanel/themes/images
PKGCONFIG += gconf-2.0 duivaluespace-1.0 
exists(/usr/include/dui/duiquerydialog.h){
	DEFINES += QUERY_DIALOG
}
message ("Plugin path will be: "$$target.path)
message ("CSS path will be: "$$css.path)
message ("Image path will be: "$$image.path)

INSTALLS += \
	        target \
	        css \
            image
