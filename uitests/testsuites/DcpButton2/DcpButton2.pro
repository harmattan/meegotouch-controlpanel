include(../../config.pri)
TEMPLATE=subdirs

suites.path=$$TEST_INSTALL_LOCATION/DcpButton2
suites.files=ts_dcpbutton2.rb \

cases.path=$$TEST_INSTALL_LOCATION/DcpButton2/cases
cases.files=cases/tc_dcpbutton2.rb \

INSTALLS += \
    cases \
    suites \


include(../check.pri)
