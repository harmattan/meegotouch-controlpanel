TEMPLATE      = lib
CONFIG       += plugin gui dui debug
INCLUDEPATH  += $$system(find ./ -type d)
MOC_DIR	      = .moc
OBJECTS_DIR   = .objects
QMAKE_RPATH = -Wl
include(../dcpconfig.pri)

# this has to be above finds, because it generates .h .cpp files
include(service_interface/service_interface.pri)

# Input
HEADERS += $$system(find ./ -name \'*.h\')
SOURCES += $$system(find ./ -name \'*.cpp\' -not -name \'moc_*\')

TARGET        = $$qtLibraryTarget(duicontrolpanel)
DESTDIR       = ../lib

# disable debugging:
# DEFINES += QT_NO_DEBUG_OUTPUT

contains(DEFINES, COVERAGE) {
  message("Coverage options enabled")
  QMAKE_CXXFLAGS += --coverage -fno-elide-constructors -O0
  QMAKE_LFLAGS += --coverage
}

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
    widget/dcpspaceritem.h \
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

QMAKE_EXTRA_TARGETS += coverage
#coverage.depends = clean
coverage.commands = lcov --d .objects --zerocounters && cd ../tests && make check && cd ../src && rm -f .objects/moc_*.gcda .objects/moc_*.gcno && \
                    lcov -b `pwd` -d .objects --capture --output-file app.info && lcov -r app.info \"/targets/*\" --output-file app.info && genhtml -o coverage.html app.info

QMAKE_CLEAN += .objects/.* .objects/* coverage.html/* app.info .moc*.gcov
QMAKE_DISTCLEAN += -r coverage.html/