include(../config.pri)
TEMPLATE=subdirs


TESTSUITES += \
    DcpButton2 

SUBDIRS += \
    $$TESTSUITES \


meta.commands=$$system(touch tests.xml)
meta.files=tests.xml
meta.path=$$TEST_INSTALL_LOCATION

unix{
  QMAKE_DEL_FILE = rm -rf 
}
QMAKE_CLEAN += .ri tests.xml
QMAKE_EXTRA_TARGETS += doc test_xml ridoc
doc.commands = rdoc -d -x ts_*.rb -I png -o ./doc

ridoc.target=./.ri/created.rid
ridoc.commands=rdoc -r --op .ri

test_xml.PRE_TARGETDEPS=./.ri/created.rid
test_xml.target=tests.xml
test_xml.commands=/usr/bin/buildTestXml.rb -sMATTI-duicontrolpanel -pmatti -i $$TEST_INSTALL_LOCATION -f \"$$TESTSUITES\"
test_xml.depends=ridoc
test_xml.path=$$TEST_INSTALL_LOCATION

meta.depends=test_xml
meta.files=tests.xml
meta.path=$$TEST_INSTALL_LOCATION


QMAKE_EXTRA_TARGETS+=testcheck
testcheck.depends=test_xml
testcheck.commands=@xmllint --noout --schema testdefinition.xsd tests.xml


INSTALLS+=meta test_xml 

include(../check.pri)
