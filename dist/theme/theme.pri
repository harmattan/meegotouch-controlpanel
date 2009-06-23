# themedir = $${PREFIX}/share/duicontrolpanel/themes

# images.files += theme/images/*
# images.path = $$themedir/images

# style.files += theme/style/*
# style.path = $$themedir/style

# svg.files += theme/svg/*
# svg.path = $$themedir/svg

# message ("Theme path will be: "$$themedir)
# INSTALLS += images svg style

# -- backport starts for dui 0.7.5:
theme.files += theme/style/* \
               theme/svg/*
theme.path = $${PREFIX}/share/themes/dui/duicontrolpanel

images.files += theme/images/*
images.path += $${PREFIX}/share/themes/dui/duicontrolpanel/images

INSTALLS += theme images
# -- backport ends

