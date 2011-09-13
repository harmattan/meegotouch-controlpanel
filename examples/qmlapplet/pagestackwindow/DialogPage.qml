import QtQuick 1.1
import com.nokia.meego 1.0
import com.nokia.controlpanel 0.1

Page {
    id: root
    tools: tabTools
    anchors.margins: UiConstants.DefaultMargin
    anchors.fill: parent

    QueryDialog {
        id: query

        icon: "image://theme/icon-l-contacts"
        titleText: "Query Dialog Example"
        message: "Press accept or reject button"
        acceptButtonText: "Accept"
        rejectButtonText: "Reject"
        onAccepted: labelQueryResult.text = "Result: Accepted";
        onRejected: labelQueryResult.text = "Result: Rejected";
    }

    SelectionDialog {
        id: singleSelectionDialog

        titleText: "Single Selection Dialog Header"
        selectedIndex: 1

        model: ListModel {
            ListElement { name: "ListElement #1" }
            ListElement { name: "ListElement #2" }
            ListElement { name: "ListElement #3" }
            ListElement { name: "ListElement #4" }
        }
    }

    // Create page and buttons
    ScrollDecorator {
        flickableItem: container
    }

    Flickable {
        id: container

        x: 0 // we need to set the width and height
        y: 0
        width: root.width
        height: root.height
        contentWidth: dialogs.width
        contentHeight: dialogs.height

        flickableDirection: Flickable.VerticalFlick
        pressDelay: 100

        Column {
            id: dialogs
            spacing: 24

            DcpPageTitle {
                text: "Page About Dialogs"
            }

            Row {
                spacing: 32

                Button {
                    text: "Query"
                    width: 200
                    onClicked: {
                        query.open();
                    }
                }

                Label {
                    id: labelQueryResult
                    text: "Result: N/A"
                }
            }

            Row {
                spacing: 32

                Button {
                    text: "SingleSelection"
                    width: 200
                    onClicked: {
                        singleSelectionDialog.open();
                    }
                }


                Grid {
                    rows: screen.orientation == Screen.Landscape || screen.orientation == Screen.LandscapeInverted ? 1 : 2

                    Rectangle {
                        width: 200
                        height: 30
                        color: "white"

                        Text {
                            y: 10
                            anchors.centerIn: parent
                            text: "Selected:"
                            font.pixelSize: 15
                            font.bold: true
                        }
                    }

                    Rectangle {
                        width: 200
                        height: 30
                        color: "lightgray"

                        Text {
                            anchors.centerIn: parent
                            text: singleSelectionDialog.model.get(singleSelectionDialog.selectedIndex).name
                            font.pixelSize: 15
                            font.bold: true
                        }
                    }
                }
            }

            Row {
                spacing: 32

                Button {
                    text: "Color menu"
                    width: 200
                    onClicked: {
                        colorMenu.open();
                    }
                }

                Rectangle {
                    id : colorRect
                    width: 50; height: 50;
                    color : "black"

                    MouseArea {
                        anchors.fill: parent
                        onClicked: { colorMenu.open(); }
                    }
                }
            }
        }
    }    

    DcpToolBar {
        id: tabTools
        viewMenu: colorMenu
    }

    Menu {
        id: colorMenu
        visualParent: pageStack

        MenuLayout {
            MenuItem {text: "Red"; onClicked: { colorRect.color = "darkred" } }
            MenuItem {text: "Green"; onClicked: { colorRect.color = "darkgreen" }}
            MenuItem {text: "Blue"; onClicked: { colorRect.color = "darkblue" }}
            MenuItem {text: "Yellow"; onClicked: { colorRect.color = "yellow" }}
        }
    }
}

