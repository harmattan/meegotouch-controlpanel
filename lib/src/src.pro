TEMPLATE      = lib
CONFIG       += gui meegotouch debug
INCLUDEPATH  += $$system(find ./ -type d)
MOC_DIR	      = .moc
OBJECTS_DIR   = .objects

include(../dcpconfig.pri)

!meego {
	LIBS += -lsysinfo
}

MOSTUSED {
    DEFINES += MOSTUSED
}
# this has to be above finds, because it generates .h .cpp files
include(service_interface/service_interface.pri)

PERF_MEASUREMENT {
    DEFINES += PERF_MEASUREMENT
}

# Input
HEADERS += $$system(find ./ -name \'*.h\')
SOURCES += $$system(find ./ -name \'*.cpp\' -not -name \'moc_*\')

VERSION       = 0.9.0
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
    appletdb/dcpstylablewidget.h \
    appletdb/dcpappletmetadata.h \
    appletdb/dcpbrief.h \
    appletdb/dcpappletdb.h \
    appletdb/dcpappletplugin.h \
    appletdb/dcpappletobject.h \
    appletdb/dcpappletmetadata.h \
    appletdb/dcpmostusedcounter.h \
    widget/dcpwidgettypes.h \
    widget/dcpcontentbutton.h \
    widget/dcpcontentitem.h \
    dcpdebug.h \
    dcpperflogger.h \
    dcpretranslator.h \
    service_interface/dcpappletlauncherif.h \
    service_interface/dcpappletlauncherifproxy.h \
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

# create pkg-config info:
CONFIG += create_pc create_prl no_install_prl

QMAKE_PKGCONFIG_NAME = meegotouch-controlpanel
QMAKE_PKGCONFIG_DESCRIPTION = MeeGo Control Panel
PKG_CONFIG_PATH = $$[QT_INSTALL_LIBS]/pkgconfig
QMAKE_PKGCONFIG_REQUIRES = meegotouch
QMAKE_PKGCONFIG_LIBDIR = $$target.path
QMAKE_PKGCONFIG_INCDIR = $$install_headers.path
QMAKE_PKGCONFIG_DESTDIR = pkgconfig

pcfilelink.commands += $(SYMLINK) "$$TARGET".pc "$$QMAKE_PKGCONFIG_NAME".pc && mv "$$QMAKE_PKGCONFIG_NAME".pc $(INSTALL_ROOT)/$$[QT_INSTALL_LIBS]/pkgconfig/
pcfilelink.path += $$[QT_INSTALL_LIBS]/pkgconfig

INSTALLS += pcfilelink

DEFINES += QT_USE_FAST_CONCATENATION
DEFINES += QT_USE_FAST_OPERATOR_PLUS


