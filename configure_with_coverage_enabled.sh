#! /bin/sh

LCOV=`which lcov`

if test "x$LCOV" = x; then
    echo "You need to install lcov to get actual reports!";
    echo "See http://ltp.sf.net/coverage/lcov.php";
    echo "!!! ATTENTION !!!"
    echo "The current lcov-1.8 contains some silly bug.";
    echo "Please, use a newer one or the cvs version."
    exit 1;
fi

if test "x$SBOX_USE_CCACHE" = xyes; then
    echo "Please set SBOX_USE_CCACHE=no to use coverage.";
    echo "For example : 'export SBOX_USE_CCACHE=no'";
    exit 1;
fi

if [ -f Makefile ]; then
    make distclean
fi

qmake DCP_BUILD_FEATURES=coverage

echo
echo "You can start 'make' now.";
echo "After compilation use 'make coverage'";
echo "Results :";
echo "           ./coverage/index.html";
echo
