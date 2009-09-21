include(../../lib/dcpconfig.pri)
QMAKE_EXTRA_TARGET += desktop

desktop.files += desktop/*.desktop
desktop.path = $$DCP_DESKTOP_DIR
message ("Desktop path will be: "$$desktop.path)
# message ("Desktop files are: "$$desktop.files)
INSTALLS += desktop

