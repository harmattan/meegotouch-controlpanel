#!/bin/sh

#echo test suite directory $PWD
for srcfile in "$@"; do
    gcov $srcfile >/dev/null
    base=$(basename $srcfile)
    gcov="$base.gcov"
    covered=$(grep '^ *[0-9]\+:' $gcov | wc -l)
    uncovered=$(grep '^ *#####:' $gcov | wc -l)
    excluded=$(grep '^ *-: *[1-9]' $gcov | wc -l)

    if [ $((covered + uncovered)) -eq 0 ]; then
        echo "$srcfile: generated no code"
        break;
    fi
    cov00=$((covered * 10000 / (covered + uncovered)))
    covint=$((cov00 / 100))
    covfrac=$((cov00 - 100*covint))
    echo "$srcfile: $covint.$covfrac% ($covered covered, $uncovered uncovered, $excluded excluded)"
done
