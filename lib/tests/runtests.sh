#!/bin/sh

export DISPLAY=:0

TESTSDIR=/usr/lib/libduicontrolpanel-tests
OUTDIR=/tmp/libduicontrolpanel-tests

mkdir -p ${OUTDIR}

EXIT_CODE=0
for TEST in `ls ${TESTSDIR}/ut_*`; do
	$TEST -xml -o "${OUTDIR}/$(basename $TEST)".xml
	if [ $? -ne 0 ]; then
		EXIT_CODE=$((EXIT_CODE+1))
	fi
done
exit $EXIT_CODE
