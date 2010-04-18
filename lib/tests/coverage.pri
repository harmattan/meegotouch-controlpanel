
contains(DCP_BUILD_FEATURES,coverage) {
  QMAKE_CXXFLAGS += --coverage 
  QMAKE_LFLAGS += --coverage

  QMAKE_EXTRA_TARGETS += coverage
  coverage.commands    =    lcov --directory . --zerocounters \
                         && make check \
                         && lcov --base-directory `pwd` --directory . --capture --output-file all.cov \
                         && lcov --extract all.cov \"*src*.cpp\" --output-file selected.cov
}

QMAKE_CLEAN += *.gcda *.gcno *.cov

