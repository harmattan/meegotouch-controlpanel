#! /bin/sh

newApplet() {
echo "
[Desktop Entry]
Type=DUIApplet
Name=Test$1

[DUI]
X-DUIApplet-ApplicationCommand=widgetsgallery

[DCP]
Category=Look & Feel
Order=100
" >/usr/lib/duicontrolpanel/test$1.desktop
}

seq 1000 | while read num; do
    newApplet $num
done

