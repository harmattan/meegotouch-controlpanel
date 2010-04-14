TEMPLATE = subdirs

CONFIG += ordered debug
CONFIG += build_all silent warn_on

SUBDIRS += src tests
include(doc/doc.pri)
include(libconfig.pri)
# for check:
check.target = check
check.CONFIG = recursive
QMAKE_EXTRA_TARGETS += check

check-xml.target = check-xml
check-xml.CONFIG = recursive
QMAKE_EXTRA_TARGETS += check-xml

#coverage.target = coverage
#coverage.depends = clean
#coverage.CONFIG = recursive
#QMAKE_EXTRA_TARGETS += coverage
