include(../../lib/dcpconfig.pri)

images.files += theme/images/*
images.path = $$DCP_THEME_DIR/images

style.files += theme/style/*
style.path = $$DCP_THEME_DIR/style

svg.files += theme/svg/*
svg.path = $$DCP_THEME_DIR/svg

message ("Theme path will be: "$$DCP_THEME_DIR)
INSTALLS += images svg style

