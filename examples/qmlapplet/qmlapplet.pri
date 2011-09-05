desktop.files += qmlapplet/pagestackwindow/qmlexample2.desktop
desktop.files += qmlapplet/simple/qmlexample.desktop

qmlexample.files += qmlapplet/simple/*.qml
qmlexample.path = /usr/share/duicontrolpanel/qml-example/

qmlexample2.files += qmlapplet/pagestackwindow/*.qml
qmlexample2.path = /usr/share/duicontrolpanel/qml-example2/

INSTALLS += qmlexample qmlexample2

