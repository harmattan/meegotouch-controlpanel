PWDPATH=declarativeapplet/localized

# generate .qm files:
system ("lrelease -idbased *.ts")

declxml.files += $$PWDPATH/example2.xml
decldesktop.files += $$PWDPATH/declexample2.desktop

decltranslations.files += $$PWDPATH/*qm
decltranslations.path = $$DCP_TRANSLATIONS_DIR

INSTALLS += decltranslations

