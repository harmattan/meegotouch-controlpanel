TEMPLATE      = subdirs
CONFIG += ordered

SUBDIRS += buttonapplet \
           src \

check.commands = $$system(true)

QMAKE_EXTRA_TARGETS += check-xml
check-xml.commands = $$system(true)

