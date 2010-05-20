TEMPLATE = subdirs

CONFIG += build_all silent warn_on debug

CONFIG += conf

SUBDIRS += binaryapplet
include (declarativeapplet/declarativeapplet.pri)
include (externalapplet/desktop.pri)

