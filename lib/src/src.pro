TEMPLATE      = lib
CONFIG       += plugin gui dui debug
INCLUDEPATH  += $$system(find ./ -type d)
MOC_DIR	      = .moc
OBJECTS_DIR   = .objects

include(../../dcpconfig.pri)
# Input
HEADERS += $$system(find ./ -name \'*.h\')
SOURCES += $$system(find ./ -name \'*.cpp\' -not -name \'moc_*\')

TARGET        = $$qtLibraryTarget(duicontrolpanel)
DESTDIR       = ../lib

target.path    += $$DCP_INSTALL_LIB
install_headers.path    += $$DCP_INSTALL_HEADERS
install_headers.files += include/Dcp* \
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
    appletdb/dcpmostusedcounter.h
INSTALLS += target install_headers

