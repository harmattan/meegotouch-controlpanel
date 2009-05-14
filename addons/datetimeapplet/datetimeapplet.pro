TEMPLATE = subdirs

CONFIG += debug
CONFIG += build_all silent warn_on

SUBDIRS += src 

include(debian/deb.pri)
