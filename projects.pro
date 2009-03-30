TEMPLATE = subdirs

CONFIG += debug
CONFIG += build_all silent warn_on

SUBDIRS += lib \
           dist \
           addons

include(debian/deb.pri)
