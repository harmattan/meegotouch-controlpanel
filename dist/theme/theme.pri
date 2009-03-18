theme.files += theme/*.svg \
		theme/*.conf \
		theme/*.css
images.files += theme/images/*.svg \
		theme/images/*.png

theme.path = $${PREFIX}/share/themes/dui/duicontrolpanel
images.path = $${theme.path}/images

message ("Theme path will be: "$$theme.path)
# message ("Files are: "$$theme.files)
INSTALLS += theme images

