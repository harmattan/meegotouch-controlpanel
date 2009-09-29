VERSION = 0.0.1

QMAKE_STRIP = echo
OBJECTS_DIR = .obj
MOC_DIR = .moc
DESTDIR = ../../lib

CONFIG += qt warn_on depend_includepath
CONFIG += qmake_cache target_qt 

include(mtestapp_targets.pri)
