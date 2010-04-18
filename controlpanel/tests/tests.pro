TEMPLATE    = subdirs

contains(DCP_BUILD_FEATURES,coverage) {
  SUBDIRS = $$system(ls -1d ut_*/)
} else {
  SUBDIRS = $$system(ls -1d ut_*/ ft_*/)
}

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
