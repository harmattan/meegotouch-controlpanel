TEMPLATE = subdirs

CONFIG += build_all silent warn_on debug

CONFIG += conf

SUBDIRS += binaryapplet
SUBDIRS += qmlapplet
include (declarativeapplet/declarativeapplet.pri)
include (briefviews/briefviews.pri)
include (externalapplet/desktop.pri)

