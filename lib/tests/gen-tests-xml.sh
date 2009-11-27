#!/bin/bash

UT_TESTCASES=""
FT_TESTCASES=""

for TEST in `ls -d ?t_*`; do
	if [ -x $TEST/$TEST ]; then

TESTCASE_TEMPLATE="<case name=\"$TEST\" description=\"$TEST\" requirement=\"\" timeout=\"60\">
        <step expected_result=\"0\">/usr/lib/libduicontrolpanel-tests/$TEST</step>
      </case>
      "

		if [ -n "`echo $TEST | egrep '^u'`" ]; then
			UT_TESTCASES="${UT_TESTCASES}${TESTCASE_TEMPLATE}"
		else
			FT_TESTCASES="${FT_TESTCASES}${TESTCASE_TEMPLATE}"
		fi
	fi
done

echo "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>
<testdefinition version=\"0.1\">
  <suite name=\"libduicontrolpanel-tests\">"

if [ -n "$UT_TESTCASES" ]; then
    echo "    <set name=\"unit_tests\" description=\"Unit Tests\">
      $UT_TESTCASES

      <environments>
        <scratchbox>false</scratchbox>
        <hardware>true</hardware>    
      </environments> 

    </set>"
fi
if [ -n "$FT_TESTCASES" ]; then
    echo "    <set name=\"functional_tests\" description=\"Functional Tests\">
      $FT_TESTCASES

      <environments>
        <scratchbox>false</scratchbox>
        <hardware>true</hardware>    
      </environments> 

    </set>"
fi
echo "  </suite>
</testdefinition>"

