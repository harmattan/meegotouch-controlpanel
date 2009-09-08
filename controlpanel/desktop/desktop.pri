QMAKE_EXTRA_TARGET += desktop

desktop.files += desktop/*.desktop
desktop.path = $${PREFIX}/lib/duicontrolpanel
message ("Desktop path will be: "$$desktop.path)
# message ("Desktop files are: "$$desktop.files)
INSTALLS += desktop

