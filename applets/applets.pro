TEMPLATE = subdirs

CONFIG += debug
CONFIG += build_all silent warn_on

SUBDIRS += displayapplet \
           datetimeapplet \

include(debian/deb.pri)
