themedir = $${PREFIX}/share/duicontrolpanel/themes

images.files += theme/images/*
images.path = $$themedir/images

style.files += theme/style/*
style.path = $$themedir/style

svg.files += theme/svg/*
svg.path = $$themedir/svg

message ("Theme path will be: "$$themedir)
INSTALLS += images svg style

