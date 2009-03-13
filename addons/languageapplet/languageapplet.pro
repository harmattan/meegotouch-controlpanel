TEMPLATE      = lib
CONFIG       += plugin gui dui
LIBS         += -ldui
INCLUDEPATH  += $$[QT_INSTALL_HEADERS]/dui
MOC_DIR	      = .moc
OBJECTS_DIR   = .objects

HEADERS       = languageapplet.h \
                languagewidget.h \
                languagebutton.h

SOURCES       = languageapplet.cpp \
                languagewidget.cpp \
                languagebutton.cpp

TARGET        = $$qtLibraryTarget(languageapplet)
css.files     = languageapplet.css
DESTDIR       = lib

target.path += $$(DEBIAN_DESTDIR)$$[QT_INSTALL_LIBS]/duicontrolpanel/applets
css.path += $$(DEBIAN_DESTDIR)/usr/share/theme/dui/duicontrolpanel

message ("Plugin path will be: "$$target.path)
message ("CSS path will be: "$$css.path)

INSTALLS += \
	    target \
	    css
