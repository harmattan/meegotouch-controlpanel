QMAKE_LIBDIR  += ../../lib/lib/
TEMPLATE      = lib
CONFIG       += plugin gui dui silent
LIBS         += -lduicontrolpanel
INCLUDEPATH  += $$system(find ../../lib/src/ -type d) 

MOC_DIR	      = .moc
OBJECTS_DIR   = .objects

HEADERS       = languageapplet.h \
                languagewidget.h \
                languagebutton.h \
                servicescontainer.h \
                servicesbutton.h \
                servicesbuttonblock.h \
                dcplanguage.h \
                displaydialog.h \
                keyboarddialog.h \
                languagetranslation.h \
                languagelistitem.h \
                dcpspaceritem.h \
                languageselectcontainer.h \
                keyboardselectcontainer.h \
                languagelabelbuttoncontainer.h \
                grouptitlewidget.h \
                dcplanguageconf.h \
                languagelabel.h \
                removablelistitem.h \
                commondialog.h

SOURCES       = languageapplet.cpp \
                languagewidget.cpp \
                languagebutton.cpp \
                servicescontainer.cpp \
                servicesbutton.cpp \
                servicesbuttonblock.cpp \
                displaydialog.cpp \
                keyboarddialog.cpp \
                languagelistitem.cpp \
                dcpspaceritem.cpp \
                languageselectcontainer.cpp \
                keyboardselectcontainer.cpp \
                languagelabelbuttoncontainer.cpp \
                grouptitlewidget.cpp\
                dcplanguageconf.cpp \
                languagelabel.cpp \
                removablelistitem.cpp \
                commondialog.cpp


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
