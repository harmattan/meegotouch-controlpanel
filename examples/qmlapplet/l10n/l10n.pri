# generate .qm files:
system ("lrelease -markuntranslated '' -idbased *.ts")

decltranslations.files += l10n/*qm
decltranslations.path = $$DCP_TRANSLATIONS_DIR

desktop.files += l10n/qmll10nexample.desktop

qmlexample4.files += l10n/*.qml
qmlexample4.path = /usr/share/duicontrolpanel/qml-example4/

INSTALLS += decltranslations qmlexample4

