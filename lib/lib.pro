TEMPLATE = subdirs

CONFIG += ordered debug
CONFIG += build_all silent warn_on

SUBDIRS += src tests
include(doc/doc.pri)
# for check:
check.target = check
check.CONFIG = recursive
QMAKE_EXTRA_TARGETS += check

