TEMPLATE = subdirs

CONFIG += debug
CONFIG += build_all silent warn_on

CONFIG += conf

SUBDIRS += src \

minimal {
    CONFIG += NOTESTS
} else {
    SUBDIRS += translations
}

!NOTESTS {
    SUBDIRS += tests
}

# install targets:

config.files = duicontrolpanel.conf
config.path = /etc
INSTALLS += config

include (common.pri)
include (../platform.pri)
include(theme/theme.pri)
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

