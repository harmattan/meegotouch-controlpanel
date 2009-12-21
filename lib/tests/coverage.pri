QMAKE_EXTRA_TARGETS += coverage
coverage.depends = check
coverage.commands = @../coverage-calc.sh $$TEST_SOURCES
