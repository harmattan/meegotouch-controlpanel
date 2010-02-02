TEMPLATE    = subdirs
SUBDIRS     = $$system(ls -1d ut_*/)
include(shell.pri)
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
