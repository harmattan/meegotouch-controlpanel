include(../config.pri)
OBJECTS_DIR = .obj
MOC_DIR = .moc
TEMPLATE = app
CONFIG += dui
LIBS += -L../../lib -lmtestapp
INCLUDEPATH += ../mtestapp
target.path=$$APP_INSTALL_LOCATION
INSTALLS += target
QMAKE_LIBDIR += ../../lib 
support_files.files =
support_files.path = $$APP_INSTALL_LOCATION

TEST_THEME_LOCATION = $${TEST_THEME_ROOT_LOCATION}/$${TARGET}/themes
theme_root.files+= $${TARGET}.conf
theme_root.path= $${TEST_THEME_LOCATION}
theme_style.files+= $${TARGET}.css
theme_style.path= $${TEST_THEME_LOCATION}/style
theme_images.path = $$TEST_THEME_LOCATION/images 
theme_images.files = 

INSTALLS += support_files  theme_root theme_style theme_images

QMAKE_EXTRA_TARGETS += check run
run.depends = FORCE
run.commands += LD_LIBRARY_PATH=$$QMAKE_LIBDIR ;
run.commands += ./${TARGET} -software


QMAKE_LIBS -= -Wl,-rpath-link=/usr/lib
QMAKE_LIBS_OPENGL_QT -= -Wl,-rpath-link=/usr/lib
check.depends = $$TARGET
check.commands = @LD_LIBRARY_PATH=../../lib:$$(LD_LIBRARY_PATH) ./$$TARGET
check.commands = $$system(/bin/true)


