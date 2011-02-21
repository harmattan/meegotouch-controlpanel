include(../../lib/dcpconfig.pri)

meego {
    categories.files += categories/meego_variant/*.cpcategory
} else {
    categories.files += categories/harm_variant/*.cpcategory
}
categories.path = $$DCP_CATEGORY_DIR

INSTALLS += categories

