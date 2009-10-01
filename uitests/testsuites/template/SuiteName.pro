include(../../config.pri)
TEMPLATE=subdirs

suites.path=$$TEST_INSTALL_LOCATION/SuiteName
suites.files=ts_suitename.rb \

cases.path=$$TEST_INSTALL_LOCATION/SuiteName/cases
cases.files=cases/tc_suitename.rb \

INSTALLS += \
    cases \
    suites \


include(../check.pri)
