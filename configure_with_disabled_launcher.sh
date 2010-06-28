#! /bin/sh

if [ -f Makefile ]; then
    make distclean
fi
qmake CONFIG+=DISABLE_LAUNCHER
echo "You can start 'make' now."

