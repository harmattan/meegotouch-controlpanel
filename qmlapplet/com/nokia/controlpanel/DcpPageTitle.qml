import QtQuick 1.1
import com.nokia.meego 1.0
import "/usr/lib/qt4/imports/com/meego/UIConstants.js" as UI1


// page's title:
Label {
    text: "Title"
    anchors.topMargin: UI1.HEADER_DEFAULT_TOP_SPACING_PORTRAIT
    anchors.bottomMargin: UI1.HEADER_DEFAULT_BOTTOM_SPACING_PORTRAIT
    height: UI1.HEADER_DEFAULT_HEIGHT_PORTRAIT
    width: parent.width
    verticalAlignment: Text.AlignVCenter

    platformStyle: LabelStyle {
        fontFamily: UI1.FONT_FAMILY_LIGHT
        fontPixelSize: UI1.FONT_XLARGE
    }

    Rectangle {
        height: 1
        width: parent.width
        anchors.bottom: parent.bottom
        color: "#404060" // FIXME
    }
}


