TEMPLATE      = lib
CONFIG       += plugin gui dui
LIBS         += -ldui 
INCLUDEPATH  += $$[QT_INSTALL_HEADERS]/dui
MOC_DIR	      = .moc
OBJECTS_DIR   = .objects


# Input
HEADERS += $$system(find ./ -name \'*.h\')
SOURCES += $$system(find ./ -name \'*.cpp\')

TARGET        = $$qtLibraryTarget(duicontrolpanel)
DESTDIR       = ../lib

target.path    += $$(DEBIAN_DESTDIR)/usr/lib/
install_headers.path    += $$(DEBIAN_DESTDIR)/usr/include/qt4/dui/
install_headers.files += dcpappletif.h dcpwidget.h

INSTALLS += \
	        target \
	        install_headers 
