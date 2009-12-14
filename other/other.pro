TEMPLATE = subdirs

CONFIG += debug
CONFIG += build_all silent

SUBDIRS += \
    badapplets \
    dcp_service_tester \
    declarative \

# for check:
check.target = check
check.CONFIG = recursive
QMAKE_EXTRA_TARGETS += check

check-xml.target = check-xml
check-xml.CONFIG = recursive
QMAKE_EXTRA_TARGETS += check-xml

