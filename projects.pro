TEMPLATE = subdirs

CONFIG += debug ordered
CONFIG += build_all silent warn_on

SUBDIRS += lib \
           controlpanel \
           declapplet

include(debian/deb.pri)
include(gentests/gentests.pri)

# for check:
check.target = check
check.CONFIG = recursive
QMAKE_EXTRA_TARGETS += check

check-xml.target = check-xml
check-xml.CONFIG = recursive
QMAKE_EXTRA_TARGETS += check-xml

contains(DCP_BUILD_FEATURES,coverage) {
  QMAKE_EXTRA_TARGETS += coverage
  coverage.depends = lib/src/Makefile controlpanel/src/Makefile
  #coverage.commands = cd lib && make coverage && cd ../../controlpanel/src && make coverage
  coverage.commands =      cd lib && make coverage && cd .. \
                        && genhtml -o coverage/ lib/tests/ut*/selected.cov

  QMAKE_DISTCLEAN += -r coverage/*
}

