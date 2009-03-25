TEMPLATE = subdirs

CONFIG += debug
CONFIG += build_all silent warn_on

SUBDIRS += displayapplet \
           languageapplet

include(debian/deb.pri)
