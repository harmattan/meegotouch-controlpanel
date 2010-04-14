#! /bin/sh

LCOV=`which lcov`

if test "x$LCOV" = x; then
    echo "You need to install lcov to get actual reports!"
    echo "See http://ltp.sf.net/coverage/lcov.php"
    exit 1;
fi

if test "x$SBOX_USE_CCACHE" = xyes; then
    echo "Please set SBOX_USE_CCACHE=no to use coverage";
    echo "for example : \$export SBOX_USE_CCACHE=no";
    exit 1;
fi

if [ -f Makefile ]; then
    make distclean
fi

qmake DEFINES+=COVERAGE
echo "You can start 'make' now."

