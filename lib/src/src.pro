TEMPLATE      = lib
CONFIG       += plugin gui dui debug
INCLUDEPATH  += $$system(find ./ -type d)
MOC_DIR	      = .moc
OBJECTS_DIR   = .objects

include(../dcpconfig.pri)

# this has to be above finds, because it generates .h .cpp files
include(service_interface/service_interface.pri)

# Input
HEADERS += $$system(find ./ -name \'*.h\')
SOURCES += $$system(find ./ -name \'*.cpp\' -not -name \'moc_*\')

TARGET        = $$qtLibraryTarget(duicontrolpanel)
DESTDIR       = ../lib

target.path    += $$DCP_INSTALL_LIB
install_headers.path    += $$DCP_INSTALL_HEADERS
install_headers.files += include/D* \
    applet/dcpapplet.h \
    applet/dcpappletif.h \
    applet/dcpwidget.h \
    applet/dcpmetadata.h \
    applet/dcpbrief.h \
    button/dcpbutton2.h \
    button/dcpbutton2align.h \
    button/dcpbutton2toggle.h \
    button/dcpbutton2image.h \
    button/dcpbriefwidget.h \
    widget/dcpwidgettypes.h \
    widget/dcpspaceritem.h \
    widget/dcpdialog.h \
    widget/dcpcommondialog.h \
    appletdb/dcpappletdb.h \
    appletdb/dcpappletloader.h \
    appletdb/dcpappletmetadata.h \
    dcpdebug.h \
    appletdb/dcpmostusedcounter.h \
    service_interface/duicontrolpanelif.h \
    service_interface/duicontrolpanelifproxy.h

install_prf.path = $$[QT_INSTALL_DATA]/mkspecs/features
install_prf.files = duicontrolpanel.prf

INSTALLS += target install_headers install_prf


QMAKE_EXTRA_TARGETS += check
check.commands = $$system(true)

QMAKE_EXTRA_TARGETS += check-xml
check-xml.commands = $$system(true)

