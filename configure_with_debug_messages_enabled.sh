#! /bin/sh

if [ -f Makefile ]; then
    make distclean
fi
qmake DEFINES+=DEBUG
echo "You can start 'make' now."

