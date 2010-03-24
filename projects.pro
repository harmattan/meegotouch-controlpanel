TEMPLATE = subdirs

CONFIG += debug ordered
CONFIG += build_all silent warn_on

SUBDIRS += lib \
           controlpanel \
           declapplet

include(debian/deb.pri)
include(gentests/gentests.pri)

# for check:
check.target = check
check.CONFIG = recursive
QMAKE_EXTRA_TARGETS += check

check-xml.target = check-xml
check-xml.CONFIG = recursive
QMAKE_EXTRA_TARGETS += check-xml


QMAKE_EXTRA_TARGETS += coverage
coverage.depends = lib/Makefile
coverage.commands = cd lib && make coverage
# dont want to make it CONFIG = recursive because other subdirs would need
# a stub rule for this target

