include(../../common.pri)

TEMPLATE      = lib
CONFIG       += qt plugin
QT           += declarative

MOC_DIR	      = .moc
OBJECTS_DIR   = .objects

HEADERS       = *.h
SOURCES       = *.cpp

TARGET        = qmlqtimeexampleplugin
DESTDIR       = com/nokia/TimeExample

desktop.files += qmlexample3.desktop
desktop.path = $$DCP_DESKTOP_DIR

qmlexample3.files += *.qml
qmlexample3.files += com
qmlexample3.path += /usr/share/duicontrolpanel/qml-example3/

INSTALLS += qmlexample3 desktop

