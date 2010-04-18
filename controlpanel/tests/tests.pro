TEMPLATE    = subdirs
SUBDIRS     = \
              ut_dcpappletbuttons \
              ut_dcppage \
              ut_pagefactory \
              ut_pages \
              ut_dcpbriefcomponent \
              ut_dcpsinglecomponent \
              ut_dcpmaincategory \
              ut_dcpmainpage \

QMAKE_STRIP = echo

check.target = check
check.CONFIG = recursive
QMAKE_EXTRA_TARGETS += check


check-xml.target = check-xml
check-xml.CONFIG = recursive
QMAKE_EXTRA_TARGETS += check-xml

coverage.target = coverage
coverage.depends = clean
coverage.CONFIG = recursive
QMAKE_EXTRA_TARGETS += coverage

QMAKE_CLEAN += **/*.log.xml **/*.log coverage.out


