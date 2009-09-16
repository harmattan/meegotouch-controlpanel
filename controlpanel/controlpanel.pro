TEMPLATE = subdirs

CONFIG += debug
CONFIG += build_all silent warn_on

SUBDIRS += src \
#	   tests \
#	   examples

# install targets:
include (common.pri)
include(theme/theme.pri)
include(desktop/desktop.pri)


# for check:

QMAKE_EXTRA_TARGETS += check
check.commands = $$system(true)

QMAKE_EXTRA_TARGETS += check-xml
check-xml.commands = $$system(true)

