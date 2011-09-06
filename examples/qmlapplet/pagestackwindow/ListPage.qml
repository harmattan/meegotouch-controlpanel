import QtQuick 1.1
import com.nokia.meego 1.0
import com.nokia.extras 1.1
import "/usr/lib/qt4/imports/com/meego/UIConstants.js" as UI1
import "/usr/lib/qt4/imports/com/meego/extras/constants.js" as UI2

Page {
    id: listPage
    anchors.margins: UiConstants.DefaultMargin

// unfortunately this does not work, so doing the rotation instead for the Window
//    orientationLock: PageOrientation.LockPortrait

    tools: commonTools

    function openFile(file) {
        var component = Qt.createComponent(file)

        if (component.status == Component.Ready)
            pageStack.push(component);
        else
            console.log("Error loading component:", component.errorString());
    }

Flickable {
    id: flickable
    anchors.fill: parent
    flickableDirection: Flickable.VerticalFlick

    // page's title:
    Label {
        id: titleLabel
        text: "Qml Window Example " + pageStack.depth
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
            id: titleSeparator
            height: 1
            width: parent.width
            anchors.bottom: parent.bottom
            color: "#404060" // FIXME
        }
    }

    ListView {
        id: listView
        anchors.top: titleLabel.bottom
        anchors.left: titleLabel.left
        anchors.topMargin: UI1.MARGIN_XLARGE

        width: parent.width
        model: pagesModel
        height: pagesModel.count * UI2.LIST_ITEM_HEIGHT
        interactive: false

        delegate:  ListDelegate {
            Image {
                source: "image://theme/icon-m-common-drilldown-arrow-inverse"
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
            }

            onClicked: { listPage.openFile(page) }
        }
    }

    contentHeight: listView.height + titleLabel.height
}

    ListModel {
        id: pagesModel
        ListElement {
            page: "ListPage.qml"
            title: "This page"
            subtitle: "open this page again"
        }
        ListElement {
            page: "DialogPage.qml"
            title: "Dialog"
            subtitle: "open a dialog"
        }
        ListElement {
            page: "SheetPage.qml"
            title: "Sheet"
            subtitle: "open a sheet"
        }
        ListElement {
            page: "1.qml"
            title: "example button 2"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 3"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 4"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 5"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 6"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 7"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 8"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 9"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 10"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 11"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 12"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 13"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 14"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 15"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 16"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 17"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 18"
            subtitle: "no subtitle"
        }
    }

    ScrollDecorator {
        flickableItem: flickable
    }
}


