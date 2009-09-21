TEMPLATE = subdirs

CONFIG += build_all silent warn_on debug

CONFIG += conf

SUBDIRS += src 

include(debian/deb.pri)
