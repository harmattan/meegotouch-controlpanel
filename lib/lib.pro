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

contains(DCP_BUILD_FEATURES,coverage) {
  QMAKE_EXTRA_TARGETS += coverage
  coverage.target = coverage
  coverage.CONFIG = recursive
} 
