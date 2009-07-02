QMAKE_LIBDIR  += ../../../lib/lib/
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
                datetimetranslation.h \
                timezoneview.h \
                timezonelistitem.h \
                timezonecontainer.h \
                dcptimezoneconf.h \
                dcptimezonedata.h \
                dcpdatetime.h \
                dcpicuconversions.h \
                dateview.h \
                timeview.h

SOURCES       = datetimeapplet.cpp \
		        datetimewidget.cpp \
                updatebutton.cpp \
                datetimebrief.cpp \
                timezoneview.cpp \
                timezonelistitem.cpp \
                timezonecontainer.cpp \
                dcptimezoneconf.cpp \
                dcptimezonedata.cpp \
                dcpicuconversions.cpp \
                dateview.cpp \
                timeview.cpp


TARGET        = $$qtLibraryTarget(datetimeapplet)
css.files     = datetimeapplet.css 
DESTDIR       = ../lib

target.path += $$(DEBIAN_DESTDIR)$$[QT_INSTALL_LIBS]/duicontrolpanel/applets
css.path    += $$(DEBIAN_DESTDIR)/usr/share/duicontrolpanel/themes/style

message("The plugin will be installed to: " $$target.path)
message("CSS path will be: " $$css.path)

INSTALLS += \
	    target \
        css

