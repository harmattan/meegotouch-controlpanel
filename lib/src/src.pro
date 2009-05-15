TEMPLATE      = lib
CONFIG       += plugin gui dui
INCLUDEPATH  += $$system(find ./ -type d)
MOC_DIR	      = .moc
OBJECTS_DIR   = .objects


# Input
HEADERS += $$system(find ./ -name \'*.h\')
message(HEADERS)
SOURCES += $$system(find ./ -name \'*.cpp\')

TARGET        = $$qtLibraryTarget(duicontrolpanel)
DESTDIR       = ../lib

target.path    += $$(DEBIAN_DESTDIR)/usr/lib/
install_headers.path    += $$(DEBIAN_DESTDIR)/usr/include/qt4/dui/
install_headers.files += applet/dcpapplet.h \
    applet/dcpappletif.h \
    applet/dcpwidget.h \
    applet/dcpmetadata.h \
    button/dcpbutton.h \
    widget/dcpwidgettypes.h \
    widget/dcpspaceritem.h \
    scene/dcpscenelayereffectdialogview.h

INSTALLS += target install_headers 
