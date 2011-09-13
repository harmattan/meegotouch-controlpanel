include(../common.pri)

TEMPLATE = subdirs

# the extended example contains c++ which needs to be compiled:
SUBDIRS += extended

# simple and pagestackwindow examples only need an install target
# (nothing to compile):
desktop.files += simple/qmlexample.desktop
desktop.files += pagestackwindow/qmlexample2.desktop
desktop.path = $$DCP_DESKTOP_DIR

qmlexample.files += simple/*.qml
qmlexample.path = /usr/share/duicontrolpanel/qml-example/

qmlexample2.files += pagestackwindow/*.qml
qmlexample2.path = /usr/share/duicontrolpanel/qml-example2/

INSTALLS += qmlexample qmlexample2 desktop

