TEMPLATE = app
TARGET = decltester
DEPENDPATH += .
INCLUDEPATH += $$DEPENDPATH
OBJECTS_DIR = tmp
MOC_DIR = tmp

# Input
HEADERS += $$system(find ./ -name \'*.h\')
SOURCES += $$system(find ./ -name \'*.cpp\')

CONFIG += dui build_all warn_on debug
QT += xml

