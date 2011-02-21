TEMPLATE = subdirs

CONFIG += ordered debug
CONFIG += silent warn_on

SUBDIRS += src

minimal {
    CONFIG += NOTESTS NODOC
}

! NOTESTS {
    SUBDIRS += tests
}

include (../platform.pri)
include (doc/doc.pri)
include (libconfig.pri)

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

