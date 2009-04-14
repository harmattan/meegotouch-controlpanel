QMAKE_LIBDIR  += ../../lib/lib/
TEMPLATE      = lib
CONFIG       += plugin gui dui silent
LIBS         += -ldui -lduicontrolpanel
INCLUDEPATH  += $$[QT_INSTALL_HEADERS]/dui\
                $$system(find ../../lib/src/ -type d) 

INCLUDEPATH += /usr/include/dui

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
                displaydialog.h \
                keyboardwidget.h \
                keyboarddialog.h \
                languagetranslation.h \
                languagelistitem.h \
                dcpspaceritem.h \
                languageselectcontainer.h \
                keyboardselectcontainer.h \
                grouptitlewidget.h \
                dcplanguageconf.h

SOURCES       = languageapplet.cpp \
                languagewidget.cpp \
                languagebutton.cpp \
                servicescontainer.cpp \
                servicesbutton.cpp \
                servicesbuttonblock.cpp \
                displaywidget.cpp \
                displaydialog.cpp \
                keyboardwidget.cpp \
                keyboarddialog.cpp \
                languagelistitem.cpp \
                dcpspaceritem.cpp \
                languageselectcontainer.cpp \
                keyboardselectcontainer.cpp \
                grouptitlewidget.cpp\
                dcplanguageconf.cpp


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
