#! /bin/bash

set -e

outputPath="$1"

pos=0
mkdir -p "$outputPath"

widgetType() {
    let wt=$pos%4
    case "$wt" in
        0) echo "Label"; ;;
        1) echo "Image"; ;;
        2) echo "Toggle"; ;;
        3) echo "Slider" ;;
    esac
}

seqStuff() {
    let wt=($pos/$1)%2
    if [ $wt = 1 ]; then
        echo "$2"
    else
        echo
    fi
}

helpId() {
    seqStuff 4 "tips.cfg"
}

text2() {
    seqStuff 8 "This brief has a second line"
}

image() {
    echo "icon-m-bluetooth-device-root"
}

name() {
    {
        widgetType
        seqStuff 8 "+value"
        seqStuff 16 "+horiz"
        seqStuff 4 "+help"
    } | tr -d '\n\r'
}

textOrientation() {
    seqStuff 16 "Horizontal"
}

category() {
    let wt=$pos/8+1
    echo "Category$wt"
    return

    local rand=$RANDOM
    let rand=$rand/8192+1
    echo "Category$rand"
}

genDesktop() {
echo "
[Desktop Entry]
Type=Application
Name=$(name)
Exec=

[DUI]
# this makes dcp believe that there is a binary applet here
X-DUIApplet-Applet=fail

[DCP]
Category=$(category)
Order=$pos
WidgetType=$(widgetType)
HelpId=$(helpId)
Text2=$(text2)
Image=$(image)
HasMainView=1
TextOrientation=$(textOrientation)
"
}

for (( pos=0; pos<32; pos++ )) do
    genDesktop >"$outputPath/bv_example$pos.desktop"
done


