TEMPLATE    = subdirs
                                                                                                                     
contains(DCP_BUILD_FEATURES,coverage) {                                                                               
  SUBDIRS = $$system(ls -1d ut_*/)                                                                                    
} else {                                                                                                              
  SUBDIRS = $$system(ls -1d ut_*/ ft_*/)                                                                              
}

# this is only because the tests shares the compile directory for object and
# moc files, so that the same files does not have to be compiled over and over
# again,
# and it causes problems when two project are building/generating the same file
CONFIG += ordered

QMAKE_STRIP = echo

check.target = check
check.CONFIG = recursive
QMAKE_EXTRA_TARGETS += check

check-xml.target = check-xml
check-xml.CONFIG = recursive
QMAKE_EXTRA_TARGETS += check-xml

contains(DCP_BUILD_FEATURES,coverage) {
  QMAKE_EXTRA_TARGETS += coverage
  coverage.target = coverage
  coverage.CONFIG = recursive
}
OBJECTS_DIR = .tmp
MOC_DIR = .tmp

QMAKE_CLEAN += **/*.log.xml **/*.log

