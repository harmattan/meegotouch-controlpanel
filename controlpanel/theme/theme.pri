include(../../lib/dcpconfig.pri)

images.files += theme/images/*
images.path = $$DCP_THEME_DIR/images

style.files += theme/style/*css
style.path = $$DCP_THEME_DIR/style

svg.files += theme/svg/*
svg.path = $$DCP_THEME_DIR/svg

conf.files += theme/mcontrolpanel.conf
conf.path = $$DCP_THEME_DIR

message ("Theme path will be: "$$DCP_THEME_DIR)
INSTALLS += images svg style conf

