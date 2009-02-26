TEMPLATE = subdirs

SUBDIRS += $$system(ls -1d ut_*)

check.target = check
check.CONFIG = recursive
QMAKE_EXTRA_TARGETS += check

CONFIG += silent

