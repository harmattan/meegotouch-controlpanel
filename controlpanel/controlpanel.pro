TEMPLATE = subdirs

CONFIG += debug
CONFIG += build_all silent warn_on

CONFIG += conf

SUBDIRS += src \

!minimal {
       SUBDIRS += translations \
                  tests
}

# install targets:
include (common.pri)
include(theme/theme.pri)
include(desktop/desktop.pri)
include (categories/categories.pri)

# for check:

QMAKE_EXTRA_TARGETS += check
check.target = check
check.CONFIG = recursive

QMAKE_EXTRA_TARGETS += check-xml
check-xml.target = check-xml
check-xml.CONFIG = recursive

contains(DCP_BUILD_FEATURES,coverage) {
  QMAKE_EXTRA_TARGETS += coverage
  coverage.target = coverage
  coverage.CONFIG = recursive
}

