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
<<<<<<< HEAD:lib/src/src.pro
    applet/dcpmetadata.h \
    widget/dcpwidgettypes.h \
    scene/dcpscenelayereffectdialogview.h
=======
    applet/dcpbrief.h \
    button/dcpbutton.h \
    widget/dcpwidgettypes.h \
    widget/dcpspaceritem.h \
    scene/dcpscenelayereffectdialogview.h \
    appletdb/dcpappletdb.h \
    appletdb/dcpappletloader.h \
    appletdb/dcpappletmetadata.h
>>>>>>> 22f5557afc384178953f682d532d13248dd609af:lib/src/src.pro

INSTALLS += target install_headers 
