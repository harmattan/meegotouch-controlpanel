theme.files += theme/*.svg \
		theme/*.conf \
		theme/*.css \
		theme/images/*.svg \
		theme/images/*.png \

theme.path = $${PREFIX}/share/themes/dui/duicontrolpanel
message ("Theme path will be: "$$theme.path)
# message ("Files are: "$$theme.files)
INSTALLS += theme

