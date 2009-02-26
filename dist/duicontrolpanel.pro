TEMPLATE = subdirs

CONFIG += debug
CONFIG += build_all silent warn_on

SUBDIRS += src \
	   tests
#	   examples

# this creates the installation process
# PREFIX = "debian/duicontrolpanel/usr"
PREFIX = $(DEBIAN_DESTDIR)/usr

target.path += $${PREFIX}/bin

# skin.files += themes ??? ...
# skin.path = $${PREFIX}/share/duicontrolpanel

# desktop.files += mediaplayer.desktop
# desktop.path = $${PREFIX}/share/applications/... ???

INSTALLS += target  # skin desktop

# for make deb
include(debian/deb.pri)

# for check:
check.target = check
check.CONFIG = recursive
QMAKE_EXTRA_TARGETS += check


