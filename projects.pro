TEMPLATE = subdirs

CONFIG += debug ordered
CONFIG += build_all silent warn_on

SUBDIRS += lib \
           controlpanel \
           applets

include(dcpconfig.pri)
include(debian/deb.pri)

check.target = check 
check.CONFIG = recursive
QMAKE_EXTRA_TARGETS += check

check-xml.target = check-xml
check-xml.CONFIG = recursive
QMAKE_EXTRA_TARGETS += check-xml
