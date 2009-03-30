TEMPLATE = subdirs

CONFIG += debug
CONFIG += build_all silent warn_on

SUBDIRS += src

# for check:
check.target = check
check.CONFIG = recursive
QMAKE_EXTRA_TARGETS += check


