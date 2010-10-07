TEMPLATE      = lib
CONFIG       += plugin gui meegotouch debug
INCLUDEPATH  += $$system(find ./ -type d)
MOC_DIR	      = .moc
OBJECTS_DIR   = .objects
QMAKE_LFLAGS_RPATH = -Wl
include(../dcpconfig.pri)

# we can not disable functions from the lib since our api is considered stable
CONFIG += MOSTUSED

# FIXME: this has to be removed if the functionality has merged into meegotouch
CONFIG+=userguide

MOSTUSED {
    DEFINES += MOSTUSED
}
# this has to be above finds, because it generates .h .cpp files
include(service_interface/service_interface.pri)

# Input
HEADERS += $$system(find ./ -name \'*.h\')
SOURCES += $$system(find ./ -name \'*.cpp\' -not -name \'moc_*\')

TARGET        = $$qtLibraryTarget(duicontrolpanel)
DESTDIR       = ../lib

# disable internal deprecation warnings:
DEFINES += DCP_DISABLE_DEPRECATION_WARNING


target.path    += $$DCP_INSTALL_LIB
install_headers.path    += $$DCP_INSTALL_HEADERS
install_headers.files += $$system(echo include/D*) \
    appletdb/dcpapplet.h \
    appletdb/dcpappletif.h \
    appletdb/dcpwidget.h \
    appletdb/dcpmetadata.h \
    appletdb/dcpbrief.h \
    appletdb/dcpappletdb.h \
    appletdb/dcpappletplugin.h \
    appletdb/dcpappletobject.h \
    appletdb/dcpappletmetadata.h \
    appletdb/dcpmostusedcounter.h \
    appletdb/dcpmostusedcounter.h \
    widget/dcpbutton.h \
    widget/dcpbuttonalign.h \
    widget/dcpbuttontoggle.h \
    widget/dcpbuttonimage.h \
    widget/dcpbriefwidget.h \
    widget/dcpwidgettypes.h \
    dcpdebug.h \
    dcpretranslator.h \
    service_interface/duicontrolpanelif.h \
    service_interface/duicontrolpanelifproxy.h

message ("Install headers:" $$install_headers.files)

install_prf.path = $$[QT_INSTALL_DATA]/mkspecs/features
install_prf.files = duicontrolpanel.prf

INSTALLS += target install_headers install_prf

QMAKE_EXTRA_TARGETS += check
check.commands = $$system(true)

QMAKE_EXTRA_TARGETS += check-xml
check-xml.commands = $$system(true)

contains(DCP_BUILD_FEATURES,coverage) {
  QMAKE_EXTRA_TARGETS += coverage
  coverage.commands = $$system(true)
}

QMAKE_CLEAN += .objects/.* .objects/*

