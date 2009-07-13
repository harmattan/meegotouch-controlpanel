TEMPLATE = subdirs

CONFIG += build_all silent warn_on debug

SUBDIRS += src 

include(debian/deb.pri)
