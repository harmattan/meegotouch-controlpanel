TEMPLATE = subdirs

CONFIG += debug
CONFIG += build_all silent warn_on

SUBDIRS += displayapplet \
           datetimeapplet \
           languageapplet

include(debian/deb.pri)
