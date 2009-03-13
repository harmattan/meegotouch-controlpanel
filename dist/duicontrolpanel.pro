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

# for make deb
include(debian/deb.pri)

# for check:
check.target = check
check.CONFIG = recursive
QMAKE_EXTRA_TARGETS += check


