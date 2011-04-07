include(common.pri)

system (./genDesktops.sh desktops)

bvdesktops.files += briefviews/desktops/*.desktop
bvdesktops.path = $$DCP_DESKTOP_DIR

bvcategories.files += briefviews/categories/*.cpcategory
bvcategories.path += $$DCP_CATEGORY_DIR/examples

INSTALLS += bvcategories bvdesktops

