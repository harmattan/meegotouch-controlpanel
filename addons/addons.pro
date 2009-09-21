TEMPLATE = subdirs

CONFIG += debug
CONFIG += build_all silent warn_on

CONFIG += conf

SUBDIRS += displayapplet \
           datetimeapplet \

include(debian/deb.pri)
