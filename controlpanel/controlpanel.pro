TEMPLATE = subdirs

CONFIG += debug
CONFIG += build_all silent warn_on

CONFIG += conf

SUBDIRS += src \
       translations \
	   tests \
#	   examples

# install targets:
include (common.pri)
include(theme/theme.pri)
include(desktop/desktop.pri)

# for check:

QMAKE_EXTRA_TARGETS += check
check.commands = $$system(true)

QMAKE_EXTRA_TARGETS += check-xml
check-xml.commands = $$system(true)

contains(DEFINES, COVERAGE) {
  message("Coverage options enabled")
  QMAKE_CXXFLAGS += --coverage -fno-elide-constructors -O0
  QMAKE_LFLAGS += --coverage
}

QMAKE_EXTRA_TARGETS += coverage
#coverage.depends = clean
#coverage.commands = echo "iiiiiiittttttttttttttttttt"
coverage.commands =   lcov --d tmp --zerocounters && cd tests && make check && cd ../ && rm -f tmp/moc_*.gcda tmp/moc_*.gcno && lcov -b `pwd` -d tmp --capture --output-file app.info\
                   && lcov -r app.info \"/targets/*\" --output-file app.info && genhtml -o coverage.html app.info

QMAKE_CLEAN += coverage.html/* app.info .moc*.gcov
QMAKE_DISTCLEAN += -r coverage.html/