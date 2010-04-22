TEMPLATE    = subdirs

SUBDIRS     = \
              ut_dcpappletbuttons \
              ut_dcppage \
              ut_pagefactory \
              ut_pages \
#              ut_dcpbriefcomponent \
              ut_dcpsinglecomponent \
              ut_dcpmaincategory \
#              ut_dcpmainpage \
              ut_dcpcategorycomponent \
              ft_dcpcomponent \
              ft_dcpbriefcomponent \
              ft_dcpsinglecomponent \

QMAKE_STRIP = echo

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

QMAKE_CLEAN += **/*.log.xml **/*.log

