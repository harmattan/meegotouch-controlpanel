#QMAKE_EXTRA_TARGETS += coverage-calc
#coverage-calc.depends = check
#coverage-calc.commands = ../coverage-calc.sh $$TEST_SOURCES >>../coverage.out


#QMAKE_EXTRA_TARGETS += coverage
#coverage.depends = clean
#coverage.commands = qmake "CONFIG+=coverage" && make coverage-calc


#QMAKE_CLEAN += \
#    *.gcda \
#    *.gcno \

