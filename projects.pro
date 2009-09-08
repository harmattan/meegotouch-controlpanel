TEMPLATE = subdirs

CONFIG += debug ordered
CONFIG += build_all silent warn_on

SUBDIRS += lib \
           controlpanel \
           applets

include(debian/deb.pri)

