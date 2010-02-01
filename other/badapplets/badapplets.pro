TEMPLATE = subdirs

CONFIG += debug
CONFIG += build_all silent warn_on

SUBDIRS += badapplet1 \
           badapplet2 \
           badapplet3 \

# for check:
check.target = check
check.CONFIG = recursive
QMAKE_EXTRA_TARGETS += check

check-xml.target = check-xml
check-xml.CONFIG = recursive
QMAKE_EXTRA_TARGETS += check-xml
