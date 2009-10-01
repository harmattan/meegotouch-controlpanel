CONFIG+=ordered
TEMPLATE = subdirs

TESTAPPS+=  \
        ta_dcpbutton2 \

SUBDIRS += \
        $$TESTAPPS


check.target = check
check.CONFIG = recursive
QMAKE_EXTRA_TARGETS += check

