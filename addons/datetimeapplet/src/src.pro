QMAKE_LIBDIR  += ../../../lib/lib/
TEMPLATE      = lib
CONFIG       += plugin gui dui silent debug
LIBS         += -lduicontrolpanel -lclockwidgets -ltime

LIBS += /usr/lib/libdatepicker.so

INCLUDEPATH  += ../../../lib/src/include

MOC_DIR	      = .moc
OBJECTS_DIR   = .objects


HEADERS += $$system(find ./ -name \'*.h\')
SOURCES += $$system(find ./ -name \'*.cpp\')


TARGET        = $$qtLibraryTarget(datetimeapplet)
css.files     = datetimeapplet.css
DESTDIR       = ../lib

target.path += $$(DEBIAN_DESTDIR)$$[QT_INSTALL_LIBS]/duicontrolpanel/applets
css.path    += $$(DEBIAN_DESTDIR)/usr/share/duicontrolpanel/themes/style
desktop.files += *.desktop
desktop.path = $$(DEBIAN_DESTDIR)/usr/lib/duicontrolpanel

message("The plugin will be installed to: " $$target.path)
message("CSS path will be: " $$css.path)
message ("Desktop path will be: "$$desktop.path)


INSTALLS += \
	    target \
        css \
        desktop

INSTALLS +=     conf
