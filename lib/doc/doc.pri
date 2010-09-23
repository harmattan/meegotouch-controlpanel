
# DOXYGEN_BIN=$$findFile(doxygen)
DOXYGEN_BIN=doxygen

QMAKE_EXTRA_TARGETS += doc
doc.target = doc
isEmpty(DOXYGEN_BIN) {
    doc.commands = @echo "Unable to detect doxygen in PATH"
} else {
    doc.commands = @$${DOXYGEN_BIN} doc/doxygen.cfg  ;
    doc.commands+= ./doc/xmlize.pl ;
}

install_doc.path  += /usr/share/doc/libduicontrolpanel/
install_doc.files += doc/html
install_doc.depends += doc
INSTALLS += install_doc

doc.depends = FORCE

